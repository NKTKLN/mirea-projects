import 'package:flutter/material.dart';
import '../data/leaderboard_repository.dart';
import '../data/api_client.dart';
import '../models/score.dart';

class LeaderboardPage extends StatefulWidget {
  const LeaderboardPage({super.key});

  @override
  State<LeaderboardPage> createState() => _LeaderboardPageState();
}

class _LeaderboardPageState extends State<LeaderboardPage> {
  final repo = LeaderboardRepository(
    ApiClient(baseUrl: "https://6920348231e684d7bfcc1628.mockapi.io"),
  );

  List<Score> scores = [];
  bool loading = true;

  @override
  void initState() {
    super.initState();
    load();
  }

  Future<void> load() async {
    scores = await repo.list();
    setState(() => loading = false);
  }

  @override
  Widget build(BuildContext context) {
    final cs = Theme.of(context).colorScheme;

    return Scaffold(
      appBar: AppBar(title: const Text("Лидерборд")),
      body: loading
          ? const Center(child: CircularProgressIndicator())
          : ListView.builder(
              itemCount: scores.length,
              itemExtent: 64,
              itemBuilder: (_, i) {
                final s = scores[i];

                return ListTile(
                  key: ValueKey(s.id),
                  title: Text(s.name, style: TextStyle(color: cs.onSurface)),
                  subtitle: Text(
                    "Время: ${s.time} сек",
                    style: TextStyle(color: cs.onSurface.withValues(alpha: 0.6)),
                  ),
                  trailing: Text(
                    "#${i + 1}",
                    style: TextStyle(color: cs.primary),
                  ),
                );
              },
            ),
    );
  }
}
