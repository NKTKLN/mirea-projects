using System;
using System.Linq;

class Program
{
    static void Main()
    {
        string[] strings = { "apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "cucumber" };

        Console.WriteLine("Выберите критерий фильтрации:");
        Console.WriteLine("1. Строки, длина которых больше указанного числа.");
        Console.WriteLine("2. Строки, начинающиеся с определенной буквы.");
        Console.WriteLine("3. Строки, содержащие заданное количество гласных букв или больше.");
        Console.Write(":> ");

        int choice = int.Parse(Console.ReadLine());

        // Результат фильтрации
        string[] filteredStrings;
        switch (choice)
        {
            case 1:
                // Фильтрация по длине строки
                Console.Write("Введите минимальную длину строки: ");
                int minLength = int.Parse(Console.ReadLine());
                filteredStrings = strings.Where(s => s.Length > minLength).ToArray();
                break;
            case 2:
                // Фильтрация по начальной букве
                Console.Write("Введите начальную букву: ");
                string startLetter = Console.ReadLine();
                filteredStrings = strings.Where(s => s.StartsWith(startLetter, StringComparison.OrdinalIgnoreCase)).ToArray();
                break;
            case 3:
                // Фильтрация по количеству гласных букв
                Console.Write("Введите минимальное количество гласных букв: ");
                int minVowelCount = int.Parse(Console.ReadLine());
                char[] vowels = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
                filteredStrings = strings.Where(s => s.Count(c => vowels.Contains(c)) >= minVowelCount).ToArray();
                break;
            default:
                throw new InvalidOperationException("Некорректный выбор");
        };

        Console.WriteLine("Отфильтрованные строки:");
        foreach (var str in filteredStrings)
        {
            Console.WriteLine(str);
        }
    }
}
