using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        // Тест 1: Добавление товара в склад
        TestProcessDelivery();

        // Тест 2: Попытка доставки товаров в неподходящий склад
        TestProcessDeliveryNoSuitableWarehouse();

        // Тест 3: Оптимизация складов
        TestInternalOptimize();

        // Тест 4: Перемещение просроченных товаров на утилизацию
        TestMoveExpiredProducts();

        // Тест 5: Проверка ошибки при нехватке места на складе для просроченных товаров
        TestMoveExpiredProductsNotEnoughSpace();

        // Тест 6: Перемещение товаров между складами
        TestMoveProducts();
    }

    static void TestProcessDelivery()
    {
        Console.WriteLine("Тест 1: Добавление товара в склад");

        // Создаем склады и товары
        var warehouse = new Warehouse(1, "general", 1000, "Warehouse1");
        var product = new Product(1, 101, "Product1", 10, 100, 40);  // Долгий срок годности

        // Делаем поставку
        var delivery = new List<Product> { product };
        warehouse.AddProducts(delivery);

        var logisticsManager = new LogisticsManager(new List<Warehouse> { warehouse });

        try
        {
            logisticsManager.ProcessDelivery(delivery);
            Console.WriteLine("Поставка успешно добавлена на склад.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);
        }
    }

    static void TestProcessDeliveryNoSuitableWarehouse()
    {
        Console.WriteLine("Тест 2: Попытка доставки товаров в неподходящий склад");

        // Создаем склады и товары
        var warehouse = new Warehouse(1, "cold", 1000, "Warehouse1");
        var product = new Product(1, 101, "Product1", 10, 100, 10);  // Короткий срок годности

        // Делаем поставку
        var delivery = new List<Product> { product };

        var logisticsManager = new LogisticsManager(new List<Warehouse> { warehouse });

        try
        {
            logisticsManager.ProcessDelivery(delivery);
            Console.WriteLine("Поставка успешно добавлена на склад.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);  // Ожидаем ошибку, так как нет склада с холодным типом
        }
    }

    static void TestInternalOptimize()
    {
        Console.WriteLine("Тест 3: Оптимизация складов");

        // Создаем склады и товары
        var warehouse1 = new Warehouse(1, "sorting", 1000, "Warehouse1");
        var warehouse2 = new Warehouse(2, "general", 1000, "Warehouse2");

        var product1 = new Product(1, 101, "Product1", 10, 100, 40);
        var product2 = new Product(2, 102, "Product2", 10, 150, 10);

        warehouse1.AddProducts(new List<Product> { product1, product2 });

        var logisticsManager = new LogisticsManager(new List<Warehouse> { warehouse1, warehouse2 });

        try
        {
            logisticsManager.InternalOptimize();
            Console.WriteLine("Оптимизация складов прошла успешно.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);
        }
    }

    static void TestMoveExpiredProducts()
    {
        Console.WriteLine("Тест 4: Перемещение просроченных товаров на утилизацию");

        // Создаем склады и товары
        var warehouse = new Warehouse(1, "general", 1000, "Warehouse1");
        var disposalWarehouse = new Warehouse(2, "disposal", 1000, "DisposalWarehouse");

        var expiredProduct = new Product(1, 101, "ExpiredProduct", 10, 100, -1);  // Просроченный товар
        warehouse.AddProducts(new List<Product> { expiredProduct });

        var logisticsManager = new LogisticsManager(new List<Warehouse> { warehouse, disposalWarehouse });

        try
        {
            logisticsManager.MoveExpiredProducts();
            Console.WriteLine("Просроченные товары успешно перемещены в утилизацию.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);
        }
    }

    static void TestMoveExpiredProductsNotEnoughSpace()
    {
        Console.WriteLine("Тест 5: Ошибка при нехватке места для просроченных товаров");

        // Создаем склады и товары
        var warehouse = new Warehouse(1, "general", 1000, "Warehouse1");
        var disposalWarehouse = new Warehouse(2, "disposal", 0, "DisposalWarehouse");  // Нет места

        var expiredProduct = new Product(1, 101, "ExpiredProduct", 10, 100, -1);  // Просроченный товар
        warehouse.AddProducts(new List<Product> { expiredProduct });

        var logisticsManager = new LogisticsManager(new List<Warehouse> { warehouse, disposalWarehouse });

        try
        {
            logisticsManager.MoveExpiredProducts();
            Console.WriteLine("Просроченные товары успешно перемещены.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);  // Ожидаем ошибку
        }
    }

    static void TestMoveProducts()
    {
        Console.WriteLine("Тест 6: Перемещение товаров между складами");

        // Создаем склады и товары
        var warehouse1 = new Warehouse(1, "general", 1000, "Warehouse1");
        var warehouse2 = new Warehouse(2, "general", 1000, "Warehouse2");

        var product = new Product(1, 101, "Product1", 10, 100, 40);  // Долгий срок годности
        warehouse1.AddProducts(new List<Product> { product });

        var logisticsManager = new LogisticsManager(new List<Warehouse> { warehouse1, warehouse2 });

        try
        {
            logisticsManager.MoveProducts(1, 2, new List<int> { 1 });
            Console.WriteLine("Товары успешно перемещены между складами.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);  // Ожидаем ошибку, если чего-то не хватает
        }
    }
}
