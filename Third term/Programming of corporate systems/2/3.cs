using System;

class SimplifyFraction
{
    static void Main()
    {
        Console.Write("Введите числитель: ");
        int numerator = int.Parse(Console.ReadLine());

        Console.Write("Введите знаменатель: ");
        int denominator = int.Parse(Console.ReadLine());

        if (denominator == 0)
        {
            Console.WriteLine("Знаменатель не может быть равен 0.");
            return;
        }

        int gcd = GCD(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }

        Console.WriteLine($"Результат: {numerator} / {denominator}");
    }

    static int GCD(int a, int b)
    {
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}
