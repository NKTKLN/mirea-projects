import 'package:flutter/material.dart';

class AppTheme {
  static final ThemeData darkTheme = ThemeData(
    brightness: Brightness.dark,
    scaffoldBackgroundColor: const Color(0xFF0E0E0E),
    colorScheme: const ColorScheme(
      brightness: Brightness.dark,
      primary: Color(0xFFF5D96A),
      onPrimary: Colors.black,
      secondary: Color(0xFFE8C75A),
      onSecondary: Colors.black,
      surface: Color(0xFF1A1A1A),
      onSurface: Color(0xFFEDEDED),
      surfaceContainerHighest: Color(0xFF141414),
      error: Colors.red,
      onError: Colors.white,
      outline: Color(0x33FFFFFF),
      shadow: Colors.black,
      scrim: Colors.black,
    ),
    appBarTheme: const AppBarTheme(
      backgroundColor: Color(0xFF141414),
      foregroundColor: Color(0xFFF5D96A),
      elevation: 0,
    ),
    floatingActionButtonTheme: const FloatingActionButtonThemeData(
      backgroundColor: Color(0xFFF5D96A),
      foregroundColor: Colors.black,
    ),
    elevatedButtonTheme: ElevatedButtonThemeData(
      style: ElevatedButton.styleFrom(
        backgroundColor: Color(0xFFF5D96A),
        foregroundColor: Colors.black,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.all(Radius.circular(12)),
        ),
      ),
    ),
    textTheme: const TextTheme(
      bodyMedium: TextStyle(color: Color(0xFFEDEDED)),
      bodyLarge: TextStyle(color: Color(0xFFF0F0F0)),
      titleLarge: TextStyle(
        color: Color(0xFFF5D96A),
        fontWeight: FontWeight.w600,
      ),
    ),
  );
}
