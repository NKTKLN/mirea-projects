using System;

class ATMProgram
{
    static void Main()
    {
        int[] banknotes = { 5000, 2000, 1000, 500, 200, 100 };

        Console.Write("Введите сумму, которую хотите обналичить: ");
        int amount = int.Parse(Console.ReadLine());

        if (amount > 150000)
        {
            Console.WriteLine("Cумма должна быть меньше 150 000 рублей");
            return;
        }

        if (amount % 100 != 0)
        {
            Console.WriteLine("Cумма должна быть кратна 100");
            return;
        }

        Console.WriteLine("Купюры:");
        foreach (int note in banknotes)
        {
            int count = amount / note;
            if (count > 0)
            {
                Console.WriteLine($"{count} - {note} руб");
                amount -= count * note;
            }
        }
    }
}
