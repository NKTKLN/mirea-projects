using System;

class MatrixCalculator
{
    static void Main()
    {
        Console.Write("Введите количество строк n для первой матрицы: ");
        int n = int.Parse(Console.ReadLine());

        Console.Write("Введите количество столбцов m для первой матрицы: ");
        int m = int.Parse(Console.ReadLine());

        Console.Write("Введите количество строк n для второй матрицы: ");
        int n2 = int.Parse(Console.ReadLine());

        Console.Write("Введите количество столбцов m для второй матрицы: ");
        int m2 = int.Parse(Console.ReadLine());

        double[,] matrix1 = new double[n, m];
        double[,] matrix2 = new double[n2, m2];

        Console.WriteLine("\nВыберите действие:");
        Console.WriteLine("1 - Заполнить матрицы значениями с клавиатуры");
        Console.WriteLine("2 - Заполнить матрицы случайными числами");
        Console.WriteLine("3 - Сложить матрицы");
        Console.WriteLine("4 - Умножить матрицы");
        Console.WriteLine("5 - Найти детерминант первой матрицы");
        Console.WriteLine("6 - Найти обратную матрицу первой матрицы");
        Console.WriteLine("7 - Транспонировать первую матрицу");
        Console.WriteLine("8 - Найти корни системы уравнений");
        Console.WriteLine("0 - Выход");

        while (true)
        {
            Console.Write(":> ");
            int choice = int.Parse(Console.ReadLine());

            switch (choice)
            {
                case 0:
                    Console.WriteLine("Выход.");
                    return;
                case 1:
                    Console.WriteLine("Введите первую матрицу:");
                    FillFromInput(matrix1);
                    Console.WriteLine("Введите вторую матрицу:");
                    FillFromInput(matrix2);
                    Print(matrix1);
                    Console.WriteLine();
                    Print(matrix2);
                    break;
                case 2:
                    Console.WriteLine("Введите диапазон для случайных чисел (a и b):");
                    int a = int.Parse(Console.ReadLine());
                    int b = int.Parse(Console.ReadLine());
                    FillRandom(matrix1, a, b);
                    FillRandom(matrix2, a, b);
                    Print(matrix1);
                    Console.WriteLine();
                    Print(matrix2);
                    break;
                case 3:
                    if (matrix1.GetLength(0) != matrix2.GetLength(0) || matrix1.GetLength(1) != matrix2.GetLength(1))
                    {
                        Console.WriteLine("Сложение невозможно.");
                        break;
                    }

                    Print(Add(matrix1, matrix2));
                    break;
                case 4:
                    if (matrix1.GetLength(1) != matrix2.GetLength(0))
                    {
                        Console.WriteLine("Умножение невозможно.");
                        break;
                    }
                    Print(Multiply(matrix1, matrix2));
                    break;
                case 5:
                    if (matrix1.GetLength(0) != matrix1.GetLength(1))
                    {
                        Console.WriteLine("Только для квадратных матриц.");
                        break;
                    }

                    double determinant = CalculateDeterminant(matrix1);
                    Console.WriteLine($"Детерминант: {determinant}");
                    break;
                case 6:
                    if (matrix1.GetLength(0) != matrix1.GetLength(1))
                    {
                        Console.WriteLine("Только для квадратных матриц.");
                        break;
                    }

                    determinant = CalculateDeterminant(matrix1);
                    if (determinant == 0)
                    {
                        Console.WriteLine("Обратная матрица не существует.");
                        break;
                    }

                    Print(Inverse(matrix1, determinant));
                    break;
                case 7:
                    Print(Transpose(matrix1));
                    break;  
                case 8:
                    Console.WriteLine("Введите вектор решений:");
                    double[] ans = new double[matrix1.GetLength(0)];
                    for (int i = 0; i < matrix1.GetLength(0); i++)
                    {
                        ans[i] = double.Parse(Console.ReadLine());
                    }

                    double[] roots = SolveLinearSystem(matrix1, ans);
                    if (roots == null)
                    {
                        Console.WriteLine("Нет однозначного решения.");
                        break;
                    }

                    Console.WriteLine("Корни:");
                    foreach (var root in roots)
                    {
                        Console.WriteLine(root);
                    }
                    break;
                default:
                    Console.WriteLine("Некорректный выбор.");
                    break;
            }
        }
    }

    static void FillFromInput(double[,] targetMatrix)
    {
        for (int row = 0; row < targetMatrix.GetLength(0); row++)
        {
            for (int col = 0; col < targetMatrix.GetLength(1); col++)
            {
                targetMatrix[row, col] = double.Parse(Console.ReadLine());
            }
        }
    }

    static void FillRandom(double[,] targetMatrix, int minValue, int maxValue)
    {
        Random randomGenerator = new Random();
        for (int row = 0; row < targetMatrix.GetLength(0); row++)
        {
            for (int col = 0; col < targetMatrix.GetLength(1); col++)
            {
                targetMatrix[row, col] = randomGenerator.Next(minValue, maxValue);
            }
        }
    }

    static void Print(double[,] targetMatrix)
    {
        for (int row = 0; row < targetMatrix.GetLength(0); row++)
        {
            for (int col = 0; col < targetMatrix.GetLength(1); col++)
            {
                Console.Write(targetMatrix[row, col] + "\t");
            }
            Console.WriteLine();
        }
    }

    static double[,] Add(double[,] firstMatrix, double[,] secondMatrix)
    {
        int rows = firstMatrix.GetLength(0);
        int cols = firstMatrix.GetLength(1);
        double[,] sumMatrix = new double[rows, cols];

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                sumMatrix[row, col] = firstMatrix[row, col] + secondMatrix[row, col];
            }
        }

        return sumMatrix;
    }

    static double[,] Multiply(double[,] firstMatrix, double[,] secondMatrix)
    {
        int rows1 = firstMatrix.GetLength(0);
        int cols1 = firstMatrix.GetLength(1);
        int cols2 = secondMatrix.GetLength(1);
        double[,] productMatrix = new double[rows1, cols2];

        for (int row = 0; row < rows1; row++)
        {
            for (int col = 0; col < cols2; col++)
            {
                productMatrix[row, col] = 0;
                for (int k = 0; k < cols1; k++)
                {
                    productMatrix[row, col] += firstMatrix[row, k] * secondMatrix[k, col];
                }
            }
        }

        return productMatrix;
    }

    static double CalculateDeterminant(double[,] inputMatrix)
    {
        int size = inputMatrix.GetLength(0);
        if (size == 1)
        {
            return inputMatrix[0, 0];
        }
        if (size == 2)
        {
            return inputMatrix[0, 0] * inputMatrix[1, 1] - inputMatrix[0, 1] * inputMatrix[1, 0];
        }

        double determinant = 0;
        for (int column = 0; column < size; column++)
        {
            double[,] minorMatrix = GetSubMatrix(inputMatrix, 0, column);
            determinant += inputMatrix[0, column] * Math.Pow(-1, column) * CalculateDeterminant(minorMatrix);
        }
        return determinant;
    }

    static double[,] GetSubMatrix(double[,] inputMatrix, int excludeRow, int excludeColumn)
    {
        int size = inputMatrix.GetLength(0);
        double[,] minorMatrix = new double[size - 1, size - 1];
        int newRow = 0;
        int newColumn = 0;

        for (int row = 0; row < size; row++)
        {
            if (row == excludeRow) continue;
            newColumn = 0;
            for (int column = 0; column < size; column++)
            {
                if (column == excludeColumn) continue;
                minorMatrix[newRow, newColumn] = inputMatrix[row, column];
                newColumn++;
            }
            newRow++;
        }
        return minorMatrix;
    }

    static double[,] Inverse(double[,] inputMatrix, double determinant)
    {
        int size = inputMatrix.GetLength(0);
        double[,] adjugateMatrix = new double[size, size];

        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                adjugateMatrix[col, row] = Math.Pow(-1, row + col) * CalculateDeterminant(GetSubMatrix(inputMatrix, row, col));
            }
        }

        double[,] inverseMatrix = new double[size, size];
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                inverseMatrix[row, col] = adjugateMatrix[row, col] / determinant;
            }
        }

        return inverseMatrix;
    }

    static double[,] Transpose(double[,] inputMatrix)
    {
        int rows = inputMatrix.GetLength(0);
        int cols = inputMatrix.GetLength(1);
        double[,] transposedMatrix = new double[cols, rows];

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                transposedMatrix[col, row] = inputMatrix[row, col];
            }
        }

        return transposedMatrix;
    }

    static double[] SolveLinearSystem(double[,] inputMatrix, double[] matrixWithAns)
    {
        int size = inputMatrix.GetLength(0);
        double[,] augmentedMatrix = new double[size, size + 1];

        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                augmentedMatrix[row, col] = inputMatrix[row, col];
            }
            augmentedMatrix[row, size] = matrixWithAns[row];
        }

        for (int row = 0; row < size; row++)
        {
            if (augmentedMatrix[row, row] == 0) return null;

            for (int col = row + 1; col < size; col++)
            {
                double factor = augmentedMatrix[col, row] / augmentedMatrix[row, row];
                for (int k = row; k <= size; k++)
                {
                    augmentedMatrix[col, k] -= factor * augmentedMatrix[row, k];
                }
            }
        }

        double[] solution = new double[size];
        for (int row = size - 1; row >= 0; row--)
        {
            solution[row] = augmentedMatrix[row, size];
            for (int col = row + 1; col < size; col++)
            {
                solution[row] -= augmentedMatrix[row, col] * solution[col];
            }
            solution[row] /= augmentedMatrix[row, row];
        }

        return solution;
    }
}
