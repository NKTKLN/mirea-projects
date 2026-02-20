import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';
import '../widgets/sudoku_grid.dart';
import '../logic/sudoku_logic.dart';
import '../data/leaderboard_repository.dart';
import '../data/api_client.dart';

class SudokuPage extends StatefulWidget {
  final bool isRecordMode;
  final String? username;

  const SudokuPage({super.key, required this.isRecordMode, this.username});

  @override
  State<SudokuPage> createState() => _SudokuPageState();
}

class _SudokuPageState extends State<SudokuPage> {
  List<List<int>>? board;
  List<List<int>>? puzzle;

  late Stopwatch stopwatch;
  Timer? timer;
  int elapsedSeconds = 0;

  int? selectedR;
  int? selectedC;
  int? selectedNumber;

  final repo = LeaderboardRepository(
    ApiClient(baseUrl: "https://6920348231e684d7bfcc1628.mockapi.io"),
  );

  @override
  void initState() {
    super.initState();
    initPuzzle();
  }

  Future<void> initPuzzle() async {
    final generated = await compute(
      SudokuLogic.generatePuzzleCompute,
      50,
    ); // ISOLATE

    puzzle = generated;
    board = generated.map((row) => List<int>.from(row)).toList();

    stopwatch = Stopwatch()..start();

    timer = Timer.periodic(const Duration(seconds: 1), (_) {
      setState(() {
        elapsedSeconds = stopwatch.elapsed.inSeconds;
      });
    });

    setState(() {});
  }

  @override
  void dispose() {
    timer?.cancel();
    super.dispose();
  }

  String formatTime(int seconds) {
    final m = (seconds ~/ 60).toString().padLeft(2, '0');
    final s = (seconds % 60).toString().padLeft(2, '0');
    return "$m:$s";
  }

  void finishGame() async {
    stopwatch.stop();
    timer?.cancel();

    if (widget.isRecordMode && widget.username != null) {
      await repo.create(
        widget.username!,
        stopwatch.elapsed.inSeconds,
        "Medium",
      );
    }

    if (!mounted) return;

    showDialog(
      context: context,
      builder: (_) => AlertDialog(
        backgroundColor: Theme.of(context).colorScheme.surfaceContainerHighest,
        title: const Text("Победа!"),
        content: Text("Ваше время: ${formatTime(stopwatch.elapsed.inSeconds)}"),
        actions: [
          ElevatedButton(
            onPressed: () {
              Navigator.pop(context);
              Navigator.pop(context);
            },
            child: const Text("OK"),
          ),
        ],
      ),
    );
  }

  void onCellTap(int r, int c) {
    setState(() {
      selectedR = r;
      selectedC = c;

      if (selectedNumber != null) placeNumber();
    });
  }

  void placeNumber() {
    if (selectedR == null || selectedC == null || selectedNumber == null) {
      return;
    }

    final r = selectedR!;
    final c = selectedC!;

    if (puzzle![r][c] != 0) return;

    setState(() {
      board![r][c] = selectedNumber!;
      selectedR = null;
      selectedC = null;
    });

    if (SudokuLogic.isCompleted(board!)) {
      finishGame();
    }
  }

  void onNumberSelect(int number) {
    setState(() => selectedNumber = number);

    if (selectedR != null && selectedC != null) {
      placeNumber();
    }
  }

  @override
  Widget build(BuildContext context) {
    if (board == null) {
      return const Scaffold(body: Center(child: CircularProgressIndicator()));
    }

    final cs = Theme.of(context).colorScheme;

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.isRecordMode ? "Игра на рекорд" : "Судоку"),
        actions: [
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 16),
            child: Center(
              child: Text(
                formatTime(elapsedSeconds),
                style: const TextStyle(fontSize: 20),
              ),
            ),
          ),
        ],
      ),

      body: Column(
        children: [
          const SizedBox(height: 16),

          SudokuGrid(
            board: board!,
            puzzle: puzzle!,
            selectedRow: selectedR,
            selectedCol: selectedC,
            selectedNumber: selectedNumber,
            onCellTap: onCellTap,
          ),

          const Spacer(),
          const SizedBox(height: 12),

          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: List.generate(5, (i) => _numberButton(i + 1, cs)),
          ),

          const SizedBox(height: 12),

          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: [
              for (int n = 6; n <= 9; n++) _numberButton(n, cs),
              ElevatedButton(
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.redAccent,
                  foregroundColor: Colors.white,
                ),
                onPressed: () {
                  setState(() => selectedNumber = 0);
                },
                child: const Text("X"),
              ),
            ],
          ),

          const SizedBox(height: 24),
        ],
      ),
    );
  }

  Widget _numberButton(int n, ColorScheme cs) {
    final isSelected = selectedNumber == n;

    return ElevatedButton(
      style: ElevatedButton.styleFrom(
        backgroundColor: isSelected ? cs.primary : cs.surface,
        foregroundColor: isSelected ? Colors.black : cs.primary,
        padding: const EdgeInsets.symmetric(vertical: 14, horizontal: 20),
      ),
      onPressed: () => onNumberSelect(n),
      child: Text("$n", style: const TextStyle(fontSize: 20)),
    );
  }
}
