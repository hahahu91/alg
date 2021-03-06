// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#ifndef PCH_H
#define PCH_H

#include <string>
using namespace std;

struct Node;
struct Elem;


void byPassTree(Node *&tree);

void Show(Node *&tree);
void ShowOpen(Node *&tree, int &count, bool show = false);
void SaveTree(Node *&tree, ofstream &fout);

void add_node(int x, string info, Node *&MyTree);
void add_from_fath_node(int x, string info, Node *&MyTree);

void pasteTreeNode(Node *&tree, Node *pasteTree);
void paste_tree_from_fath_node(Node *&MyTree, Node *&pasteTree);
void paste_from_fath_node(int x, Node *&MyTree, Node *&pasteTree);
void searchParent(Node *&tree, struct Elem fath, Node *&father);

void deleteTree(Node *&tree);
void freemem(Node *&tree);

bool copyTree(Node *copyTreeEl, Node *&tree, int &count);

bool correctionTree(Node *&tree, int &count, Node *pasteTree = NULL);
bool correctionElem(Node *&tree, int &count, string Elem, Node *pasteTree = NULL);
int correctElem(Node *&tree, int &count, string Elem, string action, Node *pasteTree = NULL);

void copyTreeFunction(Node *&newTree, Node *&copyTree);

// TODO: add headers that you want to pre-compile here

#endif //PCH_H
