from fastapi import FastAPI, HTTPException, Request, Query
from pydantic import BaseModel, Field
from uuid import uuid4
from datetime import datetime
from typing import List, Optional

from models import *
from utils import *

app = FastAPI(title="Orders Service")

@app.post("/v1/orders")
def create_order(request: Request, data: OrderCreate):
    user_id = request.headers.get("X-User-ID")
    if not user_id:
        raise HTTPException(status_code=401, detail={"code": "UNAUTHORIZED", "message": "Missing X-User-ID header"})

    order = {
        "id": str(uuid4()),
        "user_id": user_id,
        "items": [item.model_dump() for item in data.items],
        "status": "created",
        "total": data.total,
        "created_at": datetime.now(),
        "updated_at": datetime.now(),
    }
    orders.append(order)
    return {"success": True, "data": order}

@app.get("/v1/orders/{order_id}")
def get_order(request: Request, order_id: str):
    user_id = request.headers.get("X-User-ID")
    roles = request.headers.get("X-User-Roles", "")
    order = find_order_by_id(order_id)

    if not order:
        raise HTTPException(status_code=404, detail={"code": "ORDER_NOT_FOUND", "message": "Order not found"})

    if order["user_id"] != user_id and "admin" not in roles:
        raise HTTPException(status_code=403, detail={"code": "FORBIDDEN", "message": "Access denied"})

    return {"success": True, "data": order}

@app.get("/v1/orders")
def list_orders(request: Request, skip: int = 0, limit: int = 10, sort_by: Optional[str] = Query("created_at")):
    user_id = request.headers.get("X-User-ID")
    roles = request.headers.get("X-User-Roles", "")

    if not user_id:
        raise HTTPException(status_code=401, detail={"code": "UNAUTHORIZED", "message": "Missing X-User-ID header"})

    if "admin" in roles:
        filtered = orders
    else:
        filtered = filter_orders_by_user(user_id)

    sorted_orders = sorted(filtered, key=lambda x: x.get(sort_by, ""), reverse=True)
    paginated = sorted_orders[skip: skip + limit]

    return {"success": True, "data": paginated, "meta": {"total": len(filtered), "skip": skip, "limit": limit}}

@app.patch("/v1/orders/{order_id}/status")
def update_status(request: Request, order_id: str, data: OrderUpdateStatus):
    user_id = request.headers.get("X-User-ID")
    roles = request.headers.get("X-User-Roles", "")

    order = find_order_by_id(order_id)
    if not order:
        raise HTTPException(status_code=404, detail={"code": "ORDER_NOT_FOUND", "message": "Order not found"})

    if order["user_id"] != user_id and "admin" not in roles:
        raise HTTPException(status_code=403, detail={"code": "FORBIDDEN", "message": "Not your order"})

    order["status"] = data.status
    order["updated_at"] = datetime.now()
    return {"success": True, "data": order}

@app.delete("/v1/orders/{order_id}")
def cancel_order(request: Request, order_id: str):
    user_id = request.headers.get("X-User-ID")
    roles = request.headers.get("X-User-Roles", "")

    order = find_order_by_id(order_id)
    if not order:
        raise HTTPException(status_code=404, detail={"code": "ORDER_NOT_FOUND", "message": "Order not found"})

    if order["user_id"] != user_id and "admin" not in roles:
        raise HTTPException(status_code=403, detail={"code": "FORBIDDEN", "message": "Access denied"})

    order["status"] = "cancelled"
    order["updated_at"] = datetime.now()
    return {"success": True, "data": order}
