import 'package:flutter/material.dart';
import 'package:geolocator/geolocator.dart';
import 'package:geocoding/geocoding.dart';
import 'package:sensors_plus/sensors_plus.dart';
import 'package:flutter_compass/flutter_compass.dart';
import 'package:fl_chart/fl_chart.dart';
import 'dart:async';
import 'dart:math';

class GeoSensorsPage extends StatefulWidget {
  const GeoSensorsPage({super.key});
  @override
  State<GeoSensorsPage> createState() => _GeoSensorsPageState();
}

class _GeoSensorsPageState extends State<GeoSensorsPage> {
  List<FlSpot> accHistory = [];
  int tick = 0;

  Position? _position;
  String _address = '–';
  double? _compass;
  List<double>? _accelerometerValues;
  List<double>? _gyroscopeValues;

  StreamSubscription<AccelerometerEvent>? _accSub;
  StreamSubscription<GyroscopeEvent>? _gyroSub;
  StreamSubscription<CompassEvent>? _compassSub;

  @override
  void initState() {
    super.initState();

    _accSub = accelerometerEvents.listen((event) {
      if (!mounted) return;

      final accValue = sqrt(
        event.x * event.x + event.y * event.y + event.z * event.z,
      );

      setState(() {
        _accelerometerValues = [event.x, event.y, event.z];

        accHistory.add(FlSpot(tick.toDouble(), accValue));
        tick++;

        if (accHistory.length > 100) {
          accHistory.removeAt(0);
        }
      });
    });

    _gyroSub = gyroscopeEvents.listen((event) {
      if (!mounted) return;
      setState(() => _gyroscopeValues = [event.x, event.y, event.z]);
    });

    _compassSub = FlutterCompass.events?.listen((event) {
      if (!mounted) return;
      setState(() => _compass = event.heading);
    });
  }

  @override
  void dispose() {
    _accSub?.cancel();
    _gyroSub?.cancel();
    _compassSub?.cancel();
    super.dispose();
  }

  Future<void> _getLocation() async {
    bool serviceEnabled = await Geolocator.isLocationServiceEnabled();
    if (!serviceEnabled) return;

    LocationPermission permission = await Geolocator.requestPermission();
    if (permission == LocationPermission.denied) return;

    final pos = await Geolocator.getCurrentPosition(
      desiredAccuracy: LocationAccuracy.high,
    );

    List<Placemark> placemarks = await placemarkFromCoordinates(
      pos.latitude,
      pos.longitude,
    );

    setState(() {
      _position = pos;
      _address =
          '${placemarks.first.locality}, ${placemarks.first.street ?? ''}';
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Geo & Sensors Demo')),
      body: Padding(
        padding: const EdgeInsets.all(16),
        child: ListView(
          children: [
            ElevatedButton(
              onPressed: _getLocation,
              child: const Text('Определить местоположение'),
            ),
            const SizedBox(height: 12),
            Text(
              _position != null
                  ? 'Координаты: ${_position!.latitude}, ${_position!.longitude}'
                  : 'Координаты: –',
            ),
            Text('Адрес: $_address'),
            const Divider(height: 30),
            Text('Компас: ${_compass?.toStringAsFixed(2) ?? '–'}°'),
            const Divider(height: 30),
            Text(
              'Акселерометр: ${_accelerometerValues?.map((e) => e.toStringAsFixed(2)).join(', ') ?? '–'}',
            ),
            Text(
              'Гироскоп: ${_gyroscopeValues?.map((e) => e.toStringAsFixed(2)).join(', ') ?? '–'}',
            ),
            const SizedBox(height: 30),
            SizedBox(
              height: 200,
              child: LineChart(
                LineChartData(
                  gridData: const FlGridData(show: true),
                  titlesData: const FlTitlesData(show: false),
                  borderData: FlBorderData(show: true),
                  lineBarsData: [
                    LineChartBarData(
                      spots: accHistory,
                      isCurved: true,
                      barWidth: 2,
                    ),
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
