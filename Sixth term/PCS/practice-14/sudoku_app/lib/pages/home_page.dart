import 'package:flutter/material.dart';
import 'leaderboard_page.dart';
import 'sudoku_page.dart';
import '../utils/validation.dart';

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  Widget _buildEnterNameDialog(BuildContext context) {
    final cs = Theme.of(context).colorScheme;

    String username = "";
    String? errorText;

    final controller = TextEditingController();

    return StatefulBuilder(
      builder: (context, setState) {
        void validate(String value) {
          username = value;
          errorText = validateUsername(username);
          setState(() {});
        }

        return AlertDialog(
          backgroundColor: cs.surfaceContainerHighest,
          title: const Text("Введите имя"),
          content: TextField(
            controller: controller,
            style: const TextStyle(color: Color(0xFFEDEDED)),
            cursorColor: cs.primary,
            onChanged: validate,
            decoration: InputDecoration(labelText: "Имя", errorText: errorText),
          ),
          actions: [
            const TextButton(onPressed: null, child: Text("Отмена")),
            ElevatedButton(
              onPressed: errorText != null || username.isEmpty
                  ? null
                  : () {
                      Navigator.pop(context);
                      Navigator.push(
                        context,
                        MaterialPageRoute(
                          builder: (_) => SudokuPage(
                            isRecordMode: true,
                            username: username,
                          ),
                        ),
                      );
                    },
              child: const Text("Начать"),
            ),
          ],
        );
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    // throw Exception("Тестовая ошибка в UI — проверка ErrorWidget.builder");

    return Scaffold(
      body: Center(
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 30),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                "Sudoku",
                style: Theme.of(
                  context,
                ).textTheme.titleLarge?.copyWith(fontSize: 42),
              ),
              const SizedBox(height: 40),

              MenuButton(
                text: "Обычная игра",
                onTap: () {
                  Navigator.push(
                    context,
                    MaterialPageRoute(
                      builder: (_) => const SudokuPage(isRecordMode: false),
                    ),
                  );
                },
              ),

              const SizedBox(height: 16),

              MenuButton(
                text: "Играть на рекорд",
                onTap: () {
                  showDialog(
                    context: context,
                    builder: (_) => _buildEnterNameDialog(context),
                  );
                },
              ),

              const SizedBox(height: 16),

              MenuButton(
                text: "Лидерборд",
                onTap: () {
                  Navigator.push(
                    context,
                    MaterialPageRoute(builder: (_) => const LeaderboardPage()),
                  );
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}

class MenuButton extends StatelessWidget {
  final String text;
  final VoidCallback onTap;

  const MenuButton({super.key, required this.text, required this.onTap});

  @override
  Widget build(BuildContext context) {
    final cs = Theme.of(context).colorScheme;

    return SizedBox(
      width: double.infinity,
      child: OutlinedButton(
        style: OutlinedButton.styleFrom(
          foregroundColor: cs.primary,
          side: BorderSide(color: cs.primary, width: 1.5),
        ),
        onPressed: onTap,
        child: Text(text),
      ),
    );
  }
}
