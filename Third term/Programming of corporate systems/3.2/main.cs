using System;

class BookingSystem
{
    private Table[] tables;
    private Reservation[] reservations;

    public BookingSystem()
    {
        tables = new Table[100];
        reservations = new Reservation[300];

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
    }

    static void Main()
    {
        BookingSystem bookingSystem = new BookingSystem();

        Console.WriteLine("\nИнформация о столе 1:");
        bookingSystem.tables[0].PrintInfo();
        bookingSystem.tables[0].UpdateInfo("у окна с видом", 5);

        Console.WriteLine("\nПосле изменения информации о столе 1:");
        bookingSystem.tables[0].PrintInfo();

        Console.WriteLine("\nОсвобождение брони на столе 1 с 10 до 12:");
        bookingSystem.tables[0].Release(10, 12);
        bookingSystem.tables[0].PrintInfo();

        try
        {
            Console.WriteLine("\nПробуем сделать новую бронь на время, когда стол уже занят:");
            bookingSystem.reservations[2] = new Reservation(3, "Сидоров Сидор", "81234567890", 11, 14, "Обед", bookingSystem.tables[0]);
            bookingSystem.tables[0].Reserve(11, 14, bookingSystem.reservations[2]);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }

        Console.WriteLine("\nИнформация о всех столах:");
        for (int i = 0; i < bookingSystem.tables.Length; i++)
        {
            if (bookingSystem.tables[i] != null)
            {
                bookingSystem.tables[i].PrintInfo();
                Console.WriteLine();
            }
        }

        try
        {
            Console.WriteLine("\nПробуем освободить стол с некорректными часами:");
            bookingSystem.tables[0].Release(25, 30);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }

        Console.WriteLine("\nДоступные столы:");
        bookingSystem.DisplayAvailableTables("у окна", 4);

        Console.WriteLine("\nВсе бронирования:");
        bookingSystem.DisplayAllReservations();

        Console.WriteLine("\nПоиск бронирования по последним цифрам номера телефона и имени клиента:");
        bookingSystem.SearchReservation("7890", "Иванов Иван");
    }

    public void DisplayAvailableTables(string location, int seats)
    {
        foreach (var table in tables)
        {
            if (table != null && table.Location == location && table.Seats == seats)
            {
                table.PrintInfo();
            }
        }
    }

    public void DisplayAllReservations()
    {
        foreach (var reservation in reservations)
        {
            if (reservation != null)
            {
                reservation.PrintInfo();
            }
        }
    }

    public void SearchReservation(string phoneLast4Digits, string clientName)
    {
        foreach (var reservation in reservations)
        {
            if (reservation != null && reservation.ClientName == clientName && reservation.ClientPhone.EndsWith(phoneLast4Digits))
            {
                reservation.PrintInfo();
                return;
            }
        }
        Console.WriteLine("Бронирование не найдено.");
    }
}
