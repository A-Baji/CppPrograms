#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;

template <class T>
class hashT
{
public:
	void insert(int hashIndex, const T& rec);
	void search(int& hashIndex, const T& rec, bool& found) const;
	bool isItemAtEqual(int hashIndex, const T& rec) const;
	void remove(int hashIndex, const T& rec);
	hashT(int size = 101);
	~hashT();
private:
	T *HTable;   //pointer to the hash table
	int *indexStatusList;  //pointer to the array indicating the
						   //status of a position in the hash table
	int length;    //number of items in the hash table
	int HTSize;    //maximum size of the hash table
};

template<class T>
void hashT<T>::insert(int hashIndex, const T& rec) {
	int j = 0;//for the quadratic probing
	while (j < HTSize) {
		if (indexStatusList[hashIndex] == 0 || indexStatusList[hashIndex] == 2) {
			HTable[hashIndex] = rec;
			indexStatusList[hashIndex] = 1;
			length++;
			break;
		}
		else {
			j++;
			hashIndex = hashIndex + j * j;
			hashIndex = hashIndex % HTSize;
		}
	}
	if (j >= HTSize) {
		std::cout << "\nhash table is full!!!";
	}
}

template<class T>
void hashT<T>::remove(int hashIndex, const T& rec) {
	int j = 0;
	while (j < HTSize) {
		if (indexStatusList[hashIndex] == 0) {
			return;
		}
		else if (indexStatusList[hashIndex] == 1) {
			if (isItemAtEqual(hashIndex, rec)) {
				indexStatusList[hashIndex] = 2;
				HTable[hashIndex].~T();
				length--;
				return;
			}
			return;
		}
		j++;
		hashIndex += j * j;
		hashIndex = hashIndex % HTSize;
	}
}

template<class T>
void hashT<T>::search(int& hashIndex, const T& rec, bool& found)const {
	int j = 0;
	while (j < HTSize) {
		if (indexStatusList[hashIndex] == 0) {
			found = false;
			return;
		}
		else if (indexStatusList[hashIndex] == 1) {
			if (HTable[hashIndex] == rec) {
				found = true;
				return;
			}
		}
		j++;
		hashIndex = hashIndex + j * j;
		hashIndex = hashIndex % HTSize;
	}
	found = false;
}

template<class T>
bool hashT<T>::isItemAtEqual(int hashIndex, const T& rec) const {
	if (indexStatusList[hashIndex] == 1) {
		return HTable[hashIndex] == rec;
	}
}

template<class T>
hashT<T>::hashT(int size) {
	HTSize = size;
	length = 0;
	HTable = new T[size];
	indexStatusList = new int[size];
	for (int i = 0; i < size; i++) {
		indexStatusList[i] = 0;
	}
}

template<class T>
hashT<T>::~hashT() {
	delete[] HTable;
	delete[] indexStatusList;
}

int hash1(int val, int max) {
	return val % max;
}

int main()
{
	int usArr[100];
	int sArr[100];
	hashT<int> hTable;

	ifstream ifile;
	ifile.open("ints.txt");
	string line;
	int i = 0;
	while (getline(ifile, line)) {
		usArr[i] = stoi(line);
		sArr[i] = stoi(line);
		hTable.insert(i, stoi(line));
		i++;
	}
	sort(sArr, sArr + 20);
	int size = 20;

	int num;
	int idx;
	int select = -1;
	while (select != 0) {
		cout << "\nEnter a number:\n1. Insert\n2. Delete\n3. Search\n0. Exit\n";
		cin >> select;

		if (select == 1) { //insert
			cout << "Enter number to insert:\n";
			cin >> num;
			cout << "Enter index to insert at:\n";
			cin >> idx;

			//Unsorted
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (int i = size; i > idx; i--)
				usArr[i] = usArr[i-1];
			usArr[idx] = num;
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			cout << "\nUnsorted execution time: " << time_span.count() << " seconds.\n";

			//Sorted
			t1 = high_resolution_clock::now();
			sArr[size] = num;
			sort(sArr, sArr + size + 1);
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			cout << "\nSorted execution time: " << time_span.count() << " seconds.\n";

			//Hashing table
			t1 = high_resolution_clock::now();
			hTable.insert(hash1(num,101), num);
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			cout << "\nHashing table execution time: " << time_span.count() << " seconds.\n\n";

			size++;
		}

		else if (select == 2) { //delete
			cout << "Enter number to delete:\n";
			cin >> num;
			int i;
			int c = 0;

			//Unsorted
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (i = 0; i < size; i++)
				if (usArr[i] == num) {
					c = 1;
					break;
				}

			if (c == 0) {
				cout << "\nNumber does not exist\n";
				continue;
			}

			for (int k = i; k < size; k++)
				usArr[k] = usArr[k+1];
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			cout << "\nUnsorted execution time: " << time_span.count() << " seconds.\n";

			//Sorted
			t1 = high_resolution_clock::now();
			for (i = 0; i < size; i++)
				if (sArr[i] == num)
					break;
			for (int k = i; k < size; k++)
				sArr[k] = sArr[k + 1];
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			cout << "\nSorted execution time: " << time_span.count() << " seconds.\n";

			//Hashing table
			t1 = high_resolution_clock::now();
			hTable.remove(hash1(num,101), num);
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			cout << "\nHashing table execution time: " << time_span.count() << " seconds.\n\n";

			size--;
		}

		else if (select == 3) { //search
			cout << "Enter number to search:\n";
			cin >> num;
			int c;

			//Unsorted
			c = 0;
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (int i = 0; i < size; i++)
				if (usArr[i] == num) {
					c = 1;
					break;
				}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			if (c == 0) {
				cout << "\nNumber not found\n";
				continue;
			}
			duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			cout << "\nUnsorted execution time: " << time_span.count() << " seconds.\n";

			//Sorted
			t1 = high_resolution_clock::now();
			for (int i = 0; i < size; i++)
				if (sArr[i] == num)
					break;
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			cout << "\nSorted execution time: " << time_span.count() << " seconds.\n";

			//Hashing table
			t1 = high_resolution_clock::now();
			bool found;
			int hIdx = hash1(num, 101);
			hTable.search(hIdx, num, found);
			t2 = high_resolution_clock::now();
			time_span = duration_cast<duration<double>>(t2 - t1);
			cout << "\nHashing table execution time: " << time_span.count() << " seconds.\n\n";
		}

		else if (select == 0) {
			cout << "Exiting\n";
			break;
		}
		else
			cout << "Invalid choice, Try again.\n";
	}

	return 0;
}
