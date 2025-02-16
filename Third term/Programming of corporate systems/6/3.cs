using System;

class Thermostat
{
    // Определяем события для перегрева и переохлаждения
    public event Action OverheatEvent;
    public event Action OvercoolEvent;

    private int currentTemperature;

    // Свойства для максимальной и минимальной температуры
    public int MaxTemperature { get; set; }
    public int MinTemperature { get; set; }

    // Метод для обновления температуры
    public void UpdateTemperature(int newTemperature)
    {
        currentTemperature = newTemperature;
        Console.WriteLine($"Текущая температура: {currentTemperature}°C");

        // Проверка на перегрев
        if (currentTemperature > MaxTemperature)
            OverheatEvent?.Invoke();
        
        // Проверка на переохлаждение
        if (currentTemperature < MinTemperature)
            OvercoolEvent?.Invoke();
    }
}

class Program
{
    static void Main()
    {
        // Создаем объект термостата
        var thermostat = new Thermostat();

        // Запрос у пользователя минимальной и максимальной температуры
        Console.Write("Введите максимальную температуру: ");
        thermostat.MaxTemperature = int.Parse(Console.ReadLine());
        
        Console.Write("Введите минимальную температуру: ");
        thermostat.MinTemperature = int.Parse(Console.ReadLine());

        // Регистрация обработчиков событий с использованием лямбда-функций
        thermostat.OverheatEvent += () => Console.WriteLine("Внимание! Перегрев!");
        thermostat.OvercoolEvent += () => Console.WriteLine("Внимание! Переохлаждение!");

        // Симуляция изменения температуры в случайных пределах
        Random random = new Random();
        for (int i = 0; i < 10; i++)
        {
            int newTemperature = random.Next(-10, 50); // Генерация случайной температуры
            thermostat.UpdateTemperature(newTemperature);
            System.Threading.Thread.Sleep(1000);
        }
    }
}
