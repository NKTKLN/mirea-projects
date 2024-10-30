using System;
using System.Linq;
using System.Collections.Generic;

public class Order
{
    public int Id { get; private set; }
    public int TableId { get; private set; }
    public List<Dish> Dishes { get; private set; }
    public string Comment { get; private set; }
    public DateTime OrderTime  { get; private set; }
    public int WaiterId { get; private set; }
    public DateTime? CloseTime  { get; private set; }
    public decimal TotalCost  { get; private set; }

    public Order(int orderId, int tableId, string comment, DateTime orderTime, int waiterId, params Dish[] dishes)
    {
        Id = orderId;
        TableId = tableId;
        Dishes = new List<Dish>(dishes);
        Comment = comment;
        OrderTime = orderTime;
        WaiterId = waiterId;
        CloseTime = null;
        CalculateTotalCost();
    }

    public void EditOrder(int tableId, string comment, in DateTime orderTime, params Dish[] dishes)
    {
        if (CloseTime.HasValue)
        {
            return;
        }

        TableId = tableId;
        Dishes = new List<Dish>(dishes);
        Comment = comment;
        OrderTime = orderTime;
        CalculateTotalCost();
    }

    public void PrintInfo()
    {
        Console.WriteLine($"Id заказа: {Id}");
        Console.WriteLine($"Id стола: {TableId}");
        Console.WriteLine($"Официант Id: {WaiterId}");
        Console.WriteLine($"Время принятия заказа: {OrderTime}");
        if (CloseTime.HasValue)
        {
            Console.WriteLine($"Время закрытия заказа: {CloseTime.Value}");
        }
        Console.WriteLine("Блюда в заказе:");
        
        var groupedDishes = Dishes.GroupBy(d => d.Name)
                                .Select(g => new { Dish = g.First(), Count = g.Count() });
        foreach (var item in groupedDishes)
        {
            Console.WriteLine($"- {item.Dish.Name}: {item.Dish.Price} x {item.Count}");
        }

        Console.WriteLine($"Комментарий: {Comment}");
        Console.WriteLine($"Итоговая стоимость: {TotalCost}");

        if (CloseTime.HasValue)
        {
            Console.WriteLine($"Дата закрытия: {CloseTime.Value}");
        }
    }

    public void GetOrderSummary(out string summary)
    {
        summary = $"Заказ Id: {Id}\nСтол: {TableId}\nОфициант: {WaiterId}\nВремя заказа: {OrderTime}\nКомментарий: {Comment}";
    }

    public void CloseOrder()
    {
        if (!CloseTime.HasValue)
        {
            CloseTime = DateTime.Now;
        }
    }

    public void PrintReceipt()
    {
        if (CloseTime.HasValue)
        {
            Console.WriteLine($"Столик: {Id}");
            Console.WriteLine($"Официант: {WaiterId}");
            Console.WriteLine($"Период обслуживания: с {OrderTime} по {CloseTime.Value}");
            Console.WriteLine();

            var groupedDishesByCategory = Dishes.GroupBy(d => d.DishCategory)
                                            .Select(g => new
                                            {
                                                Category = g.Key,
                                                Dishes = g.GroupBy(d => d.Name)
                                                    .Select(dg => new { Dish = dg.First(), Count = dg.Count() })
                                            });
            decimal overallTotal = 0;
            foreach (var categoryGroup in groupedDishesByCategory)
            {
                Console.WriteLine($"Категория: {categoryGroup.Category}");
                decimal categoryTotal = 0;

                foreach (var dishGroup in categoryGroup.Dishes)
                {
                    decimal dishTotal = dishGroup.Count * dishGroup.Dish.Price;
                    Console.WriteLine($"{dishGroup.Dish.Name} {dishGroup.Count} * {dishGroup.Dish.Price} = {dishTotal}");
                    categoryTotal += dishTotal;
                }

                Console.WriteLine($"Под_итог категории: {categoryTotal}");
                overallTotal += categoryTotal;
                Console.WriteLine();
            }

            Console.WriteLine($"Итог счета: {overallTotal}");
        }
        else
        {
            Console.WriteLine("Заказ еще не закрыт, чек не может быть выведен.");
        }
    }

    public void ApplyDiscount(ref decimal discountPercentage)
    {

        if (!CloseTime.HasValue && discountPercentage > 0 && discountPercentage <= 100)
        {
            TotalCost -= TotalCost * (discountPercentage / 100);
            discountPercentage = 0;
        }
    }

    private void CalculateTotalCost()
    {
        TotalCost = Dishes.Sum(dish => dish.Price);
    }
}
