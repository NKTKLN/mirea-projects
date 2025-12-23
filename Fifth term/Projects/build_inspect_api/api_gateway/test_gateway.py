import pytest
from httpx import AsyncClient, ASGITransport
from main import app
import pytest
import respx
from httpx import Response as HttpxResponse, ASGITransport, AsyncClient
from main import app
from config import USERS_SERVICE_URL


@pytest.mark.anyio
async def test_open_path_without_token():
    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.post("/v1/users/register", json={"username": "test", "password": "123"})
        assert response.status_code != 401
        data = response.json()
        assert "success" in data

@pytest.mark.anyio
async def test_protected_path_without_token():
    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.get("/v1/orders/123")
        assert response.status_code == 401
        data = response.json()
        assert data["error"]["code"] == "UNAUTHORIZED"

@pytest.mark.anyio
async def test_protected_path_with_invalid_token():
    headers = {"Authorization": "Bearer invalidtoken"}
    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://testserver") as client:
        response = await client.get("/v1/orders/123", headers=headers)
        assert response.status_code == 401
        data = response.json()
        assert data["error"]["code"] == "INVALID_TOKEN"

@pytest.mark.anyio
async def test_request_id_header_added():
    transport = ASGITransport(app=app)

    with respx.mock(base_url=USERS_SERVICE_URL) as mock:
        route = mock.post("/v1/users/register").mock(
            return_value=HttpxResponse(200, json={"success": True})
        )

        async with AsyncClient(transport=transport, base_url="http://testserver") as client:
            response = await client.post("/v1/users/register", json={"username": "test", "password": "123"})
            
            assert route.called
            
            assert "X-Request-ID" in response.headers
            data = response.json()
            assert data["success"] is True
