/*
Описание программного продукта

1) Функционал

Калькулятор предоставляет пользователям возможность выполнять базовые арифметические операции,
а также использовать функции для работы с памятью и дополнительными вычислениями.
Возможности калькулятора включают:

Арифметические операции:
  - Сложение (+)
  - Вычитание (-)
  - Умножение (*)
  - Деление (/)
  - Процент от числа (%)
  - Возведение в степень (^)
  - Квадратный корень (sqrt)
  - Обратное значение (1/)
  - Возведение в квадрат (^2)

Функции работы с памятью:
  - m+ — добавление текущего результата в память
  - m- — вычитание текущего результата из памяти
  - ms — сохранение текущего результата в память
  - mc — очистка памяти
  - mr — вывод сохранённого значения из памяти
  - c — сброс текущего результата

2) Ограничения

Числовые ограничения:
  - При выполнении операции квадратного корня (sqrt), число должно быть неотрицательным.
  - При вычислении обратного значения (1/), делитель не должен быть равен нулю.
  - При вычислении опраций деления, остатка от деления и обратного значения (/, %, 1/),
    делитель не должен быть равен нулю.

Операции:
  - Калькулятор поддерживает только указанные операции и функции.
  - Не предусмотрены расширенные математические функции (тригонометрические, логарифмические и др.).

Ввод данных:
  - Вводимые данные должны быть числовыми, неверный формат приводит к ошибкам.
  - Программа не обрабатывает некорректные или неподдерживаемые команды.

3) Возможные ошибки

Формат ввода:
  - Неверный формат числа: Появляется при вводе данных, которые не могут быть преобразованы в число.

Математические ошибки:
  - Отрицательное число: Появляется при попытке вычислить квадратный корень от отрицательного числа.
  - Деление на 0: Происходит при попытке деления на ноль или вычислении остатка от деления на ноль.

Неподдерживаемая операция:
  - Появляется, если пользователь вводит операцию, которая не поддерживается калькулятором.
*/

using System;

class Calculator
{
    static double memory = 0;
    static double lastResult = 0;

    static void Main()
    {
        Console.WriteLine("Калькулятор\n\nКоманды: +, -, *, /, %, ^, sqrt, 1/, ^2\nФункции: m+, m-, ms, mc, mr, c, ce\nДля выхода используйте 'exit'\n");

        while (true)
        {
            Console.Write(":> ");
            string userInput = Console.ReadLine().Trim().ToLower();

            if (userInput == "exit") break;

            if (ProcessFunction(userInput)) continue;

            try
            {
                double result = Calculate(userInput);
                lastResult = result;
                Console.WriteLine($"Результат: {result}");
            }
            catch (Exception exception)
            {
                Console.WriteLine($"Ошибка: {exception.Message}");
            }
        }
    }

    static bool ProcessFunction(string command)
    {
        switch (command)
        {
            case "m+":
                memory += lastResult;
                Console.WriteLine($"M+: {memory}");
                return true;
            case "m-":
                memory -= lastResult;
                Console.WriteLine($"M-: {memory}");
                return true;
            case "ms":
                memory = lastResult;
                Console.WriteLine($"MS: {memory}");
                return true;
            case "mc":
                memory = 0;
                Console.WriteLine("MC: память очищена");
                return true;
            case "mr":
                Console.WriteLine($"MR: {memory}");
                return true;
            case "c":
                lastResult = 0;
                Console.WriteLine("C: сброс");
                return true;
            default:
                return false;
        }
    }

    static double Calculate(string operation)
    {
        double first = ReadNumber("First");

        switch (operation)
        {
            case "sqrt" when first >= 0: return Math.Sqrt(first);
            case "sqrt": throw new ArgumentException("Отрицательное число");
            case "1/" when first != 0: return 1 / first;
            case "1/": throw new DivideByZeroException("Делить на 0 нельзя");
            case "^2": return Math.Pow(first, 2);
        }

        double second = ReadNumber("Second");

        switch (operation)
        {
            case "+": return first + second;
            case "-": return first - second;
            case "*": return first * second;
            case "%": return second * first / 100;
            case "^": return Math.Pow(first, second);
            case "/" when second != 0: return first / second;
            case "/": throw new DivideByZeroException("Делить на 0 нельзя");
            default: throw new ArgumentException("Неподдерживаемая операция");
        }
    }

    static double ReadNumber(string prompt)
    {
        Console.Write($"{prompt} :> ");
        if (double.TryParse(Console.ReadLine().Trim(), out double value)) return value;
        throw new FormatException("Неверный формат числа");
    }
}
