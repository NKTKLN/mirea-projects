# Практическое занятие №12 Аппаратная часть мобильных устройств. Работа с камерой устройства.

## ЭФБО-09-23 Калинин Никита

*Цели:*

- Изучить архитектуру и возможности аппаратной части мобильных устройств.
- Ознакомиться с API камеры и галереи во Flutter.
- Научиться создавать приложения, использующие камеру и хранилище устройства.
- Разобраться с разрешениями, обработкой изображений и сохранением данных.

## Ход работы

### Настройка разрешения платформ (Android)

Android (`AndroidManifest.xml`):

```xml
<uses-permission android:name="android.permission.CAMERA" />
<uses-permission android:name="android.permission.READ_MEDIA_IMAGES" />
```

## Логика работы и слой функциональности

Было создано простое приложение, состоящее из одного экрана, который:

* делает фото через камеру;
* выбирает картинку из галереи;
* отображает её в интерфейсе;
* применяет чёрно-белый фильтр;
* сохраняет результат в локальное хранилище приложения.

Ключевая часть — обработка изображения с использованием пакета **`image`**:

```dart
final bytes = await _image!.readAsBytes();
final decoded = img.decodeImage(bytes);
final bw = img.grayscale(decoded!);
final newBytes = img.encodeJpg(bw);
```

### Запрос разрешений

Через `permission_handler`:

```dart
await Permission.camera.request();
await Permission.photos.request();
```

### Съёмка фото / выбор из галереи

```dart
final XFile? pickedFile = await picker.pickImage(source: source);
if (pickedFile != null) {
  setState(() => _image = File(pickedFile.path));
}
```

### Чёрно-белый фильтр

```dart
final decoded = img.decodeImage(bytes);
final bw = img.grayscale(decoded!);
```

### Сохранение в память устройства

Через `path_provider`:

```dart
final dir = await getApplicationDocumentsDirectory();
await _image!.copy('${dir.path}/photo_${DateTime.now().millisecondsSinceEpoch}.jpg');
```

## Скриншоты работы приложения

1. Главный экран

<img width="474" height="876" alt="image" src="https://github.com/user-attachments/assets/bfd59955-fdb6-4ab5-87fd-004de9f45da1" />

2. Фото после съёмки

<img width="484" height="868" alt="image" src="https://github.com/user-attachments/assets/6a55b841-0ae1-4bd2-b02b-4e3cc1914fbd" />

3. Фото после применения ч/б фильтра

<img width="484" height="877" alt="image" src="https://github.com/user-attachments/assets/145b8bc9-de16-4f5c-90ba-951b585cbc37" />

4. Уведомление о сохранении

<img width="499" height="879" alt="image" src="https://github.com/user-attachments/assets/4496a1ba-4d77-49d0-a55d-79e5d43f416c" />

## Результаты

* Реализовано приложение, позволяющее работать с камерой и галереей.
* Добавлена возможность обработки изображения через библиотеку `image`.
* Чёрно-белый фильтр применяется локально.
* Поддержана работа с разрешениями Android и iOS.
* Файлы корректно сохраняются в пользовательское хранилище приложения.
