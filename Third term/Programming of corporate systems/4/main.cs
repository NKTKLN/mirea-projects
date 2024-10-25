using System;
using System.Linq;
using System.Collections.Generic;

class OrderingSystem
{
    private static List<Dish> dishes;
    private static List<Order> orders;
    private static Random random = new Random();

    static void Main()
    {
        dishes = new List<Dish>();
        orders = new List<Order>();
        GenerateDishes(20);
        GenerateOrders(5);

        PrintMenu();
        DishStatistics();
    }

    private static void GenerateDishes(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            dishes.Add(new Dish(
                i,
                $"Блюдо {i}",
                $"Ингредиенты {i}",
                $"{random.Next(100, 500)}/{random.Next(10, 50)}/{random.Next(5, 30)}",
                random.Next(100, 1000),
                (Category)random.Next(Enum.GetNames(typeof(Category)).Length),
                random.Next(10, 60),
                "острое", "веганское"));
        }
    }

    private static void GenerateOrders(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            int tableId = random.Next(1, 11);
            List<Dish> orderDishes = new List<Dish>();
            int dishCount = random.Next(1, 6);

            for (int j = 0; j < dishCount; j++)
            {
                orderDishes.Add(dishes[random.Next(dishes.Count)]);
            }
            
            orders.Add(new Order(
                i,
                tableId,
                $"Комментарий к заказу {i}",
                DateTime.Now,
                random.Next(1, 6),
                orderDishes.ToArray()
            ));
        }
    }

    private static void CalculateTotalCost()
    {
        decimal TotalCost = 0;
        foreach (var order in orders)
        {
            if (!order.CloseTime.HasValue)
            {
                TotalCost += order.TotalCost;
            }
        }

        Console.WriteLine($"Стоимость всех закрытых заказов: {TotalCost}");
    }

    private static void CountClosedOrdersByWaiter(in int waiterId) 
    {
        decimal TotalCost = 0;
        foreach (var order in orders)
        {
            if (order.CloseTime != null && order.WaiterId == waiterId)
            {
                TotalCost += order.TotalCost;
            }
        }

        Console.WriteLine($"Стоимость всех закрытых заказов конкретного официанта ({waiterId}): {TotalCost}");
    }

    private static void PrintMenu()
    {
        var groupedDishesByCategory = dishes.GroupBy(d => d.DishCategory)
                                        .Select(g => new
                                        {
                                            Category = g.Key,
                                            Dishes = g.GroupBy(d => d.Name)
                                                    .Select(dg => new { Dish = dg.First(), Count = dg.Count() })
                                        });
        foreach (var categoryGroup in groupedDishesByCategory)
        {
            Console.WriteLine($"Категория: {categoryGroup.Category}");

            foreach (var dishGroup in categoryGroup.Dishes)
            {
                dishGroup.Dish.GetDishDetails(out string dishDetails);
                Console.WriteLine(dishDetails);
            }
            Console.WriteLine();
        }
    }

    private static void DishStatistics() 
    {
        Dictionary<Dish, int> dishCount = new Dictionary<Dish, int>();
        foreach (var order in orders)
        {
            foreach (var dish in order.Dishes)
            {
                if (dishCount.ContainsKey(dish))
                {
                    dishCount[dish]++;
                }
                else
                {
                    dishCount[dish] = 1;
                }
            }
        }

        foreach (var dish in dishes)
        {
            Console.Write($"{dish.Name} - ");
            if (dishCount.ContainsKey(dish))
            {
                Console.WriteLine(dishCount[dish]);
            }
            else 
            {
                Console.WriteLine(0);
            }
        }
    }
}
