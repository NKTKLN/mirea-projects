import 'package:api_notes_app/data/notes_repository.dart';
import 'package:api_notes_app/models/note.dart';
import 'package:flutter/material.dart';

class NoteDetailsPage extends StatelessWidget {
  final int id;
  final NotesRepository repo;
  const NoteDetailsPage({super.key, required this.id, required this.repo});

  @override
  Widget build(BuildContext context) {
    return FutureBuilder<Note>(
      future: repo.get(id),
      builder: (context, snap) {
        if (snap.hasError) return const Scaffold(body: Center(child: Text('Ошибка')));
        if (!snap.hasData) return const Scaffold(body: Center(child: CircularProgressIndicator()));
        final n = snap.data!;
        return Scaffold(
          appBar: AppBar(title: Text('Запись #${n.id} (${n.title})')),
          body: Padding(
            padding: const EdgeInsets.all(16),
            child: Text(n.body),
          ),
        );
      },
    );
  }
}
