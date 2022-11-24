#include <iostream>
using namespace std;
using namespace std;
class node
{
public:
	int key;
	node* left;
	node* right;
	int height;
};
// Функция получения высоты дерева
int height(node* N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
// Функция сравнения
int max(int a, int b)
{
	return (a > b) ? a : b;
}

void print_level(node*p, int n, int level, int prob) { //печать одного уровня дерева
	if (p) {
		if (level == n) {
			for (int i = 1; i <= prob; i++) cout << " ";
			cout << p->key;
		}
		else {
			print_level(p->right, n, level + 1, prob);
			print_level(p->left, n, level + 1, prob);
		}
	}
}

void print(node* p) { //красивый вывод
	int h = p->height;
	int prob = 3;
	if (p) {
		for (int i = 0; i <= h; i++) {
			print_level(p, i, 0, prob * (h - i));
			cout << endl;
		}
	}
}
node* newNode(int key)
{
	node* nod = new node();
	nod->key = key;
	nod->left = NULL;
	nod->right = NULL;
	nod->height = 1;
	return(nod);
}
// Поворот дерева вправо около корня у
node* rightRotate(node* y)
{
	node* x = y->left;
	node* T2 = x->right;
	// Поворот
	x->right = y;
	y->left = T2;
	// Новые высоты
	y->height = max(height(y->left),
		height(y->right)) + 1;
	x->height = max(height(x->left),
		height(x->right)) + 1;
	// Возвращение нового корня
	return x;
}
// Поворот дерева около корня х
node* leftRotate(node* x)
{
	node* y = x->right;
	node* T2 = y->left;
	// Поворот
	y->left = x;
	x->right = T2;
	// Новые высоты
	x->height = max(height(x->left),
		height(x->right)) + 1;
	y->height = max(height(y->left),
		height(y->right)) + 1;
	// Возвращение нового корня
	return y;
}
// вычисление баланса левого и правого дерева
int getBalance(node* p) {
	return (height(p->right) - height(p->left));
}
// Выставка элемента
node* insert(node* pNode, int key)
{
	/* 1. Обычная вставка элемента в бинарном дереве */
	if (pNode == NULL)
		return(newNode(key));
	if (key < pNode->key)
		pNode->left = insert(pNode->left, key);
	else if (key > pNode->key)
		pNode->right = insert(pNode->right, key);
	else // Одинаковые ключи не разрешены
		return pNode;
	/* 2. Обновление высоты корневого узла */
	pNode->height = 1 + max(height(pNode->left),
		height(pNode->right));
	/* Вычисление баланса корневого узла чтобы понять стал ли он
	несбалансированным */
	int balance = getBalance(pNode);
	// Если узел несбалансирован:
	// Left Left Case
	if (balance > 1) {
		if (key < pNode->right->key)
		{
			pNode->right = rightRotate(pNode->right);
			return leftRotate(pNode);
		}
		else if (key > pNode->right->key)
			return leftRotate(pNode);
	}
	else if (balance < -1)
	{
		if (key > pNode->left->key)
		{
			pNode->left = leftRotate(pNode->left);
			return rightRotate(pNode);
		}
		else if (key < pNode->left->key)
			return rightRotate(pNode);
	}
	/* Если узел сбалансирован, возвращаем не меняя */
	return pNode;
}

/* Симметричный обход */
void inOrder(node* root) {
	if (root != NULL)
	{
		inOrder(root->left);
		cout << root->key << " ";
		inOrder(root->right);
	}
}
void summa(node* node, int& sum)
{
	if (!node) { return; }
	summa(node->left, sum);
	summa(node->right, sum);
	sum += node->key;
}
void count(node* node, int& num)
{
	if (!node) { return; }
	count(node->left, num);
	count(node->right, num);
	(num)++;
}

//среднее арифметическое узлов дерева
double average(node* node)
{
	int s = 0, c = 0;
	summa(node, s);
	count(node, c);
	return ((double)s) / ((double)c);
}
int main() {
	node* root = NULL;
	int sum = 0, command = -1, input = 0;
	while (command != 0) {
		cout << "Выберите команду";
		cout << "1 - ввод элементов дерева\n";
		cout << "2 - симметричный обход\n";
		cout << "3 - среднее арифметическое\n";
		cout << "4 - высота дерева\n";
		cout << "5 -наглядный вывод дерева\n";
		cout << "6 - выход\n";
		cin >> command;
		switch (command) {
		case 1:
			cout << "\n введите 10 значений" << endl;
			cout << "\n Input 10 keys: " << endl;
			for (int i = 0; i < 10; i++) {
				cin >> input;
				root = insert(root, input);
			}
			cout << endl;
			break;
		case 2:
			cout << "Симметричный обход " << endl;
			inOrder(root);
			cout << endl;
			break;
		case 3:
			cout << average(root) << endl;
			break;
		case 4:
			cout << height(root);
			break;
		case 5:
			print(root);
		case 6:
			return 0;
		}
		
	}
	return 0;
}