# Практическое занятие №11 Работа с базами данных. Основы работы с API (HTTP/REST) для Flutter

## ЭФБО-09-23 Калинин Никита

*Цели:*

- Понять базовые понятия HTTP/REST: методы, URL/эндпоинты, коды ответов, заголовки, тела запросов/ответов (JSON).
- Освоить основы интеграции Flutter-приложения с внешним API: http/dio, сериализация JSON, обработка ошибок и таймаутов.
- Научиться выстраивать слой данных с репозиторием и отделять его от UI (продолжаем архитектурную линию прошлых ПЗ).
- Реализовать список сущностей из публичного API + экран деталей + форму создания/редактирования (с демонстрацией запросов).
- Разобраться с пагинацией, фильтрацией, аутентификацией (Bearer), ретраями и UX при сетевых сбоях.

**Вариант**: B. Полный CRUD: на mockapi.io

<img width="1222" height="381" alt="image" src="https://github.com/user-attachments/assets/a21824ec-f836-4eea-ace5-8b59a3becf97" />

### Ход работы

#### Подключение и настройка Dio

В файле **`data/api_client.dart`** создан класс `ApiClient`:

```dart
import 'package:dio/dio.dart';

class ApiClient {
  final Dio dio;

  ApiClient._(this.dio);

  factory ApiClient({required String baseUrl, String? bearerToken}) {
    final dio = Dio(BaseOptions(
      baseUrl: baseUrl,
      connectTimeout: const Duration(seconds: 10),
      receiveTimeout: const Duration(seconds: 10),
      headers: {
        'Content-Type': 'application/json',
        if (bearerToken != null) 'Authorization': 'Bearer $bearerToken',
      },
    ));

    dio.interceptors.add(InterceptorsWrapper(
      onRequest: (options, handler) {
        handler.next(options);
      },
      onError: (e, handler) {
        handler.next(e);
      },
    ));
    return ApiClient._(dio);
  }
}

```

* Настроен базовый URL и заголовки JSON.
* Поддержка Bearer-токена для аутентификации (используется для учебного задела).

#### Репозиторий и слой данных

Файл **`data/notes_repository.dart`** реализует CRUD-операции через API:

```dart
import '../models/note.dart';
import 'api_client.dart';

class NotesRepository {
  final ApiClient _client;
  NotesRepository(this._client);

  Future<List<Note>> list({int page = 1, int limit = 20}) async {
    final resp = await _client.dio.get(
      '/notes',
      queryParameters: {'page': page, 'limit': limit},
    );
    final data = resp.data as List<dynamic>;
    return data.map((e) => Note.fromJson(e as Map<String, dynamic>)).toList();
  }

  Future<Note> get(int id) async {
    final resp = await _client.dio.get('/notes/$id');
    return Note.fromJson(resp.data as Map<String, dynamic>);
  }

  Future<Note> create(String title, String body) async {
    final resp = await _client.dio.post(
      '/notes',
      data: {'title': title, 'body': body},
    );
    return Note.fromJson(resp.data as Map<String, dynamic>);
  }

  Future<Note> update(int id, String title, String body) async {
    final resp = await _client.dio.put(
      '/notes/$id',
      data: {'title': title, 'body': body},
    );
    return Note.fromJson(resp.data as Map<String, dynamic>);
  }

  Future<void> delete(int id) async {
    await _client.dio.delete('/notes/$id');
  }
}
```

* Метод `list` поддерживает пагинацию через query-параметры.
* Методы `create`, `update`, `delete` позволяют работать с mockapi.io или jsonplaceholder.
* Слой данных отделён от UI, что повышает тестируемость и гибкость.

#### Модель данных

Файл **`models/note.dart`**:

```dart
class Note {
  final int id;
  final String title;
  final String body;

  Note({required this.id, required this.title, required this.body});

  factory Note.fromJson(Map<String, dynamic> json) => Note(
    id: json['id'] is String ? int.tryParse(json['id']) ?? 0 : (json['id'] ?? 0),
    title: json['title'] ?? '',
    body: json['body'] ?? '',
  );

  Map<String, dynamic> toJson() => {
    'id': id,
    'title': title,
    'body': body,
  };
}
```

* Сериализация JSON реализована вручную через `fromJson`/`toJson`.
* Поддержка работы с API, где `id` может быть строкой.

#### Экран списка заметок

Файл **`pages/notes_page.dart`**:

* `ListView.separated` с пагинацией по скроллу.
* Pull-to-refresh через `RefreshIndicator`.
* Футер с индикатором загрузки и отложенным вызовом `_loadMore()`:

```dart
WidgetsBinding.instance.addPostFrameCallback((_) => _loadMore());
```

* Удаление записи с обновлением списка:

```dart
() async {
    final n = _items[i];
    try {
        await repo.delete(n.id);
        setState(() => _items.removeAt(i));
        ScaffoldMessenger.of(context).showSnackBar(
            const SnackBar(content: Text('Запись удалена')),
        );
    } catch (e) {
        ScaffoldMessenger.of(context).showSnackBar(
            const SnackBar(
            content: Text('Ошибка при удалении'),
            ),
        );
    }
},
```

### Пагинация, ошибки/таймауты и UX

**1. Пагинация (infinite scroll)**

* Ленивый список с футером для подгрузки.
* `_loadMore()` запрашивает следующую страницу данных.
* Флаги:

  * `_loading` — запрос уже выполняется.
  * `_canLoadMore` — есть ещё страницы.
  * `_page` — текущая страница.
* Pull-to-refresh через `RefreshIndicator` сбрасывает страницу на 1 и очищает список.

**2. Ошибки и таймауты**

* Таймауты задаются в Dio (`10 секунд`).
* Ошибки (сеть, сервер, таймаут) обрабатываются через `try/catch`.
* Сообщения пользователю через `SnackBar`.

**3. UX состояния списка**

| Состояние | Как отображается                              |
| --------- | --------------------------------------------- |
| Loading   | `CircularProgressIndicator` центр или футер   |
| Empty     | Сообщение «Список пуст»                       |
| Error     | `SnackBar` или текст ошибки на экране деталей |
| Data      | Список заметок через `ListView.separated`     |

* После создания/обновления/удаления используется `setState()` для обновления UI.
* Новый элемент добавляется в начало списка для удобства пользователя.

#### Экран деталей

Файл **`pages/note_details_page.dart`**:

```dart
FutureBuilder<Note>(
    future: repo.get(id),
    builder: (context, snap) {
        if (snap.hasError) return const Scaffold(body: Center(child: Text('Ошибка')));
        if (!snap.hasData) return const Scaffold(body: Center(child: CircularProgressIndicator()));
        final n = snap.data!;
        return Scaffold(
                appBar: AppBar(title: Text('Запись #${n.id}')),
                body: Padding(
                padding: const EdgeInsets.all(16),
                child: Text(n.body),
            ),
        );
    },
);
```

#### Диалог создания заметки

Добавлен метод `_createNoteDialog` с `AlertDialog`:

* Пользователь вводит `title` и `body`.
* После создания запись добавляется в начало списка (`_items.insert(0, newNote)`).
* Ошибки показываются через `SnackBar`.

```dart
floatingActionButton: FloatingActionButton(
  onPressed: _createNoteDialog,
  child: const Icon(Icons.add),
),
```

### Скриншоты работы приложения

Список записей с пагинацией

<img width="476" height="887" alt="image" src="https://github.com/user-attachments/assets/63bcb784-d5ef-46a3-a2ac-01af129c50c5" />

Экран деталей записи

<img width="531" height="905" alt="image" src="https://github.com/user-attachments/assets/ab676e6a-d596-4436-b113-b8e43cfee3c9" />

Диалог создания новой записи

<img width="492" height="890" alt="image" src="https://github.com/user-attachments/assets/bb7f33f2-d4a7-4801-8c36-df98385e5527" />

<img width="512" height="877" alt="image" src="https://github.com/user-attachments/assets/c11539ea-654c-4a22-a934-e95e1320c7eb" />

### Результаты

* Реализовано мини-приложение «API Notes Feed» с полноценным CRUD.
* Использован `Dio` для сетевых запросов и обработка ошибок через `SnackBar`.
* Пагинация работает при прокрутке, поддержан pull-to-refresh.
* Отделён слой данных (`NotesRepository`) от UI, повышена тестируемость и гибкость.
* Диалог создания заметки позволяет пользователю вводить данные и сохранять их на mockapi.io.
