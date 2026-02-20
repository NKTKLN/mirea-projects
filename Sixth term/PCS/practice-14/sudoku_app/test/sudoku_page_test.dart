import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:sudoku_app/widgets/sudoku_grid.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  final initialBoard = List.generate(9, (r) => List.generate(9, (c) => 0));
  final puzzle = List.generate(9, (r) => List.generate(9, (c) => 0));

  testWidgets("Сетка 9×9 рендерится корректно", (tester) async {
    await tester.pumpWidget(
      MaterialApp(
        home: SudokuGrid(
          board: initialBoard,
          puzzle: puzzle,
          selectedRow: null,
          selectedCol: null,
          selectedNumber: null,
          onCellTap: (_, __) {},
        ),
      ),
    );

    final cells = find.byType(GestureDetector);
    expect(cells, findsNWidgets(81));
  });

  testWidgets("Тап по клетке вызывает onCellTap", (tester) async {
    int? tappedR;
    int? tappedC;

    await tester.pumpWidget(
      MaterialApp(
        home: SudokuGrid(
          board: initialBoard,
          puzzle: puzzle,
          selectedRow: null,
          selectedCol: null,
          selectedNumber: null,
          onCellTap: (r, c) {
            tappedR = r;
            tappedC = c;
          },
        ),
      ),
    );

    await tester.tap(find.byType(GestureDetector).at(10));
    await tester.pump();

    expect(tappedR, isNotNull);
    expect(tappedC, isNotNull);
  });

  testWidgets("Выбранная клетка выделяется цветом", (tester) async {
    await tester.pumpWidget(
      MaterialApp(
        home: SudokuGrid(
          board: initialBoard,
          puzzle: puzzle,
          selectedRow: 0,
          selectedCol: 0,
          selectedNumber: null,
          onCellTap: (_, __) {},
        ),
      ),
    );

    final firstCell = tester.firstWidget<Container>(
      find.descendant(
        of: find.byType(GestureDetector).first,
        matching: find.byType(Container),
      ),
    );

    final BoxDecoration? deco = firstCell.decoration as BoxDecoration?;
    expect(deco?.color, isNotNull);
  });

  testWidgets("Клетки с одинаковым числом выделяются (sameNumber)", (tester) async {
    final board = List.generate(9, (r) => List.generate(9, (c) => 0));
    board[0][0] = 5;
    board[0][1] = 5;

    await tester.pumpWidget(
      MaterialApp(
        home: SudokuGrid(
          board: board,
          puzzle: puzzle,
          selectedRow: null,
          selectedCol: null,
          selectedNumber: 5,
          onCellTap: (_, __) {},
        ),
      ),
    );

    final cell1 = tester.widget<Container>(
      find.descendant(
        of: find.byType(GestureDetector).at(0),
        matching: find.byType(Container),
      ),
    );

    final cell2 = tester.widget<Container>(
      find.descendant(
        of: find.byType(GestureDetector).at(1),
        matching: find.byType(Container),
      ),
    );

    final c1 = (cell1.decoration as BoxDecoration).color;
    final c2 = (cell2.decoration as BoxDecoration).color;

    expect(c1, equals(c2));
  });

  testWidgets("Оригинальные числа отображаются жирным шрифтом", (tester) async {
    final board = List.generate(9, (r) => List.generate(9, (c) => 0));
    final puzzleTest = List.generate(9, (r) => List.generate(9, (c) => 0));
    board[0][0] = 7;
    puzzleTest[0][0] = 7;

    await tester.pumpWidget(
      MaterialApp(
        home: SudokuGrid(
          board: board,
          puzzle: puzzleTest,
          selectedRow: null,
          selectedCol: null,
          selectedNumber: null,
          onCellTap: (_, __) {},
        ),
      ),
    );

    final text = tester.widget<Text>(
      find.descendant(
        of: find.byType(GestureDetector).first,
        matching: find.byType(Text),
      ),
    );

    expect(text.style?.fontWeight, FontWeight.w700);
  });
}
