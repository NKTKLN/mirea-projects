# Практическое занятие № 9 Работа с базами данных. Подключение приложения к Supabase (Flutter)

## ЭФБО-09-23 Калинин Никита

*Цели:*

- Подключить Flutter-приложение к Supabase (Postgres + Auth + Realtime).
- Освоить инициализацию supabase_flutter, чтение/запись данных и потоковые обновления (stream()).
- Реализовать базовый CRUD (создание, чтение, обновление, удаление) с реактивным списком.
- Включить Row Level Security (RLS) и настроить безопасные политики доступа для аутентифицированных пользователей.

---

## Ход работы:

1.	Скриншот настроенного проекта Supabase (Dashboard: Database → notes, включён RLS, список Policies).

<img width="1919" height="923" alt="image" src="https://github.com/user-attachments/assets/d73d444a-dd43-4a5c-97cf-df8f90b1bd21" />

<img width="1874" height="861" alt="image" src="https://github.com/user-attachments/assets/5122f1e5-0e16-4e76-a61e-d85cb58dc6e1" />

2.	Скриншот экрана входа и экрана со списком (пустого и с данными).

<img width="924" height="997" alt="image" src="https://github.com/user-attachments/assets/60f0bbae-88f6-4451-b530-5f2e81243f7b" />

<img width="927" height="1000" alt="image" src="https://github.com/user-attachments/assets/bc0302c2-948b-400d-9bb6-35f845eefd82" />

<img width="930" height="1007" alt="image" src="https://github.com/user-attachments/assets/a7aad0d3-d094-4a27-b621-b89946b4e22b" />

3.	Скриншот после добавления заметки (элемент появился).

<img width="929" height="1006" alt="image" src="https://github.com/user-attachments/assets/724642a9-896d-43d7-aadb-79a95fb56385" />

4.	Скриншот после редактирования и после удаления.

<img width="932" height="1003" alt="image" src="https://github.com/user-attachments/assets/b2dba1ef-7158-44ad-b88d-976e61e2166e" />

<img width="930" height="1007" alt="image" src="https://github.com/user-attachments/assets/4529b533-52fc-497e-9c43-75c2efb631b0" />

### Подключение Supabase

* Создан проект в Supabase, получены публичные параметры: **Project URL** и **anon key**.
* Подключение выполнено через инициализацию Supabase во Flutter до запуска приложения.
* Приватные ключи и секреты не публиковались.
* Проверена успешная инициализация — приложение запускается без ошибок сети.

### Зависимости и инициализация

* Использован пакет **supabase_flutter (v2)**.
* Подключение и инициализация выполнены в `main.dart`.
* В проекте реализованы экраны аутентификации и заметок (AuthGate и NotesPage).

### Структура таблицы

Таблица **notes** содержит поля:
`id`, `user_id`, `title`, `content`, `created_at`, `updated_at`.
Тип базы данных — **PostgreSQL**.
Включена защита **Row Level Security (RLS)**.

### Политики безопасности (RLS)

* Чтение разрешено только для собственных записей (`user_id = auth.uid()`).
* Вставка возможна только от имени текущего пользователя.
* Обновление и удаление доступны только владельцу записи.
* Все политики действуют для аутентифицированных пользователей.

### Кратко о работе приложения

* Реализована регистрация и вход по email и паролю.
* После входа отображается список заметок пользователя.
* Поддерживается создание, редактирование и удаление заметок.
* Изменения отображаются в реальном времени через Supabase Realtime.
* Доступ к чужим данным исключён благодаря RLS.