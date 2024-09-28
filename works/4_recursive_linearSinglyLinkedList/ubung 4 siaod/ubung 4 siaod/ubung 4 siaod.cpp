#include <iostream>
#include <math.h>

using namespace std;

//double fun(int n, double a) {
//	if (n == 0) return a;
//	else return sqrt(a + fun(n - 1, a));
//}
//
//int main() {
//	double x;
//	int root;
//
//	cout << "Write down (first of all) n (number of square roots) and then the number a\n";
//	cin >> root >> x;
//
//	if (root > 0 && x > 0) cout << endl << fun(root, x);
//	else cout << "ERROR";
//	return 0;
//}
//

//ДЕРЕВО РЕКУРСИИ:				МЕТОД ПОДСТАНОВКИ:
//								fun(n, a) = sqrt(a + fun(n-1, a))
//	fun(3, a)					= sqrt(a + sqrt(a + fun(n - 2, a)))
//	  /     \					= sqrt(a + sqrt(a + sqrt(a + fun(n - 3, a))))
//	 /       \					...
//	fun(2, a) a					= sqrt(a + sqrt(a + sqrt(a + ... sqrt(a + a))))
//	  /     \
//	 /       \
//	fun(1, a) a
//	  /     \
// 	 /       \
//	fun(0, a) a

struct Node {
    int data;
    Node* next;
};

Node* reverseListHelper(Node* curr, Node* prev);

Node* reverseList(Node* head) {
    return reverseListHelper(head, nullptr);
}

Node* reverseListHelper(Node* curr, Node* prev) {
    if (curr == nullptr) {
        return prev;
    }
    Node* next = curr->next;
    curr->next = prev;
    return reverseListHelper(next, curr);
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << std::endl;
}

void deleteList(Node* head) {
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    int n, x;
    cout << "Enter the number of nodes: ";
    cin >> n;
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < n; i++) {
        cout << "Enter the value for node " << i + 1 << ": ";
        cin >> x;
        Node* node = new Node{ x, nullptr };
        if (head == nullptr) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }
    cout << "Original list: ";
    printList(head);
    head = reverseList(head);
    cout << "Reversed list: ";
    printList(head);
    deleteList(head);
    return 0;
}