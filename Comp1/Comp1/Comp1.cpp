#include "pch.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

struct Node {
	Node *l, *r, *f; //левое и правое поддерево
	int x; //уровень
	string info;
	bool show = false;
};
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
		Node *fath = NULL;

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
			string str = vecStrComp[i];
			for (int k = 0; k < str.length(); k++) {
				if (str[k] == '.' && (k == 0 || str[k - 1] == '.')) {
					count++;
				}
				else {
					vecStrComp[i] = str.substr(count);
					break;
				}
			}
			bool looking;
			do {
				looking = false;
				if (prevElem.lvl < count) {
					steckElems.push(prevElem);
				}
				else if (prevElem.lvl > count){
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
			searchParent(MyTree, prevElem, fath);
			if (fath != NULL) {
				add_from_fath_node(count, vecStrComp[i], fath);
			}
			else {
				add_node(count, vecStrComp[i], MyTree);
			}
		}
		while (true) {
			cout << " Выберите режим работы:" << endl;
			cout << " [1]Раскрыть все дерево:" << endl;
			cout << " [2]Обход:" << endl;
			cout << " [3]Сохранить:" << endl;
			cout << " [4]выход:" << endl;
			int n;
			cin >> n;
			switch (n) {
				case 1: {
					Show(MyTree);
					break;
				}
				case 2: {
					byPassTree(MyTree);
					break;
				}
				case 3: {
					ofstream fout("output.txt");
					SaveTree(MyTree, fout);
					break;
				}
				case 4: {
					return false;
				}
			}
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

void byPassTree(Node *&tree) {
	bool B = true;
	while (B) {
		cout << " [all]Раскрыть все дерево" << endl;
		cout << " [correct]редактировать дерево" << endl;
		cout << " [exit]В главное меню" << endl;
		cout << " Укажите номер елемента который нужно раскрыть:" << endl;
		int count = 0;
		ShowOpen(tree, *&count);
		string s;
		cin >> s;
		if (s == "exit") {
			B = false;
		}
		else if (s == "all") {
			count = 0;
			ShowOpen(tree, *&count, true);
		}
		else if (s == "correct") {
			count = 0;
			if (correctionTree(tree, *&count)) {
				B = false;
			}
		}
		else {
			count = 0;
			correctElem(tree, *&count, s, "open");
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
void ShowOpen(Node *&tree, int &count, bool show) {
	if (NULL == tree)    return;    //Если дерева нет, выходим
	if (tree->f == NULL || tree->f->show || show) {
		for (int i = 0; i < tree->x; i++) {
			cout << " ";
		}
		cout << "[" << count << "]" << tree->info << endl; //Посетили узел
		count++;
		ShowOpen(tree->l, *&count, show); //Обошли левое поддерево   
		ShowOpen(tree->r, *&count, show); //Обошли правое поддерево   
	}
}
void SaveTree(Node *&tree, ofstream &fout) {
	if (NULL == tree)    return;    //Если дерева нет, выходим
	for (int i = 0; i < tree->x; i++) {
		fout << ".";
	}
	fout << tree->info << endl;
	SaveTree(tree->l, fout); //Обошли левое поддерево   
	SaveTree(tree->r, fout); //Обошли правое поддерево   
}

void add_node(int x, string info, Node *&MyTree)
{
	if (NULL == MyTree)
	{
		MyTree = new Node; //Выделяем память под звено дерева
		MyTree->x = x; //Записываем данные в звено
		MyTree->info = info;
		MyTree->l = MyTree->r = MyTree->f = NULL; //Подзвенья инициализируем пустотой во избежание ошибок
	}
	else if (x > MyTree->x)   //Если нововведенный элемент x меньше чем элемент x из семечка дерева, уходим влево
	{
		if (MyTree->l != NULL) add_node(x, info, MyTree->l); //При помощи рекурсии заталкиваем элемент на свободный участок
		else //Если элемент получил свой участок, то
		{
			MyTree->l = new Node;  //Выделяем память левому подзвену. Именно подзвену, а не просто звену
			MyTree->l->l = MyTree->l->r = NULL; //У левого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
			MyTree->l->x = x; //Записываем в левое подзвено записываемый элемент 
			MyTree->l->info = info;
		}
	}
	else if (x = MyTree->x)   //Если нововведенный элемент x больше чем элемент x из семечка дерева, уходим вправо
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
void searchParent(Node *&tree, struct Elem fath, Node *&father) {
	if (tree != NULL) {
		if (tree->info == fath.info && tree->x == fath.lvl) {
			father = tree;
			return;
		}
		else if (tree->x <= fath.lvl) {
			searchParent(tree->l, fath, father);
			searchParent(tree->r, fath, father);
		}
	}
	return;
}
void add_from_fath_node(int x, string info, Node *&MyTree) //Функция добавления звена в дерево через отца(брата)
{
	if (NULL == MyTree)
	{
		cout << "не задан отец";
		return;
	}
	else if (x > MyTree->x)
	{
		if (MyTree->l != NULL) add_from_fath_node(x, info, MyTree->l);
		else
		{
			MyTree->l = new Node;
			MyTree->l->l = MyTree->l->r = NULL;
			MyTree->l->x = x;
			MyTree->l->info = info;
			MyTree->l->f = MyTree;
		}
	}
	else if (x = MyTree->x)
	{
		if (MyTree->r != NULL) add_from_fath_node(x, info, MyTree->r);
		else
		{
			MyTree->r = new Node;
			MyTree->r->l = MyTree->r->r = NULL;
			MyTree->r->x = x;
			MyTree->r->info = info;
			MyTree->r->f = MyTree->f;
		}
	}

}
void pasteTreeNode(Node *&tree, Node *pasteTree) {
	Node *newTree = NULL;
	Node *paste = pasteTree;
	add_node(tree->x + 1, pasteTree->info, newTree);
	newTree->f = tree;
	newTree->l = newTree->r = NULL;
	newTree->show = false;
	if (paste->l != NULL) {
		newTree->l = new Node;
		newTree->l->x = newTree->x + 1;
		newTree->l->f = newTree;
		copyTreeFunction(newTree->l, paste->l);
	}
	paste_tree_from_fath_node(tree, newTree);
	return;
}
void paste_tree_from_fath_node(Node *&MyTree, Node *&pasteTree) {
	if (NULL == MyTree) {
		cout << "не задан отец";
	}
	else if (pasteTree->x > MyTree->x) {
		if (MyTree->l != NULL) {
			paste_tree_from_fath_node(MyTree->l, pasteTree);
		}
		else {
			MyTree->l = pasteTree;
		}
	}
	else if (pasteTree->x = MyTree->x) {
		if (MyTree->r != NULL) {
			paste_tree_from_fath_node(MyTree->r, pasteTree);
		}
		else {
			MyTree->r = pasteTree;
		}
	}
	return;
}

void deleteTree(Node *&tree) {
	if (tree->r == NULL) {
		freemem(tree);
	}
	else {
		freemem(tree->l);
		tree = tree->r;
	}
	return;
}
void freemem(Node *&tree) {
	if (tree != NULL) {
		freemem(tree->l);
		freemem(tree->r);
		tree = NULL;
	}
}

bool copyTree(Node *copyTreeEl, Node *&tree, int &count) {
	if (tree->f != NULL) {
		copyTree(copyTreeEl, tree->f, *&count);
	}
	else {
		correctionTree(tree, *&count, copyTreeEl);
		return true;
	}

}

bool correctionTree(Node *&tree, int &count, Node *pasteTree) {
	bool B = true;
	while (B) {
		cout << " [exit]В главное меню" << endl;
		cout << " Укажите элемент который нужно изменить" << endl;
		int count = 0;
		ShowOpen(tree, *&count);
		string s;
		cin >> s;
		if (s == "exit") {
			B = false;
		}
		else {
			if (correctionElem(tree, count, s, pasteTree)) {
				return true;
			}
		}
	}
}
bool correctionElem(Node *&tree, int &count, string Elem, Node *pasteTree) {
	bool B = true;
	while (B) {
		cout << " [exit]В главное меню" << endl;
		cout << " [open]раскрыть" << endl;
		cout << " [rename]переименовать" << endl;
		cout << " [create]создать" << endl;
		cout << " [delete]удалить" << endl;
		cout << " [move]перенести" << endl;
		cout << " [copy]скопировать" << endl;
		if (pasteTree != NULL) {
			cout << " [paste]вставить" << endl;
		}
		int count = 0;
		string s;
		cin >> s;
		if (s == "open") {
			correctElem(tree, count, Elem, s, pasteTree);
			return false;
		}
		else if (s == "rename" || s == "create" || s == "delete" || s == "move" || s == "copy" || s == "paste") {
			 correctElem(tree, count, Elem, s, pasteTree);			
		}
		B = false;
	}
}
int correctElem(Node *&tree, int &count, string Elem, string action, Node *pasteTree) {
	if (tree == NULL)    return 0;    //Если дерева нет, выходим
	if (tree->f == NULL || tree->f->show) {
		if (count == atoi(Elem.c_str())) {
			if (action == "open") {
				tree->show = !tree->show;
			}
			else if (action == "rename") {
				cout << "Введите новое имя" << endl;
				string s;
				cin >> s;
				tree->info = s;
				return 1;
			}
			else if (action == "delete") {
				deleteTree(tree);
				count++;
				return 1;
			}
			else if (action == "copy") {
				if (copyTree(tree, tree, *&count)) {
					return 1;
				}
				else return 0;
			}
			else if (action == "move") {
				if (copyTree(tree, tree, *&count)) {
					deleteTree(tree);
					count++;
					return 1;
				}
				else  return 0;
			}
			else if (action == "paste" && pasteTree != NULL) {
				pasteTreeNode(tree, pasteTree);
				count++;
				return 2;
			}
		}
		count++;
		correctElem(tree->l, *&count, Elem, action, pasteTree); //Обошли левое поддерево   
		correctElem(tree->r, *&count, Elem, action, pasteTree); //Обошли правое поддерево   
	}
}

void copyTreeFunction(Node *&newTree, Node *&copyTree) {
	if (copyTree == NULL) {
		return;
	}
	if (copyTree != NULL) {
		newTree->info = copyTree->info;
		newTree->l = newTree->r = NULL;
		newTree->show = false;
		if (copyTree->l != NULL) {
			newTree->l = new Node;
			newTree->l->x = newTree->x + 1;
			newTree->l->f = newTree;
			copyTreeFunction(newTree->l, copyTree->l);
		}
		if (copyTree->r != NULL) {
			newTree->r = new Node;
			newTree->r->x = newTree->x;
			newTree->r->f = newTree->f;
			copyTreeFunction(newTree->r, copyTree->r);
		}
	}
	else {
		cout << "не инициализировано дерево" << endl;
	}
};

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
