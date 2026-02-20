import 'dart:math';

class SudokuLogic {
  static List<List<int>> _generateSolvedBoard() {
    final board = List.generate(9, (_) => List.filled(9, 0));
    _solve(board);
    return board;
  }

  static bool _solve(List<List<int>> board) {
    for (int r = 0; r < 9; r++) {
      for (int c = 0; c < 9; c++) {
        if (board[r][c] == 0) {
          for (int n = 1; n <= 9; n++) {
            if (isValid(board, r, c, n)) {
              board[r][c] = n;
              if (_solve(board)) return true;
              board[r][c] = 0;
            }
          }
          return false;
        }
      }
    }
    return true;
  }

  static bool isValid(List<List<int>> board, int r, int c, int n) {
    for (int i = 0; i < 9; i++) {
      if (board[r][i] == n) return false;
      if (board[i][c] == n) return false;
    }

    final br = (r ~/ 3) * 3;
    final bc = (c ~/ 3) * 3;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[br + i][bc + j] == n) return false;
      }
    }
    return true;
  }

  static List<List<int>> generatePuzzle({int removeCount = 50}) {
    final solved = _generateSolvedBoard();
    final puzzle = solved.map((row) => List<int>.from(row)).toList();

    final rnd = Random();
    int removed = 0;

    while (removed < removeCount) {
      int r = rnd.nextInt(9);
      int c = rnd.nextInt(9);
      if (puzzle[r][c] != 0) {
        puzzle[r][c] = 0;
        removed++;
      }
    }

    return puzzle;
  }

  static List<List<int>> generatePuzzleCompute(int removeCount) {
    return generatePuzzle(removeCount: removeCount);
  }

  static bool isCompleted(List<List<int>> board) {
    for (final row in board) {
      if (row.contains(0)) return false;
    }
    return true;
  }
}
