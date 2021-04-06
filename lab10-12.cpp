#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <io.h>
#include <string>
#include <conio.h> 


using namespace std;

FILE* file;
struct DataBase {
    char numb[40];
    char dest[40];
    char thour[40];
    char tmin[40];
    int time;
};

char fileName[40];
int number;
DataBase s[20];
char destination[20];

int menu();
void EnterFileName();
void createFile();
void enterInfo();
void openFile();
void resScreenFile();
int SortMenu();
void SortVibor(DataBase*, int);
void QuickSort(DataBase*, int, int);
void ViewRes();
int SearchMenu();
int FullSearch(DataBase*, int);
int InterSearch(DataBase*, int, int);

int main()
{
    setlocale(LC_ALL, "ru");
    EnterFileName();
    switch (menu()) {
    case 1: createFile(); break;
    case 2: openFile(); break;
    case 3: return 0; break;
    }
    switch (SortMenu()) {
    case 1: SortVibor(s, number); ViewRes(); break;
    case 2: QuickSort(s, 0, number - 1); ViewRes(); break;
    case 3: return 0; break;
    }
    switch (SearchMenu()) {
    case 1: {
        int t = FullSearch(s, number);
        if (t > -1) {
            cout << "Рейсы в 14:00: \n" << "Номер рейса: " << s[t].numb << ". Пункт назначения: " << s[t].dest << endl;
        }
        else {
            cout << "Рейсов в 14:00 не надено." << endl;
        }
        break;
    }
    case 2: {
        int t = InterSearch(s, number, 840);
        if (t > -1) {
            cout << "Рейсы в 14:00: \n" << "Номер рейса: " << s[t].numb << ". Пункт назначения: " << s[t].dest << endl;
        }
        else {
            cout << "Рейсов в 14:00 не надено." << endl;
        }
        break;
    }
    case 3: return 0; break;
    }
}

int menu() {
    cout << "1. Создать файл c именем " << fileName << " и ввести информацию о рейсах" << endl;
    cout << "2. Открыть файл c именем " << fileName << endl;
    cout << "3. Закончить работу программы." << endl;
    int k;
    cin >> k;
    return k;
}

void EnterFileName() {
    cout << "Введите имя файла: " << endl;
    cin >> fileName;
}

void createFile() {
    if ((file = fopen(fileName, "w")) == NULL) {
        cout << "Ошибка при создании файла" << endl;
        exit(1);
    }
    cout << "Файл " << fileName << " создан успешно" << endl;
    fclose(file);
    enterInfo();
}

void enterInfo() {
    cout << "Введите количество рейсов: " << endl;
    cin >> number;
    if ((file = fopen(fileName, "w")) == NULL) {
        cout << "Ошибка при создании файла вывода";
        exit(1);
    }
    for (int i = 0; i < number; i++) {
        cout << "Введите номер рейса: " << endl;
        cin >> s[i].numb;
        fputs("Номер рейса: ", file);
        fputs(s[i].numb, file);
        cout << "Введите пункт назначения: " << endl;
        cin >> s[i].dest;
        fputs("\nПункт назначения: ", file);
        fputs(s[i].dest, file);
        cout << "Введите время вылета (часы, минуты): " << endl;
        cin >> s[i].thour;
        fputs("\nВремя вылета: ", file);
        fputs(s[i].thour, file);
        cin >> s[i].tmin;
        fputs(":", file);
        fputs(s[i].tmin, file);
        fputs("\n\n", file);
        s[i].time = atoi(s[i].thour) * 60 + atoi(s[i].tmin);
    }
    fclose(file);
    cout << "Вас интересует какой-нибудь определенный пункт назначения?\n1.Да\n2.Нет" << endl;
    int k;
    cin >> k;
    switch (k) {
    case 1: resScreenFile(); break;
    case 2: break;
    }
}

void openFile() {
    if ((file = fopen(fileName, "r")) == NULL) {
        cout << "Ошибка при открытии файла вывода";
        exit(1);
    }
    int i = 0;
    rewind(file);
    while (fscanf(file, "%s%s%s%s", &(s[i].numb), &(s[i].dest), &(s[i].thour), &(s[i].tmin)) != EOF)
    {
        cout << s[i].numb << s[i].dest << s[i].thour << s[i].tmin << endl;
        i++;
    }
    fclose(file);
}


void resScreenFile() {
    cout << "Введите интересующий пункт назначения: " << endl;
    cin >> destination;
    cout << "Рейсы в " << destination << ": " << endl;
    for (int i = 0; i < number; i++) {
        if (strcmp(s[i].dest, destination) == 0) {
            cout << "Номер рейса: " << s[i].numb << " Время отправки: " << s[i].thour << ":" << s[i].tmin << endl;
        }
    }
    FILE* fl;
    char fName[20];
    cout << "Введите имя файла вывода: " << endl;
    cin >> fName;
    if ((fl = fopen(fName, "w")) == NULL) {
        cout << "Ошибка при создании файла вывода";
        exit(1);
    }
    for (int i = 0; i < number; i++) {
        if (strcmp(s[i].dest, destination) == 0) {
            fputs("Номер рейса: ", fl);
            fputs(s[i].numb, fl);
            fputs("\nВремя вылета: ", fl);
            fputs(s[i].thour, fl);
            fputs(":", fl);
            fputs(s[i].tmin, fl);
            fputs("\n\n", fl);
        }
    }
    fclose(fl);
}

void SortVibor(DataBase* s, int number) {
    int i, imin, j;
    DataBase t;
    for (i = 0; i < number-1; i++) {
        imin = i; 
        for (j = i + 1; j < number; j++) {
            if (s[imin].time > s[j].time) {
                imin = j;
            }
        }
        if (imin != i) {
            t = s[imin];
            s[imin] = s[i];
            s[i] = t;
        }
    }

}

int SortMenu() {
    cout << "1. Отсортировать данные методом выбора." << endl;
    cout << "2. Отсортировать данные методом QuickSort. " << endl;
    cout << "3. Закончить работу программы." << endl;
    int k;
    cin >> k;
    return k;
}

void QuickSort(DataBase *s, int left, int right) {
    if (left < right) {
        int i = left, j = right;
        DataBase t, x;
        int mid;
        mid = s[(left + right) / 2].time;
        do {
            while (s[i].time < mid) i++;
            while (s[j].time > mid) j--;
            if (i <= j) {
                x = s[i];
                s[i] = s[j];
                s[j] = x;
                i++;
                j--;
            }
        } while (i <= j);
        if (left < j) QuickSort(s, left, j);
        if (i < right) QuickSort(s, i, right);
    }
}

void ViewRes() {
    if ((file = fopen(fileName, "w")) == NULL) {
        cout << "Ошибка при создании файла вывода";
        exit(1);
    }
    for (int i = 0; i < number; i++) {
        cout << "Номер рейса:" << s[i].numb << ". Пункт назначения: " << s[i].dest << ". Время вылета: " << s[i].thour << ":" << s[i].tmin << endl;
        fputs("Номер рейса: ", file);
        fputs(s[i].numb, file);
        fputs("\nВремя вылета: ", file);
        fputs(s[i].thour, file);
        fputs(":", file);
        fputs(s[i].tmin, file);
        fputs("\n\n", file);
    }
    fclose(file);
}

int SearchMenu() {
    cout << "Выберите метод поиска: " << endl;
    cout << "1. Поиск методом полного перебора." << endl;
    cout << "2. Поиск интерполяционным методом. " << endl;
    cout << "3. Закончить работу программы." << endl;
    int k;
    cin >> k;
    return k;
}

int FullSearch(DataBase* s, int number) {
    for (int i = 0; i < number; i++) {
        if (s[i].time == 840) { 
                return i;
        }
    }
    return -1;
}

int InterSearch(DataBase* s, int number, int x) {
    int i = 0, j = number - 1, m;
    while (i < j) {
        if (s[i].time == s[j].time) {
            if (s[i].time == x) {
                return i;
            }
            else return -1;
        }
            m = i + (j - i) * (x - s[i].time) / (s[j].time - s[i].time);
            if (s[m].time == x) {
                return m;
            }
            else if (x > s[m].time)
                i = m + 1;
            else j = m - 1;
    }
    return -1;
}
