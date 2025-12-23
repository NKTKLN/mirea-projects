import pytest
from httpx import AsyncClient, ASGITransport
from main import app
from uuid import uuid4
from data import orders
from datetime import datetime

@pytest.mark.anyio
async def test_create_order_success():
    transport = ASGITransport(app=app)
    payload = {
        "items": [{"product": "item1", "quantity": 2}],
        "total": 100.0
    }
    headers = {"X-User-ID": "user123"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.post("/v1/orders", json=payload, headers=headers)
        assert response.status_code == 200
        data = response.json()
        assert data["success"] is True
        assert data["data"]["user_id"] == "user123"
        assert data["data"]["total"] == 100.0

@pytest.mark.anyio
async def test_create_order_missing_user_id():
    transport = ASGITransport(app=app)
    payload = {
        "items": [{"product": "item1", "quantity": 2}],
        "total": 100.0
    }

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.post("/v1/orders", json=payload)
        assert response.status_code == 401
        assert response.json()["detail"]["code"] == "UNAUTHORIZED"

@pytest.mark.anyio
async def test_get_order_success():
    transport = ASGITransport(app=app)

    order_id = str(uuid4())
    orders.append({
        "id": order_id,
        "user_id": "user123",
        "items": [{"product": "item1", "quantity": 2}],
        "status": "created",
        "total": 100.0,
        "created_at": datetime.now(),
        "updated_at": datetime.now(),
    })

    headers = {"X-User-ID": "user123"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.get(f"/v1/orders/{order_id}", headers=headers)
        assert response.status_code == 200
        data = response.json()
        assert data["data"]["id"] == order_id

@pytest.mark.anyio
async def test_get_order_forbidden():
    transport = ASGITransport(app=app)

    order_id = str(uuid4())
    orders.append({
        "id": order_id,
        "user_id": "user123",
        "items": [{"product": "item1", "quantity": 2}],
        "status": "created",
        "total": 100.0,
        "created_at": datetime.now(),
        "updated_at": datetime.now(),
    })

    headers = {"X-User-ID": "other_user"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.get(f"/v1/orders/{order_id}", headers=headers)
        assert response.status_code == 403
        assert response.json()["detail"]["code"] == "FORBIDDEN"

@pytest.mark.anyio
async def test_list_orders_for_user():
    transport = ASGITransport(app=app)
    headers = {"X-User-ID": "user123"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.get("/v1/orders", headers=headers)
        assert response.status_code == 200
        data = response.json()
        for o in data["data"]:
            assert o["user_id"] == "user123"

@pytest.mark.anyio
async def test_update_status_success():
    transport = ASGITransport(app=app)

    order_id = str(uuid4())
    orders.append({
        "id": order_id,
        "user_id": "user123",
        "items": [{"product": "item1", "quantity": 2}],
        "status": "created",
        "total": 100.0,
        "created_at": datetime.now(),
        "updated_at": datetime.now(),
    })

    headers = {"X-User-ID": "user123"}
    payload = {"status": "done"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.patch(f"/v1/orders/{order_id}/status", json=payload, headers=headers)
        assert response.status_code == 200
        data = response.json()
        assert data["data"]["status"] == "done"

@pytest.mark.anyio
async def test_cancel_order_success():
    transport = ASGITransport(app=app)

    order_id = str(uuid4())
    orders.append({
        "id": order_id,
        "user_id": "user123",
        "items": [{"product": "item1", "quantity": 2}],
        "status": "created",
        "total": 100.0,
        "created_at": datetime.now(),
        "updated_at": datetime.now(),
    })

    headers = {"X-User-ID": "user123"}

    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.delete(f"/v1/orders/{order_id}", headers=headers)
        assert response.status_code == 200
        data = response.json()
        assert data["data"]["status"] == "cancelled"
