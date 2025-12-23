from fastapi import FastAPI, Request, Response
from fastapi.middleware.cors import CORSMiddleware
from jose import jwt, JWTError
import httpx
import uuid
import logging
import time
from starlette.responses import JSONResponse
from fastapi.exceptions import RequestValidationError

from config import *

app = FastAPI(title="API Gateway", version="1.0")

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
)
logger = logging.getLogger("gateway")


app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.middleware("http")
async def add_request_id_and_log(request: Request, call_next):
    request_id = request.headers.get("X-Request-ID", str(uuid.uuid4()))
    request.state.request_id = request_id
    start_time = time.time()

    logger.info(f"{request.method} {request.url.path} started (Request-ID: {request_id})")

    try:
        response = await call_next(request)
    except Exception as e:
        logger.error(f"Internal error during {request.method} {request.url.path}: {e}")
        return JSONResponse(
            status_code=500,
            content={"success": False, "error": {"code": "INTERNAL_ERROR", "message": str(e)}},
        )

    duration = round(time.time() - start_time, 3)
    response.headers["X-Request-ID"] = request_id
    logger.info(f"{request.method} {request.url.path} finished in {duration}s (Request-ID: {request_id})")

    return response

@app.middleware("http")
async def verify_jwt(request: Request, call_next):
    open_paths = ["/v1/users/register", "/v1/users/login"]

    if any(request.url.path.startswith(p) for p in open_paths):
        return await call_next(request)

    auth_header = request.headers.get("Authorization")
    if not auth_header or not auth_header.startswith("Bearer "):
        return JSONResponse(
            status_code=401,
            content={"success": False, "error": {"code": "UNAUTHORIZED", "message": "Missing token"}},
        )

    token = auth_header.split(" ")[1]
    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=[ALGORITHM])
        request.state.user_id = payload.get("sub")
        request.state.roles = payload.get("roles", [])
    except JWTError:
        return JSONResponse(
            status_code=401,
            content={"success": False, "error": {"code": "INVALID_TOKEN", "message": "Token invalid or expired"}},
        )

    return await call_next(request)

async def proxy_request(request: Request, target_base: str, subpath: str):
    target_url = f"{target_base}/v1/{subpath}"

    body = await request.body()

    headers = dict(request.headers)
    headers["X-Request-ID"] = request.state.request_id

    if hasattr(request.state, "user_id"):
        headers["X-User-ID"] = str(request.state.user_id)
        headers["X-User-Roles"] = ",".join(request.state.roles)

    async with httpx.AsyncClient() as client:
        resp = await client.request(
            method=request.method,
            url=target_url,
            headers=headers,
            content=body,
            params=request.query_params,
            timeout=15.0,
        )

    return Response(
        content=resp.content,
        status_code=resp.status_code,
        media_type=resp.headers.get("content-type", "application/json"),
        headers={"X-Request-ID": request.state.request_id},
    )

@app.api_route("/v1/users{path:path}", methods=["GET", "POST", "PUT", "PATCH", "DELETE"])
async def users_proxy(request: Request, path: str):
    return await proxy_request(request, USERS_SERVICE_URL, f"users{path}")

@app.api_route("/v1/orders{path:path}", methods=["GET", "POST", "PUT", "PATCH", "DELETE"])
async def orders_proxy(request: Request, path: str):
    return await proxy_request(request, ORDERS_SERVICE_URL, f"orders{path}")

@app.exception_handler(RequestValidationError)
async def validation_exception_handler(request, exc):
    return JSONResponse(
        status_code=400,
        content={"success": False, "error": {"code": "VALIDATION_ERROR", "message": str(exc)}},
    )
