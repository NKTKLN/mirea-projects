import 'package:flutter/material.dart';

class SudokuGrid extends StatelessWidget {
  final List<List<int>> board;
  final List<List<int>> puzzle;

  final int? selectedRow;
  final int? selectedCol;
  final int? selectedNumber;

  final void Function(int r, int c) onCellTap;

  const SudokuGrid({
    super.key,
    required this.board,
    required this.puzzle,
    required this.selectedRow,
    required this.selectedCol,
    required this.selectedNumber,
    required this.onCellTap,
  });

  @override
  Widget build(BuildContext context) {
    final cs = Theme.of(context).colorScheme;

    return AspectRatio(
      aspectRatio: 1,
      child: Container(
        padding: const EdgeInsets.all(8),
        child: Column(
          children: List.generate(9, (r) {
            return Expanded(
              child: Row(
                children: List.generate(9, (c) {
                  final bool isSelected = selectedRow == r && selectedCol == c;
                  final bool isOriginal = puzzle[r][c] != 0;

                  final bool sameNumber =
                      selectedNumber != null &&
                      selectedNumber != 0 &&
                      board[r][c] == selectedNumber;

                  Color cellColor;
                  if (isSelected) {
                    cellColor = cs.primary.withValues(alpha: 0.40);
                  } else if (sameNumber) {
                    cellColor = cs.primary.withValues(alpha: 0.28);
                  } else if (isOriginal) {
                    cellColor = Colors.grey.shade900;
                  } else {
                    cellColor = const Color(0xFF111111);
                  }

                  return Expanded(
                    child: GestureDetector(
                      onTap: () => onCellTap(r, c),
                      child: Container(
                        margin: const EdgeInsets.all(2),
                        decoration: BoxDecoration(
                          borderRadius: BorderRadius.circular(14),
                          color: cellColor,
                          border: Border.all(
                            color: Colors.grey.shade800,
                            width: 1,
                          ),
                        ),
                        child: Stack(
                          children: [
                            // Толстая граница 3×3
                            Positioned.fill(
                              child: CustomPaint(
                                painter: _ThickBorderPainter(
                                  r: r,
                                  c: c,
                                  color: cs.primary,
                                ),
                              ),
                            ),

                            Center(
                              child: Text(
                                board[r][c] == 0 ? "" : "${board[r][c]}",
                                style: TextStyle(
                                  fontSize: 26,
                                  fontWeight: isOriginal
                                      ? FontWeight.w700
                                      : FontWeight.w400,
                                  color: isOriginal
                                      ? Colors.white70
                                      : Colors.white,
                                ),
                              ),
                            ),
                          ],
                        ),
                      ),
                    ),
                  );
                }),
              ),
            );
          }),
        ),
      ),
    );
  }
}

class _ThickBorderPainter extends CustomPainter {
  final int r;
  final int c;
  final Color color;

  _ThickBorderPainter({required this.r, required this.c, required this.color});

  @override
  void paint(Canvas canvas, Size size) {
    final paint = Paint()
      ..color = color.withValues(alpha: 0.5)
      ..strokeWidth = 2;

    if (c == 0 || c == 3 || c == 6) {
      canvas.drawLine(Offset(0, 0), Offset(0, size.height), paint);
    }
    if (c == 8) {
      canvas.drawLine(
        Offset(size.width, 0),
        Offset(size.width, size.height),
        paint,
      );
    }

    if (r == 0 || r == 3 || r == 6) {
      canvas.drawLine(Offset(0, 0), Offset(size.width, 0), paint);
    }
    if (r == 8) {
      canvas.drawLine(
        Offset(0, size.height),
        Offset(size.width, size.height),
        paint,
      );
    }
  }

  @override
  bool shouldRepaint(_) => false;
}
