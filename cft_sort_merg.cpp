#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <conio.h>
#include <algorithm>

using namespace std;

template <typename T>
bool sort_a(vector<T>& vec) {

	int n = vec.size();
	int i = 0;
	for (int i = 0; i < n-1; i++) {
			if (vec[i] > vec[i++])
				continue;

			else
				return false;			
		}	
	return true;
}

template <typename T>
bool sort_b(vector<T>& vec) {

	int n = vec.size();
		for (int i = 0; i < n - 1; i++){
			
				if (vec[i] < vec[i++])
					continue;
				else 
					return false;		
		}
	return true;
}

template <typename T>
vector<T> sort_merge (vector<T>& start, vector<T>& finish, int n, int m) {
	
	vector<T> sort(n + m);

	if (m == 0)
		return start;

	int i = 0, j = 0, index = 0;
	
	while (i < n && j < m)
		sort[index++] = start[i] < finish[j] ? start[i++] : finish[j++];

	while (i < n)
		sort[index++] = start[i++];

	while (j < m)
		sort[index++] = finish[j++];
		
	return sort;
}

template<typename T>
void merge(vector<T>& vec, int left, int right, int middle)
{
	if (left >= right || middle < left || middle > right) 
		return;
	if (right == left + 1 && vec[left] > vec[right]) {
		swap(vec[left], vec[right]);
		return;
	}

	vector<T> tmp(&vec[left], &vec[right] + 1);

	for (int i = left, j = 0, k = middle - left + 1; i <= right; ++i) {
		if (j > middle - left) 
			vec[i] = tmp[k++];
	
		else if (k > right - left) 
			vec[i] = tmp[j++];
		
		else 
			vec[i] = (tmp[j] < tmp[k]) ? tmp[j++] : tmp[k++];		
	}
}

template<typename T>
void MergeSort(vector<T>& vec, int left, int right)
{
	if (left >= right) return;

	int middle = left + (right - left) / 2;

	MergeSort(vec, left, middle);
	MergeSort(vec, middle + 1, right);
	merge(vec, left, right, middle);
}



template <typename T>
void finish_create(vector<T>& start, vector<T>& finish, char u, char s) {
	
	cout << "Введите название файлов для сортировки через пробел, если ввод файлов закончен нажмите esc" << endl;
	
	while (_getch() != 27) 
	{		
		char car[25];
		cin >> car;
		ifstream file(car);

		if (!file.is_open()) {
			cout << "Файл не существует! Введите название заново." << endl;
			continue;
		}
	
		if (file.eof()) {
			cout << "Файл " << car << " пустой!" << endl << "Введите название заново. " << endl;
			continue;
		}

		T type;

		while (!file.eof())
		{
			if (file >> type)
				start.insert(start.end(), type);
			else
			{
				file.clear();
				file.ignore(1, ' ');
			}
		}
		
		file.close();	
		
			int n = start.size(), m = finish.size();

			if (!sort_a(start)) 
			{	
				if (sort_b(start)) 
					reverse(start.begin(), start.end());
					

				else 
				{
					cout << "Файл не отсортирован. Подождите немного, идет сортировка..." << endl;						
					MergeSort(start,0,n-1);
					cout << "Файл отсортирован." << endl;
				}

				
			}

	finish = sort_merge(start, finish, n, m);
	start.clear();	
	}	

	cout << "Введите название итогового файла, куда сохранить" << endl;
	char cdr[25];
	cin >> cdr;
	ofstream file(cdr);
	
	if (u == 'b') 
		copy(finish.rbegin(), finish.rend(), ostream_iterator<T>(file, "\n"));
	else
		copy(finish.begin(), finish.end(), ostream_iterator<T>(file, "\n"));
	
	cout << "Файл успешно сохранен!" << endl;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (1) {

		char ty, u;
		cout << "Введите i-отсортировать int, s - отсортировать char, e-если хотите выйти из программы " << endl;
		cin >> ty;

		if (ty == 'e')
			return 0;

		if (ty != 'e' && ty != 'i' && ty != 's') {
			cout << "Ввели неверное значение! Попробуйте снова." << endl;
			continue;
		}

		cout << "Введите a - сортировка по возрастанию, b - сортировка по убыванию" << endl;
		cin >> u;

		if (ty == 'i') {

			vector<int> finish_int, start_int;
			finish_create(start_int, finish_int, u, ty);
			finish_int.clear();	start_int.clear();

			continue;
		}

		if (ty == 's') {

			vector<char> finish_char, start_char;
			finish_create(start_char, finish_char, u, ty);
			finish_char.clear(); start_char.clear();

			continue;
		}

	}

	return 0;
}

