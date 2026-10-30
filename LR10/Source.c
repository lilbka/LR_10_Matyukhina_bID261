#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#include <locale.h>
#include <stdio.h>
#include <math.h>


double F1(double x);
double F2(double x);
double cot_std(double x);
double cot_n(double x, int N);
double cot_eps(double x, double epps);

int main()
{
	setlocale(LC_ALL, "RUS");

	// задание 1

	double x, f1_val, f2_val, result;
	int choice;

    do
    {
        printf("\n1. вычислить значение F1(x)\n");
        printf("2. вычислить значение F2(x)\n");
        printf("3. произведение F1(x) * F2(x)\n");
        printf("4. разность квадратов F1(x)^2 - F2(x)^2\n");
        printf("5. удвоенная сумма 2 * (F1(x) + F2(x))\n");
        printf("0. выход\n\n");
        printf("выберите действие: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            break;
        }

        printf("введите x: ");
        scanf("%lf", &x);

        f1_val = F1(x);
        f2_val = F2(x);

        switch (choice)
        {
        case 1:
            result = f1_val;
            printf("\nF1(%.2lf) = %lf\n", x, result);
            break;
        case 2:
            result = f2_val;
            printf("\nF2(%.2lf) = %lf\n", x, result);
            break;
        case 3:
            result = f1_val * f2_val;
            printf("\nпроизведение F1 * F2 = %lf\n", result);
            break;
        case 4:
            result = pow(f1_val, 2) - pow(f2_val, 2);
            printf("\nразность квадратов (F1^2 - F2^2) = %lf\n", result);
            break;
        case 5:
            result = 2.0 * (f1_val + f2_val);
            printf("\nудвоенная сумма 2*(F1 + F2) = %lf\n", result);
            break;
        default:
            printf("\nневерный выбор.\n");
        }

    } 
    
    while (choice != 0);

	// задание 2, вариант 9

    double x2, res_std, res_n, res_eps, dev_n, dev_eps;
    int N;
    double epps;

    printf("\n\n\nвведите x (|x| < пи, x != 0): ");
    scanf("%lf", &x2);

    if (fabs(x2) >= M_PI || x2 == 0.0) 
    {
        printf("|x| должно быть меньше %.4lf и не равно 0.\n", M_PI);

        return 1;
    }

    printf("введите количество членов ряда (от 1 до 6): ");
    scanf("%d", &N);

    if (N < 1 || N > 6) 
    {
        printf("должно быть от 1 до 6.\n");

        return 1;
    }

    printf("введите точность (например, 0,0001): ");
    scanf("%lf", &epps);

    if (epps <= 0)
    {
        printf("точность должна быть положительной.\n");
        return 1;
    }

    res_std = cot_std(x2);
    res_n = cot_n(x2, N);
    res_eps = cot_eps(x2, epps);

    dev_n = fabs(res_n - res_std);
    dev_eps = fabs(res_eps - res_std);

    printf("| метод                  | результат  | отклонение         |\n");
    printf("------------------------------------------------------------\n");
    printf("| стандартная функция    | %10.6lf | %+18.4le |\n", res_std, 0.0);
    printf("| ряд (N = %d)            | %10.6lf | %+18.4le |\n", N, res_n, dev_n);
    printf("| ряд (epps = %.0le)      | %10.6lf | %+18.4le |\n", epps, res_eps, dev_eps);
    printf("------------------------------------------------------------\n");

}

double F1(double x)
{
    double y;

    if (x <= 3.0)
    {
        y = x * x - 3.0 * x + 9.0;
    }
    else
    {
        y = 1.0 / (pow(x, 3) + 3.0);
    }

    return y;
}

double F2(double x)
{
    double y = x * exp(sin(x * x));
    return y;
}

double cot_std(double x)
{
    return 1.0 / tan(x);
}

double cot_n(double x, int N)
{
    double sum = 1.0 / x;
    double power = x;

    for (int i = 0; i < N; i++)
    {
        if (i > 0)
        {
            power = power * (x * x);
        }

        double coeff = 0.0;

        switch (i) 
        {
        case 0: coeff = 1.0 / 3.0;
            break;
        case 1: coeff = 1.0 / 45.0; 
            break;
        case 2: coeff = 2.0 / 945.0; 
            break;
        case 3: coeff = 1.0 / 4725.0; 
            break;
        case 4: coeff = 2.0 / 93555.0; 
            break;
        case 5: coeff = 1382.0 / 638512875.0;
            break;
        }

        sum = sum - (coeff * power);
    }

    return sum;
}

double cot_eps(double x, double epps)
{
    double sum = 1.0 / x;
    double power = x;

    for (int i = 0; i < 6; i++)
    {
        if (i > 0)
        {
            power = power * (x * x);
        }

        double coeff = 0.0;

        switch (i) 
        {
        case 0: coeff = 1.0 / 3.0; 
            break;
        case 1: coeff = 1.0 / 45.0; 
            break;
        case 2: coeff = 2.0 / 945.0; 
            break;
        case 3: coeff = 1.0 / 4725.0; 
            break;
        case 4: coeff = 2.0 / 93555.0;
            break;
        case 5: coeff = 1382.0 / 638512875.0; 
            break;
        }

        double term = coeff * power;

        if (fabs(term) < epps) 
        {
            break;
        }

        sum = sum - term;
    }

    return sum;
}