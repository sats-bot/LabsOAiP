#include <iostream>
#include <cstdio>

using namespace std;

struct comp {
	comp* next;
	int info;
};

comp *AddStack(comp*, int);
void ReadDelStack(comp**);
comp* DelAllStack(comp*);
void ViewStack(comp*);

int main()
{
	comp* Stack = NULL;
	setlocale(LC_ALL, "ru");
	cout << "Введите количество элементов: ";
	int n, elem;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Введите " << i + 1 << " элемент:" << endl;
		cin >> elem;
		Stack = AddStack(Stack, elem);
	}
	cout << "Исходный стек:" << endl;
	ViewStack(Stack);
	ReadDelStack(&Stack);
	cout << "Стек без отрицательных чисел:" << endl;
	if (Stack) ViewStack(Stack);
	DelAllStack(Stack);
	return 0;
}

comp* AddStack(comp* a, int info) {
	comp* temp = new comp;
	temp->info = info;
	temp->next = a;
	return temp;
}

void ReadDelStack(comp** ptr) {
	comp* temp = *ptr;
	comp* deleted = NULL;
	comp* prev = NULL;
	while (temp) {
		if (temp->info < 0) {
			cout << "Элемет " << temp->info << " меньше 0 - удаление..." << endl;
			if (temp == *ptr) {
				*ptr = temp->next;
				deleted = temp->next;
				delete temp;
			}
			else
			{
				prev->next = temp->next;
				deleted = temp->next;
				delete temp;
			}
			temp = deleted;
		}
		else {
			prev = temp;
			temp = temp->next;
		}
	}
	cout << "Отрицательные элементы удалены." << endl;
}

comp* DelAllStack(comp* ptr) {
	comp* temp;
	if (ptr == NULL) {
		cout << "Стек пуст." << endl;
		return NULL;
	}
	while (ptr) {
		cout << "Удаление элемента " << ptr->info << endl;
		temp = ptr;
		ptr = ptr->next;
		delete temp;
	}
	cout << "Стек очищен." << endl;
	return NULL;
}

void ViewStack(comp* a) {
	comp* ptr = a;
	if (ptr == NULL) {
		cout << "Стек пуст." << endl;
		return;
	}
	while (ptr != NULL) {
		cout << ptr->info << " ";
		ptr = ptr->next;
	}
	cout << endl;
}
