#include <iostream>
#include <stack>
#include <string>
using namespace std;

int priority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '^') {
        return 3;
    }
    else {
        return 0;
    }
}

string convertPostfixToInfix(string postfix) {
    stack<string> s;
    for (char c : postfix) {
        if (isdigit(c)) {
            string operand(1, c);
            s.push(operand);
        }
        else {
            string op2 = s.top();
            s.pop();
            string op1 = s.top();
            s.pop();
            string exp = "(" + op1 + c + op2 + ")";
            s.push(exp);
        }
    }
    return s.top();
}

int evaluatePostfix(string postfix) {
    stack<int> s;
    for (char c : postfix) {
        if (isdigit(c)) {
            s.push(c - '0');
        }
        else {
            int op2 = s.top();
            s.pop();
            int op1 = s.top();
            s.pop();
            int result;
            switch (c) {
            case '+': result = op1 + op2; break;
            case '-': result = op1 - op2; break;
            case '*': result = op1 * op2; break;
            case '/': result = op1 / op2; break;
            case '^': result = pow(op1, op2); break;
            }
            s.push(result);
        }
    }
    return s.top();
}

string convertPrefixToInfix(string prefix) {
    stack<string> s;
    int length = prefix.size();
    for (int i = length - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isdigit(c)) {
            string operand(1, c);
            s.push(operand);
        }
        else {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            string exp = "(" + op1 + c + op2 + ")";
            s.push(exp);
        }
    }
    return s.top();
}

int evaluatePrefix(string prefix) {
    stack<int> s;
    int length = prefix.size();
    for (int i = length - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isdigit(c)) {
            s.push(c - '0');
        }
        else {
            int op1 = s.top();
            s.pop();
            int op2 = s.top();
            s.pop();
            int result;
            switch (c) {
            case '+': result = op1 + op2; break;
            case '-': result = op1 - op2; break;
            case '*': result = op1 * op2; break;
            case '/': result = op1 / op2; break;
            case '^': result = pow(op1, op2); break;
            }
            s.push(result);
        }
    }
    return s.top();
}

int main() {
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Выберите число и введите его. Каким методом вы будете пользоваться для перевода его инфиксную форму:\n"
        <<"1) Префиксной 2) Постфиксной\n";
    cin >> n;

    if (n == 1) {
        string prefix;
        cout << "ВВОД: ";
        cin >> prefix;
        cout << endl;

        string infix = convertPrefixToInfix(prefix);

        cout << "Infix: " << infix << endl;
        cout << "Result: " << evaluatePrefix(prefix) << endl;
    }
    else if (n == 2) {
        string postfix;
        cout << "ВВОД: ";
        cin >> postfix;
        cout << endl;

        string infix = convertPostfixToInfix(postfix);

        cout << "Infix: " << infix << endl;
        cout << "Result: " << evaluatePostfix(postfix) << endl;
    }
    else cout << "////ERROR////\n";
    return 0;
}