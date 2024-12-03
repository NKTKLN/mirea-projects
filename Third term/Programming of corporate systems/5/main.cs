using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Тест 1: Поставка товаров. Вариант 1 (все товары подходят под склад общего типа)");
        var warehouseG = new Warehouse(1, "general", 3000, "GeneralWarehouse");
        var warehouseS = new Warehouse(2, "sorting", 3000, "SortingWarehouse");
        var warehouseC = new Warehouse(3, "cold", 1000, "ColdWarehouse");
        var warehouseD = new Warehouse(4, "disposal", 500, "DisposalWarehouse");
        var products = new List<Product>
        {
            new Product(1, 730, "Product1", 50, 100, 1024), // Срок годности больше 1024 дней
            new Product(2, 1024, "Product2", 40, 200, 1500)
        };

        var logisticsManager = new LogisticsManager(new List<Warehouse> { warehouseG, warehouseS, warehouseC, warehouseD });
        try
        {
            logisticsManager.ProcessDelivery(products);
            Console.WriteLine("Товары успешно добавлены на склад.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }

        Console.WriteLine("Тест 2: Поставка товаров. Вариант 2 (есть товар, требующий сортировочного склада)");
        products = new List<Product>
        {
            new Product(3, 230, "Product3", 30, 150, 12), // Требует сортировки
            new Product(4, 500, "Product4", 20, 100, 1500)
        };

        try
        {
            logisticsManager.ProcessDelivery(products);
            Console.WriteLine("Товары успешно добавлены на сортировочный склад.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }

        Console.WriteLine("Тест 3: Поставка товаров. Вариант 3 (товар с коротким сроком годности, нужен холодный склад)");
        products = new List<Product>
        {
            new Product(5, 101, "Product5", 10, 50, -1) // Просроченный товар
        };

        try
        {
            logisticsManager.ProcessDelivery(products);
            Console.WriteLine("Товары успешно добавлены на холодный склад.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }

        Console.WriteLine("Тест 4: Оптимизация складов");
        products = new List<Product>
        {
            new Product(6, 1020, "Product6", 10, 100, 12),
            new Product(7, 6020, "Product7", 20, 150, 100)
        };

        warehouseS.AddProducts(products);

        try
        {
            logisticsManager.InternalOptimize(1, 2, 3);
            Console.WriteLine("Оптимизация складов выполнена.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }

        Console.WriteLine("Тест 5: Анализ складской сети");
        products = new List<Product>
        {
            new Product(8, 105, "ExpiredProduct", 10, 200, -5) // Просроченный товар
        };

        warehouseG.AddProducts(products);

        logisticsManager.AnalyzeNetwork();

        Console.WriteLine("Тест 6: Перемещение товаров с истекшим сроком годности");
        try
        {
            logisticsManager.MoveExpiredProducts(1, 2, 3);
            Console.WriteLine("Просроченные товары успешно перемещены в утилизацию.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }

        Console.WriteLine("Тест 2: Поставка товаров. Вариант 2 (есть товар, требующий сортировочного склада)");
        
        products = new List<Product>
        {
            new Product(3, 230, "Product3", 30, 150, 12), // Требует сортировки
            new Product(4, 500, "Product4", 20, 100, 1500)
        };

        try
        {
            logisticsManager.ProcessDelivery(products);
            Console.WriteLine("Товары успешно добавлены на сортировочный склад.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }

        Console.WriteLine("Тест 4: Оптимизация складов");

        try
        {
            logisticsManager.InternalOptimize(1, 2, 3);
            Console.WriteLine("Оптимизация складов выполнена.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }

        Console.WriteLine("Тест 9: Подсчет стоимости товаров");
        
        try
        {
            var totalValue = logisticsManager.CalculateTotalValue(1);
            Console.WriteLine($"Общая стоимость товаров на складе: {totalValue}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
    }
}

