#include "pch.h"
#include <vector>
#include <iostream>
#include <fstream>
#define MAX 100
using namespace std;

struct Arc {
	long vertex1, vertex2;
	long weight;
};
void printWay(int cur, int start, int prev[MAX]) {
	if (cur != start) {
		printWay(prev[cur], start, prev);
	};
	cout << cur+1 << ' ';
	
};
void Dijkstra(int GR[MAX][MAX], int size, int st, int finish)
{
	int prev[MAX];
	int distance[MAX], count, index, i, u, m = st + 1;
	bool visited[MAX];
	for (i = 0; i < size; i++)
	{
		distance[i] = INT_MIN; visited[i] = false;
		prev[i] = INT_MAX;
	}
	distance[st] = 0;
	prev[st] = 0;
	for (count = 0; count < size - 1; count++)
	{
		int max = INT_MIN;
		for (i = 0; i < size; i++)
			if (!visited[i] && distance[i] > max)
			{
				max = distance[i]; index = i;
			}
		u = index;
		visited[u] = true;
		for (i = 0; i < size; i++) {
			if (!visited[i] && GR[u][i] && distance[u] != INT_MIN &&
				(distance[u] > distance[i] && GR[u][i] > distance[i])) {
				prev[i] = u;
				if (distance[u] < GR[u][i] && distance[u] != 0) {
					distance[i] = distance[u];
				}
				else {
					distance[i] = GR[u][i];
				}
			}
		}
	}
	cout << "Стоимость пути из начальной вершины до остальных:\t\n";
	for (int i = 0; i < size; i++) {
		if (distance[i] != INT_MIN) {
			cout << m << " > " << i + 1 << " = " << distance[i] << endl;
		}
		else {
			cout << m << " > " << i + 1 << " = " << "маршрут недоступен" << endl;
		}
	}
	int tempPrev;
	if (prev[finish] != st - 1 && prev[finish] != INT_MAX) {
		cout << "путь -> ";
		tempPrev = prev[finish];
		printWay(tempPrev, st, prev);
		cout << finish + 1 << endl;
	}
	else {
		cout << "пути нет" << endl;
	}
}

int main()
{
	int g[MAX][MAX];
	int N, start, finish;
	setlocale(LC_ALL, "rus");
	vector <Arc> vecMatrixArc;
	Arc arc;
	std::ifstream fin("input.txt");
	if (fin.is_open()) {
		fin >> N >> start >> finish; //size from to
		while (fin >> arc.vertex1 >> arc.vertex2 >> arc.weight) {
			vecMatrixArc.push_back(arc);
		}
	}
	else {
		cout << "Файл не может быть открыт!\n";
		return 0;
	}
	fin.close();
	vector <long> vecMatrixLong;
	cout << N << " " << start << " " << finish << endl;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			g[i][j] = 0;
		}
	}
	//инициализация не нулевых дуг
	for (int i = 0; i < vecMatrixArc.size(); i++) {
		cout << vecMatrixArc[i].vertex1 << " " << vecMatrixArc[i].vertex2 << " " << vecMatrixArc[i].weight << endl;
		g[vecMatrixArc[i].vertex1-1][vecMatrixArc[i].vertex2-1] = vecMatrixArc[i].weight;
		g[vecMatrixArc[i].vertex2-1][vecMatrixArc[i].vertex1-1] = vecMatrixArc[i].weight;
	}
	Dijkstra(g, N, start - 1, finish - 1);
	
}