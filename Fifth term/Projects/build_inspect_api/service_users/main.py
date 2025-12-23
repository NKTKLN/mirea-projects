from fastapi import FastAPI, HTTPException, Request
from datetime import datetime
from uuid import uuid4

from config import *
from models import *
from utils import *
from data import users

app = FastAPI(title="User Service")

@app.post("/v1/users/register")
def register_user(data: UserRegister):
    existing = find_user_by_email(data.email)
    if existing:
        raise HTTPException(status_code=409, detail={"code": "USER_EXISTS", "message": "Email already registered"})

    user = {
        "id": str(uuid4()),
        "email": data.email,
        "password_hash": hash_password(data.password),
        "name": data.name,
        "roles": ["user"],
        "created_at": datetime.now(),
        "updated_at": datetime.now()
    }
    users.append(user)
    return {"success": True, "data": {"id": user["id"], "email": user["email"]}}

@app.post("/v1/users/login")
def login_user(data: UserLogin):
    user = find_user_by_email(data.email)
    if not user or user["password_hash"] != hash_password(data.password):
        raise HTTPException(status_code=401, detail={"code": "INVALID_CREDENTIALS", "message": "Invalid email or password"})

    token = create_access_token(user["id"], user["email"], user["roles"])
    return {"success": True, "data": {"access_token": token, "token_type": "bearer"}}

@app.get("/v1/users/me")
def get_profile(request: Request):
    user_id = request.headers.get("X-User-ID")
    if not user_id:
        raise HTTPException(status_code=401, detail={"code": "NO_USER", "message": "Unauthorized"})

    user = find_user_by_id(user_id)
    if not user:
        raise HTTPException(status_code=404, detail={"code": "USER_NOT_FOUND", "message": "User not found"})

    return {"success": True, "data": user}

@app.put("/v1/users/me")
def update_profile(request: Request, update: dict):
    user_id = request.headers.get("X-User-ID")
    if not user_id:
        raise HTTPException(status_code=401, detail={"code": "NO_USER", "message": "Unauthorized"})

    user = find_user_by_id(user_id)
    if not user:
        raise HTTPException(status_code=404, detail={"code": "USER_NOT_FOUND", "message": "User not found"})

    if "name" in update:
        user["name"] = update["name"]
    user["updated_at"] = datetime.now()

    return {"success": True, "data": user}

@app.get("/v1/users")
def list_users(request: Request, skip: int = 0, limit: int = 10):
    roles_header = request.headers.get("X-User-Roles", "")
    if "admin" not in roles_header:
        raise HTTPException(status_code=403, detail={"code": "FORBIDDEN", "message": "Admin only"})

    result = users[skip: skip + limit]
    return {"success": True, "data": result}
