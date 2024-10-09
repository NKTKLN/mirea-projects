using System;

public class Reservation 
{
    public int ClientId { get; private set; }
    public string ClientName { get; private set; }
    public string ClientPhone { get; private set; }
    public int StartHour { get; private set; }
    public int EndHour { get; private set; }
    public string Comment { get; private set; }
    public Table AssignedTable { get; private set; }

    public Reservation(int clientId, string clientName, string clientPhone, int startHour, int endHour, string comment, Table table)
    {
        ClientId = clientId;
        ClientName = clientName;
        ClientPhone = clientPhone;
        StartHour = startHour;
        EndHour = endHour;
        Comment = comment;
        AssignedTable = table;

        table.Reserve(startHour, endHour, this);
    }

    public void UpdateBooking(int startHour, int endHour, string comment, Table table)
    {
        AssignedTable.Release(StartHour, EndHour);
        
        StartHour = startHour;
        EndHour = endHour;
        AssignedTable = table;
        Comment = comment;

        AssignedTable.Reserve(StartHour, EndHour, this);
    }

    ~Reservation()
    {
        AssignedTable.Release(StartHour, EndHour);
    }
}
