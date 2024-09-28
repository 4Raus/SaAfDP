#include <iostream>
#include <chrono>
//using namespace std;
//
//// Function to sort an array using
//// insertion sort
//void insertionSort(int arr[], int n)
//{
//	int i, key, j, p = 0;
//	for (i = 1; i < n; i++)
//	{
//		key = arr[i];
//		j = i - 1;
//
//		// Move elements of arr[0..i-1],
//		// that are greater than key, to one
//		// position ahead of their
//		// current position
//		while (j >= 0 && arr[j] > key)
//		{
//			arr[j + 1] = arr[j];
//			j = j - 1;
//			p += 1;
//		}
//		arr[j + 1] = key;
//	}
//	cout << endl << endl;
//	cout << p << endl;
//}
//
//// A utility function to print an array
//// of size n
//void printArray(int arr[], int n)
//{
//	int i;
//	for (i = 0; i < n; i++)
//		cout << arr[i] << " ";
//	cout << endl;
//}
//
//// Driver code
//int main()
//{
//	setlocale(LC_ALL, "Rus");
//
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
//	insertionSort(arr, size);
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
// selection sort
using namespace std;

//Swap function
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
	// One by one move boundary of
	// unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in
		// unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
		}
		// Swap the found minimum element
		// with the first element
		if (min_idx != i)
			swap(&arr[min_idx], &arr[i]);
	}
}

//Function to print an array
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
		cout << endl;
	}
}

// Driver program to test above functions
int main()
{

	int k;
	const long size = 10000;
	int arr[size];
	
	auto begin = chrono::steady_clock::now();
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 100;
		cout << arr[i] << '\t';
	}
	cout << '\n\n';
	
	selectionSort(arr, size);
	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
	for (auto& k : arr) {
		cout << k << " ";
	}
	cout << "\nTime: " << elapsed_ms.count() << " ms\n";
	
	return 0;
}