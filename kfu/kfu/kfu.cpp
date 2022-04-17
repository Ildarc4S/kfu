#include <iostream>
#include <cmath>
#include <ctime>

                 //РАСКОМЕНТИРУЙ ЧТОБЫ:
//#define NON                       // ВКЛЮЧИТЬ РЕШЕНИЕ НЕЛИНЕЙНОГО УРАВНЕНИЯ
//define INTEG                      // ВКЛЮЧИТЬ РЕШЕНИЕ ИНТЕГРАЛА
//#define PRINT                     // ВКЛЮЧИТЬ АВОМАТИЧЕСКОЕ СРАВНЕНИЕ МЕТОДОВ ИНТЕГРИРОВАНИЯ 

double a{ }, b{  }, e{ };

double timef(double f(void))
{
    clock_t start = clock(); //фиксирование времени перед функцией
    f();
    clock_t end = clock();//фиксирование времени после выполнения функции
    double seconds = (double)(end - start) / CLOCKS_PER_SEC; // CLOCKS_PER_SEC - число тактов, выполняемое процессором в секунду

    return seconds;
}

template <typename T>
void input(T& a, T& b, T& eps)
{
    std::cout << "Введите левую границу = ";
    std::cin >> a;
    std::cout << "\nВведите правую границу = ";
    std::cin >> b;
    std::cout << "\nВведите точность = ";
    std::cin >> eps;
    std::cout << "\n";
}

namespace nonlinearEquations 
{
    double funcNonlinear(double x)
    {
        return sin(x) - 1 / x;
    }
    double funcNonlinearEquationSolve()
    {
        double c{ };

        do {
            c = (a + b) / 2; //выбор середины отрезка в качестве приблежения корня

            //////выбор отрезка
            if (funcNonlinear(a) * funcNonlinear(c) <= 0) { b = c; }
            else { a = c;}
            /////////

        } while (b - a > 2 * e); //(b-a)/2 - полученная нами точность 
                                 // сравниваем заданную точность с полученной точностью
        return (a + b) / 2;
    }
}
namespace Integral
{
    double funcIntegral(double x) {
        return (10 - x);
    }

    double rectangleIntegral(double a, double b, int n)
    {
        double x, h;
        double sum = { 0.0 };

        h = (b - a) / n;  //шаг

        for (int i = 0; i < n; i++) {
            x = a + i * h;
            sum += funcIntegral(x);
        }
        return (sum * h); //приближенное значение интеграла равно 
                          //сумма площадей прямоугольников
    }
    double mainRectangleIntegral()
    {

        double s1, s;
        int n = 1; //начальное число шагов

        s1 = rectangleIntegral(a, b, n); //первое приближение для интеграла

        do {
            s = s1;     //второе приближение
            n = 2 * n;  //уменьшение значения шага в два раза

            s1 = rectangleIntegral(a, b, n);
        } while (abs(s1 - s) > e);  //сравнение приближений  c точностью
        return s1;
        std::cout << "Интеграл = " << s1 << std::endl;
    }

    double simpsonIntegral(double a, double b, int n)
    {
        const double h = (b - a) / n;
        double k1{ 0.0 }, k2{ 0.0 };

        for (int i = 1; i < n; i += 2)
        {
            k1 += funcIntegral(a + i * h);
            k2 += funcIntegral(a + (i + 1) * h);
        }

        return h / 3 * (funcIntegral(a) + 4 * k1 + 2 * k2);
    }
    double mainSimpsonIntegral()
    {
        double s1, s;
        int n = 1; //начальное число шагов


        s1 = simpsonIntegral(a, b, n); //первое приближение для интеграла
        do {
            s = s1;     //второе приближение
            n = 2 * n;  // уменьшение значения шага в два раза
            s1 = simpsonIntegral(a, b, n);
        } while (abs(s1 - s) > e);  //сравнение приближений с точностью

        return s1;
    }

}




int main() {

    setlocale(LC_ALL, "Rus");
    double timeRectangleIntegral{};
    double timeSimpsonIntegral{};

#ifdef NON

    std::cout << "_______Нелинейные уравнения_____" << std::endl;

    input(a, b, e);//ввод данных для нелинейных ур-ий:  a и b - границы, e - точность
    double result = nonlinearEquations::funcNonlinearEquationSolve();
    std::cout << "Корень: " << result << std::endl;
#endif // NON

    std::cout << "_________________________________" << std::endl;
    std::cout << "\n";

#ifdef INTEG

    std::cout << "_______Интегралы_____" << std::endl;
    input(a, b, e); //ввод данных для интегралов:   a и b - границы, e - точность

    timeRectangleIntegral = timef(Integral::mainRectangleIntegral);  //замер времени первого алгоритма
    std::cout << "Интеграл(прямоугольник) = " << Integral::mainRectangleIntegral() << std::endl;

    timeSimpsonIntegral = timef(Integral::mainSimpsonIntegral);//замер времени второго алгоритма
    std::cout << "Интеграл(Симпсон) = " << Integral::mainSimpsonIntegral() << std::endl;


#ifndef PRINT
    {
        std::cout << "\nВремя первого алгоритма = " << timeRectangleIntegral << std::endl;
        std::cout << "\nВремя второго алгоритма = " << timeSimpsonIntegral << std::endl;

    }
#endif

#ifdef PRINT
    if (timeRectangleIntegral > timeSimpsonIntegral)
    {
        std::cout << "\nМетод Cимпсона быстрее!" << std::endl;
    }
    else
    {
        std::cout << "\nМетод прямоугольников быстрее!" << std::endl;
    }
#endif 

#endif // INTEG

}

