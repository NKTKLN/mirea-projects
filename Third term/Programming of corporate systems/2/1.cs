using System;

class MaclaurinSeries
{
    static void Main()
    {
        Console.WriteLine("0 - Вычисление значения функции с заданной точностью");
        Console.WriteLine("1 - Вычисление n-го члена ряда");
        Console.Write("Выберите режим работы: ");
        int choice = int.Parse(Console.ReadLine());

        Console.Write("Введите x (-1 < x <= 1): ");
        double x = double.Parse(Console.ReadLine());

        int n_max = 1;
        double e = 0.05;

        switch (choice)
        {
            case 0:
                Console.Write("Введите точность e (e < 0.01): ");
                e = double.Parse(Console.ReadLine());
                break;

            case 1:
                Console.Write("Введите номер члена ряда n (n > 0): ");
                n_max = int.Parse(Console.ReadLine());
                break;
        }

        double result = 0;
        double term;
        int n = 1;

        while (true)
        {
            term = Math.Pow(-1, n + 1) * Math.Pow(x, n) / n;
            if ((choice == 0 && Math.Abs(term) > e) || (choice == 1 && n <= n_max))
            {
              break;
            }
            result += term;
            n++;
        }

        Console.WriteLine($"Значение функции f(x): {result}");
    }
}
