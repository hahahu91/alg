// Comp1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
using namespace std;
struct Node
{
	Node *l, *r; //левое и правое поддерево
	int x; //Некоторые данные
	string info;
};
void add_node(int x, string info, Node *&MyTree) //Функция добавления звена в дерево
{
	if (NULL == MyTree)  //То, о чем я в самом начале писал. Если дерева нет, то сеем семечко
	{
		MyTree = new Node; //Выделяем память под звено дерева
		MyTree->x = x; //Записываем данные в звено
		MyTree->info = info;
		MyTree->l = MyTree->r = NULL; //Подзвенья инициализируем пустотой во избежание ошибок
	} else if (x > MyTree->x)   //Если нововведенный элемент x меньше чем элемент x из семечка дерева, уходим влево
	{
		if (MyTree->l != NULL) add_node(x, info, MyTree->l); //При помощи рекурсии заталкиваем элемент на свободный участок
		else //Если элемент получил свой участок, то
		{
			MyTree->l = new Node;  //Выделяем память левому подзвену. Именно подзвену, а не просто звену
			MyTree->l->l = MyTree->l->r = NULL; //У левого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
			MyTree->l->x = x; //Записываем в левое подзвено записываемый элемент 
			MyTree->l->info = info;
		}
	} else if (x = MyTree->x)   //Если нововведенный элемент x больше чем элемент x из семечка дерева, уходим вправо
	{
		if (MyTree->r != NULL) add_node(x, info, MyTree->r); //При помощи рекурсии заталкиваем элемент на свободный участок
		else //Если элемент получил свой участок, то
		{
			MyTree->r = new Node;  //Выделяем память правому подзвену. Именно подзвену, а не просто звену
			MyTree->r->l = MyTree->r->r = NULL; //У правого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
			MyTree->r->x = x; //Записываем в правое подзвено записываемый элемент 
			MyTree->r->info = info;
		}
	}

}
void Show(Node *&tree)
{
	if (NULL == tree)    return;    //Если дерева нет, выходим
	for (int i = 0; i < tree->x; i++) {
		cout << " ";
	}
	cout << tree->info << endl; //Посетили узел
	Show(tree->l); //Обошли левое поддерево   
	Show(tree->r); //Обошли правое поддерево   
}
struct Elem {
	string info;
	int lvl;
};
int main()
{
	setlocale(LC_ALL, "rus");
	char buff[50];
	vector <string> vecStrComp;
	ifstream fin("input.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else {

		stack <struct Elem> steckElems;
		while (!fin.eof()) {
			fin.getline(buff, 50); // считали строку из файла
			vecStrComp.push_back(buff);
		}
		fin.close();
		Node *MyTree = NULL;
		int count = 0;
		for (int i = 0; i < vecStrComp.size(); ++i) {
			cout << vecStrComp[i] << endl;
			int prevCount = count;
			Elem prevElem;
			prevElem.lvl = count;
			if (i == 0) {
				prevElem.info = "root";
			}
			else {
				prevElem.info = vecStrComp[i - 1];
			}
			count = 0;
			//узнаем
			string str = vecStrComp[i];
			for (int k = 0; k < str.length(); k++) {
				if (str[k] == '.' && (k == 0 || str[k - 1] == '.')) {
					count++;
				}
				else {
					vecStrComp[i] = str.substr(count);
					//cout << count << " " << vecStrComp[i];
					break;
				}
			}
			bool looking;
			do {
				looking = false;
				if (prevElem.lvl < count) {
					//cout << " Сын" << endl;
					steckElems.push(prevElem);
				}
				else if (prevElem.lvl == count) {
					//cout << " брат" << endl;
				}
				else {
					if (steckElems.empty()) {
						cout << "ошибка" << endl;
						break;
					}
					else {
						prevElem = steckElems.top();
						steckElems.pop();
						looking = true;
					}
				}
			} while (looking);
			add_node(count, vecStrComp[i], MyTree);
		}
		Show(MyTree);
	}
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
