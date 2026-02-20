import 'package:flutter_test/flutter_test.dart';
import 'package:sudoku_app/utils/validation.dart';

void main() {
  group('Username validation', () {
    test('Пустая строка → ошибка', () {
      expect(validateUsername(""), "Имя не может быть пустым");
    });

    test('Одна буква → ошибка', () {
      expect(validateUsername("A"),
          "Разрешены только буквы и пробелы (мин. 2 символа)");
    });

    test('Цифры → ошибка', () {
      expect(validateUsername("John123"),
          "Разрешены только буквы и пробелы (мин. 2 символа)");
    });

    test('Спецсимволы → ошибка', () {
      expect(validateUsername("J@ne"),
          "Разрешены только буквы и пробелы (мин. 2 символа)");
    });

    test('Русские буквы → OK', () {
      expect(validateUsername("Анна"), null);
    });

    test('Английские буквы → OK', () {
      expect(validateUsername("Michael"), null);
    });

    test('С пробелом → OK', () {
      expect(validateUsername("Иван Петров"), null);
    });

    test('Два пробела подряд → ошибка', () {
      // Если хочешь, можно добавить отдельное правило
      expect(validateUsername("Иван  Петров"),
          "Разрешены только буквы и пробелы (мин. 2 символа)");
    });

    test('Пробел в начале → ошибка', () {
      expect(validateUsername(" Иван"),
          "Разрешены только буквы и пробелы (мин. 2 символа)");
    });

    test('Пробел в конце → ошибка', () {
      expect(validateUsername("Иван "),
          "Разрешены только буквы и пробелы (мин. 2 символа)");
    });
  });
}
