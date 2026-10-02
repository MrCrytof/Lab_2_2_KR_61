#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FUNCTION_C


double integrandFunction(double x)

{
    return x * x * sqrt(1.0 + x * x * x);
}

double leftRectangles(double a, double b, int n)
{
    double h;
    double sum = 0.00;
    double x;

    int i;


    // Обчислення ширини одного проміжку.
    h = (b - a) / n;


    // Цикл проходить по всіх n проміжках.
    for (i = 0; i < n; i++)
    {
        // Для методу лівих прямокутників
        // беремо ліву точку поточного проміжку.
        x = a + i * h;

        // Додаємо значення функції до загальної суми.
        sum += integrandFunction(x);
    }


    // Площа всіх прямокутників.
    return sum * h;
}

double rightRectangles(double a, double b, int n)
{
    double h;
    double sum = 0.0;
    double x;

    int i;


    // Обчислення ширини одного проміжку.
    h = (b - a) / n;


    // Перебираємо всі проміжки.
    for (i = 1; i <= n; i++)
    {
        // Для правих прямокутників
        // використовується права точка проміжку.
        x = a + i * h;

        // Додаємо значення функції до суми.
        sum += integrandFunction(x);
    }


    // Отримуємо наближене значення інтеграла.
    return sum * h;
}

double trapezoids(double a, double b, int n)
{
    double h;
    double sum;
    double x;

    int i;


    // Ширина одного проміжку.
    h = (b - a) / n;


    // Крайні точки мають коефіцієнт 1.
    sum = (
        integrandFunction(a) +
        integrandFunction(b)
    ) / 2.0;


    // Обробка внутрішніх точок.
    for (i = 1; i < n; i++)
    {
        // Координата поточної внутрішньої точки.
        x = a + i * h;

        // Додаємо значення функції.
        sum += integrandFunction(x);
    }


    // Множення суми на ширину проміжку.
    return sum * h;
}

double simpson(double a, double b, int n)
{
    double h;
    double sum;
    double x;

    int i;


    // Визначення ширини одного проміжку.
    h = (b - a) / n;


    // Крайні точки мають коефіцієнт 1.
    sum =
        integrandFunction(a) +
        integrandFunction(b);


    // Обробка всіх внутрішніх точок.
    for (i = 1; i < n; i++)
    {
        // Визначення координати поточної точки.
        x = a + i * h;


        // Якщо номер точки парний,
        // її значення множиться на 2.
        if (i % 2 == 0)
        {
            sum += 2.0 * integrandFunction(x);
        }
        // Якщо номер точки непарний,
        // її значення множиться на 4.
        else
        {
            sum += 4.0 * integrandFunction(x);
        }
    }


    // Остаточна формула методу Сімпсона.
    return sum * h / 3.0;
}

double calculateIntegral(double a, double b, int n, int method)
{
    // Конструкція switch вибирає необхідну
    // функцію відповідно до номера методу.
    switch (method)
    {
        case 1:
            return leftRectangles(a, b, n);

        case 2:
            return rightRectangles(a, b, n);

        case 3:
            return trapezoids(a, b, n);

        case 4:
            return simpson(a, b, n);

        // Якщо номер методу некоректний,
        // повертаємо нуль.
        default:
            return 0.0;
    }
}

int findRequiredN(
    double a,
    double b,
    double epsilon,
    int method,
    double *integralValue
)
{
    // Починаємо з двох проміжків.
    int n = 2;

    double i1;
    double i2;
    double delta;


    // Цикл виконується доти,
    // поки необхідна точність не буде досягнута.
    while (n < 10000000)
    {
        // Перше значення інтеграла при N проміжках.
        i1 = calculateIntegral(a, b, n, method);

        // Друге значення інтеграла при N + 2 проміжках.
        i2 = calculateIntegral(a, b, n + 2, method);


        // Визначення різниці між двома результатами.
        //
        // fabs() повертає абсолютне значення числа,
        // тому Delta завжди буде невід'ємною.
        delta = fabs(i1 - i2);


        // Перевірка умови заданої точності.
        if (delta <= epsilon)
        {
            // Записуємо останнє обчислене
            // значення інтеграла через вказівник.
            *integralValue = i2;

            // Повертаємо необхідну кількість проміжків.
            return n + 2;
        }


        // Якщо похибка ще більша за допустиму,
        // збільшуємо кількість проміжків на 2.
        n += 2;
    }


    // Захист від надто великої кількості ітерацій.
    *integralValue =
        calculateIntegral(a, b, n, method);

    return n;
}

void printResult(
    const char *methodName,
    double a,
    double b,
    int n,
    double result
)
{
    printf("Method: %s\n", methodName);

    // Виведення меж інтегрування.
    printf("Left boundary: %.6f\n", a);
    printf("Right boundary: %.6f\n", b);

    // Виведення кількості проміжків.
    printf("Number of intervals: %d\n", n);

    // Виведення отриманого значення інтеграла.
    printf("Integral value: %.10f\n", result);
}

double readDouble(const char *message)
{
    char input[100];
    char *end;

    double value;


    while (1)
    {
        printf("%s", message);


        // Зчитування всього рядка з клавіатури.
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Input error. Try again.\n");
            continue;
        }


        // Перетворення тексту на число.
        value = strtod(input, &end);


        // Якщо перетворення не відбулося,
        // користувач ввів некоректні дані.
        if (end == input)
        {
            printf("Error: please enter a number.\n");
            continue;
        }


        // Пропускаємо пробіли та табуляцію
        // після введеного числа.
        while (*end == ' ' || *end == '\t')
        {
            end++;
        }


        // Якщо після числа залишилися сторонні символи,
        // введення вважається некоректним.
        if (*end != '\n' && *end != '\0')
        {
            printf("Error: invalid input.\n");
            continue;
        }


        // Якщо всі перевірки пройдено,
        // повертаємо введене число.
        return value;
    }
}

int readPositiveInt(const char *message)
{
    char input[100];
    char *end;

    long value;


    while (1)
    {
        printf("%s", message);


        // Зчитування рядка з клавіатури.
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Input error. Try again.\n");
            continue;
        }


        // Перетворення тексту на ціле число.
        value = strtol(input, &end, 10);


        // Перевірка, чи вдалося виконати перетворення.
        if (end == input)
        {
            printf("Error: please enter an integer.\n");
            continue;
        }


        // Пропускаємо пробіли після числа.
        while (*end == ' ' || *end == '\t')
        {
            end++;
        }


        // Перевірка на наявність зайвих символів.
        if (*end != '\n' && *end != '\0')
        {
            printf("Error: invalid input.\n");
            continue;
        }


        // Кількість проміжків повинна бути додатною.
        if (value <= 0 || value > 10000000)
        {
            printf("Error: enter a positive integer.\n");
            continue;
        }


        // Перетворення long у int після перевірки.
        return (int)value;
    }
}