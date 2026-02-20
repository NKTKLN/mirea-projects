# Sudoku App

Мобильное приложение на Flutter для игры в судоку, включающее режим игры «на рекорд», серверный лидерборд и тёмную тему оформления.

## Возможности

### Режимы игры

* Обычная игра без ограничений.
* Игра «на рекорд» с таймером и отправкой результата в онлайн-лидерборд.
* Генерация уникальных судоку в изоляте (`compute`), чтобы не блокировать интерфейс.

### Лидерборд

* Получение списка рекордов с сервера (MockAPI.io).
* Отправка результатов (имя, время, указание сложности).
* Сортировка по времени.

### Интерфейс

* Тёмная тема.
* Подсветка выбранной ячейки и одинаковых чисел.
* Диалоги ввода имени и кастомная обработка ошибок через `ErrorWidget.builder`.

### Надёжность

* Обработка ошибок через `FlutterError.onError` и `runZonedGuarded`.
* Валидация имени пользователя.
* Чёткое разделение проекта на слои: данные, логика, интерфейс.

## Стек технологий

* Flutter 3.35.5 (stable)
* Dart
* Isolates (`compute`)
* MockAPI.io для REST-бэкенда
* Material Widgets
* CustomPainter для сетки судоку

## Запуск проекта

### 1. Установка зависимостей

```bash
flutter pub get
```

### 2. Запуск приложения

```bash
flutter run
```

### 3. Настройка API (при необходимости)

Файл: `lib/data/leaderboard_repository.dart`

```dart
ApiClient(baseUrl: "https://6920348231e684d7bfcc1628.mockapi.io")
```

## Структура проекта

```
lib/
 ├─ data/
 │   ├─ api_client.dart
 │   └─ leaderboard_repository.dart
 ├─ logic/
 │   └─ sudoku_logic.dart
 ├─ models/
 │   └─ score.dart
 ├─ pages/
 │   ├─ home_page.dart
 │   ├─ sudoku_page.dart
 │   └─ leaderboard_page.dart
 ├─ widgets/
 │   └─ sudoku_grid.dart
 ├─ theme/
 │   └─ app_theme.dart
 ├─ utils/
 │   └─ validation.dart
 └─ main.dart
```
