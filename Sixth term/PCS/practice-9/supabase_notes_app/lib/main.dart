import 'package:flutter/material.dart';
import 'package:supabase_flutter/supabase_flutter.dart';
import 'package:supabase_notes_app/auth_page.dart';

const supabaseUrl = 'https://ldrtmzncdwymbnqtpltf.supabase.co';
const supabaseAnonKey =
    'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImxkcnRtem5jZHd5bWJucXRwbHRmIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NjE2NDIxOTYsImV4cCI6MjA3NzIxODE5Nn0.TLTkuMhVG8nR_0_We-xcw1tZs4fszfG_PkQBUAYNLEc';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Supabase.initialize(url: supabaseUrl, anonKey: supabaseAnonKey);
  runApp(const NotesApp());
}

class NotesApp extends StatelessWidget {
  const NotesApp({super.key});
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Supabase Notes',
      theme: ThemeData(useMaterial3: true),
      home: const AuthGate(),
    );
  }
}
