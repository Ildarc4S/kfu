#include <iostream>
#include <cmath>

double integrlFunc(double x)
{
	return sin(x);
}
double func(double x)
{
	return pow(x, 3) - 7 * pow(x, 2) +7* x + 15;
}
double funcDerivativeOne(double x)
{
	return 3*pow(x, 2) - 14 * x + 7;
}
double funcDerivativeTwo(double x)
{
	return 6*x - 14;
}

void iterFunc(double f(double, double, double,int &), double a, double b, double e)
{
	int n = 1;
	for (double i = a; i < b; i += 0.005)
	{
		int iter = 0;
		if (func(a) * func(i) < 0)
		{
			std::cout << "Root#" <<n << " = " << f(a, i, e, iter) << std::endl;
			std::cout << "Iter =  " << iter << "\n\n";
			n++;
			a = i;
		}
	}
}



double funcNonlinearEquationSolve(double a, double b, double e,int &iter)
{
	double c = 0.0;

	do
	{
		c = (a + b) / 2;

		if (func(a) * func(c) < 0)
		{
			b = c;
		}
		else
		{
			a = c;
		}

		iter++;

	} while ((fabs(b - a)) > e);

	return c;
}
double funcNonlinearEquationSolveNewton(double a,double b,double e, int& iter)
{

	double x0, xn;

	if (func(a) * func(b) < 0) 
	{
		if (func(a) * funcDerivativeTwo(a) > 0) //выбирается такое число x0, при котором f(x0) имеет тот же знак, что и f''(x0)
			x0 = a;                             //выбирается точка с абсциссой x0, в которой касательная к кривой y = f(x) на отрезке[a; b] пересекает ось Ox.
		else
			x0 = b;

		xn = x0 - func(x0) / funcDerivativeOne(x0); // считаем первое приближение

		while (fabs(x0-xn) > e) // пока не достигнем необходимой точности, будет продолжать вычислять
		{
			x0 = xn;
			if (funcDerivativeOne == 0)
				break;

			iter++;
			xn = x0 - func(x0) / funcDerivativeOne(x0); // формула Ньютона
		}
	}
	else
	{
		return 0;
	}

	return xn;

}

double integralLeftRectangle(double a, double b, double n)
{
	double sum{ 0.0 }, h = (b - a) / n;

	for (int i = 0; i < n-1; i++)
	{
		sum += h * func(a + i * h);
	}

	return sum;
}
double integralSimpson(double a, double b, double n)
{
	double sum = integrlFunc(a)+integrlFunc(b), h = (b - a) / n;
	int ind;

	for (int i = 1; i < n - 1; i++)
	{
		ind = 2 + 2 * (i % 2);//умножение либо на 4, либо на 2 в зависимости от четноти i
		sum += ind * func(a + i * h);
	}
	sum *= h / 3;

	return sum;
}

void Integral(double f(double, double, double), double a, double b, double e)
{

	double s1, s;
	int n = 1; //начальное число шагов


	s1 = f(a, b, n); //первое приближение для интеграла
	do {
		s = s1;     //второе приближение
		n = 2 * n;  // уменьшение значения шага в два раза
		s1 = f(a, b, n);
	} while (abs(s1 - s) > e);  //сравнение приближений с точностью

	std::cout << s1 << "\n";
}

int main()
{
	//нелинейные уравнения

	double a = -4.0, b = 6.0, e = 0.0001;
	std::cout << "-----NonLinear equations---------" << "\n" << std::endl;
	
	iterFunc(funcNonlinearEquationSolveNewton, a, b, e);
	iterFunc(funcNonlinearEquationSolve, a, b, e);


	//интегралы
	a = 1.0;
	b = 2.0;
	e = 0.0001;
	std::cout << "-----Integral---------" << "\n" << std::endl;

	
	Integral(integralLeftRectangle,a, b, e);	
	Integral(integralSimpson, a, b, e);
	
	return 0;
}