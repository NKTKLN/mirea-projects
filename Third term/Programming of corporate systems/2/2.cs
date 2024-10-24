using System;

class LuckyTicket
{
    static void Main()
    {
        const int ticketLen = 6;

        Console.Write("Введите номер билета: ");
        int ticketNumber = int.Parse(Console.ReadLine());

        int firstSum = 0;
        int secondSum = 0;

        for (int i = 0; i < ticketLen; i++)
        {
            if (i < ticketLen / 2)
            {
                secondSum += ticketNumber % 10;
            }
            else
            {
                firstSum += ticketNumber % 10;
            }

            ticketNumber /= 10;
        }

        if (firstSum == secondSum)
        {
            Console.WriteLine("Счастливый билет.");
        }
        else
        {
            Console.WriteLine("Не счастливый билет.");
        }
    }
}
