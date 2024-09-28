#include <iostream>
#include <chrono>

// C++ program for implementation of
// selection sort
using namespace std;

//Swap function
//void swap(int* xp, int* yp)
//{
//	int temp = *xp;
//	*xp = *yp;
//	*yp = temp;
//}
//
//void selectionSort(int arr[], int n)
//{
//	int i, j, min_idx;
//	// One by one move boundary of
//	// unsorted subarray
//	for (i = 0; i < n - 1; i++)
//	{
//		// Find the minimum element in
//		// unsorted array
//		min_idx = i;
//		for (j = i + 1; j < n; j++)
//		{
//			if (arr[j] < arr[min_idx])
//				min_idx = j;
//		}
//		// Swap the found minimum element
//		// with the first element
//		if (min_idx != i)
//			swap(&arr[min_idx], &arr[i]);
//	}
//}
//// Driver program to test above functions
//int main()
//{
//
//	int k;
//	const long size = 1000;
//	int arr[size];
//
//	auto begin = chrono::steady_clock::now();
//	for (int i = 0; i < size; i++) {
//		arr[i] = rand() % 100;
//		cout << arr[i] << '\t';
//	}
//	cout << '\n\n';
//
//	selectionSort(arr, size);
//	auto end = chrono::steady_clock::now();
//	auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
//	for (auto& k : arr) {
//		cout << k << " ";
//	}
//	cout << "\nTime: " << elapsed_ms.count() << " ms\n";
//
//	return 0;
//}

// C++ program for implementation of
// heapsort
// Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является
// индексом в arr[]. n - размер кучи

//void heapify(int arr[], int n, int i)
//{
//	int largest = i;
//	// Инициализируем наибольший элемент как корень
//	int l = 2 * i + 1; // левый = 2*i + 1
//	int r = 2 * i + 2; // правый = 2*i + 2
//
//	// Если левый дочерний элемент больше корня
//	if (l < n && arr[l] > arr[largest])
//		largest = l;
//
//	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
//	if (r < n && arr[r] > arr[largest])
//		largest = r;
//
//	// Если самый большой элемент не корень
//	if (largest != i)
//	{
//		swap(arr[i], arr[largest]);
//
//		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
//		heapify(arr, n, largest);
//	}
//}
//
//// Основная функция, выполняющая пирамидальную сортировку
//void heapSort(int arr[], int n)
//{
//	// Построение кучи (перегруппируем массив)
//	for (int i = n / 2 - 1; i >= 0; i--)
//		heapify(arr, n, i);
//
//	// Один за другим извлекаем элементы из кучи
//	for (int i = n - 1; i >= 0; i--)
//	{
//		// Перемещаем текущий корень в конец
//		swap(arr[0], arr[i]);
//
//		// вызываем процедуру heapify на уменьшенной куче
//		heapify(arr, i, 0);
//	}
//}
//
///* Вспомогательная функция для вывода на экран массива размера n*/
//void printArray(int arr[], int n)
//{
//	for (int i = 0; i < n; ++i)
//		cout << arr[i] << " ";
//	cout << "\n";
//}
//
//// Управляющая программа
//int main(){
//	int k;
//	const long size = 100000;
//	int arr[size];
//	
//	auto begin = chrono::steady_clock::now();
//	for (int i = 0; i < size; i++) {
//		arr[i] = rand() % 100;
//		cout << arr[i] << '\t';
//	}
//	cout << '\n\n';
//	
//	heapSort(arr, size);
//	auto end = chrono::steady_clock::now();
//	auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
//	for (auto& k : arr) {
//		cout << k << " ";
//	}
//	cout << "\nTime: " << elapsed_ms.count() << " ms\n";
//	printArray(arr, size);
//	
//	return 0;
//}

// C++ program for implementation of
// merge sort
//#define N 1000

// Объединяем два отсортированных подмассива `arr[low…mid]` и `arr[mid+1…high]`
//void Merge(int arr[], int aux[], int low, int mid, int high)
//{
//    int k = low, i = low, j = mid + 1;
//
//    // Пока есть элементы в левом и правом прогонах
//    while (i <= mid && j <= high)
//    {
//        if (arr[i] <= arr[j]) {
//            aux[k++] = arr[i++];
//        }
//        else {
//            aux[k++] = arr[j++];
//        }
//    }
//
//    // Копируем оставшиеся элементы
//    while (i <= mid) {
//        aux[k++] = arr[i++];
//    }
//
//    // Вторую половину копировать не нужно (поскольку остальные элементы
//    // уже находятся на своем правильном месте во вспомогательном массиве)
//
//    // копируем обратно в исходный массив, чтобы отразить порядок сортировки
//    for (int i = low; i <= high; i++) {
//        arr[i] = aux[i];
//    }
//}
//
//// Сортируем массив `arr[low…high]`, используя вспомогательный массив `aux`
//void mergesort(int arr[], int aux[], int low, int high)
//{
//    // Базовый вариант
//    if (high == low) {        // если размер прогона == 1
//        return;
//    }
//
//    // найти середину
//    int mid = (low + ((high - low) >> 1));
//
//    // рекурсивное разделение выполняется на две половины до тех пор, пока размер выполнения не станет == 1,
//    // затем объединяем их и возвращаемся вверх по цепочке вызовов
//
//    mergesort(arr, aux, low, mid);          // разделить/объединить левую половину
//    mergesort(arr, aux, mid + 1, high);     // разделить/объединить правую половину
//
//    Merge(arr, aux, low, mid, high);        // объединить два полупрогона.
//}
//
//// Функция для проверки, отсортирован ли arr в порядке возрастания или нет
//int isSorted(int arr[])
//{
//    int prev = arr[0];
//    for (int i = 1; i < N; i++)
//    {
//        if (prev > arr[i])
//        {
//            printf("MergeSort Fails!!");
//            return 0;
//        }
//        prev = arr[i];
//    }
//
//    return 1;
//}
//
//// Реализация алгоритма сортировки слиянием на C
//int main(void)
//{
//    int arr[N], aux[N];
//    srand(time(NULL));
//
//    // генерируем случайный ввод целых чисел
//    for (int i = 0; i < N; i++) {
//        aux[i] = arr[i] = (rand() % 100) - 50;
//    }
//
//    // сортируем массив `arr`, используя вспомогательный массив `aux`
//    mergesort(arr, aux, 0, N - 1);
//
//    if (isSorted(arr))
//    {
//        for (int i = 0; i < N; i++) {
//            printf("%d ", arr[i]);
//        }
//    }
//
//    return 0;
//}