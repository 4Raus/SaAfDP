#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class cl_base;
typedef void (cl_base::* SIGNAL_TYPE)(string&);
typedef void (cl_base::* HANDLER_TYPE)(const string& S);
#define SIGNAL(_signal) ((SIGNAL_TYPE)(&_signal))
#define HANDLER(_handler) ((HANDLER_TYPE)(&_handler))
struct net
{
	SIGNAL_TYPE the_signal;
	cl_base* the_target;
	HANDLER_TYPE the_handler;
};

class cl_base {
protected:
	string name;
	cl_base* parents;
	int bereit;
	int static st;
public:
	int cl_num;
	vector<cl_base*> children;
	vector<net> pVer;

	cl_base(cl_base* parents, string name = "Undefined");

	void setName(string name);
	string GN();

	void GT();

	void SP(cl_base* parents);
	cl_base* GP();
	cl_base* FBN(string name);

	void GMT();
	void SB(int n);
	void RB();
	bool IB();

	cl_base* find(string name1);
	cl_base* p_suchen(cl_base* found, string name1);
	void connect(SIGNAL_TYPE sig, cl_base* target, HANDLER_TYPE
		hand);
	void trennen(SIGNAL_TYPE sig, cl_base* target,
		HANDLER_TYPE handl);
	void emit(SIGNAL_TYPE sig, string& value);

		string GAP();
	void SAB();
};

class cl_application : public cl_base{
private:
	void leselos();
	void ersteller(cl_base* child, string name2, int num);
	void kommando();
	void connection();
	void signalen();

public:
	cl_application(cl_base * parents, string name = "Undefined");

	void build_T();
	int exec_app();

	void handler(const string& value);
	void signal(string& value);
};

class s_cl2 : public cl_base {
public:
	s_cl2(cl_base* parents, string name = "Undefined");
	void handler(const string& value);
	void signal(string& value);
};

class s_cl3 : public cl_base {
public:
	s_cl3(cl_base* parents, string name = "Undefined");
	void handler(const string& value);
	void signal(string& value);
};

class s_cl4 : public cl_base {
public:
	s_cl4(cl_base* parents, string name = "Undefined");
	void handler(const string& value);
	void signal(string& value);
};

class s_cl5 : public cl_base {
public:
	s_cl5(cl_base* parents, string name = "Undefined");
	void handler(const string& value);
	void signal(string& value);
};

class s_cl6 : public cl_base {
public:
	s_cl6(cl_base* parents, string name = "Undefined");
	void handler(const string& value);
	void signal(string& value);
};


cl_base::cl_base(cl_base* parents, string name) {
	this->parents = parents;
	this->name = name;
	this->bereit = 0;
	this->st = 0;
	if (parents != nullptr)
	{
		parents->children.push_back(this);
	}
};
void cl_base::setName(string name) {
	this->name = name;
};
string cl_base::GN() {
	return name;
};
void cl_base::SP(cl_base* parents) {
	this->parents = parents;
};
cl_base* cl_base::GP() {
	return parents;
};
void cl_base::GT() {
	st++;
	for (int i = 0; i < children.size(); i++) {
		cout << "\n";
		for (int j = 0; j < st; j++) {
			cout << " ";
		}
		cout << children[i]->GN();
			if (children[i]->children.size() != 0) {
				children[i]->GT();
			}
	}
	st--;
};
void cl_base::GMT()
{
	st++;
	for (int i = 0; i < children.size(); i++) {
		cout << "\n";
		for (int j = 0; j < st; j++) {
			cout << " ";
		}
		cout << children[i]->GN() << " " << (children[i] -> IB() ? "is bereit" : "is not bereit");
		if (children[i]->children.size() != 0) {
			children[i]->GMT();
		}
	}
	st--;
};
cl_base* cl_base::FBN(string name) {
	if (GN() == name) {
		return this;
	}
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->GN() == name)
		{
			return children[i];
		}
		else {
			cl_base* temp = (children[i] -> FBN(name));
			if (temp != nullptr) {
				if (temp->GN() == name)
				{
					return (temp);
				}
			}
		}
	}
	return nullptr;
}
void cl_base::SB(int n)
{
	bool isAllTrue = true;
	cl_base* lparents = GP();
	while (lparents != nullptr) {
		if (!lparents->IB()) {
			isAllTrue = false;
			break;
		}
		lparents = lparents->GP();
	}
	if (isAllTrue) {
			bereit = n;
		if (n == 0) {
			RB();
		}
	}
}
void cl_base::RB() {
	for (int i = 0; i < children.size(); i++) {
		children[i]->bereit = 0;
		if (children[i]->children.size() != 0) {
			children[i]->RB();
		}
	}
}
bool cl_base::IB()
{
	if (bereit != 0) {
		return true;
	}
	else {
		return false;
	}
}
cl_base* cl_base::find(string name1) {
	string temp_name;
	cl_base* found = this;
	cl_base* root = this;
	while (root->GP() != nullptr) {
		root = root->GP();
	}
	if (name1[0] == '/') {
		//абсолютный с уникальным именем
		if (name1[1] == '/') {
			for (int i = 2; i < name1.size(); i++) {
				temp_name += name1[i];
			}
			found = root->FBN(temp_name);
			temp_name.clear();
			return found;
		}
		else {
			//корневой объект
			if (name1 == "/") {
				return root;
			}
			//корень/name1...
			else {
				found = root;
				found = p_suchen(found, name1);
				return found;
			}
		}
	}
	//текущий объект
	else if (name1 == ".") {
		return this;
	}
	else {
		//относительно name1
		found = p_suchen(found, name1);
		return found;
	}
}
cl_base* cl_base::p_suchen(cl_base* found, string name1) {
	string temp_name;
	int start = 0;
	if (name1[0] == '/') {
		start = 1;
	}
	for (int i = start; i < name1.size(); i++) {
		if ((name1[i] != '/') != (i == name1.size() - 1)) {
			temp_name += name1[i];
		}
		else {
			if (i == name1.size() - 1) {
				temp_name += name1[i];
			}
			if (found->children.size() == 0) {
				return nullptr;
			}
			for (int j = 0; j < found->children.size(); j++) {
				if (found->children[j] -> GN() == temp_name) {
					found = found->children[j];
					break;
				}
				if (j == found->children.size() - 1) {
					return nullptr;
				}
			}
			temp_name.clear();
		}
	}
	return found;
}
void cl_base::connect(SIGNAL_TYPE sig, cl_base* target, HANDLER_TYPE
	hand) {
	for (unsigned int i = 0; i < pVer.size(); i++) {
		if (pVer[i].the_signal == sig &&
			pVer[i].the_target == target &&
			pVer[i].the_handler == hand) {
			return;
		}
	}
	net temp;
	temp.the_signal = sig;
	temp.the_target = target;
	temp.the_handler = hand;
	pVer.push_back(temp);
}

void cl_base::trennen(SIGNAL_TYPE sig, cl_base * target, HANDLER_TYPE
	hand) {
	for (int i = 0; i < pVer.size(); i++) {
		if (pVer[i].the_signal == sig &&
			pVer[i].the_target == target &&
			pVer[i].the_handler == hand)
		{
			pVer.erase(pVer.begin()
				+ i);
			return;
		}
	}
}
void cl_base::emit(SIGNAL_TYPE sig, string& value) {
	if (IB()) {
		(this->*(sig))(value);
		for (int i = 0; i < pVer.size(); i++)
		{
			if (pVer[i].the_signal == sig &&
				pVer[i].the_target->IB()) {
				(pVer[i].the_target ->*(pVer[i].the_handler))(value);
			}
		}
	}
}
string cl_base::GAP() {
	cl_base* object = this;
	string path = "";
	while (object->GP() != nullptr)
	{
		path = "/" + object->GN() + path;
		object = object->GP();
	}
	if (path == "") {
		path = "/";
	}
	return path;
}
void cl_base::SAB() {
	bereit = 1;
	for (int i = 0; i < children.size(); i++) {
		if (children[i]->children.size() != 0) {
			children[i]->SAB();
		}
		else {
			children[i]->SB(1);
		}
	}
}

int cl_base::st;
cl_application::cl_application(cl_base* parents, string name) :cl_base(parents,
	name) {
	cl_num = 1;
};
int cl_application::exec_app() {
	cout << "Object tree" << "\n";
	cout << GN();
	GT();
	SAB();
	signalen();
	return 0;
};
void cl_application::build_T() {
	string name1;
	string name2;
	int num;
	cl_base* found;
	cl_base* root = this;
	while (root->GP() != nullptr) {
		root = root->GP();
	}

	cin >> name1;
	setName(name1);

	while (true) {
			cin >> name1;
		if (name1 != "endtree") {
			cin >> name2 >> num;
			found = find(name1);
			if (found == nullptr) {
				cout << "Object tree" << "\n";
				cout << root->GN();
				root->GT();
				cout << "\nThe parents object " << name1 << " is not found";
					exit(0);
			}
			ersteller(found, name2, num);
		}
		else {
			break;
		}
	}
	connection();
};
void cl_application::leselos() {
	string name;
	int num;
	while (cin >> name >> num) {
		FBN(name)->SB(num);
	}
}
void cl_application::kommando() {
	string name1;
	string name2;
	cl_base* found;
	cl_base* current = this;
	while (cin >> name1) {
		if (name1 == "FIND") {
			cout << "\n";
			cin >> name2;
			cout << name2 << " ";
			found = current->find(name2);
			if (found != nullptr) {
				cout << "Object name: " << found->GN();
			}
			else {
				cout << "Object is not found";
			}
		}
		else if (name1 == "SET") {
			cout << "\n";
			cin >> name2;
			found = current->find(name2);
			if (found != nullptr) {
				current = found;
				cout << "Object is set: " << found->GN();
			}
			else {
				cout << "Object is not found";
			}
		}
		else if (name1 == "END") {
				break;
		}
	}
}
void cl_application::ersteller(cl_base* child, string name2, int num) {
	switch (num)
	{
	case 2:
		new s_cl2(child, name2);
		break;
	case 3:
		new s_cl3(child, name2);
		break;
	case 4:
		new s_cl4(child, name2);
		break;
	case 5:
		new s_cl5(child, name2);
		break;
	case 6:
		new s_cl6(child, name2);
		break;
	}
}
void cl_application::connection() {
	SIGNAL_TYPE signals[] = {
	SIGNAL(cl_application::signal), SIGNAL(s_cl2::signal),
   SIGNAL(s_cl3::signal), SIGNAL(s_cl4::signal),
   SIGNAL(s_cl5::signal), SIGNAL(s_cl6::signal)
	};
	HANDLER_TYPE handlers[] = {
	HANDLER(cl_application::handler),
   HANDLER(s_cl2::handler), HANDLER(s_cl3::handler),
   HANDLER(s_cl4::handler), HANDLER(s_cl5::handler),
   HANDLER(s_cl6::handler)
	};

	string path1 = "";
	string path2;
	cl_base* from;
	cl_base* target;
	while (true) {
		if (cin >> path1) {}
		else break;
		if (path1 != "end_of_connections") {
			cin >> path2;
			from = find(path1);
			if (from == nullptr) {
				cout << "\nObject " << path1 << " not found";
				continue;
			}
			target = find(path2);
			if (target == nullptr) {
				cout << "\nObject " << path2 << " not found";
				continue;
			}
				from->connect(signals[from->cl_num - 1],
					target, handlers[target->cl_num - 1]);
		}
		else {
			break;
		}
	}
}
void cl_application::signalen() {
	SIGNAL_TYPE signals[] = {
		SIGNAL(cl_application::signal), SIGNAL(s_cl2::signal),
		SIGNAL(s_cl3::signal), SIGNAL(s_cl4::signal),
		SIGNAL(s_cl5::signal), SIGNAL(s_cl6::signal)
	};
	HANDLER_TYPE handlers[] = {
		HANDLER(cl_application::handler),
		HANDLER(s_cl2::handler), HANDLER(s_cl3::handler),
		HANDLER(s_cl4::handler), HANDLER(s_cl5::handler),
		HANDLER(s_cl6::handler)
	};
	string op;
	string name1;
	string name2;
	int num;
	cl_base* found1;
	cl_base* found2;
	while (cin >> op) {
		if (op == "EMIT") {
			cin >> name1;
			getline(cin, name2);
			found1 = find(name1);
			if (found1 == nullptr) {
				cout << "\nObject " << name1 << " not found";
			}
			else {
				found1->emit(signals[found1->cl_num -
					1], name2);
			}
		}
		else if (op == "SET_CONNECT") {
			cin >> name1 >> name2;
			found1 = find(name1);
			if (found1 == nullptr) {
				cout << "\nObject " << name1 << " not found";
				continue;
			}
			found2 = find(name2);
			if (found2 == nullptr) {
				cout << "\nHandler object " << name2 << " not found";
					continue;
			}
			found1->connect(signals[found1->cl_num - 1],
				found2, handlers[found2->cl_num - 1]);
		}
		else if (op == "DELETE_CONNECT") {
			cin >> name1 >> name2;
			found1 = find(name1);
			if (found1 == nullptr) {
				cout << "\nObject " << name1 << " not found";
					continue;
			}
			found2 = find(name2);
			if (found2 == nullptr) {
				cout << "\nHandler object " << name2 << " not found";
					continue;
			}
			found1->trennen(signals[found1->cl_num - 1],
				found2, handlers[found2->cl_num - 1]);
		}
		else if (op == "SET_CONDITION") {
			cin >> name2 >> num;
			found2 = find(name2);
			found2->SB(num);
		}
		else if (op == "END") {
			break;
		}
	}
}
void cl_application::handler(const string& value) {
	cout << "\n" << "Signal to " << GAP() << " Text: " <<
		value;
}
void cl_application::signal(string& value) {
	cout << "\n" << "Signal from " << GAP();
	value += " (class: 1)";
}

s_cl2::s_cl2(cl_base* parents, string name) :cl_base(parents, name) {
	cl_num = 2;
}
void s_cl2::handler(const string& value) {
	cout << "\n" << "Signal to " << GAP() << " Text: " <<
		value;
}
void s_cl2::signal(string& value) {
	cout << "\n" << "Signal from " << GAP();
	value += " (class: 2)";
}

s_cl3::s_cl3(cl_base* parents, string name) :cl_base(parents, name) {
	cl_num = 3;
}
void s_cl3::handler(const string& value) {
	cout << "\n" << "Signal to " << GAP() << " Text: " <<
		value;
}
void s_cl3::signal(string& value) {
	cout << "\n" << "Signal from " << GAP();
	value += " (class: 3)";
}

s_cl4::s_cl4(cl_base* parents, string name) :cl_base(parents, name) {
	cl_num = 4;
}
void s_cl4::handler(const string& value) {
	cout << "\n" << "Signal to " << GAP() << " Text: " <<
		value;
}
void s_cl4::signal(string& value) {
	cout << "\n" << "Signal from " << GAP();
	value += " (class: 4)";
}

s_cl5::s_cl5(cl_base* parents, string name) :cl_base(parents, name) {
	cl_num = 5;
}
void s_cl5::handler(const string& value) {
	cout << "\n" << "Signal to " << GAP() << " Text: " <<
		value;
}
void s_cl5::signal(string& value) {
	cout << "\n" << "Signal from " << GAP();
	value += " (class: 5)";
}

s_cl6::s_cl6(cl_base* parents, string name) :cl_base(parents, name) {
	cl_num = 6;
}
void s_cl6::handler(const string& value) {
	cout << "\n" << "Signal to " << GAP() << " Text: " <<
		value;
}
void s_cl6::signal(string& value) {
	cout << "\n" << "Signal from " << GAP();
	value += " (class: 6)";
}

int main()
{
	cl_application ob_cl_application(nullptr);
	ob_cl_application.build_T();//Построение дерева объектов
	return ob_cl_application.exec_app(); //запуск системы
}


//class cl_base;//
//typedef void (cl_base::* SIGNAL_TYPE)(string&);//
//typedef void (cl_base::* HANDLER_TYPE)(const string& S);//
//#define SIGNAL(_signal)((SIGNAL_TYPE)(&_signal))//
//#define HANDLER(_handler)((HANDLER_TYPE)(&_handler))//
//
//struct net {
//	SIGNAL_TYPE the_signal;//
//	cl_base* the_target;//
//	HANDLER_TYPE the_handler;//
//};
//
//class cl_base {//
//protected://
//	string name;//
//	cl_base* parents;//
//	int bereit;//
//	int static st;//
//public://
//	int cl_num;//
//	vector<cl_base*> children;//
//	vector<net> pVer;//
//	cl_base(cl_base* parents, string name = "Undefined");//
//	void setName(string name);//
//	string GN();//
//	void GT();//
//	void SP(cl_base* parents);//
//	cl_base* GP();//
//	cl_base* FBN(string name);//
//	void GMT();//
//	void SB(int n);//
//	void RB();//
//	bool IB();//
//	cl_base* find(string name1);//
//	cl_base* p_suchen(cl_base* found, string name1);//
//	void connect(SIGNAL_TYPE sig, cl_base* target, HANDLER_TYPE hand);//
//	void trennen(SIGNAL_TYPE sig, cl_base* target, HANDLER_TYPE handl);//
//	void emit(SIGNAL_TYPE sig, string& value);//
//	string GAP();//
//	void SAB();//
//};
//
//class cl_application : public cl_base {//начало описания работы тела класса, модификатор доступа - публичный при наследовании
//private:
//	void leselos();//установка состояния чтения
//	void ersteller(cl_base* child, string name2, int num);//создание новог объекта
//	void kommando();//обработка команд
//	void connection();//
//	void signalen();//
//public://модификатор доступа - публичный
//	cl_application(cl_base* parents, string name = "Undefined");//
//	void build_T();//создание метода вывода дерева
//	int exec_app();//создание метода запуска программы
//	void handler(const string& value);//
//	void signal(string& value);//
//};
//
//class s_cl2 : public cl_base {
//public:
//	s_cl2(cl_base* parents, string name = "Undefined");
//	void handler(const string& value);
//	void signal(string& value);
//};
//
//class s_cl3 : public cl_base {
//public:
//	s_cl3(cl_base* parents, string name = "Undefined");
//	void handler(const string& value);
//	void signal(string& value);
//};
//
//class s_cl4 : public cl_base {
//public:
//	s_cl4(cl_base* parents, string name = "Undefined");
//	void handler(const string& value);
//	void signal(string& value);
//};
//
//class s_cl5 : public cl_base {
//public:
//	s_cl5(cl_base* parents, string name = "Undefined");
//	void handler(const string& value);
//	void signal(string& value);
//};
//
//class s_cl6 : public cl_base {
//public:
//	s_cl6(cl_base* parents, string name = "Undefined");
//	void handler(const string& value);
//	void signal(string& value);
//};
//
//cl_base::cl_base(cl_base* parents, string name) {//присвоение параметезированного конструктора
//	this->parents = parents;//Указатель на головной объект
//	this->name = name;//Наименование объекта
//	this->bereit = 0;//присвоение указателю значения
//	this->st = 0;//присвоение указателю значения
//	if (parents != nullptr) parents->children.push_back(this);//условный оператор, если головной объект не равен константе нулевого показателя, добавление в конец вектора children текущего элемента
//};
//
//void cl_base::setName(string name) {//присвоение метода задачи имени объекта
//	this->name = name;//Наименование объекта
//};
//
//string cl_base::GN() {//присвоение метода получения имени объекта
//	return name;//возвращение параметра и присвоение его текущему
//};
//
//void cl_base::GT() {//присвоение метода построения дерева
//	st++;//прибавление 1
//	for (int i = 0; i < children.size(); i++) {//цикл с присвоением, сравнением и прибавлением 1
//		cout << "\n";//вывод переноса строки
//		for (int j = 0; j < st; j++) {//цикл с присвоением, сравнением и прибавлением 1
//			cout << "    ";//вывод 4х пробелов
//		}
//		cout << children[i]->GN();//вывод указателя
//		if (children[i]->children.size() != 0) children[i]->GT();//если размер массива существует, то элемент заносится в метод
//	}
//	st--;//вычитание 1
//}
//
//cl_base* cl_base::FBN(string name) {//присвоение метода обЪявление методов в качестве публичного члена класса и возвращение указателя на объект типа cl_base
//	if (GN() == name) return this;//если метод (значение) равно имени, то вернуть текущий указатель
//	for (int i = 0; i < children.size(); i++) {//цикл с присвоением, сравнением и прибавлением 1
//		if (children[i]->GN() == name) return children[i];//если указатель имени равен имени, то возврат итого элемента
//		else {//иначе
//			cl_base* temp = (children[i]->FBN(name));//вызов метода и присвоение значения другого метода
//			if (temp != nullptr) {//если поле не равняется 0 указателю, то
//				if (temp->GN() == name) return (temp);//если метод равен переменной, то вернуть значение поля
//			}
//		}
//	}
//	return nullptr;//возврат нулевого указателя
//}
//
//void cl_base::SP(cl_base* parents) {//присвоение метода задачи головного объекта
//	this->parents = parents;//Указатель на головной объект
//}
//
//cl_base* cl_base::GP() {//присвоение метода возврат головного объекта
//	return parents;//возврат значения поля
//}
//
//void cl_base::GMT() {//присвоение метода вывод дерева с готовностью каждого элемента
//	st++;//прибавление 1
//	for (int i = 0; i < children.size(); i++) {//цикл с присвоением, сравнением и прибавлением 1
//		cout << "\n";//перенос строки
//		for (int j = 0; j < st; j++) {//цикл с присвоением, сравнением и прибавлением 1
//			cout << "    ";//вывод 4х пробелов
//		}
//		cout << children[i]->GN() << " " << (children[i]->IB() ? "is ready" : "is not ready");//вывод указателя элемента, пробела, в зависимости от ситуации вывод предложение
//		if (children[i]->children.size() != 0) children[i]->GMT();//если размер массива не равен 0, то указатель элемента заностися в метод
//	}
//	st--;//вычитание 1
//}
//
//void cl_base::SB(int n) {//присвоение метода сеттер поля bereit
//	bool alles = true;//инициализация с присвоением
//	cl_base* lparents = GP();//вызов метода
//	while (lparents != nullptr) {//пока элемент не на нулевом месте
//		if (!lparents->IB()) {//если отрицание, то
//			alles = false;//присвоение лжи
//			break;//выход
//		}
//		lparents = lparents->GP();//присвоение указателя
//	}
//	if (alles) {//если всё правда, то
//		bereit = n;//присвоение
//		if (n == 0) RB();//если переменная равна 0, то вызов метода
//	}
//}
//
//void cl_base::RB() {//присвоение метода функция сброса поля bereit
//	for (int i = 0; i < children.size(); i++) {//цикл с присвоением, сравнением и прибавлением 1
//		children[i]->bereit = 0;//присвоение
//		if (children[i]->children.size() != 0) children[i]->RB();//если размер массива существует, то массив используется в методе
//	}
//}
//
//bool cl_base::IB() {//присвоение метода функция сброса поля bereit
//	if (bereit != 0) return true;//если готовность не равна 0, возврат правды
//	else return false;//иначе вернуть ложь
//}
//
//cl_base* cl_base::find(string name1) {//вызов метода нахождения объекта по имени
//	string temp_n;//инициализация переменной
//	cl_base* found = this;//присвоение значения полю поля
//	cl_base* root = this;//присвоение значения полю поля
//	while (root->GP() != nullptr) {//пока (цикл) значения указателя метода не равняется 0 указателю
//		root = root->GP();//присвоение значения метода
//	}
//	if (name1[0] == '/') {//если значение перменной по индексу равняется
//		//абсолютно с уникальным именем
//		if (name1[1] == '/') {//если значение переменной по индексу равняется
//			for (int i = 2; i < name1.size(); i++) temp_n += name1[i];//цикл (с условием) присвоением, сравнением, инициализацией и прибавлением 1, прибавление значения перменной от перменной по ее индексу
//			found = root->FBN(temp_n);
//			temp_n.clear();
//			return found;
//		}
//		else {
//			//корневой объект
//			if (name1 == "/") {
//				return root;
//			}
//			//корень/name1...
//			else {
//				found = root;
//				found = p_suchen(found, name1);
//				return found;
//			}
//		}
//	}
//	//текущий объект
//	else if (name1 == ".") return this;
//	else {
//		//относительно name1
//		found = p_suchen(found, name1);
//		return found;
//	}
//}
//
//cl_base* cl_base::p_suchen(cl_base* found, string name1) {//вызов метода нахождения объекта по абсолютному и относительному адресам
//	string temp_n;//инициализаия
//	int start = 0;//инициализаия и присвоение
//	if (name1[0] == '/') start = 1;//если индексное значения переменной не равняется, то переменная равна 1
//	for (int i = start; i < name1.size(); i++) {//цикл с условием, сравнением, инициализацией и прибавлением 1
//		if ((name1[i] != '/') != (i == name1.size() - 1)) {//если индексное значения переменной не равняется и это все не равно переменной, которая равна размеру переменной - 1
//			temp_n += name1[i];//прибавление к переменной значения другой по индексу
//		}
//		else {//иначе
//			if (i == name1.size() - 1) temp_n += name1[i];//если переменная равна размеру другой -1, то прибавляем переменной значения другой по индексу
//			if (found->children.size() == 0) return nullptr;//если значение метода по размеру равно 0
//			for (int j = 0; j < found->children.size(); j++) {//цикл с условием, сравнением, инициализацией и прибавлением 1
//				if (found->children[j]->GN() == temp_n) {//если значение метода по переменной равно переменной, то
//					found = found->children[j];//присвоение  знаяения метода по переменной 
//					break;//выход
//				}
//				if (j == found->children.size() - 1) return nullptr;//
//			}
//			temp_n.clear();//отчистка
//		}
//	}
//	return found;//возврат значения
//}
///*
//string temp_n;
//int start = 0;
//if (n1[0] == '/' || n1[0] == '.') start = 1;
//for (int i = start; i < n1.size(); i++){
//	if ((n1[i] != '/') != (i == n1.size() - 1)) {
//		temp_n += n1[i];
//	}
//	else{
//		if (i == n1.size() - 1) temp_n += n1[i];
//		if (found->children.size() == 0) return nullptr;
//		int mat = 0;
//		un_suchung(temp_n, mat);
//		if (mat != 0) return nullptr;
//		else suchung_id(temp_n, found);
//		temp_n.clear();
//	}
//}
//return found;
//*/
//
//void cl_base::connect(SIGNAL_TYPE sig, cl_base* target, HANDLER_TYPE hand) {
//	for (unsigned int i = 0; i < children.size(); i++) {
//		if (pVer[i].the_signal == sig && pVer[i].the_target == target && pVer[i].the_handler == hand) {
//			return;
//		}
//	}
//	net temp;
//	temp.the_signal = sig;
//	temp.the_target = target;
//	temp.the_handler = hand;
//	pVer.push_back(temp);
//}
//
//void cl_base::trennen(SIGNAL_TYPE sig, cl_base* target, HANDLER_TYPE hand) {
//	for (int i = 0; i < pVer.size(); i++) {
//		if (pVer[i].the_signal == sig && pVer[i].the_target == target && pVer[i].the_handler == hand) {
//			pVer.erase(pVer.begin() + i);
//			return;
//		}
//	}
//}
//
//void cl_base::emit(SIGNAL_TYPE sig, string& value) {
//	if (IB()) {
//		(this->*(sig))(value);
//		for (int i = 0; i < pVer.size(); i++) {
//			if (pVer[i].the_signal == sig && pVer[i].the_target->IB()) {
//				(pVer[i].the_target->*(pVer[i].the_handler))(value);
//			}
//		}
//	}
//}
//
//string cl_base::GAP() {
//	cl_base* obj = this;
//	string path = "";
//	while (obj->GP() != nullptr) {
//		path = "/" + obj->GN() + path;
//		obj = obj->GP();
//	}
//	if (path == "") {
//		path = "/";
//	}
//	return path;
//}
//
//void cl_base::SAB() {
//	bereit = 1;
//	for (int i = 0; i < children.size(); i++) {
//		if (children[i]->children.size() != 0) {
//			children[i]->SAB();
//		}
//		else children[i]->SB(1);
//	}
//}
//
//int cl_base::st;//присвоение поля метода
//
//cl_application::cl_application(cl_base* parents, string name) :cl_base(parents, name) {
//	cl_num = 1;
//}
//
//int cl_application::exec_app() {//присвоение метода запуска программы
//	cout << "Object tree" << "\n";
//	cout << GN();
//	GT();
//	SAB();
//	signalen();
//	return 0;
//};
//
//void cl_application::build_T() {//присвоение метода вывода дерева
//	string name1;
//	string name2;
//	int num;
//	cl_base* found;
//	cl_base* root = this;
//	while (root->GP() != nullptr) {
//		root = root->GP();
//	}
//	cin >> name1;
//	setName(name1);
//	while (true) {
//		cin >> name1;
//		if (name1 != "endtree") {
//			cin >> name2 >> num;
//			found = find(name1);
//			if (found == nullptr) {
//				cout << "Object tree" << "\n";
//				cout << root->GN();
//				root->GT();
//				cout << "\nThe head object " << name1 << " is not found";
//				exit(0);
//			}
//			ersteller(found, name2, num);
//		}
//		else break;
//	}
//	connection();
//};
//
//void cl_application::leselos() {//присвоение метода установка состояния чтения
//	string name;//инициализация переменной
//	int num;//инициализация переменной
//	while (cin >> name >> num) FBN(name)->SB(num);//пока есть ввод, то вызов метода по этим переменным
//}
//
//void cl_application::kommando() {//присвоение метода обработки команд
//	string name1;//инициализация переменной
//	string name2;//инициализация переменной
//	cl_base* found;//вызов метода
//	cl_base* cur = this;//вызов метода с присвоением его занчения в текущее
//	while (cin >> name1) {//пока есть ввод
//		if (name1 == "FIND") {//если переменная равна сообщению
//			cout << "\n";//вывод переноса
//			cin >> name2;//ввод переменной
//			cout << name2 << "     ";//вывод переменной и 5 пробелов
//			found = cur->find(name2);//присвоение полю значения метода по переменной
//			if (found != nullptr) {//если поле не равняется нулевому укащателю, то
//				cout << "Object name: " << found->GN();//вывод сообщения и значения метода
//			}
//			else cout << "Object is not found";//иначе вывод сообщения
//		}
//		else if (name1 == "SET") {//иначе(с условием) переменная равна сообщению
//			cout << "\n";//вывод переноса
//			cin >> name2;//ввод переменной
//			found = cur->find(name2);//присвоение полю значения метода
//			if (found != nullptr) {//если поле не равняется нулевому указателю,то
//				cur = found;//присвоение
//				cout << "Object is set: " << found->GN();//вывод сообщения и значения метода
//			}
//			else cout << "Object is not found";//иначе вывод собщения и переменной
//		}
//		else if (name1 == "END") break;//иначе(с условием) переменная равна сообщению
//	}
//}
//
//void cl_application::ersteller(cl_base* child, string name2, int num) {//метод новог объекта
//	switch (num) {
//	case 2:
//		new s_cl2(child, name2);
//		break;
//	case 3:
//		new s_cl3(child, name2);
//		break;
//	case 4:
//		new s_cl4(child, name2);
//		break;
//	case 5:
//		new s_cl5(child, name2);
//		break;
//	case 6:
//		new s_cl6(child, name2);
//		break;
//	}
//}
//
//void cl_application::connection() {
//	SIGNAL_TYPE signals[] = {
//		SIGNAL(cl_application::signal),
//		SIGNAL(s_cl2::signal),SIGNAL(s_cl3::signal),
//		SIGNAL(s_cl4::signal),SIGNAL(s_cl5::signal), SIGNAL(s_cl6::signal) };
//	HANDLER_TYPE handlers[] = {
//		HANDLER(cl_application::handler),
//		HANDLER(s_cl2::handler), HANDLER(s_cl3::handler),
//		HANDLER(s_cl4::handler), HANDLER(s_cl5::handler),HANDLER(s_cl6::handler) };
//	string path1 = "";
//	string path2;
//	cl_base* from;
//	cl_base* target;
//	while (true) {
//		if (cin >> path1) {}
//		else break;
//		if (path1 != "end_of_connections") {
//			cin >> path2;
//			from = find(path1);
//			if (from == nullptr) {
//				cout << "\nObject " << path1 << " not found";
//				continue;
//			}
//			target = find(path2);
//			if (target == nullptr) {
//				cout << "\nObject " << path2 << " not found";
//				continue;
//			}
//			from->connect(signals[from->cl_num - 1], target, handlers[target->cl_num - 1]);
//		}
//		else break;
//	}
//}
//
//void cl_application::signalen() {
//	SIGNAL_TYPE signals[] = {
//		SIGNAL(cl_application::signal), SIGNAL(s_cl2::signal),
//		SIGNAL(s_cl3::signal), SIGNAL(s_cl4::signal),
//		SIGNAL(s_cl5::signal), SIGNAL(s_cl6::signal)
//	};
//	HANDLER_TYPE handlers[] = {
//		HANDLER(cl_application::handler),
//		HANDLER(s_cl2::handler), HANDLER(s_cl3::handler),
//		HANDLER(s_cl4::handler), HANDLER(s_cl5::handler),
//		HANDLER(s_cl6::handler)
//	};
//	string op;
//	string name1;
//	string name2;
//	int num;
//	cl_base* found1;
//	cl_base* found2;
//	while (cin >> op) {
//		if (op == "EMIT") {
//			cin >> name1;
//			getline(cin, name2);
//			found1 = find(name1);
//			if (found1 == nullptr) {
//				cout << "\nObject " << name1 << " not found";
//			}
//			else found1->emit(signals[found1->cl_num - 1], name2);
//		}
//		else if (op == "SET_CONNECT") {
//			cin >> name1 >> name2;
//			found1 = find(name1);
//			if (found1 == nullptr) {
//				cout << "\nObject " << name1 << " not found";
//				continue;
//			}
//			found2 = find(name2);
//			if (found2 == nullptr) {
//				cout << "\nHandler object " << name2 << " not found";
//				continue;
//			}
//			found1->connect(signals[found1->cl_num - 1],
//				found2, handlers[found2->cl_num - 1]);
//		}
//		else if (op == "DELETE_CONNECT") {
//			cin >> name1 >> name2;
//			found1 = find(name1);
//			if (found1 == nullptr) {
//				cout << "\nObject " << name1 << " not found";
//				continue;
//			}
//			found2 = find(name2);
//			if (found2 == nullptr) {
//				cout << "\nHandler object " << name2 << " not found";
//				continue;
//			}
//			found1->trennen(signals[found1->cl_num - 1],
//				found2, handlers[found2->cl_num - 1]);
//		}
//		else if (op == "SET_CONDITION") {
//			cin >> name2 >> num;
//			found2 = find(name2);
//			found2->SB(num);
//		}
//		else if (op == "END") break;
//	}
//}
//
//void cl_application::handler(const string& value) {
//	cout << "\n" << "Signal to " << GAP() << " Text: " << value;
//}
//
//void cl_application::signal(string& value) {
//	cout << "\n" << "Signal from " << GAP();
//	value += " (class: 1)";
//}
//
//s_cl2::s_cl2(cl_base* parents, string name) :cl_base(parents, name) {
//	cl_num = 2;
//}
//
//void s_cl2::handler(const string& value) {
//	cout << "\n" << "Signal to " << GAP() << " Text: " << value;
//}
//
//void s_cl2::signal(string& value) {
//	cout << "\n" << "Signal from " << GAP();
//	value += " (class: 2)";
//}
//
//s_cl3::s_cl3(cl_base* parents, string name) :cl_base(parents, name) {
//	cl_num = 3;
//}
//
//void s_cl3::handler(const string& value) {
//	cout << "\n" << "Signal to " << GAP() << " Text: " << value;
//}
//
//void s_cl3::signal(string& value) {
//	cout << "\n" << "Signal from " << GAP();
//	value += " (class: 3)";
//}
//
//s_cl4::s_cl4(cl_base* parents, string name) :cl_base(parents, name) {
//	cl_num = 4;
//}
//
//void s_cl4::handler(const string& value) {
//	cout << "\n" << "Signal to " << GAP() << " Text: " << value;
//}
//
//void s_cl4::signal(string& value) {
//	cout << "\n" << "Signal from " << GAP();
//	value += " (class: 4)";
//}
//
//s_cl5::s_cl5(cl_base* parents, string name) :cl_base(parents, name) {
//	cl_num = 5;
//}
//
//void s_cl5::handler(const string& value) {
//	cout << "\n" << "Signal to " << GAP() << " Text: " << value;
//}
//
//void s_cl5::signal(string& value) {
//	cout << "\n" << "Signal from " << GAP();
//	value += " (class: 5)";
//}
//
//s_cl6::s_cl6(cl_base* parents, string name) :cl_base(parents, name) {
//	cl_num = 6;
//}
//
//void s_cl6::handler(const string& value) {
//	cout << "\n" << "Signal to " << GAP() << " Text: " << value;
//}
//
//void s_cl6::signal(string& value) {
//	cout << "\n" << "Signal from " << GAP();
//	value += " (class: 6)";
//}
//
//int main()
//{
//	cl_application ob_cl_application(nullptr);//создание корневого объекта
//	ob_cl_application.build_T();//конструирование системы, построение дерева объектов
//	return ob_cl_application.exec_app();//запуск системы
//}