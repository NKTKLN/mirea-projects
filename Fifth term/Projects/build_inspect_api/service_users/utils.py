from jose import jwt
from datetime import datetime, timedelta
import hashlib

from config import *
from data import users


def hash_password(password: str) -> str:
    return hashlib.sha256(password.encode()).hexdigest()

def create_access_token(user_id: str, email: str, roles: list[str]):
    payload = {
        "sub": user_id,
        "email": email,
        "roles": roles,
        "exp": datetime.now() + timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)
    }
    return jwt.encode(payload, SECRET_KEY, algorithm=ALGORITHM)

def find_user_by_email(email: str):
    return next((u for u in users if u["email"] == email), None)

def find_user_by_id(user_id: str):
    return next((u for u in users if u["id"] == user_id), None)
