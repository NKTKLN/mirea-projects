using System;

public class Product
{
    public int Id { get; private set; }
    public int SupplierId  { get; private set; }
    public string Name { get; private set; }
    public decimal ItemVolume  { get; private set; }
    public decimal ItemPrice { get; private set; }
    public int ExpirationDays  { get; private set; }

    public Product(int id, int supplierId, string name, decimal itemVolume, decimal itemPrice, int expirationDays)
    {
        Id = id;
        SupplierId = supplierId;
        Name = name;
        ItemVolume = itemVolume;
        ItemPrice = itemPrice;
        ExpirationDays = expirationDays;
    }

    public void EditProduct(int supplierId, string name, decimal itemVolume, decimal itemPrice, int expirationDays)
    {
        SupplierId = supplierId;
        Name = name;
        ItemVolume = itemVolume;
        ItemPrice = itemPrice;
        ExpirationDays = expirationDays;
    }

    public void PrintInfo()
    {
        Console.WriteLine($"Id: {Id}");
        Console.WriteLine($"Id Поставщика: {SupplierId}");
        Console.WriteLine($"Название: {Name}");
        Console.WriteLine($"Объем одной единицы товара: {ItemVolume}");
        Console.WriteLine($"Цена одной единицы товара: {ItemPrice}");
        Console.WriteLine($"Количество дней до окончания срока годности: {ExpirationDays}");
    }

    public void DeleteProduct()
    {
        Id = 0;
        SupplierId = 0;
        Name = "";
        ItemVolume = 0;
        ItemPrice = 0;
        ExpirationDays = 0;
    }
}
