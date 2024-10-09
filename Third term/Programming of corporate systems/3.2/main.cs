using System;
using System.Collections.Generic;

class BookingSystem 
{
    static void Main()
    {
        Table[] tables = new Table[6];
        Reservation[] reservations = new Reservation[6];

        tables[0] = new Table(1, "у окна", 4);
        tables[1] = new Table(2, "у прохода", 2);
        tables[2] = new Table(3, "у выхода", 6);
        tables[3] = new Table(4, "в глубине", 3);
        tables[4] = new Table(5, "у окна", 2);
        tables[5] = new Table(6, "у прохода", 4);

        try
        {
            reservations[0] = new Reservation(1, "Иванов Иван", "8234567890", 10, 12, "Деловая встреча", tables[0]);

            reservations[1] = new Reservation(2, "Петров Петр", "8987654321", 13, 17, "Обед", tables[0]);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }

        Console.WriteLine("\nИнформация о столе 1:");
        tables[0].PrintInfo();

        tables[0].UpdateInfo("у окна с видом", 5);
        Console.WriteLine("\nПосле изменения информации о столе 1:");
        tables[0].PrintInfo();

        Console.WriteLine("\nОсвобождение брони на столе 1 с 10 до 12:");
        tables[0].Release(10, 12);
        tables[0].PrintInfo();

        try
        {
            Console.WriteLine("\nПробуем сделать новую бронь на время, когда стол уже занят:");
            reservations[2] = new Reservation(3, "Сидоров Сидор", "81234567890", 11, 14, "Обед", tables[0]);
            tables[0].Reserve(11, 14, reservations[2]);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }

        Console.WriteLine("\nИнформация о всех столах:");
        for (int i = 0; i < tables.Length; i++)
        {
            tables[i].PrintInfo();
            Console.WriteLine();
        }

        try
        {
            Console.WriteLine("\nПробуем освободить стол с некорректными часами:");
            tables[0].Release(25, 30);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}
