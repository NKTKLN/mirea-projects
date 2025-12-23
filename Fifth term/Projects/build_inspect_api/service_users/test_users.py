import pytest
from httpx import AsyncClient
from httpx._transports.asgi import ASGITransport
from datetime import datetime
from uuid import uuid4

from main import app, users
from config import SECRET_KEY, ALGORITHM
from utils import hash_password

from jose import jwt

@pytest.mark.anyio
async def test_register_user_success():
    users.clear()
    payload = {"email": "test@example.com", "password": "password123", "name": "Test User"}
    transport = ASGITransport(app=app)
    
    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.post("/v1/users/register", json=payload)
    
    assert response.status_code == 200
    data = response.json()["data"]
    assert data["email"] == "test@example.com"
    assert "id" in data
    assert len(users) == 1

@pytest.mark.anyio
async def test_register_user_conflict():
    users.clear()
    user = {"id": str(uuid4()), "email": "test@example.com", "password_hash": hash_password("pass"), "name": "Test", "roles": ["user"], "created_at": datetime.now(), "updated_at": datetime.now()}
    users.append(user)

    transport = ASGITransport(app=app)
    payload = {"email": "test@example.com", "password": "password123", "name": "Test User"}
    
    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.post("/v1/users/register", json=payload)

    assert response.status_code == 409
    assert response.json()["detail"]["code"] == "USER_EXISTS"

@pytest.mark.anyio
async def test_login_user_success():
    users.clear()
    password = "password123"
    hashed = hash_password(password)
    user = {"id": str(uuid4()), "email": "login@example.com", "password_hash": hashed, "name": "Login User", "roles": ["user"], "created_at": datetime.now(), "updated_at": datetime.now()}
    users.append(user)

    transport = ASGITransport(app=app)
    payload = {"email": "login@example.com", "password": password}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.post("/v1/users/login", json=payload)

    assert response.status_code == 200
    token = response.json()["data"]["access_token"]
    decoded = jwt.decode(token, SECRET_KEY, algorithms=[ALGORITHM])
    assert decoded["sub"] == user["id"]

@pytest.mark.anyio
async def test_login_user_invalid():
    users.clear()
    transport = ASGITransport(app=app)
    payload = {"email": "notfound@example.com", "password": "wrongpass"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.post("/v1/users/login", json=payload)

    assert response.status_code == 401
    assert response.json()["detail"]["code"] == "INVALID_CREDENTIALS"

@pytest.mark.anyio
async def test_get_profile_success():
    users.clear()
    user = {"id": str(uuid4()), "email": "profile@example.com", "password_hash": hash_password("pass"), "name": "Profile User", "roles": ["user"], "created_at": datetime.now(), "updated_at": datetime.now()}
    users.append(user)

    transport = ASGITransport(app=app)
    headers = {"X-User-ID": user["id"]}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.get("/v1/users/me", headers=headers)

    assert response.status_code == 200
    assert response.json()["data"]["email"] == "profile@example.com"

@pytest.mark.anyio
async def test_update_profile_success():
    users.clear()
    user = {"id": str(uuid4()), "email": "update@example.com", "password_hash": hash_password("pass"), "name": "Old Name", "roles": ["user"], "created_at": datetime.now(), "updated_at": datetime.now()}
    users.append(user)

    transport = ASGITransport(app=app)
    headers = {"X-User-ID": user["id"]}
    payload = {"name": "New Name"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.put("/v1/users/me", headers=headers, json=payload)

    assert response.status_code == 200
    assert response.json()["data"]["name"] == "New Name"

@pytest.mark.anyio
async def test_list_users_admin_only():
    users.clear()
    user1 = {"id": str(uuid4()), "email": "user1@example.com", "password_hash": hash_password("pass"), "name": "User1", "roles": ["user"], "created_at": datetime.now(), "updated_at": datetime.now()}
    user2 = {"id": str(uuid4()), "email": "user2@example.com", "password_hash": hash_password("pass"), "name": "User2", "roles": ["user"], "created_at": datetime.now(), "updated_at": datetime.now()}
    users.extend([user1, user2])

    transport = ASGITransport(app=app)
    headers = {"X-User-Roles": "admin"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.get("/v1/users", headers=headers)

    assert response.status_code == 200
    assert len(response.json()["data"]) == 2

@pytest.mark.anyio
async def test_list_users_forbidden():
    users.clear()
    transport = ASGITransport(app=app)
    headers = {"X-User-Roles": "user"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.get("/v1/users", headers=headers)

    assert response.status_code == 403
    assert response.json()["detail"]["code"] == "FORBIDDEN"
