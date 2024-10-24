using System;

class CalendarProgram
{
    static void Main()
    {
        Console.Write("Введите номер дня недели, с которого начинается месяц (1-пн, ..., 7-вс): ");
        int firstDayOfWeek = int.Parse(Console.ReadLine());
        if (firstDayOfWeek < 1 || firstDayOfWeek > 7)
        {
            Console.WriteLine("Неверный номер дня недели");
            return;
        }

        Console.Write("Введите день месяца (1-31): ");
        int dayOfMonth = int.Parse(Console.ReadLine());
        if (dayOfMonth < 1 || dayOfMonth > 31)
        {
            Console.WriteLine("Неверный день месяца");
            return;
        }

        int dayOfWeek = (firstDayOfWeek + (dayOfMonth - 1)) % 7;
        if (dayOfMonth <= 5 || (dayOfMoynth >= 8 && dayOfMonth <= 10) || dayOfWeek == 6 || dayOfWeek == 0)
            Console.WriteLine("Выходной день");
        else Console.WriteLine("Рабочий день");
    }
}
