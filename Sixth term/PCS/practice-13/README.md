# Практическое занятие №13 Аппаратная часть мобильных устройств. Работа с геолокацией. Работа с различными датчиками устройства

## ЭФБО-09-23 Калинин Никита

---

## Цели работы

- Изучить возможности работы с аппаратными датчиками и сервисами устройства.
- Освоить получение координат устройства с помощью геолокации.
- Научиться определять местоположение, направление и движение.
- Изучить работу с сенсорами: акселерометр, гироскоп, компас, освещенность и др.
- Разработать мобильное приложение, использующее геолокацию и данные сенсоров.

## Ход работы

### Разрешения (Android)

В файле **`AndroidManifest.xml`**:

```xml
<uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />
<uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
<uses-permission android:name="android.permission.INTERNET"/>
```

Также приложение регистрируется с кастомным классом:

```xml
<application
    android:name=".MainApplication"
    ...
```

А в `MainApplication.kt` инициализируется Яндекс.Карты:

```kotlin
package com.example.geo_sensors_app

import android.app.Application
import com.yandex.mapkit.MapKitFactory

class MainApplication: Application() {
  override fun onCreate() {
    super.onCreate()
    MapKitFactory.setLocale("ru_RU"); 
    MapKitFactory.setApiKey("API_KEY");
  }
}
```

### Основная функциональность

#### 1. Получение GPS-координат и адреса

Используется пакет `geolocator` + `geocoding`:

```dart
final pos = await Geolocator.getCurrentPosition();
final placemarks = await placemarkFromCoordinates(pos.latitude, pos.longitude);
```

На экране отображается:

* широта / долгота
* определённый адрес

#### 2. Данные компаса

Через `flutter_compass`:

```dart
_compassSub = FlutterCompass.events?.listen((event) {
  heading = event.heading;
});
```

#### 3. Акселерометр и гироскоп

Используется `sensors_plus`:

```dart
accelerometerEvents.listen((event) { ... });
gyroscopeEvents.listen((event) { ... });
```

Акселерометр дополнительно обрабатывается:

```dart
final accValue = sqrt(event.x*event.x + event.y*event.y + event.z*event.z);
```

#### 4. Построение графика ускорения

Через пакет `fl_chart`:

```dart
LineChart(
  LineChartData(
    lineBarsData: [
      LineChartBarData(
        spots: accHistory,
        isCurved: true,
      ),
    ],
  ),
);
```

Обновляется в реальном времени.

#### 5. Работа с картой (Яндекс)

Используется `yandex_mapkit`:

```dart
await controller.moveCamera(
  CameraUpdate.newCameraPosition(
    CameraPosition(target: point, zoom: 15),
  ),
);
```

И отображение маркера:

```dart
PlacemarkMapObject(
  point: point,
  icon: PlacemarkIcon.single(
    PlacemarkIconStyle(
      image: BitmapDescriptor.fromAssetImage('assets/user.png'),
    ),
  ),
);
```

#### 6. Информация о пользователе (скорость, высота)

Получение из GPS:

```dart
Geolocator.getPositionStream().listen((p) {
  speed = p.speed;
  altitude = p.altitude;
});
```

## Скриншоты приложения (примерные)

1. Главный экран меню

<img width="578" height="1280" alt="image" src="https://github.com/user-attachments/assets/55428173-1dec-42ff-a41a-a66e9bb74c8a" />

2. Экран сенсоров с графиком

<img width="578" height="1280" alt="image" src="https://github.com/user-attachments/assets/51ff91a5-dc91-44d3-9156-49007fb7cdd1" />

3. Экран Яндекс.Карты

<img width="578" height="1280" alt="image" src="https://github.com/user-attachments/assets/fc758890-5497-4685-a532-7ec0cefa56e7" />

4. Экран «О пользователе»

<img width="578" height="1280" alt="image" src="https://github.com/user-attachments/assets/f6f86e19-b322-4039-bcc6-7b269a1d78ce" />

## Результаты работы

* Реализовано приложение, работающее с сенсорами устройства.
* Получены данные акселерометра, гироскопа, компаса и GPS.
* Выполнена визуализация данных в виде графика.
* Интегрирована карта Яндекс с позиционированием пользователя.
* Добавлена обработка разрешений и потоковых сенсорных данных.
* Архитектура приложения разделена на независимые экраны.
