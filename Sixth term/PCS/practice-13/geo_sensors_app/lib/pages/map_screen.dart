import 'package:flutter/material.dart';
import 'package:geolocator/geolocator.dart';
import 'package:yandex_mapkit/yandex_mapkit.dart';
import 'dart:async';

class MapScreen extends StatefulWidget {
  const MapScreen({super.key});
  @override
  State<MapScreen> createState() => _MapScreenState();
}

class _MapScreenState extends State<MapScreen> {
  YandexMapController? controller;
  Point point = const Point(latitude: 55.75, longitude: 37.61);

  Future<void> locate() async {
    final permission = await Geolocator.requestPermission();
    if (permission == LocationPermission.denied ||
        permission == LocationPermission.deniedForever) {
      return;
    }

    final pos = await Geolocator.getCurrentPosition();
    point = Point(latitude: pos.latitude, longitude: pos.longitude);

    if (controller != null) {
      await controller!.moveCamera(
        CameraUpdate.newCameraPosition(
          CameraPosition(target: point, zoom: 15),
        ),
      );
    }

    if (mounted) setState(() {});
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Карта (Яндекс)')),
      body: YandexMap(
        onMapCreated: (c) {
          controller = c;
          locate(); // <-- Вызываем ТОЛЬКО когда controller создан
        },
        mapObjects: [
          PlacemarkMapObject(
            mapId: const MapObjectId('me'),
            point: point,
            icon: PlacemarkIcon.single(
              PlacemarkIconStyle(
                image: BitmapDescriptor.fromAssetImage('assets/user.png'),
                scale: 1,
              ),
            ),
          ),
        ],
      ),
    );
  }
}
