#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#include <locale.h>
#include <stdio.h>
#include <math.h>

double s_parallelogram(double a, double h); // площадь
void def(void); // определение
int draw(int h, int a, int alpha, char symbol); // рисование
int compare(double a1, double h1, double a2, double h2); // сравнение

int main() // задание 3, вариант 18
{
    setlocale(LC_CTYPE, "RUS");

    int choice;

    do
    {
        printf("\n\n\n1. рассчитать площадь параллелограмма\n");
        printf("2. вывести определение фигуры\n");
        printf("3. нарисовать фигуру\n");
        printf("4. сравнить два параллелограмма по площади\n");
        printf("0. выход\n");
        printf("выберите действие: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            double a, h, area;
            printf("введите основание (a): ");
            scanf("%lf", &a);
            printf("введите высоту (h): ");
            scanf("%lf", &h);

            area = s_parallelogram(a, h);
            printf("ѕлощадь параллелограмма: %.2lf\n", area);

            break;
        }
        case 2:
            def();

            break;
        case 3:
        {
            int h, a, alpha;
            char symbol;
            printf("введите высоту: ");
            scanf("%d", &h);
            printf("введите основание: ");
            scanf("%d", &a);
            printf("введите угол наклона: ");
            scanf("%d", &alpha);
            printf("введите символ дл€ контура: ");
            scanf(" %c", &symbol);

            if (h < 2 || a < 2 || alpha <= 0 || alpha >= 90)
            {
                printf("h, a должны быть >= 2, а угол от 1 до 89.\n");
            }
            else 
            {
                int count = draw(h, a, alpha, symbol);

                printf("\n[напечатано %d символов контура]\n", count);
            }

            break;
        }
        case 4:
        {
            double a1, h1, a2, h2;
            printf("введите основание первого параллелограмма: ");
            scanf("%lf", &a1);
            printf("¬ведите высоту первого параллелограмма: ");
            scanf("%lf", &h1);

            printf("¬ведите основание второго параллелограмма: ");
            scanf("%lf", &a2);
            printf("¬ведите высоту второго параллелограмма: ");
            scanf("%lf", &h2);

            int compare_res = compare(a1, h1, a2, h2);

            if (compare_res == 1) 
            {
                printf("первый параллелограмм больше.\n");
            }
            else if (compare_res == -1)
            {
                printf("второй параллелограмм больше.\n");
            }
            else 
            {
                printf("площади параллелограммов равны.\n");
            }

            break;
        }
        case 0:
            break;

        default:
            printf("неверный выбор.\n");
        }

    } 
    
    while (choice != 0);

    return 0;
}


double s_parallelogram(double a, double h)
{
    return a * h;
}

void def(void)
{
    printf("\nопределение:\n");
    printf("параллелограмм Ч это четырехугольник, у которого противоположные стороны попарно параллельны.\n");
}

int draw(int h, int a, int alpha, char symbol)
{
    int count = 0;
    double rad = alpha * M_PI / 180.0;
    int shift = (int)(1.0 / tan(rad));

    if (shift < 1)
    {
        shift = 1;
    }

    for (int i = 0; i < h; i++)
    {
        for (int s = 0; s < i * shift; s++) printf(" ");

        if (i == 0 || i == h - 1)
        {
            for (int j = 0; j < a; j++)
            {
                printf("%c", symbol);
                count++;
            }
        }

        else
        {
            printf("%c", symbol);
            count++;
            for (int j = 0; j < a - 2; j++) printf(" ");
            printf("%c", symbol);
            count++;
        }

        printf("\n");
    }

    return count;
}

int compare(double a1, double h1, double a2, double h2)
{
    double area1 = a1 * h1;
    double area2 = a2 * h2;

    if (area1 > area2)
    {
        return 1;
    }

    else if (area1 < area2) 
    {
        return -1;
    }

    else 
    {
        return 0;
    }
}