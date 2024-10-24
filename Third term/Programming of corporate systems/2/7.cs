using System;

class MarsColonization
{
    static void Main()
    {
        Console.Write("Введите количество модулей n: ");
        int n = int.Parse(Console.ReadLine());

        Console.Write("Введите ширину модуля a: ");
        int a = int.Parse(Console.ReadLine());

        Console.Write("Введите высоту модуля b: ");
        int b = int.Parse(Console.ReadLine());

        Console.Write("Введите ширину поля w: ");
        int w = int.Parse(Console.ReadLine());

        Console.Write("Введите высоту поля h: ");
        int h = int.Parse(Console.ReadLine());

        int d = 0;
        while ((a + 2 * d) * (b + 2 * d) * n <= w * h)
        {
            d++;
        }

        d--;

        Console.WriteLine($"Максимальная толщина защитного слоя d: {d}");
    }
}
