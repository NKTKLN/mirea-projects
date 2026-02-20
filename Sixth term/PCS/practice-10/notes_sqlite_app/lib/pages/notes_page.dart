import 'package:flutter/material.dart';
import '../data/db_helper.dart';
import '../models/note.dart';

class NotesPage extends StatefulWidget {
  const NotesPage({super.key});
  @override
  State<NotesPage> createState() => _NotesPageState();
}

class _NotesPageState extends State<NotesPage> {
  List<Note> _notes = [];
  String _search = '';
  bool _loading = true;

  @override
  void initState() {
    super.initState();
    _reload();
  }

  Future<void> _reload() async {
    setState(() => _loading = true);
    final list = _search.isEmpty
        ? await DBHelper.fetchNotes()
        : await DBHelper.searchByTitle(_search);
    if (mounted) {
      setState(() {
        _notes = list;
        _loading = false;
      });
    }
  }

  Future<void> _createDialog() async {
    final titleCtrl = TextEditingController();
    final bodyCtrl = TextEditingController();
    final ok = await showDialog<bool>(
      context: context,
      builder: (_) =>
          _EditDialog(titleCtrl: titleCtrl, bodyCtrl: bodyCtrl, title: 'Новая заметка'),
    );
    if (ok == true) {
      final now = DateTime.now().toUtc();
      await DBHelper.insertNote(Note(
        title: titleCtrl.text.trim(),
        body: bodyCtrl.text.trim(),
        createdAt: now,
        updatedAt: now,
      ));
      _reload();
    }
  }

  Future<void> _editDialog(Note n) async {
    final titleCtrl = TextEditingController(text: n.title);
    final bodyCtrl = TextEditingController(text: n.body);
    final ok = await showDialog<bool>(
      context: context,
      builder: (_) =>
          _EditDialog(titleCtrl: titleCtrl, bodyCtrl: bodyCtrl, title: 'Редактировать'),
    );
    if (ok == true) {
      final updated = n.copyWith(
        title: titleCtrl.text.trim(),
        body: bodyCtrl.text.trim(),
        updatedAt: DateTime.now().toUtc(),
      );
      await DBHelper.updateNote(updated);
      _reload();
    }
  }

  Future<void> _delete(Note n) async {
    await DBHelper.deleteNote(n.id!);
    if (!mounted) return;
    setState(() {
      _notes.removeWhere((note) => note.id == n.id);
    });
    ScaffoldMessenger.of(context)
        .showSnackBar(const SnackBar(content: Text('Удалено')));
  }

  void _toggleFavorite(Note n) async {
    final toggled =
        n.copyWith(isFavorite: !n.isFavorite, updatedAt: DateTime.now().toUtc());
    await DBHelper.updateNote(toggled);
    _reload();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Notes SQLite'),
        actions: [
          IconButton(icon: const Icon(Icons.search), onPressed: () => _showSearch()),
        ],
      ),
      floatingActionButton:
          FloatingActionButton(onPressed: _createDialog, child: const Icon(Icons.add)),
      body: _loading
          ? const Center(child: CircularProgressIndicator())
          : _notes.isEmpty
              ? const Center(child: Text('Пока нет заметок. Нажмите +'))
              : ListView.separated(
                  padding: const EdgeInsets.all(12),
                  itemCount: _notes.length,
                  separatorBuilder: (_, __) => const SizedBox(height: 8),
                  itemBuilder: (_, i) {
                    final n = _notes[i];
                    return Dismissible(
                      key: ValueKey(n.id),
                      background: Container(
                        color: Theme.of(context).colorScheme.error.withOpacity(.1),
                        alignment: Alignment.centerLeft,
                        padding: const EdgeInsets.only(left: 16),
                        child: const Icon(Icons.delete_outline),
                      ),
                      direction: DismissDirection.startToEnd,
                      onDismissed: (_) => _delete(n),
                      child: Card(
                        child: ListTile(
                          title: Text(
                            n.title.isEmpty ? '(без названия)' : n.title,
                            maxLines: 1,
                            overflow: TextOverflow.ellipsis,
                          ),
                          subtitle: Text(
                            n.body,
                            maxLines: 2,
                            overflow: TextOverflow.ellipsis,
                          ),
                          onTap: () => _editDialog(n),
                          trailing: Row(mainAxisSize: MainAxisSize.min, children: [
                            IconButton(
                              icon: Icon(
                                  n.isFavorite ? Icons.star : Icons.star_border),
                              onPressed: () => _toggleFavorite(n),
                            ),
                            IconButton(
                              icon: const Icon(Icons.delete_outline),
                              onPressed: () => _delete(n),
                            ),
                          ]),
                        ),
                      ),
                    );
                  },
                ),
    );
  }

  void _showSearch() async {
    final q = await showDialog<String>(
      context: context,
      builder: (_) {
        final ctrl = TextEditingController(text: _search);
        return AlertDialog(
          title: const Text('Поиск по заголовку'),
          content: TextField(
              controller: ctrl,
              decoration: const InputDecoration(hintText: 'Введите фразу')),
          actions: [
            TextButton(
                onPressed: () => Navigator.pop(context, ''),
                child: const Text('Сброс')),
            FilledButton(
                onPressed: () => Navigator.pop(context, ctrl.text.trim()),
                child: const Text('Поиск')),
          ],
        );
      },
    );
    if (q == null) return;
    _search = q;
    _reload();
  }
}

class _EditDialog extends StatelessWidget {
  final TextEditingController titleCtrl;
  final TextEditingController bodyCtrl;
  final String title;
  const _EditDialog(
      {required this.titleCtrl, required this.bodyCtrl, required this.title});

  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: Text(title),
      content: Column(mainAxisSize: MainAxisSize.min, children: [
        TextField(
            controller: titleCtrl,
            decoration: const InputDecoration(labelText: 'Заголовок')),
        TextField(
            controller: bodyCtrl,
            decoration: const InputDecoration(labelText: 'Текст')),
      ]),
      actions: [
        TextButton(
            onPressed: () => Navigator.pop(context, false),
            child: const Text('Отмена')),
        FilledButton(
            onPressed: () => Navigator.pop(context, true),
            child: const Text('Сохранить')),
      ],
    );
  }
}
