# Практическое занятие № 10 Работа с базами данных. Подключение к SQLite (Flutter, sqflite)

## ЭФБО-09-23 Калинин Никита

*Цели:*

- Подключить Flutter-приложение к локальной базе данных SQLite (пакет sqflite).
- Создать таблицы и реализовать базовый CRUD: добавление, чтение, обновление, удаление.
- Настроить класс-помощник для работы с БД и отделить слой данных от UI.
- Отработать миграции схемы и диагностику частых ошибок.

### Ход работы

#### Работа с базой данных

В файле **`data/db_helper.dart`** реализован класс `DBHelper`, отвечающий за взаимодействие с локальной базой данных.

**Основные функции:**

* Инициализация базы (`openDatabase`);
* Создание таблицы `notes`;
* Методы для выполнения CRUD-операций:

  ```dart
  insertNote(Note note)
  fetchNotes()
  updateNote(Note note)
  deleteNote(int id)
  searchByTitle(String query)
  ```

#### Где хранится база данных

Файл базы данных `notes.db` хранится во внутреннем каталоге приложения (в песочнице Android):

```
/data/data/com.example.notes_sqlite_app/databases/notes.db
```

При первом запуске приложение автоматически создаёт файл базы, если его ещё нет:

```dart
final dbPath = await getDatabasesPath();
final path = join(dbPath, 'notes.db');
final db = await openDatabase(path, version: 1, onCreate: _createDB);
```

#### Структура таблицы

База данных содержит одну основную таблицу — **`notes`**, где хранятся все заметки.

```sql
CREATE TABLE notes (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  title TEXT NOT NULL,
  body TEXT NOT NULL,
  is_favorite INTEGER NOT NULL DEFAULT 0,
  created_at TEXT NOT NULL,
  updated_at TEXT NOT NULL
);
```

| Поле          | Тип          | Описание                               |
| ------------- | ------------ | -------------------------------------- |
| `id`          | INTEGER (PK) | Уникальный идентификатор заметки       |
| `title`       | TEXT         | Заголовок заметки                      |
| `body`        | TEXT         | Основной текст заметки                 |
| `is_favorite` | INTEGER      | Признак «избранного» (0 — нет, 1 — да) |
| `created_at`  | TEXT         | Дата создания                          |
| `updated_at`  | TEXT         | Дата последнего изменения              |

#### Индексы

По умолчанию SQLite создаёт **PRIMARY KEY индекс** по полю `id`.
Для ускорения поиска по заголовку можно добавить дополнительный индекс:

```sql
CREATE INDEX idx_notes_title ON notes(title);
```

#### Реализация CRUD-операций

##### **Create**

```dart
static Future<int> insertNote(Note note) async {
    final db = await _open();
    return db.insert(notesTable, note.toMap(), conflictAlgorithm: ConflictAlgorithm.abort);
}
```

##### **Read**

```dart
// READ all
static Future<List<Note>> fetchNotes({int limit = 100, int offset = 0}) async {
    final db = await _open();
    final rows = await db.query(
      notesTable,
      orderBy: 'created_at DESC',
      limit: limit,
      offset: offset,
    );
    return rows.map((m) => Note.fromMap(m)).toList();
}

// READ by id
static Future<Note?> fetchNoteById(int id) async {
    final db = await _open();
    final rows = await db.query(notesTable, where: 'id = ?', whereArgs: [id], limit: 1);
    if (rows.isEmpty) return null;
    return Note.fromMap(rows.first);
}
```

Поиск по заголовку:

```dart
static Future<List<Note>> searchByTitle(String q) async {
    final db = await _open();
    final rows = await db.query(
      notesTable,
      where: 'title LIKE ?',
      whereArgs: ['%$q%'],
      orderBy: 'created_at DESC',
    );
    return rows.map((m) => Note.fromMap(m)).toList();
}
```

##### **Update**

```dart
static Future<int> updateNote(Note note) async {
    final db = await _open();
    return db.update(
      notesTable,
      note.toMap(),
      where: 'id = ?',
      whereArgs: [note.id],
      conflictAlgorithm: ConflictAlgorithm.abort,
    );
}
```

##### **Delete**

```dart
static Future<int> deleteNote(int id) async {
    final db = await _open();
    return db.delete(notesTable, where: 'id = ?', whereArgs: [id]);
}
```

#### Модель данных

Файл **`models/note.dart`**:

```dart
class Note {
  final int? id;
  final String title;
  final String body;
  final DateTime createdAt;
  final DateTime updatedAt;
  final bool isFavorite;

  Note({
    this.id,
    required this.title,
    required this.body,
    required this.createdAt,
    required this.updatedAt,
    this.isFavorite = false,
  });

  Note copyWith({
    int? id,
    String? title,
    String? body,
    DateTime? createdAt,
    DateTime? updatedAt,
    bool? isFavorite,
  }) {
    return Note(
      id: id ?? this.id,
      title: title ?? this.title,
      body: body ?? this.body,
      createdAt: createdAt ?? this.createdAt,
      updatedAt: updatedAt ?? this.updatedAt,
      isFavorite: isFavorite ?? this.isFavorite,
    );
  }

  factory Note.fromMap(Map<String, Object?> map) => Note(
        id: map['id'] as int?,
        title: (map['title'] as String?) ?? '',
        body: (map['body'] as String?) ?? '',
        createdAt: DateTime.fromMillisecondsSinceEpoch(map['created_at'] as int),
        updatedAt: DateTime.fromMillisecondsSinceEpoch(map['updated_at'] as int),
        isFavorite: (map['is_favorite'] as int?) == 1,
      );

  Map<String, Object?> toMap() => {
        'id': id,
        'title': title,
        'body': body,
        'created_at': createdAt.millisecondsSinceEpoch,
        'updated_at': updatedAt.millisecondsSinceEpoch,
        'is_favorite': isFavorite ? 1 : 0,
      };
}
```

#### Экран списка заметок

Главный экран — **NotesPage** (`pages/notes_page.dart`):

* Отображение списка через `ListView.separated`;
* Удаление заметки свайпом с помощью `Dismissible`;
* Диалог добавления/редактирования заметок через `AlertDialog`;
* Возможность пометки «избранного» через `IconButton`.

#### Интерфейс и функции

* Добавление заметки: кнопка **+** вызывает диалог с `TextField`.
* Редактирование: по нажатию на карточку.
* Удаление: свайп влево или иконка корзины.
* Поиск: реализован через `AlertDialog` с текстовым вводом.
* Список обновляется через `_reload()` и `setState()`.

### Скриншоты работы приложения

Экран при первом запуске

<img width="481" height="903" alt="image" src="https://github.com/user-attachments/assets/2dc1c46c-6ef0-459d-8cd3-f753a5a639a9" />

Добавление новой заметки

<img width="539" height="884" alt="image" src="https://github.com/user-attachments/assets/f54d6ebb-71e4-4081-8ea7-918ba3835324" />\

Список с заметками

<img width="489" height="889" alt="image" src="https://github.com/user-attachments/assets/3ffee9a0-0aa3-4592-bc60-eae77fc8d828" />

Удаление и редактирование заметок

<img width="494" height="906" alt="image" src="https://github.com/user-attachments/assets/3956ab65-63f1-4f94-88de-2829fe7f7ae7" />

<img width="511" height="892" alt="image" src="https://github.com/user-attachments/assets/ec521c42-f74b-4b23-ab95-ad78b9615438" />

### Результаты

В ходе работы было создано приложение заметок с локальным хранилищем SQLite.
Реализованы все CRUD-операции, поиск и пометка «избранных» записей.
Использованы Flutter-виджеты `FutureBuilder`, `AlertDialog`, `Dismissible`, `ListView`.
Приложение готово к расширению.
