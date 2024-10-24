using System;

class GuessNumber
{
    static void Main()
    {
        int left = 0, right = 63;

        while (left < right)
        {
            int middle = (left + right) / 2;
            Console.Write($"Ваше число больше {middle}? (да-1, нет-0): ");
            int answer = int.Parse(Console.ReadLine());

            if (answer == 1)
            {
                left = middle + 1;
            }
            else
            {
                right = middle;
            }
        }

        Console.WriteLine($"Ваше число: {left}");
    }
}
