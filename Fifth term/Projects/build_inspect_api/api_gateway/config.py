import os

USERS_SERVICE_URL = os.getenv("USERS_SERVICE_URL", "http://service_users:8000")
ORDERS_SERVICE_URL = os.getenv("ORDERS_SERVICE_URL", "http://service_orders:8000")
SECRET_KEY = os.getenv("SECRET_KEY", "supersecret")
ALGORITHM = "HS256"
