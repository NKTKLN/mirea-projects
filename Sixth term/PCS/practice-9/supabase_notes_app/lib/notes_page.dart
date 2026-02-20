import 'package:flutter/material.dart';
import 'package:supabase_flutter/supabase_flutter.dart';
import 'package:supabase_notes_app/auth_page.dart';

final supabase = Supabase.instance.client;

class NotesPage extends StatefulWidget {
  const NotesPage({super.key});

  @override
  State<NotesPage> createState() => _NotesPageState();
}

class _NotesPageState extends State<NotesPage> {
  late final Stream<List<Map<String, dynamic>>> _notesStream;

  @override
  void initState() {
    super.initState();

    final user = supabase.auth.currentUser;
    if (user == null) {
      WidgetsBinding.instance.addPostFrameCallback((_) {
        Navigator.pushReplacement(
          context,
          MaterialPageRoute(builder: (_) => const AuthGate()),
        );
      });
      return;
    }

    _notesStream = supabase
        .from('notes')
        .stream(primaryKey: ['id'])
        .order('created_at', ascending: false)
        .map((notes) => notes.where((n) => n['user_id'] == user.id).toList());
  }

  Future<void> _createNote(String title, String content) async {
    final user = supabase.auth.currentUser;
    if (user == null) return;

    await supabase.from('notes').insert({
      'user_id': user.id,
      'title': title,
      'content': content,
      'updated_at': DateTime.now().toIso8601String(),
    }).select();
  }

  Future<void> _updateNote(String id, String title, String content) async {
    await supabase
        .from('notes')
        .update({
          'title': title,
          'content': content,
          'updated_at': DateTime.now().toIso8601String(),
        })
        .eq('id', id)
        .select();
  }

  Future<void> _deleteNote(String id) async {
    await supabase.from('notes').delete().eq('id', id);
  }

  void _openCreateDialog() {
    final titleCtrl = TextEditingController();
    final contentCtrl = TextEditingController();

    showDialog(
      context: context,
      builder: (_) => AlertDialog(
        title: const Text('Новая заметка'),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            TextField(
              controller: titleCtrl,
              decoration: const InputDecoration(labelText: 'Заголовок'),
            ),
            TextField(
              controller: contentCtrl,
              decoration: const InputDecoration(labelText: 'Текст'),
            ),
          ],
        ),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context),
            child: const Text('Отмена'),
          ),
          ElevatedButton(
            onPressed: () async {
              await _createNote(titleCtrl.text.trim(), contentCtrl.text.trim());
              if (mounted) Navigator.pop(context);
            },
            child: const Text('Сохранить'),
          ),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    final user = supabase.auth.currentUser;
    if (user == null) {
      return const Scaffold(body: Center(child: CircularProgressIndicator()));
    }

    return Scaffold(
      appBar: AppBar(
        title: const Text('Supabase Notes'),
        actions: [
          IconButton(
            icon: const Icon(Icons.logout),
            onPressed: () async {
              await supabase.auth.signOut();
              if (!mounted) return;
              Navigator.pushReplacement(
                context,
                MaterialPageRoute(builder: (_) => const AuthGate()),
              );
            },
          ),
        ],
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _openCreateDialog,
        child: const Icon(Icons.add),
      ),
      body: StreamBuilder<List<Map<String, dynamic>>>(
        stream: _notesStream,
        builder: (context, snapshot) {
          if (snapshot.hasError) {
            return const Center(child: Text('Ошибка загрузки'));
          }
          if (!snapshot.hasData) {
            return const Center(child: CircularProgressIndicator());
          }
          final notes = snapshot.data!;
          if (notes.isEmpty) {
            return const Center(child: Text('Пока нет заметок'));
          }

          return ListView.separated(
            padding: const EdgeInsets.all(12),
            itemCount: notes.length,
            separatorBuilder: (_, __) => const SizedBox(height: 8),
            itemBuilder: (context, i) {
              final n = notes[i];
              return Dismissible(
                key: ValueKey(n['id']),
                background: Container(color: Colors.red.withOpacity(.1)),
                onDismissed: (_) => _deleteNote(n['id']),
                child: Card(
                  child: ListTile(
                    title: Text(
                      n['title'] ?? '(без названия)',
                      maxLines: 1,
                      overflow: TextOverflow.ellipsis,
                    ),
                    subtitle: Text(
                      n['content'] ?? '',
                      maxLines: 2,
                      overflow: TextOverflow.ellipsis,
                    ),
                    onTap: () {
                      final tc = TextEditingController(text: n['title'] ?? '');
                      final cc = TextEditingController(
                        text: n['content'] ?? '',
                      );
                      showDialog(
                        context: context,
                        builder: (_) => AlertDialog(
                          title: const Text('Редактировать'),
                          content: Column(
                            mainAxisSize: MainAxisSize.min,
                            children: [
                              TextField(
                                controller: tc,
                                decoration: const InputDecoration(
                                  labelText: 'Заголовок',
                                ),
                              ),
                              TextField(
                                controller: cc,
                                decoration: const InputDecoration(
                                  labelText: 'Текст',
                                ),
                              ),
                            ],
                          ),
                          actions: [
                            TextButton(
                              onPressed: () => Navigator.pop(context),
                              child: const Text('Отмена'),
                            ),
                            ElevatedButton(
                              onPressed: () async {
                                await _updateNote(
                                  n['id'],
                                  tc.text.trim(),
                                  cc.text.trim(),
                                );
                                if (mounted) Navigator.pop(context);
                              },
                              child: const Text('Обновить'),
                            ),
                          ],
                        ),
                      );
                    },
                    trailing: IconButton(
                      icon: const Icon(Icons.delete_outline),
                      onPressed: () => _deleteNote(n['id']),
                    ),
                  ),
                ),
              );
            },
          );
        },
      ),
    );
  }
}
