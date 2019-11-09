#include <iostream>

using namespace std;

void printVector(vector<int> &data) {
	for (int val : data) {
		cout << val << endl;
	}
}

void swap(vector<int> &data, int ind1, int ind2) {
	int tempData = data[ind1];
	data[ind1] = data[ind2];
	data[ind2] = tempData;
}

void selectionSort(vector<int> &data) {

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
}

void bubbleSort(vector<int> &data) {
	bool swapped = true;
	//do while data is not sorted
	while(swapped) {
		 swapped = false;
		for (int i = 0; i < data.size()-1;i++) {
			//swap values if i > i+1
			if (data[i] > data[i+1]) {
				swap(data, i, i + 1);
				//values have been swapped
				swapped = true;
			}
		}
		//data is sorted if no values are swapped
		
	} 
}

void insertionSort(vector<int> &data) {
	for (int i = 1; i < data.size() ; i++) {
		int place = i-1;
		int key = data[i];
		while (place >= 0 && data[place] > key) {
			data[place+1] = data[place];
			place--;
		}
		data[place + 1] = key;
	}
}




// use two pointer
void merge(vector<int> &data, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;
	vector<int> tr, tl;

	for (int i = 0; i < n1; i++) {
		tl.push_back(data[l+i]);
	}
	for (int i = 0; i < n2; i++) {
		tr.push_back(data[m + 1 + i]);
	}

	int i = 0;
	int j = 0;
	int k = l;

	while (i<n1 && j<n2) {
		if (tr[j]<tl[i]) {
			data[k] = tr[j];
			j++;
		}
		else {
			data[k] = tl[i];
			i++;
		}
		k++;
	}

	for (i; i < tl.size();i++) {
		data[k] = tl[i];
		k++;
	}

	for (j; j < tr.size(); j++) {
		data[k] = tr[j];
		k++;
	}


}

void mergeS(vector<int> &data, int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		mergeS(data, l, m);
		mergeS(data, m + 1, r);
		merge(data, l, m, r);
	}
}

void mergeSort(vector<int> &data) {
	mergeS(data, 0, data.size() - 1);
}




int partition(vector<int> &data,int low, int high) {
	int piv = data[high];
	int i = low - 1;
	for (int j = low ; j <= high-1; j++) {
		if (data[j] < piv) {
			i++;
			int temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
	int temp = data[i + 1];
	data[i + 1] = data[high];
	data[high] = temp;

	return i + 1;
}

void quickS(vector<int> &data, int low, int high) {
	if (low<high) {
		int pivot = partition(data, low, high);
		quickS(data, low, pivot- 1);
		quickS(data, pivot + 1, high);
	}

}

void quickSort(vector<int> &data) {
	quickS(data, 0, data.size() - 1);
}


void heapify(vector<int> &data, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && data[l] > data[largest]) {
		largest = l;
	}
	if (r < n && data[r] > data[largest]) {
		largest = r;
	}

	if (largest != i) {
		swap(data, i, largest);
		heapify(data, n, largest);
	}
}




vector<int> heapSort(vector<int> &data) {
	int n = (data).size();
	for (int i = (n / 2) - 1; i >= 0; i--) {
		heapify(data, n, i);
	}
	for (int i = n - 1; i >= 0;i--) {
		swap(data, 0, i);
		heapify(data, i, 0);
	}
	return data;
}


void countingSort(vector<int> &data) {
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
	data = out;
}

void shellSort(vector<int> &data) {
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
}

void insertionSort(vector<int> &data, int left, int right) {
	for (int i = left + 1; i < right; i++) {
		int place = i - 1;
		int key = data[i];
		while (place >= 0 && data[place] > key) {
			data[place + 1] = data[place];
			place--;
		}
		data[place + 1] = key;
	}
}




void timSort(vector<int> &data) {
	int RUN = 32;

	for (int i = 0; i < data.size(); i+=RUN) {
		insertionSort(data, i, min( (int) (i + RUN - 1), (int) (data.size())));
	}

	for (int size = RUN; size < data.size(); size = 2*size ) {

		for (int left = 0; left < data.size(); left += 2*size) {
			int mid = left + size - 1;
			int right = min((int)(left + 2*size - 1), (int)(data.size() - 1));
			merge(data, left, mid, right);
		}
	}
}

int nextGap(int gap) {
	gap = (gap * 10) / 13;
	if (gap < 1) {
		return 1;
	}
	return gap;
}

void combSort(vector<int> &data) {
	int gap = data.size();
	bool swapped = true;
	while (gap != 1 || swapped == true) {
		gap = nextGap(gap);
		swapped = false;
		for (int i = 0; i < data.size() - gap; i++ ) {
			if (data[i] > data[i + gap]) {
				swap(data, i, i + gap);
			}
		}
	}
}

void pigeonSort(vector<int> &data) {
	int min = data[0];
	int max = data[0];
	for (int val : data) {
		if (val > max) {
			max = val;
		}
		if (val < min) {
			min = val;
		}
	}
	int range = max - min + 1;
	vector<vector<int>> holes(range);
	for (int val : data) {
		vector<int> temp;
		holes.push_back(temp);
	}
	for (int val : data) {
		holes[val - min].push_back(val);
	}

	int index = 0;
	for (int i = 0; i < range; i++) {
		vector<int>::iterator it;
		for (it = holes[i].begin(); it != holes[i].end(); ++it) {
			data[index++] = *it;
		}
	}
}

void cycleSort(vector<int> &data) {

	for (int cycle_start = 0; cycle_start <= data.size() - 2; cycle_start++) {
		int item = data[cycle_start];

		int pos = cycle_start;
		for (int i = cycle_start + 1; i < data.size(); i++) {
			if (data[i] < item) {
				pos += 1;
			}
		}
		
		if (pos == cycle_start) {
			continue;
		}

		while (item == data[pos]) {
			pos += 1;
		}

		if (pos != cycle_start) {
			int temp = item;
			item = data[pos];
			data[pos] = temp;
		}

		
		while (pos != cycle_start)
		{
			pos = cycle_start;
			for (int i = cycle_start + 1; i < data.size(); i++) {
				if (data[i] < item) {
					pos += 1;
				}
			}
			while (item == data[pos]) {
				pos += 1;
			}
			if (item != data[pos]) {
				int temp = item;
				item = data[pos];
				data[pos] = temp;
			}
		}

	}
	
	
}


void cocktailSort(vector<int> &data) {
	bool swapped = true;
	while (swapped) {
		swapped = false;
		int i = 0;
		for (i; i < data.size() - 1; i++)
		{
			if (data[i] > data[i+1]) {
				swap(data, i, i + 1);
				swapped = true;
			}
		}

		if (!swapped) {
			break;
		}

		i--;

		for (i; i >= 1; i--)
		{
			if (data[i] < data[i - 1]) {
				swap(data, i, i - 1);
				swapped = true;
			}
		}

	}
}



void strandS(list<int> &in, list<int> &out) {
	if (in.empty()) {
		return;
	}

	list<int> sublist;
	sublist.push_back(in.front());
	in.pop_front();

	for (auto i = in.begin(); i != in.end(); )
	{
		if (*i > sublist.back()) {
			sublist.push_back(*i);
			i = in.erase(i);
		}
		else {
			i++;
		}
	}
	out.merge(sublist);
	strandS(in,out);
}

void strandSort(vector<int> &data) {
	list<int> in, out;
	for (int val : data) {
		in.push_back(val);
	}
	strandS(in, out);
	vector<int> ret;
	for (auto i = out.begin(); i != out.end(); ++i)
	{
		ret.push_back(*i);
	}
	data = ret;
}












vector<int> noSort(vector<int> data) {
	return data;
}




void randomize(vector<int>& data) {

}



int main()
{
	vector<int> vec;
	int items = 5;
	for (int i = 0; i < items; i++) {
		vec.push_back(rand() % 100);
	}
	cout << "Generated" << endl;
	random_shuffle(vec.begin(),vec.end());
	printVector(vec);
	cout << "Bubble Sort" << endl;
	bubbleSort(vec);
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Cocktail Sort" << endl;
	cocktailSort(vec);
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Comb Sort" << endl;
	combSort(vec);
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Counting Sort" << endl;
	countingSort(vec);
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Cycle Sort" << endl;
	cycleSort(vec);
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Heap Sort" << endl;
	heapSort(vec);
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Insertion Sort" << endl;
	insertionSort(vec);
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Merge Sort" << endl;
	mergeSort(vec);
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Pigeon Sort" << endl;
	pigeonSort(vec);
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Quick Sort" << endl;
	quickSort(vec);	
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Selection Sort" << endl;
	selectionSort(vec);	
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Shell Sort" << endl;
	shellSort(vec);	
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Strand Sort" << endl;
	strandSort(vec);	
	printVector(vec);
	random_shuffle(vec.begin(), vec.end());
	cout << "Tim Sort" << endl;
	timSort(vec);
	printVector(vec);
	cout << endl;

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
