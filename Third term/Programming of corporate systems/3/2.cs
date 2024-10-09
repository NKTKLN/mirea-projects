using System;

class AckermanFunction
{
    static void Main()
    {
        Console.Write("Введите число m: ");
        int m = int.Parse(Console.ReadLine());
        Console.Write("Введите число n: ");
        int n = int.Parse(Console.ReadLine());

        Console.WriteLine($"Вывод: {Ackerman(m, n)}");
    }

    static int Ackerman(int m, int n)
    {
        if (m == 0)
        {
            return n + 1;
        }
        if (n == 0)
        {
            return Ackerman(m - 1, 1);
        }
        
        return Ackerman(m - 1, Ackerman(m, n - 1));
    }
}
