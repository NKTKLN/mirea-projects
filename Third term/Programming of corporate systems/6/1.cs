using System;
using System.Linq;

class Program
{
    // Объявление делегата, который определяет метод сравнения двух строк
    public delegate int Comparison(string x, string y);

    static void Main(string[] args)
    {
        string[] strings = { "apple", "banana", "cherry", "date", "elderberry", "fig", "grape" };

        Console.WriteLine("Выберите способ сортировки:");
        Console.WriteLine("1. По длине строки");
        Console.WriteLine("2. По алфавиту");
        Console.WriteLine("3. По количеству гласных букв в строке");
        Console.Write(":> ");

        int choice = int.Parse(Console.ReadLine());

        Comparison comparison;
        // Присваиваем делегату метод сортировки
        switch (choice)
        {
            case 1:
                comparison = CompareByLength;
                break;
            case 2:
                comparison = CompareAlphabetically;
                break;
            case 3:
                comparison = CompareByVowelCount;
                break;
            default:
                throw new InvalidOperationException("Некорректный выбор");
        };

        // Сортируем массив с использованием выбранного пользователем делегата
        SortArray(strings, comparison);

        Console.WriteLine("Отсортированный массив:");
        foreach (var str in strings)
        {
            Console.WriteLine(str);
        }
    }

    public static void SortArray(string[] array, Comparison comparison)
    {
        // Используем делегат в методе Array.Sort для передачи логики сравнения
        Array.Sort(array, (x, y) => comparison(x, y));
    }

    // Метод для сравнения строк по длине
    static int CompareByLength(string str1, string str2)
    {
        return str1.Length.CompareTo(str2.Length);
    }

    // Метод для сравнения строк по алфавиту
    static int CompareAlphabetically(string str1, string str2)
    {
        return string.Compare(str1, str2);
    }

    // Метод для сравнения строк по количеству гласных
    static int CompareByVowelCount(string str1, string str2)
    {
        int str1Vowels = CountVowels(str1);
        int str2Vowels = CountVowels(str2);
        return str1Vowels.CompareTo(str2Vowels);
    }

    // Метод для подсчета гласных в строке
    static int CountVowels(string str)
    {
        char[] vowels = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
        return str.Count(c => vowels.Contains(c));
    }
}
