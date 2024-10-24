using System;
using System.Collections.Generic;

public enum Category
{
    Напитки,
    Салаты,
    ХолодныеЗакуски,
    ГорячиеЗакуски,
    Супы,
    ГорячиеБлюда,
    Десерт
}

public class Dish 
{
    public int Id { get; private set; }
    public string Name { get; private set; }
    public string Ingredients { get; private set; }
    public string Weight { get; private set; } // 100/20/50
    public decimal Price { get; private set; }
    public Category DishCategory { get; private set; }
    public int CookingTime { get; private set; }
    public List<string> DishTypes { get; private set; }

    public Dish(int id, string name, string ingredients, string weight, decimal price, Category category, int cookingTime, params string[] dishTypes)
    {
        Id = id;
        Name = name;
        Ingredients = ingredients;
        Weight = weight;
        Price = price;
        DishCategory = category;
        CookingTime = cookingTime;
        DishTypes = new List<string>(dishTypes);
    }

    public void EditDish(in string name, in string ingredients, in string weight, in decimal price, in Category category, in int cookingTime, params string[] dishTypes)
    {
        Name = name;
        Ingredients = ingredients;
        Weight = weight;
        Price = price;
        DishCategory = category;
        CookingTime = cookingTime;
        DishTypes = new List<string>(dishTypes);
    }

    public void PrintInfo()
    {
        Console.WriteLine($"Id: {Id}");
        Console.WriteLine($"Название: {Name}");
        Console.WriteLine($"Состав: {Ingredients}");
        Console.WriteLine($"Вес: {Weight}");
        Console.WriteLine($"Цена: {Price}");
        Console.WriteLine($"Категория: {DishCategory}");
        Console.WriteLine($"Время готовки: {CookingTime} минут");
        Console.WriteLine("Типы блюда: " + string.Join(", ", DishTypes));
    }

    public void ApplyDiscount(ref decimal discountPercentage)
    {
        if (discountPercentage > 0 && discountPercentage <= 100)
        {
            Price -= Price * (discountPercentage / 100);
            discountPercentage = 0;
        }
    }

    public void GetDishDetails(out string details)
    {
        details = $"Название: {Name}\n* Цена: {Price}\n* Категория: {DishCategory}\n* Типы блюда: " + string.Join(", ", DishTypes);
    }

    public void DeleteDish()
    {
        //? Удаление блюда.

        Id = 0;
        Name = string.Empty;
        Ingredients = string.Empty;
        Weight = string.Empty;
        Price = 0;
        DishCategory = 0;
        CookingTime = 0;
        DishTypes.Clear();
    }
}
