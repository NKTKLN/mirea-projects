using System;

class BookingSystem
{
    private static Table[] tables;
    private static Reservation[] reservations;

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
        PrintTableById(1);
    }

    public static void CreateNTables(int count)
    {
        for (int n = 0; n < count; n++)
        {
            tables[n] = new Table(n, "", n);
        }
    }

    public static void CreateNReservations(int count)
    {   
        int h = 0;
        for (int n = 0; n < count; n++)
        {
            reservations[n] = new Reservation(n, "Петров Петр", "8987654321", h, h+1, "", tables[n]);
            h += 2;
        }
    }

    public static void UpdateTableById(int tableId, string location, int seatsCount)
    {
        foreach (var table in tables)
        {
            if (table != null && table.Id == tableId)
            {
                table.UpdateInfo(location, seatsCount);
                return;
            }
        }
    }

    public static void PrintTableById(int tableId)
    {
        foreach (var table in tables)
        {
            if (table != null && table.Id == tableId)
            {
                table.PrintInfo();
                return;
            }
        }
    }

    public static void DisplayAvailableTablesByLocations(string location)
    {
        foreach (var table in tables)
        {
            if (table != null && table.Location == location)
            {
                table.PrintInfo();
                Console.WriteLine();
            }
        }
    }

    public static void DisplayAvailableTablesBySeats(int seats)
    {
        foreach (var table in tables)
        {
            if (table != null && table.SeatsCount == seats)
            {
                table.PrintInfo();
                Console.WriteLine();
            }
        }
    }

    public static void DisplayAllReservations()
    {
        foreach (var reservation in reservations)
        {
            if (reservation != null)
            {
                reservation.PrintInfo();
                Console.WriteLine();
            }
        }
    }

    public static void SearchReservation(string phoneLast4Digits, string clientName)
    {
        foreach (var reservation in reservations)
        {
            if (reservation != null && reservation.ClientName == clientName && reservation.ClientPhone.EndsWith(phoneLast4Digits))
            {
                reservation.PrintInfo();
            }
        }
        Console.WriteLine("Бронирование не найдено.");
    }
}
