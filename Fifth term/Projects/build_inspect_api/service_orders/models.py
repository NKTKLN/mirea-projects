from fastapi import FastAPI, HTTPException, Request, Query
from pydantic import BaseModel, Field
from uuid import uuid4
from datetime import datetime
from typing import List, Optional

class OrderItem(BaseModel):
    product: str
    quantity: int = Field(gt=0)

class OrderCreate(BaseModel):
    items: List[OrderItem]
    total: float = Field(gt=0)

class OrderUpdateStatus(BaseModel):
    status: str = Field(..., pattern="^(created|in_progress|done|cancelled)$")

class Order(BaseModel):
    id: str
    user_id: str
    items: List[OrderItem]
    status: str
    total: float
    created_at: datetime
    updated_at: datetime