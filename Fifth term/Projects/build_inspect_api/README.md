# Task Management Backend

Микросервисная система управления пользователями и заказами для строительных объектов.

Состоит из трёх компонентов:

1. **Users Service** — регистрация, вход, профиль, список пользователей
2. **Orders Service** — создание, обновление, просмотр и отмена заказов
3. **API Gateway** — проксирование, JWT-аутентификация, CORS, логирование и request ID

---

## 📦 Структура проекта

```
.
├── api_gateway
│   ├── config.py
│   ├── Dockerfile
│   ├── main.py
│   ├── requirements.txt
│   └── test_gateway.py
├── compose.yml
├── README.md
├── service_orders
│   ├── data.py
│   ├── Dockerfile
│   ├── main.py
│   ├── models.py
│   ├── requirements.txt
│   ├── test_orders.py
│   └── utils.py
└── service_users
    ├── config.py
    ├── data.py
    ├── Dockerfile
    ├── main.py
    ├── models.py
    ├── requirements.txt
    ├── test_users.py
    └── utils.py
```

---

## ⚡ Технологии

* Python 3.12+
* FastAPI
* Pydantic для валидации данных
* JWT для аутентификации (`python-jose`)
* HTTPX для проксирования запросов
* Logging, CORS, Request-ID middleware

---

## 🚀 Запуск

```bash
git clone https://github.com/NKTKLN/build_inspect_api
cd build_inspect_api
```

```bash
docker compose up --build -d
```

---

## 🔑 Аутентификация

* JWT через заголовок `Authorization: Bearer <token>`
* Заголовки `X-User-ID` и `X-User-Roles` прокидываются через шлюз для сервисов
* Открытые пути (без JWT):

  * `/v1/users/register`
  * `/v1/users/login`

---

## 🛠 API Users Service

| Метод | Путь                 | Описание                          |
| ----- | -------------------- | --------------------------------- |
| POST  | `/v1/users/register` | Регистрация пользователя          |
| POST  | `/v1/users/login`    | Вход и получение токена           |
| GET   | `/v1/users/me`       | Получить свой профиль             |
| PUT   | `/v1/users/me`       | Обновить свой профиль             |
| GET   | `/v1/users`          | Список пользователей (admin only) |

---

## 🛠 API Orders Service

| Метод  | Путь                           | Описание                                         |
| ------ | ------------------------------ | ------------------------------------------------ |
| POST   | `/v1/orders`                   | Создать заказ                                    |
| GET    | `/v1/orders/{order_id}`        | Получить заказ                                   |
| GET    | `/v1/orders`                   | Список заказов пользователя (или всех для admin) |
| PATCH  | `/v1/orders/{order_id}/status` | Обновить статус заказа                           |
| DELETE | `/v1/orders/{order_id}`        | Отменить заказ                                   |

Все ответы имеют формат:

```json
{
  "success": true|false,
  "data": {...},
  "error": {"code": "...", "message": "..."} | null
}
```

---

## 🧪 Тестирование

![gateway](/src/test1.png)

![users](/src/test2.png)

![orders](/src/test3.png)
