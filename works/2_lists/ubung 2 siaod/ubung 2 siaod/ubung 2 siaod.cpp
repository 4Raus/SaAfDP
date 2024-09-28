#include <iostream>
#include <time.h>

using namespace std;

int GetRandomNumber(int min, int max)
{
	return min + rand() % (max - min + 1);
}

typedef int ND;
struct Node {
	ND data;
	Node* next;

	Node(ND value) {
		data = value;
		next = nullptr;
	}
};

void addFirst(Node*& list, ND value) {
	Node* node = new Node(value);
	node->next = list;
	list = node;
}

void display(Node* list) {
	Node* current = list;
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}

//функция, которая вставляет новое значение в список L, сохраняя упорядоченность списка.
void add(Node*& list, ND value) {
	Node* prev = nullptr;
	Node* current = list;
	while (current != nullptr && current->data < value) {
		prev = current;
		current = current->next;
	}

	if (prev != nullptr) {
		Node* node = new Node(value);
		node->next = current;
		prev->next = node;
	}
	else addFirst(list, value);
}

//функция, которая удаляет из списка L все узлы, значения в которых большие заданного.
void removeIf(Node*& list, ND value) {
	Node* prev = nullptr;
	Node* current = list;
	while (current != nullptr && current->data < value) {
		prev = current;
		current = current->next;
	}
	if (prev != nullptr) prev->next = nullptr;
	else list = nullptr;
}

//функция создает новый список L1 из значений узлов списка L, так что в списке L1 узлы упорядочены в порядке убывания их значений.
Node* reverse(Node* list) {
	Node* reverse = nullptr;
	Node* current = list;
	while (current != nullptr) {
		addFirst(reverse, current->data);
		current = current->next;
	}
	return reverse;
}

int main() {
    setlocale(LC_ALL, "");

	Node* list = nullptr;
	srand(time(NULL));

	cout << "Одномерный упорядоченный список из 96 чисел: ";
	for (int i = 0; i <= 96; i++)
	{
		int x = 0;
		x = GetRandomNumber(-325, 2346);;
		add(list, x);
	}
	display(list);

	cout << endl << "Вывод реверсивного упорядоченного списка: ";
	display(reverse(list));

	int a;
	cout << endl << "Введите значение узла, дальше которого будут удалены все остальные узлы: " << endl;
	cin >> a;
	cout << endl << "Вывод списка до позиции " << ": ";
	removeIf(list, a);
	display(list);

	cout << endl << "Вывод реверсивного упорядоченного списка: ";
	display(reverse(list));

    return 0;
}