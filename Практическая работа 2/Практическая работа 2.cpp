#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;
using nanoseconds = duration<long long, nano>;

const int N = 100, maxNum = 99, minNum = -99;
void bubblesort(int* arr, int N) {
	auto start = steady_clock::now();
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N - 1; i++) if (arr[i] > arr[i + 1]) swap(arr[i], arr[i + 1]);
	}
	auto end = steady_clock::now();
	auto elapsed = duration_cast<nanoseconds>(end - start);
	for (int i = 0; i < N; i++) cout << arr[i] << " ";
	cout << endl;
	cout << "sorting took " << elapsed.count() << " nanosec\n";
}
void shackersort(int* arr, int N) {
	auto start = steady_clock::now();
	for (int j = 0; j < N / 2; j++) {
		for (int i = 0; i < N - 1; i++) {
			if (arr[i] > arr[i + 1]) swap(arr[i], arr[i + 1]);
		}
		for (int i = N - 2; i > 0; i--) {
			if (arr[i] < arr[i - 1]) swap(arr[i], arr[i - 1]);
		}
	}
	auto end = steady_clock::now();
	auto elapsed = duration_cast<nanoseconds>(end - start);
	for (int i = 0; i < N; i++) cout << arr[i] << " ";
	cout << endl;
	cout << "sorting took " << elapsed.count() << " nanosec\n";
}
void combsort(int* arr, int N) {
	auto start = steady_clock::now();
	double S = N - 1, k = 1.3;
	int count = 0;
	while (S >= 1) {
		for (int i = 0; i + S < N; i++) {
			if (arr[i] > arr[int(i + S)]) swap(arr[i], arr[int(i + S)]);
		}
		S /= k;
	}
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N - 1; i++) if (arr[i] > arr[i + 1]) swap(arr[i], arr[i + 1]);
	}
	auto end = steady_clock::now();
	auto elapsed = duration_cast<nanoseconds>(end - start);
	for (int i = 0; i < N; i++) cout << arr[i] << " ";
	cout << endl;
	cout << "sorting took " << elapsed.count() << " nanosec\n";
}
void insertsort(int* arr, int N) {
	auto start = steady_clock::now();
	for (int i = 1; i < N; i++) {
		for (int j = i - 1; j >= 0; j--) if (arr[i] < arr[j]) {
			swap(arr[i], arr[j]);
			i -= 1;
		}
	}
	auto end = steady_clock::now();
	auto elapsed = duration_cast<nanoseconds>(end - start);
	for (int i = 0; i < N; i++) cout << arr[i] << " ";
	cout << endl;
	cout << "sorting took " << elapsed.count() << " nanosec\n";
}
void quicksort(int* arr, int end, int begin, int N) {
	int mid;
	int b = begin;
	int e = end;
	mid = arr[(b + e) / 2];
	while (b < e)
	{
		while (arr[b] < mid) b++;
		while (arr[e] > mid) e--;
		if (b <= e)
		{
			swap(arr[b], arr[e]);
			b++;
			e--;
		}
	}
	if (begin < e) quicksort(arr, e, begin, N);
	if (b < end) quicksort(arr, end, b, N);
}
void binarySearch(signed* arr, signed a, signed begin, signed end, int N, int kleft, int kright) {
	int kl = kleft, kr = kright;
	signed right = end, left = begin;
	if (-100 < a && a < 100) {
		int mid = (kl + kr) / 2;
		if (arr[mid] != a && kr - kl < 2) {
			cout << "the entered number is not in the array " << endl;
			return;
		}
		if (arr[mid] == a) {
			cout << "the entered number is in the array with the number " << mid << endl;
		}
		if (arr[mid] > a) {
			kr = mid;
			right = arr[mid];
			binarySearch(arr, a, begin, right, N, kleft, kr);
		}
		else if (arr[mid] < a) {
			kl = mid;
			left = arr[mid];
			binarySearch(arr, a, left, end, N, kl, kright);
		}
	}
	else cout << "number out of range\n";
}

int main() {
	// 1. Целочисленный массив из 100 элементов с диапазоном [-99,99].
	int arr[N] = {}, cycleArr;
	cout << "1 - create an array; 0 - finish the cycle\n";
	cin >> cycleArr;
	while (cycleArr) {
		cout << "[ ";
		for (int i = 0; i < N; i++) {
			arr[i] = minNum + rand() % (maxNum - minNum + 1);
			cout << arr[i] << " ";
		}
		cout << "]" << endl;
		cin >> cycleArr;
	}
	// *Поиск минимального и максимального элементов в неотсортированном массиве.
	int arrMaxMin[N] = {};
	for (int i = 0; i < N; i++)
		arrMaxMin[i] = arr[i];
	auto startFind = steady_clock::now();
	for (int i = 0; i < N - 1; i++)
		if (arrMaxMin[i] > arrMaxMin[i + 1])
			swap(arrMaxMin[i], arrMaxMin[i + 1]);
	for (int i = N - 1; i > 0; i--)
		if (arrMaxMin[i] < arrMaxMin[i - 1])
			swap(arrMaxMin[i], arrMaxMin[i - 1]);
	auto endFind = steady_clock::now();
	auto resultFind = duration_cast<nanoseconds>(endFind - startFind);
	// 2. Сортировка массива.
	int sortName, koef = 0, arrBub[N] = {}, arrShack[N] = {}, arrComb[N] = {}, arrIns[N] = {}, arrQuick[N] = {}, cycleSort, end = N - 1, begin = 0;
	cout << "1 - sort an array; 0 - finish the cycle\n";
	cin >> cycleSort;
	while (cycleSort) {
		cout << endl << "way to sort an array (1 - bubblesort, 2 - shackersort,3 - combsort,4 - insertsort,5 - quicksort). \n";
		cin >> sortName;
		switch (sortName) {
		case 1:
			for (int i = 0; i < N; i++) {
				arrBub[i] = arr[i];
			}
			bubblesort(arrBub, N);
			break;
		case 2:
			for (int i = 0; i < N; i++) {
				arrShack[i] = arr[i];
			}
			shackersort(arrShack, N);
			break;
		case 3:
			for (int i = 0; i < N; i++) {
				arrComb[i] = arr[i];
			}
			combsort(arrComb, N);
			break;
		case 4:
			for (int i = 0; i < N; i++) {
				arrIns[i] = arr[i];
			}
			insertsort(arrIns, N);
			break;
		case 5:
			for (int i = 0; i < N; i++) {
				arrQuick[i] = arr[i];
			}
			auto start = steady_clock::now();
			quicksort(arrQuick, end, begin, N);
			auto end1 = steady_clock::now();
			auto elapsed = duration_cast<nanoseconds>(end1 - start);
			for (int i = 0; i < N; i++)
				cout << arrQuick[i] << " ";
			cout << endl;
			cout << "sorting took " << elapsed.count() << " nanosec\n";
			break;
		}
		cin >> cycleSort;
	}
	quicksort(arr, end, begin, N);
	// 3. Поиск максмимального и минимального элемента.
	{
		cout << "\nlook up max and min values in a sorted or unsorted array?\n";
		string array;
		int j = 0;
		while (j != 2) {
			cin >> array;
			if (array == "unsorted") {
				cout << "min and max elements for array: " << arrMaxMin[0] << ", " << arrMaxMin[N - 1] << endl; // *
				j += 1;
				cout << "searching for elements took " << resultFind.count() << " nanosec\n";
			}
			else if (array == "sorted") {
				auto startFindS = steady_clock::now();
				arr[0], arr[N - 1];
				auto endFindS = steady_clock::now();
				auto resultFindS = duration_cast<nanoseconds>(endFindS - startFindS);
				cout << "min and max elements for array: " << arr[0] << ", " << arr[N - 1] << endl;
				cout << "searching for elements took " << resultFindS.count() << " nanosec\n";
				j += 1;
			}
		}
	}
	// 4. Среднее значение минимального и максимального значения. Индексы равные этому значению и их кол-во.
	{
		int avg = (arr[N - 1] + arr[0]) / 2, k = 0;
		cout << endl << "the average of the min and max elements: " << avg << endl;
		for (int i = 0; i < N; i++)
			if (arr[i] == avg) {
				k += 1;
				cout << "arr [ " << i << " ] = ";
			}
		if (k != 0) cout << avg << " ";
		cout << "amount of elements: " << k << endl;
	}
	// 5. Количество элементов в массиве меньше элемента a, введенного пользователем.
	int cycle5, a;
	cout << "1 - find elements less than the entered; 0 - end the cycle\n";
	cin >> cycle5;
	while (cycle5) {
		int k = 0, i = 0;
		cout << "input element: ";
		cin >> a;
		while (arr[i] < a && i < N) {
			i++;
			k++;
		}
		cout << "the number of elements in the array is less than the entered element: " << k << endl;
		cin >> cycle5;
	}
	// 6. Количество элементов в массиве больше элемента b, введенного пользователем.
	int cycle6, b;
	cout << "1 - find elements more than the entered; 0 - end the cycle\n";
	cin >> cycle6;
	while (cycle6) {
		int k = 0, i = N - 1;
		cout << "input element: ";
		cin >> b;
		while (arr[i] > b) {
			i--;
			k++;
		}
		cout << "the number of elements in the array is more than the entered element: " << k << endl;
		cin >> cycle6;
	}
	// 7. Есть ли введенное пользователем число в отсортированном массиве (проверка бинарным поиском и перебором).
	int cycle7;
	cout << "1 - start binary search; 0 - end the cycle\n";
	cin >> cycle7;
	while (cycle7) {
		// бинарный поиск
		int a;
		cout << "enter a number in the range [-99,99] \n";
		cin >> a;
		int kleft = 0, kright = N;
		{
			signed begin = arr[0], end = arr[N - 1];
			auto start = steady_clock::now();
			binarySearch(arr, a, begin, end, N, kleft, kright);
			auto end1 = steady_clock::now();
			auto elapsed = duration_cast<nanoseconds>(end1 - start);
			cout << endl;
			cout << "binary search took " << elapsed.count() << " nanosec\n";
		}
		cout << endl;
		// перебор
		auto start = steady_clock::now();
		for (int i = 0, k = 0; i < N; i++) {
			if (arr[i] == a) cout << "the entered number is in the array with the number " << i << endl;
			k += 1;
			if (k == 0 && i == 99) cout << "the entered number is not in the array\n";
		}
		auto endTime = steady_clock::now();
		auto elapsed = duration_cast<nanoseconds>(endTime - start);
		cout << "enumeration of elements took  " << elapsed.count() << " nanosec\n";
		cin >> cycle7;
	}
	// 8. Обмен мест элементов, индексы которых вводит пользователь.
	int cycle8;
	cout << "1 - start exchanging element locations; 0 - end the cycle\n";
	cin >> cycle8;
	while (cycle8) {
		int a, b;
		cout << "input the indices of the elements you want to swap: \n";
		cin >> a >> b;
		swap(arr[a], arr[b]);
		for (int i = 0; i < N; i++) cout << arr[i] << " ";
		cout << endl;
		cin >> cycle8;
	}
}