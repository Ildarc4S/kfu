#include <iostream>
#include <cmath>
#include <ctime>

                 //РАСКОМЕНТИРУЙ ЧТОБЫ:
//#define NON                       // ВКЛЮЧИТЬ РЕШЕНИЕ НЕЛИНЕЙНОГО УРАВНЕНИЯ
//#define INTEG                      // ВКЛЮЧИТЬ РЕШЕНИЕ ИНТЕГРАЛА
//#define PRINT                     // ВКЛЮЧИТЬ АВОМАТИЧЕСКОЕ СРАВНЕНИЕ МЕТОДОВ ИНТЕГРИРОВАНИЯ 



namespace addition
{
    double a{ }, b{  }, e{ };

    double timeRectangleIntegral{};
    double timeSimpsonIntegral{};

    double timef(double f(void));

    template <typename T>
    void input(T& a, T& b, T& eps);

    double funcIntegral(double x);
    double funcNonLinear(double x);
}

namespace nonlinearEquations 
{
    double funcNonlinearEquationSolve();
}

namespace Integral
{
    double rectangleIntegral(double a, double b, int n);
    double mainRectangleIntegral();

    double simpsonIntegral(double a, double b, int n);
    double mainSimpsonIntegral();

}

int main() {

    setlocale(LC_ALL, "Rus");

#ifdef NON

    std::cout << "_______Нелинейные уравнения_____" << std::endl;

    addition::input(addition::a, addition::b, addition::e);//ввод данных для нелинейных ур-ий:  a и b - границы, e - точность
    double result = nonlinearEquations::funcNonlinearEquationSolve();
    std::cout << "Корень: " << result << std::endl;
#endif // NON

    std::cout << "_________________________________" << std::endl;
    std::cout << "\n";

#ifdef INTEG

    std::cout << "_______Интегралы_____" << std::endl;
    addition::input(addition::a, addition::b, addition::e); //ввод данных для интегралов:   a и b - границы, e - точность

    addition::timeRectangleIntegral = addition::timef(Integral::mainRectangleIntegral);  //замер времени первого алгоритма
    std::cout << "Интеграл(прямоугольник) = " << Integral::mainRectangleIntegral() << std::endl;

    addition::timeSimpsonIntegral = addition::timef(Integral::mainSimpsonIntegral);//замер времени второго алгоритма
    std::cout << "Интеграл(Симпсон) = " << Integral::mainSimpsonIntegral() << std::endl;


#ifndef PRINT
    {
        std::cout << "\nВремя первого алгоритма = " << addition::timeRectangleIntegral << std::endl;
        std::cout << "\nВремя второго алгоритма = " << addition::timeSimpsonIntegral << std::endl;

    }
#endif //PRINT

#ifdef PRINT
    if (addition::timeRectangleIntegral > addition::timeSimpsonIntegral)
    {
        std::cout << "\nМетод Cимпсона быстрее!" << std::endl;
    }
    else
    {
        std::cout << "\nМетод прямоугольников быстрее!" << std::endl;
    }
#endif //PRINT


#endif // INTEG

}

template <typename T>
void addition::input(T& a, T& b, T& eps)
{
    std::cout << "Введите левую границу = ";
    std::cin >> a;
    std::cout << "\nВведите правую границу = ";
    std::cin >> b;
    std::cout << "\nВведите точность = ";
    std::cin >> eps;
    std::cout << "\n";
}
double addition::timef(double f(void))
{
    clock_t start = clock(); //фиксирование времени перед функцией
    f();
    clock_t end = clock();//фиксирование времени после выполнения функции
    double seconds = (double)(end - start) / CLOCKS_PER_SEC; // CLOCKS_PER_SEC - число тактов, выполняемое процессором в секунду

    return seconds;
}
double addition::funcNonLinear(double x)
{
    return sin(x) - 1 / x;
}
double addition::funcIntegral(double x)
{
    return 10-x;
}

double nonlinearEquations::funcNonlinearEquationSolve()
{
    double c{ };

    do {
        c = (addition::a + addition::b) / 2; //выбор середины отрезка в качестве приблежения корня

        //////выбор отрезка
        if (addition::funcNonLinear(addition::a) * addition::funcNonLinear(c) <= 0) { addition::b = c; }
        else { addition::a = c; }
        /////////

    } while (addition::b - addition::a > 2 * addition::e); //(b-a)/2 - полученная нами точность 
                             // сравниваем заданную точность с полученной точностью
    return (addition::a + addition::b) / 2;
}

double Integral::rectangleIntegral(double a, double b, int n)
{
    double x, h;
    double sum = { 0.0 };

    h = (b - a) / n;  //шаг

    for (int i = 0; i < n; i++) {
        x = a + i * h;
        sum += addition::funcIntegral(x);
    }
    return (sum * h); //приближенное значение интеграла равно 
                      //сумма площадей прямоугольников
}
double Integral::simpsonIntegral(double a, double b, int n)
{
    const double h = (b - a) / n;
    double k1{ 0.0 }, k2{ 0.0 };

    for (int i = 1; i < n; i += 2)
    {
        k1 += addition::funcIntegral(a + i * h);
        k2 += addition::funcIntegral(a + (i + 1) * h);
    }

    return h / 3 * (addition::funcIntegral(a) + 4 * k1 + 2 * k2);
}
double Integral::mainRectangleIntegral()
{

    double s1, s;
    int n = 1; //начальное число шагов

    s1 = Integral::rectangleIntegral(addition::a, addition::b, n); //первое приближение для интеграла

    do {
        s = s1;     //второе приближение
        n = 2 * n;  //уменьшение значения шага в два раза

        s1 = Integral::rectangleIntegral(addition::a, addition::b, n);
    } while (abs(s1 - s) > addition::e);  //сравнение приближений  c точностью
    
    return s1;
}
double Integral::mainSimpsonIntegral()
{
    double s1, s;
    int n = 1; //начальное число шагов


    s1 = Integral::simpsonIntegral(addition::a, addition::b, n); //первое приближение для интеграла
    do {
        s = s1;     //второе приближение
        n = 2 * n;  // уменьшение значения шага в два раза
        s1 = Integral::simpsonIntegral(addition::a, addition::b, n);
    } while (abs(s1 - s) > addition::e);  //сравнение приближений с точностью

    return s1;
}
