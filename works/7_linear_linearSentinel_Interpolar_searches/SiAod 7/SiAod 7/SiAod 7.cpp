#include <iostream>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

struct Employee {
	long long INN;
	string fname;
	long long num;
};

//генератор инн
long long genINN() {
	long long INN = 0;
	for (int i = 0; i < 10; i++) INN = INN * 10 + rand() % 9;
	return INN;
}

//генератор случайных Фамилий*
string genFname() {
	string fname = "";
	for (int i = 0; i < 13; i++) { char c = 'A' + rand() % 26; fname += c; }
	return fname;
}

//генератор случайных т. номеров
long long genNum() {
	long long num = 0;
	for (int i = 0; i < 11; i++) num = num * 10 + rand() % 10;
	return num;
}

//заполнение таблицы
void inTabelle(Employee tabelle[], int size) {
	for (int i = 0; i < size; i++) {
		tabelle[i].INN = genINN();
		tabelle[i].fname = genFname();
		tabelle[i].num = genNum();
		if (i == size - 1) {
			tabelle[i].INN = 9999999999;
			tabelle[i].fname = "Wolfenstein";
			tabelle[i].num = 49428374876;
		}
	}
}

//вывод таблицы
void outTabelle(Employee tabelle[], int size) {
	for (int i = 0; i < size; i++) {
		cout << "INN: " << tabelle[i].INN << " | Nachname: " << tabelle[i].fname << " | Handy: " << tabelle[i].num << endl;
	}
}

// Функция для сортировки таблицы сотрудников по ИНН
void sortTabelle(Employee tabelle[], int size) {
	sort(tabelle, tabelle + size, [](const Employee& a, const Employee& b) { return a.INN < b.INN; });
}

//линейный поиск
int linearSearch(Employee tabelle[], int size, long long key) {
	for (int i = 0; i < size; i++) {
		if (tabelle[i].INN == key) {
			return i;
		}
	}
	return -1;
}

//линейный поиск  с барьером
int linearSearchWithBarrier(Employee tabelle[], int size, long long key) {
	tabelle[size - 1].INN = key; // Установка барьера
	int i = 0;
	while (tabelle[i].INN != key) {
		i++;
	}
	if (i == size - 1 && tabelle[size - 1].INN != key) {
		return -1;
	}
	return i;
}

//интерполяционный поиск
int interpolationSearch(Employee tabelle[], int size, long long key) {
	int low = 0, high = size - 1;
	while (low <= high && key >= tabelle[low].INN && key <= tabelle[high].INN) {
		if (low == high) {
			if (tabelle[low].INN == key) {
				return low;
			}
			return -1;
		}
		int pos = low + ((key - tabelle[low].INN) * (high - low)) / (tabelle[high].INN - tabelle[low].INN);
		if (tabelle[pos].INN == key) {
			return pos;
		}
		if (tabelle[pos].INN < key) {
			low = pos + 1;
		}
		else {
			high = pos - 1;
		}
	}
	return -1;
}

//главная функция
int main() {
	const int SIZE = 10000; //я не знаю как исправить оверфлоу, так что она работает до 100.000 (к сожалению)
	Employee tabelle[SIZE];
	long long search_key = 9999999999; // Генерация случайного ключа для поиска

	inTabelle(tabelle, SIZE); // Заполнение таблицы сотрудников
	sortTabelle(tabelle, SIZE); // Сортировка таблицы по ИНН

	//cout << "tabelle of Employees:" << endl;
	//outTabelle(tabelle, SIZE); // Вывод таблицы сотрудников

	auto start = high_resolution_clock::now(); // Запуск таймера
	int result = linearSearch(tabelle, SIZE, search_key); // Линейный поиск
	auto stop = high_resolution_clock::now(); // Остановка таймера

	if (result == -1) {
		cout << "Employee not found." << endl;
	}
	else {
		cout << "Linear Search Result: Employee found at index " << result << endl;
	}

	auto duration = duration_cast<nanoseconds>(stop - start); // Вычисление времени выполнения
	cout << "Linear Search Time: " << duration.count() << " nanosec" << endl << endl;

	start = high_resolution_clock::now(); // Запуск таймера
	result = linearSearchWithBarrier(tabelle, SIZE, search_key); // Линейный поиск с барьером
	stop = high_resolution_clock::now(); // Остановка таймера

	if (result == -1) {
		cout << "Employee not found." << endl;
	}
	else {
		cout << "Linear Search with Barrier Result: Employee found at index " << result << endl;
	}

	duration = duration_cast<nanoseconds>(stop - start); // Вычисление времени выполнения
	cout << "Linear Search with Barrier Time: " << duration.count() << " nanosec" << endl << endl;

	start = high_resolution_clock::now(); // Запуск таймера
	result = interpolationSearch(tabelle, SIZE, search_key); // Интерполяционный поиск
	stop = high_resolution_clock::now(); // Остановка таймера

	if (result == -1) {
		cout << "Employee not found." << endl;
	}
	else {
		cout << "Interpolation Search Result: Employee found at index " << result << endl;
	}

	duration = duration_cast<nanoseconds>(stop - start); // Вычисление времени выполнения
	cout << "Interpolation Search Time: " << duration.count() << " nanosec" << endl << endl;

	return 0;
}