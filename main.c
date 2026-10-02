#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "function.h"
#include "function.c"

//                              ГОЛОВНА ФУНКЦІЯ

int main()
{
    // Ліва та права межі інтегрування.
    // Для Варіанта №7 за умовою вони дорівнюють 0 та 1.
    double a;
    double b;

    // Кількість проміжків розбиття інтеграла.
    int n;

    // Задана користувачем допустима похибка.
    double epsilon;

    // Номер вибраного методу інтегрування.
    int method;

    // Результат обчислення інтеграла.
    double result;


    // Виведення заголовка програми.
    printf("=============================================\n");
    printf("       NUMERICAL INTEGRATION PROGRAM\n");
    printf("                 Variant 7\n");
    printf("=============================================\n\n");

    // Виведення функції, яка використовується у програмі.
    printf("Function: f(x) = x^2 * sqrt(1 + x^3)\n");
    printf("Integration interval: [0, 1]\n\n");

    //                  ВВЕДЕННЯ ПОЧАТКОВИХ ДАНИХ

    // Введення лівої межі інтегрування.
    printf("--- Integration Parameters ---\n");

    a = readDouble("Enter the left boundary a: ");

    // Введення правої межі інтегрування.
    b = readDouble("Enter the right boundary b: ");

    // Перевірка правильності меж інтегрування.
    // Права межа повинна бути більшою за ліву.
    while (a >= b)
    {
        printf("Error: the right boundary must be greater than the left boundary.\n");

        b = readDouble("Enter the right boundary b: ");
    }


    // Введення початкової кількості проміжків.
    n = readPositiveInt("Enter the number of intervals n: ");


    // Введення допустимої похибки.
    epsilon = readDouble("Enter the required error epsilon: ");

    // За умовою лабораторної роботи:
    // 0.00001 <= epsilon <= 0.001.
    while (epsilon < 0.00001 || epsilon > 0.001)
    {
        printf("Error: epsilon must be between 0.00001 and 0.001.\n");

        epsilon = readDouble("Enter the required error epsilon: ");
    }


    //                       ВИБІР МЕТОДУ


    printf("\n=============================================\n");
    printf("              METHOD SELECTION\n");
    printf("=============================================\n");

    printf("1. Left rectangles\n");
    printf("2. Right rectangles\n");
    printf("3. Trapezoids\n");
    printf("4. Simpson's method\n");
    printf("5. All methods\n");

    method = readPositiveInt("Choose a method: ");


    // Перевірка номера вибраного методу.
    while (method < 1 || method > 5)
    {
        printf("Error: choose a number from 1 to 5.\n");

        method = readPositiveInt("Choose a method: ");
    }


    // Метод Сімпсона працює тільки для парної кількості проміжків.
    // Якщо користувач вибрав метод Сімпсона або всі методи,
    // а n є непарним, збільшуємо n на 1.
    if ((method == 4 || method == 5) && n % 2 != 0)
    {
        n++;

        printf("\nFor Simpson's method, n must be even.\n");
        printf("The number of intervals was changed to %d.\n", n);
    }


    //                       ОСНОВНИЙ РОЗРАХУНОК


    // Якщо користувач вибрав один конкретний метод,
    // викликається відповідна функція розрахунку.
    if (method >= 1 && method <= 4)
    {
        result = calculateIntegral(a, b, n, method);

        printf("\n=============================================\n");
        printf("                    RESULT\n");
        printf("=============================================\n");


        // Визначення назви вибраного методу.
        if (method == 1)
        {
            printResult(
                "Left rectangles",
                a,
                b,
                n,
                result
            );
        }
        else if (method == 2)
        {
            printResult(
                "Right rectangles",
                a,
                b,
                n,
                result
            );
        }
        else if (method == 3)
        {
            printResult(
                "Trapezoids",
                a,
                b,
                n,
                result
            );
        }
        else
        {
            printResult(
                "Simpson's method",
                a,
                b,
                n,
                result
            );
        }
    }


    // Якщо користувач вибрав пункт 5,
    // інтеграл обчислюється одразу всіма чотирма методами.
    if (method == 5)
    {
        printf("\n=============================================\n");
        printf("           RESULTS FOR ALL METHODS\n");
        printf("=============================================\n");

        printf("%-25s %-15s\n", "Method", "Integral");
        printf("---------------------------------------------\n");

        printf(
            "%-25s %-15.10f\n",
            "Left rectangles",
            leftRectangles(a, b, n)
        );

        printf(
            "%-25s %-15.10f\n",
            "Right rectangles",
            rightRectangles(a, b, n)
        );

        printf(
            "%-25s %-15.10f\n",
            "Trapezoids",
            trapezoids(a, b, n)
        );

        printf(
            "%-25s %-15.10f\n",
            "Simpson's method",
            simpson(a, b, n)
        );
    }

    //                 ТАБЛИЦЯ ДЛЯ РІЗНИХ n

    // розрахунки при декількох значеннях n.
    // Використовуємо:
    // n = 10, 100, 1000, 10000.
    printf("\n=============================================\n");
    printf("          RESULTS FOR DIFFERENT N\n");
    printf("=============================================\n");

    printf(
        "%-10s %-18s %-18s %-18s %-18s\n",
        "n",
        "Left rectangles",
        "Right rectangles",
        "Trapezoids",
        "Simpson"
    );

    printf(
        "-------------------------------------------------------------------------------\n"
    );


    // Масив містить значення кількості проміжків,
    // для яких потрібно провести порівняльний розрахунок.
    int testN[] = {10, 100, 1000, 10000};

    int i;

    // Цикл перебирає всі задані значення n
    // та обчислює інтеграл чотирма методами.
    for (i = 0; i < 4; i++)
    {
        int currentN = testN[i];

        printf(
            "%-10d %-18.10f %-18.10f %-18.10f %-18.10f\n",
            currentN,
            leftRectangles(a, b, currentN),
            rightRectangles(a, b, currentN),
            trapezoids(a, b, currentN),
            simpson(a, b, currentN)
        );
    }


    //              ПОШУК НЕОБХІДНОЇ КІЛЬКОСТІ N


    // На цьому етапі визначається така кількість проміжків N,
    // при якій похибка чисельного розрахунку
    // не перевищує задане значення epsilon.
    // Використовується:
    // I1 = I(N)
    // I2 = I(N + 2)
    // Delta = |I1 - I2|
    // Якщо Delta <= epsilon, необхідну точність досягнуто.
    printf("\n=============================================\n");
    printf("       REQUIRED NUMBER OF INTERVALS\n");
    printf("=============================================\n");


    {
        int requiredN;
        double integralValue;


        // Пошук N для методу лівих прямокутників.
        requiredN = findRequiredN(
            a,
            b,
            epsilon,
            1,
            &integralValue
        );

        printf("\nLeft rectangles:\n");
        printf("N = %d\n", requiredN);
        printf("Integral = %.10f\n", integralValue);


        // Пошук N для методу правих прямокутників.
        requiredN = findRequiredN(
            a,
            b,
            epsilon,
            2,
            &integralValue
        );

        printf("\nRight rectangles:\n");
        printf("N = %d\n", requiredN);
        printf("Integral = %.10f\n", integralValue);


        // Пошук N для методу трапецій.
        requiredN = findRequiredN(
            a,
            b,
            epsilon,
            3,
            &integralValue
        );

        printf("\nTrapezoids:\n");
        printf("N = %d\n", requiredN);
        printf("Integral = %.10f\n", integralValue);


        // Пошук N для методу Сімпсона.
        requiredN = findRequiredN(
            a,
            b,
            epsilon,
            4,
            &integralValue
        );

        printf("\nSimpson's method:\n");
        printf("N = %d\n", requiredN);
        printf("Integral = %.10f\n", integralValue);
    }


    printf("\n=============================================\n");
    printf("             PROGRAM FINISHED\n");
    printf("=============================================\n");


    return 0;
}

