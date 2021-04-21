#include <iostream>
#include <cstdio>

using namespace std;

struct Tree {
    int info;
    int height = 0;
    Tree* left;
    Tree* right;
};

void PrintPreOrder(Tree*);
void PrintPostOrder(Tree*);
void PrintInOrder(Tree*);
Tree* balanceTree(Tree*);
int heightDifference(Tree*);
Tree* rotateright(Tree*);
Tree* rotateleft(Tree*);
void deleteTree(Tree*);
Tree* insertNode(Tree*, int);
int getHeight(Tree*);
double average(Tree*);
int sum(Tree*);
int countOfNodes(Tree*);
int closest(Tree*, double);

int main()
{
    setlocale(LC_ALL, "ru");
    Tree* root = nullptr;
    cout << "Введите количество элементов: ";
    int n;
    cin >> n;
    cout << "Введите элементы дерева: " << endl;
    int* mas = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> mas[i];
        root = insertNode(root, mas[i]);
    }
    cout << "Вывод дерева (1. прямой обход; 2. обратный обход; 3. симметричный обход):\n1. ";
    PrintPreOrder(root);
    cout << "\n2. ";
    PrintPostOrder(root);
    cout << "\n3. ";
    PrintInOrder(root);
    cout << endl;
    cout << "Среднее значение всех элементов дерева: " << average(root) << endl;
    cout << "Ближайший элемент к среднему: " << closest(root, average(root)) << endl;
    delete[] mas;
    deleteTree(root);
    return 0;
}

void PrintPreOrder(Tree* temp) {
    if (temp != nullptr) {
        cout << temp->info << " ";
        PrintPreOrder(temp->left);
        PrintPreOrder(temp->right);
    }
}

void PrintPostOrder(Tree* temp) {
    if (temp != nullptr) {
        PrintPostOrder(temp->left);
        PrintPostOrder(temp->right);
        cout << temp->info << " ";
    }
}

void PrintInOrder(Tree* temp) {
    if (temp != nullptr) {
        PrintInOrder(temp->left);
        cout << temp->info << " ";
        PrintInOrder(temp->right);
    }
}

void deleteTree(Tree* temp) {
    if (temp == nullptr) return;
    deleteTree(temp->left);
    cout << "Удаление элемента " << temp->info << endl;
    deleteTree(temp->right);
    delete temp;
}

int heightDifference(Tree* temp) {
    return getHeight(temp->right) - getHeight(temp->left);
}

int getHeight(Tree* root) {
    return root ? root->height : 0;
}

void newHeight(Tree* temp) {
    int LeftHeight = getHeight(temp->left);
    int RightHeight = getHeight(temp->right);
    if (LeftHeight > RightHeight) {
        temp->height = LeftHeight + 1;
    }
    else temp->height = RightHeight + 1;
}

Tree* rotateleft(Tree* root) { //левый поворот
    Tree* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    newHeight(root);
    newHeight(temp);
    return temp;
}

Tree* rotateright(Tree* root) { //правый поворот
    Tree* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    newHeight(root);
    newHeight(temp);
    return temp;
}

Tree* balanceTree(Tree* root) {
    newHeight(root);
    if (heightDifference(root) == 2) {
        if (heightDifference(root->right) < 0) {
            root->right = rotateright(root->right);
        }
            return rotateleft(root);
    }
    if (heightDifference(root) == -2) {
        if (heightDifference(root->left) > 0) {
            root->left = rotateleft(root->left);
        }
        return rotateright(root);
    }
    return root;
}

Tree* insertNode(Tree* root, int info) {
    if (!root) {
        Tree* temp = new Tree;
        temp->info = info;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }
    if (info < root->info) {
        root->left = insertNode(root->left, info);
    }
    else {
        root->right = insertNode(root->right, info);
    }
    return balanceTree(root);
}

int sum(Tree* root) {
    if(root == nullptr) return 0;
    return root->info + sum(root->left) + sum(root->right);
}

int countOfNodes(Tree* root) {
    if (root == nullptr) return 0;
    return 1 + countOfNodes(root->left) + countOfNodes(root->right);
}

double average(Tree* root) {
    return 1.0 * sum(root) / countOfNodes(root);
}

int closest(Tree* temp, double avg) {
    double difference, minDifference = fabs(temp->info - avg) + 1;
    int ans = 0;
    while (temp) {
        if (temp->info == avg) return temp->info;
        if (temp->info > avg) {
            difference = fabs(temp->info - avg);
            if (minDifference > difference) {
                minDifference = difference;
                ans = temp->info;
            }
            temp = temp->left;
        }
        else if (temp->info < avg) {
            difference = fabs(temp->info - avg);
            if (minDifference > difference) {
                minDifference = difference;
                ans = temp->info;
            }
            temp = temp->right;
        }
    }
    return ans;
}
