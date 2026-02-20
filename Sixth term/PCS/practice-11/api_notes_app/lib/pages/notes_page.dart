import 'package:api_notes_app/note_details_page.dart';
import 'package:flutter/material.dart';
import '../data/api_client.dart';
import '../data/notes_repository.dart';
import '../models/note.dart';

class NotesPage extends StatefulWidget {
  const NotesPage({super.key});

  @override
  State<NotesPage> createState() => _NotesPageState();
}

class _NotesPageState extends State<NotesPage> {
  late final NotesRepository repo;
  final List<Note> _items = [];
  int _page = 1;
  bool _canLoadMore = true;
  bool _loading = false;

  @override
  void initState() {
    super.initState();
    final client = ApiClient(
      baseUrl: 'https://6911b7647686c0e9c20eb58c.mockapi.io',
    );
    repo = NotesRepository(client);
    _refresh();
  }

  Future<void> _refresh() async {
    setState(() {
      _page = 1;
      _canLoadMore = true;
      _items.clear();
    });
    await _loadMore();
  }

  Future<void> _loadMore() async {
    if (!_canLoadMore || _loading) return;
    setState(() => _loading = true);
    try {
      final batch = await repo.list(page: _page, limit: 20);
      setState(() {
        _items.addAll(batch);
        _canLoadMore = batch.isNotEmpty;
        if (_canLoadMore) _page++;
      });
    } catch (e) {
      if (mounted) {
        ScaffoldMessenger.of(
          context,
        ).showSnackBar(const SnackBar(content: Text('Ошибка загрузки')));
      }
    } finally {
      if (mounted) setState(() => _loading = false);
    }
  }

  Future<void> _createNoteDialog() async {
    String title = '';
    String body = '';

    final result = await showDialog<bool>(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Создать запись'),
          content: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              TextField(
                decoration: const InputDecoration(labelText: 'Заголовок'),
                onChanged: (value) => title = value,
              ),
              TextField(
                decoration: const InputDecoration(labelText: 'Текст'),
                maxLines: 3,
                onChanged: (value) => body = value,
              ),
            ],
          ),
          actions: [
            TextButton(
              onPressed: () => Navigator.pop(context, false),
              child: const Text('Отмена'),
            ),
            ElevatedButton(
              onPressed: () => Navigator.pop(context, true),
              child: const Text('Создать'),
            ),
          ],
        );
      },
    );

    if (result == true && title.isNotEmpty && body.isNotEmpty) {
      try {
        final newNote = await repo.create(title, body);
        setState(() => _items.insert(0, newNote));
        ScaffoldMessenger.of(
          context,
        ).showSnackBar(const SnackBar(content: Text('Запись создана')));
      } catch (e) {
        ScaffoldMessenger.of(
          context,
        ).showSnackBar(const SnackBar(content: Text('Ошибка при создании')));
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('API Notes Feed')),
      floatingActionButton: FloatingActionButton(
        onPressed: _createNoteDialog,
        child: const Icon(Icons.add),
      ),
      body: RefreshIndicator(
        onRefresh: _refresh,
        child: _items.isEmpty && _loading
            ? const Center(child: CircularProgressIndicator())
            : ListView.separated(
                padding: const EdgeInsets.all(12),
                itemCount: _items.length + 1,
                separatorBuilder: (_, __) => const SizedBox(height: 8),
                itemBuilder: (context, i) {
                  if (i == _items.length) {
                    if (_canLoadMore) {
                      WidgetsBinding.instance.addPostFrameCallback(
                        (_) => _loadMore(),
                      );
                      return const Center(
                        child: Padding(
                          padding: EdgeInsets.all(16),
                          child: CircularProgressIndicator(),
                        ),
                      );
                    }
                    return const SizedBox.shrink();
                  }
                  final n = _items[i];
                  return Card(
                    child: ListTile(
                      title: Text(
                        n.title,
                        maxLines: 1,
                        overflow: TextOverflow.ellipsis,
                      ),
                      subtitle: Text(
                        n.body,
                        maxLines: 2,
                        overflow: TextOverflow.ellipsis,
                      ),
                      onTap: () => Navigator.push(
                        context,
                        MaterialPageRoute(
                          builder: (_) => NoteDetailsPage(id: n.id, repo: repo),
                        ),
                      ),
                      trailing: IconButton(
                        icon: const Icon(Icons.delete_outline),
                        onPressed: () async {
                          final n = _items[i];
                          try {
                            await repo.delete(n.id);
                            setState(() => _items.removeAt(i));
                            ScaffoldMessenger.of(context).showSnackBar(
                              const SnackBar(content: Text('Запись удалена')),
                            );
                          } catch (e) {
                            ScaffoldMessenger.of(context).showSnackBar(
                              const SnackBar(
                                content: Text('Ошибка при удалении'),
                              ),
                            );
                          }
                        },
                      ),
                    ),
                  );
                },
              ),
      ),
    );
  }
}
