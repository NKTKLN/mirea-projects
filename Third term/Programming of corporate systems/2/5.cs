using System;

class CoffeeMachine
{
    static void Main()
    {
        Console.Write("Введите количество воды в мл: ");
        int water = int.Parse(Console.ReadLine());

        Console.Write("Введите количество молока в мл: ");
        int milk = int.Parse(Console.ReadLine());

        int latteCount = 0;
        int totalEarnings = 0;
        int americanoCount = 0;

        while (water >= 30)
        {
            Console.Write("Выберите напиток (1 — американо, 2 — латте): ");
            int choice = int.Parse(Console.ReadLine());

            if (choice == 1 && water >= 300)
            {
                water -= 300;
                americanoCount++;
                totalEarnings += 150;
                Console.WriteLine("Ваш напиток готов.");
            }
            else if (choice == 2 && water >= 30 && milk >= 270)
            {
                water -= 30;
                milk -= 270;
                latteCount++;
                totalEarnings += 170;
                Console.WriteLine("Ваш напиток готов.");
            }
            else
            {
                Console.WriteLine("Не хватает ингредиентов.");
            }
        }

        Console.WriteLine("*Отчёт*");
        Console.WriteLine($"Ингредиентов осталось:\n\tВода: {water} мл\n\tМолоко: {milk} мл");
        Console.WriteLine($"Кружек американо приготовлено: {americanoCount}");
        Console.WriteLine($"Кружек латте приготовлено: {latteCount}");
        Console.WriteLine($"Итого заработано: {totalEarnings} рублей.");
    }
}
