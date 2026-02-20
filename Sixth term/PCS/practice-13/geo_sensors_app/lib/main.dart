import 'package:flutter/material.dart';
import 'package:geo_sensors_app/pages/geo_sensors_screen.dart';
import 'package:geo_sensors_app/pages/map_screen.dart';
import 'package:geo_sensors_app/pages/user_info_screen.dart';
import 'package:geo_sensors_app/themes/app_theme.dart';

void main() => runApp(const GeoSensorsApp());

class GeoSensorsApp extends StatelessWidget {
  const GeoSensorsApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Geo & Sensors',
      theme: AppTheme.darkTheme,
      home: const MainMenu(),
    );
  }
}

class MainMenu extends StatelessWidget {
  const MainMenu({super.key});
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Меню')),
      body: ListView(
        padding: const EdgeInsets.all(20),
        children: [
          ElevatedButton(
            onPressed: () => Navigator.push(
              context,
              MaterialPageRoute(builder: (_) => const GeoSensorsPage()),
            ),
            child: const Text('Основной экран'),
          ),
          ElevatedButton(
            onPressed: () => Navigator.push(
              context,
              MaterialPageRoute(builder: (_) => const MapScreen()),
            ),
            child: const Text('Карта'),
          ),
          ElevatedButton(
            onPressed: () => Navigator.push(
              context,
              MaterialPageRoute(builder: (_) => const UserInfoScreen()),
            ),
            child: const Text('О пользователе'),
          ),
        ],
      ),
    );
  }
}
