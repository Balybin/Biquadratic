#include <iostream>
#include <fstream>
#include "Matrix.h"
#include "LOS.h"
#include <cmath>
//i	| j  
//n	| m  <--вот их вообще логично было бы поменять местами, но
//x	| y  я глупенький и мне лень переписывать, поэтому будет так
using namespace std;

double lyambda=1, gamma=1;

double U(double x, double y)
{
//	return x + y;					//F=U
//	return x * x + y * y;			//F=x^2+y^2-4
//	return x * x * x + y * y * y;	//F=x^3-6x+y^3-6y
//	return x*x*x*x + y*y*y*y;		//F=x^4-12x^2+y^4-12y^2
	return exp(x) + exp(y);			//F = 0
//	return sin(x + y);				//F = 3 * sin(x + y);
}

double F(double x, double y)
{
//	return (x + y);										//U=F
//	return x * x + y * y - 4;							//U=x^2+y^2
//	return x*x*x - 6*x + y*y*y - 6*y;					//U=x^3+y^3
//	return x*x*x*x + y*y*y*y - 12 * x*x - 12 * y*y;		//U=x^4+y^4
	return 0;											//U = e^x+e^y
//	return 3 * sin(x + y);								//U = sin(x + y);	
}

int Gx[3][3] = {
	7, -8, 1,
	-8, 16, -8,
	1, -8, 7 },
	Gy[3][3] = {
	7, -8, 1,
	-8, 16, -8,
	1, -8, 7 },
	Mx[3][3] = {
	4, 2, -1,
	2, 16, 2,
	-1, 2, 4 },
	My[3][3] = {
	4, 2, -1,
	2, 16, 2,
	-1, 2, 4 };

int m(int i)
{
	i = (i % 3);
	return i;
}
int v(int i)
{
	//return (i - 1) / 3 + 1;
	int buf = i / 3;
	return buf;
}

double Gmatrix111(int i, int j)
{

	return (Gx[m(i)][m(j)] * My[v(i)][v(j)]  + Mx[m(i)][m(j)] * Gy[v(i)][v(j)]);
}
double Mmatrix111(int i, int j)
{

	return (Mx[m(i)][m(j)] * My[v(i)][v(j)]);
}

double Gmatrix(double Hx, double Hy, int i, int j)
{
	return lyambda * (Gx[m(i)][m(j)]/(3 * Hx) * My[v(i)][v(j)] * Hy / 30 + Mx[m(i)][m(j)] * Hx / 30 * Gy[v(i)][v(j)] / (3 * Hy));
}
double Mmatrix(double Hx, double Hy, int i, int j)
{
	int i1 = m(i), j1 = m(j), i2 = v(i), j2 = v(j);
	return gamma * (Mx[i1][j1] * Hx / 30 * My[i2][j2] * Hy / 30);
}
double Fvector(double Hx, double Hy, int i, double *f)
{
	double sum = 0;
	for (int j = 0; j < 9; j++)
	{
		sum += (Mx[m(i)][m(j)] * Hx / 30 * My[v(i)][v(j)] * Hy / 30) * f[j];
	}
	return sum;
}

void main()
{
	ofstream out;
	LOS los;
	Matrix A;
	A.make(los.A);
	los.make();
	out.open("Mmatrix.txt");
	los.outputMatrix(out);
	out.close();
	//out.open("GM.txt");
	//for (int i = 0; i < 9; ++i)
	//{
	//	for (int j = 0; j < 9; ++j)
	//	{
	//		out << Gmatrix111(i, j) << "\t\t" ;
	//	}
	//	out << endl;
	//}
	//out << endl << endl << endl;
	//for (int i = 0; i < 9; ++i)
	//{
	//	for (int j = 0; j < 9; ++j)
	//	{
	//		out << Mmatrix111(i,j) << "\t\t";
	//	}
	//	out << endl;
	//}
	//out << endl << endl << endl;
	//for (int i = 0; i < 9; ++i)
	//{
	//	for (int j = 0; j < 9; ++j)
	//	{
	//		out << Mmatrix111(i,j) + Gmatrix111(i,j) << "\t\t";
	//	}
	//	out << endl;
	//}
	//out.close();
	los.LUdec();
	los.LOS_LU();
	for (int i = 0;i < los.A.n;i++)
	{
		cout << los.A.F.V[i] << " ";
	}
	out.open("result.txt");
	out << "x: ";
	for (int i = 0; i < A.grid.n; i++)
	{
		out << A.grid.X[i] << " ";
	}
	out << endl << "y: ";
	for (int i = 0; i < A.grid.m; i++)
	{
		out << A.grid.Y[i] << " ";
	}
	out << endl << "U(x,y): " << endl;
	for (int i = 0; i < A.n; i++)
	{
		out << los.x0.V[i] << endl;
	}
	out << endl;
	out.close();
	//system("pause");
}