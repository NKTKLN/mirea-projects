using System;

class NumberReversal
{
    static void Main()
    {
        Console.Write("Введите число: ");
        int number = int.Parse(Console.ReadLine());

        Console.WriteLine($"Перевернутое число: {ReverseNumber(number)}");
    }

    static int ReverseNumber(int number, int reversed = 0)
    {
        if (number < 10)
        {
            return reversed * 10 + number % 10;
        }

        return ReverseNumber(number / 10, reversed * 10 + number % 10);
    }
}
