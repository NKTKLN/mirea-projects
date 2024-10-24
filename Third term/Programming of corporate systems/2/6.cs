using System;

class BacteriaExperiment
{
    static void Main()
    {
        Console.Write("Введите количество бактерий: ");
        int bacteria = int.Parse(Console.ReadLine());

        Console.Write("Введите количество капель антибиотика: ");
        int drops = int.Parse(Console.ReadLine());

        int hour = 1;

        while (bacteria > 0 && hour <= 11)
        {
            bacteria *= 2;

            int killedBacteria = (11 - hour) * drops;
            bacteria -= killedBacteria;

            Console.WriteLine($"После {hour} часа бактерий осталось: {Math.Max(bacteria, 0)}");

            hour++;
        }

        if (bacteria <= 0)
        {
            Console.WriteLine("Все бактерии уничтожены.");
        }
        else
        {
            Console.WriteLine("Антибиотик больше не эффективен.");
        }
    }
}
