import 'package:flutter/material.dart';
import 'package:geolocator/geolocator.dart';
import 'package:flutter_compass/flutter_compass.dart';
import 'dart:async';

class UserInfoScreen extends StatefulWidget {
  const UserInfoScreen({super.key});
  @override
  State<UserInfoScreen> createState() => _UserInfoScreenState();
}

class _UserInfoScreenState extends State<UserInfoScreen> {
  double speed = 0;
  double altitude = 0;
  double? heading;

  StreamSubscription<Position>? _posSub;
  StreamSubscription<CompassEvent>? _compassSub;

  @override
  void initState() {
    super.initState();

    _posSub = Geolocator.getPositionStream().listen((p) {
      if (!mounted) return;
      setState(() {
        speed = p.speed;
        altitude = p.altitude;
      });
    });

    _compassSub = FlutterCompass.events!.listen((event) {
      if (!mounted) return;
      setState(() => heading = event.heading);
    });
  }

  @override
  void dispose() {
    _posSub?.cancel();
    _compassSub?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('О пользователе')),
      body: Padding(
        padding: const EdgeInsets.all(20),
        child: Column(
          children: [
            Text('Скорость: ${speed.toStringAsFixed(2)} м/с'),
            Text('Высота: ${altitude.toStringAsFixed(2)} м'),
            Text('Направление: ${heading?.toStringAsFixed(2) ?? '–'}°'),
          ],
        ),
      ),
    );
  }
}
