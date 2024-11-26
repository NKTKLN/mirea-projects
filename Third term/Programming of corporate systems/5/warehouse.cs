using System;
using System.Collections.Generic;

public class Warehouse 
{
    public int Id { get; private set; }
    public string Type { get; private set; } // cold, sorting, general, disposal
    public decimal Capacity { get; private set; }
    public string Address { get; private set; }
    public List<Product> StoredProducts { get; set; }

    public Warehouse(int id, string type, decimal capacity, string address)
    {
        Id = id;
        Type = type;
        Capacity = capacity;
        Address = address;
        StoredProducts = new List<Product>();
    }

    public void EditWarehouse(string type, decimal capacity, string address)
    {
        Type = type;
        Capacity = capacity;
        Address = address;
    }

    public void PrintInfo()
    {
        Console.WriteLine($"Id: {Id}");
        Console.WriteLine($"Тип: {Type}");
        Console.WriteLine($"Объем склада: {Capacity}");
        Console.WriteLine($"Адрес: {Address}");
        Console.WriteLine("Хранимые товары:");

        foreach (Product product in StoredProducts)
        {
            product.PrintInfo();
        }
    }

    public decimal GetRemainingCapacity()
    {
        decimal usedCapacity = 0;
        foreach (var product in StoredProducts)
        {
            usedCapacity += product.ItemVolume;
        }

        return Capacity - usedCapacity;
    }

    public void AddProducts(List<Product> products)
    {
        if (products == null || products.Count == 0)
            throw new ArgumentException("Product list cannot be null or empty.");

        decimal totalRequiredCapacity = 0;
        foreach (var product in products)
        {
            totalRequiredCapacity += product.ItemVolume;
        }

        if (GetRemainingCapacity() < totalRequiredCapacity)
            throw new InvalidOperationException($"Not enough capacity in warehouse {Id} to add these products.");

        StoredProducts.AddRange(products);
    }

    public void RemoveProduct(int productId)
    {
        var productToRemove = StoredProducts.Find(p => p.Id == productId);
        if (productToRemove == null)
            throw new KeyNotFoundException($"Product with ID {productId} not found in warehouse {Id}.");

        StoredProducts.Remove(productToRemove);
    }
}
