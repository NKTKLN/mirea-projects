using System;

public class Table 
{
    public int Id { get; private set; }
    public string Location { get; private set; }
    public int SeatsCount { get; private set; }
    private Reservation[] Availability;

    public Table(int id, string location, int seatsCount)
    {
        if (seatsCount <= 0)
        {
            throw new Exception("Некорректное колличество мест.");
        }

        Id = id;
        Location = location;
        SeatsCount = seatsCount;

        Availability = new Reservation[24];
    }

    public void UpdateInfo(string location, int seatsCount)
    {
        if (seatsCount <= 0)
        {
            throw new Exception("Некорректное колличество мест.");
        }

        Location = location;
        SeatsCount = seatsCount;
    }

    public void Reserve(int startHour, int endHour, Reservation reservation)
    {
        if (startHour < 0 || startHour >= 24 || endHour < 0 || endHour >= 24 || startHour >= endHour)
        {
            throw new Exception("Некорректный час.");
        }

        for (int hour = startHour; hour < endHour; hour++)
        {
            if (Availability[hour] != null)
            {
                throw new Exception("Стол уже занят в это время.");
            }
        }

        for (int hour = startHour; hour < endHour; hour++)
        {
            Availability[hour] = reservation;
        }
    }

    public void Release(int startHour, int endHour)
    {
        if (startHour < 0 || startHour >= 24 || endHour < 0 || endHour >= 24 || startHour >= endHour)
        {
            throw new Exception("Некорректный час.");
        }

        for (int hour = startHour; hour < endHour; hour++)
        {
            Availability[hour] = null;
        }
    }

    public void PrintInfo()
    {
        Console.WriteLine($"ID: {Id}.");
        Console.WriteLine($"Расположение: {Location}.");
        Console.WriteLine($"Количество мест: {SeatsCount}.");
        Console.WriteLine("Расписание:");
        for (int hour = 0; hour < 24; hour++)
        {
            string clientData = "";
            if (Availability[hour] != null)
            {
                clientData = $"ID: {Availability[hour].ClientId}, {Availability[hour].ClientName}, {Availability[hour].ClientPhone}";
            }
            Console.WriteLine($"  * {hour:D2}:00-{((hour+1) % 24):D2}:00 {clientData}");
        }
    }
}
