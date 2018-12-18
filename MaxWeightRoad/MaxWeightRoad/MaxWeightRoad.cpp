// MaxWeightRoad.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#define MAX 100
using namespace std;
struct Arc {
	long vertex1, vertex2;
	long weight;
};

int main()
{
	setlocale(LC_ALL, "rus");
	vector <Arc> vecMatrixArc;
	Arc arc;

	int a[MAX][MAX];// матрица связей
	int d[MAX];//  максимальный вес
	int passed[MAX]; // посещенные вершины
	int prev[MAX]; // из какой вершины макс вес
	int N, M, S;

	std::ifstream fin("input.txt");
	if (fin.is_open()) {
		fin >> N >> M >> S;
		while (fin >> arc.vertex1 >> arc.vertex2 >> arc.weight) {
			vecMatrixArc.push_back(arc);
		}
	}
	else {
		cout << "Файл не может быть открыт!\n";
		exit;
	}
	fin.close();

	vector <long> vecMatrixLong;
	cout << N << " " << M << " " << S << endl;

//инициализация все дуги нулевые
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			a[i][j] = 0;
	}
	//инициализация не нулевых дуг
	for (int i = 0; i < vecMatrixArc.size(); ++i) {
		cout << vecMatrixArc[i].vertex1 << " " << vecMatrixArc[i].vertex2 << " " << vecMatrixArc[i].weight << endl;
		a[vecMatrixArc[i].vertex1][vecMatrixArc[i].vertex2] = vecMatrixArc[i].weight;
		a[vecMatrixArc[i].vertex2][vecMatrixArc[i].vertex1] = vecMatrixArc[i].weight;
	}
	//печать матрицы
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j <= N; j++) {
			if (j == 0) {
				printf("%2d ", i);
			}
			else if (i == 0) {
				printf("%5d ", j);
			}
			else {
				printf("%5d ", a[i][j]);
			}
		}
		printf("\n");
	}
	//Инициализация вершин и расстояний
	for (int i = 1; i <= N; i++)
	{
		d[i] = INT_MIN;
		passed[i] = 1;
	}
	d[M] = INT_MAX;
	prev[M] = M;
	// Шаг алгоритма
	int indexMax, min, temp;
	do {
		indexMax = INT_MIN;
		min = INT_MAX;
		for (int i = 1; i <= N; i++)
		{ // Если вершину ещё не обошли и вес больше min
			if ((passed[i] == 1) && (d[i] < min))
			{ // Переприсваиваем значения
				min = d[i];
				indexMax = i;
			}
		}
		// Добавляем найденный максимальпый вес
		// к текущему весу вершины
		// и сравниваем с текущим максимальпым весом вершины
		if (indexMax != INT_MIN)
		{
			for (int i = 1; i <= N; i++)
			{
				if (a[indexMax][i] > 0)
				{
					temp = a[indexMax][i];
					if (temp > d[i])
					{

						d[i] = temp;
						prev[i] = indexMax;
					}
				}
			}
			passed[indexMax] = 0;
		}
	} while (indexMax > INT_MIN);

	cout << "\nМаксимальный вес до вершин из " << M << ": \n";
	int prevTemp;
	int prevIndex;
	for (int i = 1; i <= N; i++) {
		cout << "В " << i;
		if (d[i] == INT_MAX) {
			cout << "  Any ";
		}
		else if (d[i] == INT_MIN) {
			cout << "  Inf ";
		}
		else {
			printf("%5d ", d[i]);
		}
		cout << " из вершин";
		if (prev[i] == M) {
			cout << "ы";
		}
		else {
			cout << " ";
		}
		cout << " " << prev[i] << " ";
		prevTemp = prev[i];
		while (prevTemp != i) {
			prevIndex = prevTemp;
			prevTemp = prev[prevIndex];
			cout << prevTemp;
		} 
		cout << endl;
	}
	cout << "Максимальный вес из вершины " << M << " в вершину " << S << ": ";
	if (d[S] == INT_MAX) {
		cout << "  Any";
	}
	else if (d[S] == INT_MIN) {
		cout << "  Inf";
	}
	else {
		cout << d[S];
	}
	cout << " из вершин";
	if (prev[S] == M) {
		cout << "ы";
	}
	cout << " "  << prev[S] << " ";
	prevTemp = prev[S];
	while (prevTemp != M) {
		prevIndex = prevTemp;
		prevTemp = prev[prevIndex];
		cout << prevTemp << " ";
	}
	cout << endl;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
