// Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "stllib.h"
using namespace std;

void printVector(vector<int> data) {
	for (int val : data) {
		cout << val << endl;
	}
}

void swap(vector<int> *data, int ind1, int ind2) {
	int tempData = (*data)[ind1];
	(*data)[ind1] = (*data)[ind2];
	(*data)[ind2] = tempData;
}

vector<int> selectionSort(vector<int> data) {

	// index of sorted array
	int sorted = 0;
	for (int i = 0; i < data.size();i++) {
		//find the minimum
		int min = sorted;
		for (int j = sorted; j < data.size();j++) {
			if (data[j]<data[min]) {
				min = j;
			}
		}
		//swap minimum 
		int temp = data[min];
		data[min] = data[sorted];
		data[sorted] = temp;
		sorted++;
	}
	return data;
}

vector<int> bubbleSort(vector<int> data) {
	bool sorted = false;
	//do while data is not sorted
	while(!sorted) {
		bool swap = false;
		for (int i = 0; i < data.size()-1;i++) {
			//swap values if i > i+1
			if (data[i]>data[i+1]) {
				int temp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = temp;
				//values have been swapped
				swap = true;
			}
		}
		//data is sorted if no values are swapped
		if (!swap) {
			sorted = true;
		}
	} 
	return data;
}

vector<int> insertionSort(vector<int> data) {
	for (int i = 1; i < data.size() ; i++) {
		int place = i-1;
		int key = data[i];
		while (place >= 0 && data[place]< key) {
			data[place+1] = data[place];
			place--;
		}
		data[place + 1] = key;
	}
	return data;
}




// use two pointer
void merge(vector<int> *data, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;
	vector<int> tr, tl;

	for (int i = 0; i < n1; i++) {
		tl.push_back((*data)[l+i]);
	}
	for (int i = 0; i < n2; i++) {
		tr.push_back((*data)[m + 1 + i]);
	}

	int i = 0;
	int j = 0;
	int k = l;

	while (i<n1 && j<n2) {
		if (tr[j]<tl[i]) {
			(*data)[k] = tr[j];
			j++;
		}
		else {
			(*data)[k] = tl[i];
			i++;
		}
		k++;
	}

	for (i; i < tl.size();i++) {
		(*data)[k] = tl[i];
		k++;
	}

	for (j; j < tr.size(); j++) {
		(*data)[k] = tr[j];
		k++;
	}


}

void mergeS(vector<int>* data, int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		mergeS(data, l, m);
		mergeS(data, m + 1, r);
		merge(data, l, m, r);
	}
}

vector<int> mergeSort(vector<int> data) {
	mergeS(&data, 0, data.size() - 1);
	return data;
}




int partition(vector<int> *data,int low, int high) {
	int piv = (*data)[high];
	int i = low - 1;
	for (int j = low ; j <= high-1; j++) {
		if ((*data)[j] < piv) {
			i++;
			int temp = (*data)[i];
			(*data)[i] = (*data)[j];
			(*data)[j] = temp;
		}
	}
	int temp = (*data)[i + 1];
	(*data)[i + 1] = (*data)[high];
	(*data)[high] = temp;

	return i + 1;
}

void quickS(vector<int> *data, int low, int high) {
	if (low<high) {
		int pivot = partition(data, low, high);
		quickS(data, low, pivot- 1);
		quickS(data, pivot + 1, high);
	}

}

vector<int> quickSort(vector<int> data) {
	quickS(&data, 0, data.size() - 1);
	return data;
}


void heapify(vector<int> *data, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && (*data)[l] > (*data)[largest]) {
		largest = l;
	}
	if (r < n && (*data)[r] > (*data)[largest]) {
		largest = r;
	}

	if (largest != i) {
		swap(data, i, largest);
		heapify(data, n, largest);
	}
}




vector<int> heapSort(vector<int> data) {
	int n = (data).size();
	for (int i = (n / 2) - 1; i >= 0; i--) {
		heapify(&data, n, i);
	}
	for (int i = n - 1; i >= 0;i--) {
		swap(&data, 0, i);
		heapify(&data, i, 0);
	}
	return data;
}


vector<int> countingSort(vector<int> data) {
	int max = 0;
	for (int val : data) {
		if (val > max) {
			max = val;
		}
	}
	max++;
	vector<int> keys(max);
	for (int val : data) {
		keys[val]+=1;
	}
	int curr = 0;
	for (int i = 0; i < keys.size(); i++) {
		curr = curr + keys[i];
		keys[i] = curr;
	}
	vector<int> out(data.size());
	for (int val : data) {
		out[keys[val]-1] = val;
		keys[val]--;
	}


	return out;
}

vector<int> shellSort(vector<int> data) {
	int gap = data.size() / 2;
	while (gap > 0) {
		for (int i = gap; i < data.size(); i++) {
			int temp = data[i];
			int j;
			for (j = i; j >= gap && data[j - gap] > temp; j-=gap) {
				data[j] = data[j - gap];
			}
			data[j] = temp;
		}
		
		gap /= 2;
	}
	return data;
}

void insertionSort(vector<int> *data, int left, int right) {
	for (int i = left + 1; i < right; i++) {
		int place = i - 1;
		int key = (*data)[i];
		while (place >= 0 && (*data)[place] < key) {
			(*data)[place + 1] = (*data)[place];
			place--;
		}
		(*data)[place + 1] = key;
	}
}




vector<int> timSort(vector<int> data) {
	int RUN = 32;

	for (int i = 0; i < data.size(); i+=RUN) {
		insertionSort(&data, i, min( (int) (i + RUN - 1), (int) (data.size())));
	}

	for (int size = RUN; size < data.size(); size = 2*size ) {

		for (int left = 0; left < data.size(); left += 2*size) {
			int mid = left + size - 1;
			int right = min((int)(left + 2*size - 1), (int)(data.size() - 1));
			merge(&data, left, mid, right);
		}
	}

	return data;
}







vector<int> noSort(vector<int> data) {
	return data;
}








int main()
{
	cout << "Generated" << endl;
	vector<int> vec;
	int items = 20;
	for (int i = 0; i < items; i++) {
		vec.push_back(rand()%1000);
	}
	printVector(vec);
	vector<int> newVec = timSort(vec);
	cout << endl << "Sorted" << endl;
	printVector(newVec);

}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
