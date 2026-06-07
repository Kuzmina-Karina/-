#include <iostream>
#include <algorithm> // Для функции max

using namespace std;

// Структура для узла дерева
struct Node {
    int key;        // Само значение (число)
    Node* left;     // Указатель на левого ребенка
    Node* right;    // Указатель на правого ребенка
    int height;     // Высота этого узла
};

// Создание нового узла
Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // Новый узел изначально добавляется как лист, его высота 1
    return node;
}

// Функция для получения высоты узла (безопасна, если узел пустой)
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Функция для вычисления баланс-фактора узла
int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    // Баланс = высота левого минус высота правого
    return getHeight(node->left) - getHeight(node->right);
}

// Правый поворот вокруг узла y
Node* rightRotate(Node* y) {
    // у - узел который перевешивает влево
    Node* x = y->left; // левый ребенок узла у
    Node* T2 = x->right; // правый ребонок узла х и его потомки

    // Совершаем поворот
    x->right = y;
    y->left = T2;

    // Обновляем высоты узлов (сначала y, так как он теперь ниже, потом x)
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Возвращаем новый корень этого поддерева
    return x;
}

// Левый поворот вокруг узла x
Node* leftRotate(Node* x) {
    // х - узел который перевешивает влево
    Node* y = x->right; // правый ребенок узла х
    Node* T2 = y->left; // правый ребонок узла у и его потомки

    // Совершаем поворот
    y->left = x;
    x->right = T2;

    // Обновляем высоты
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Возвращаем новый корень
    return y;
}

// Большой лево-правый поворот (Left-Right Rotation)
Node* leftRightRotate(Node* node) {
    // малый левый поворот для левого ребенка
    node->left = leftRotate(node->left);
    
    // малый правый поворот для самого узла и возвращаем новый корень
    return rightRotate(node);
}

// Большой право-левый поворот (Right-Left Rotation)
Node* rightLeftRotate(Node* node) {
    // малый правый поворот для правого ребенка
    node->right = rightRotate(node->right);
    
    // малый левый поворот для самого узла и возвращаем новый корень
    return leftRotate(node);
}

Node* insert(Node* node, int key) {
    // 1. Обычная вставка
    if (node == nullptr)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else 
        return node; // Равные ключи не добавляем

    // 2. Обновляем высоту
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. Проверяем баланс
    int balance = getBalance(node);

    // 4. Балансировка с использованием наших новых функций

    // Перекос влево-влево (Малый правый поворот)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Перекос вправо-вправо (Малый левый поворот)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Перекос влево-вправо (Большой лево-правый поворот)
    if (balance > 1 && key > node->left->key)
        return leftRightRotate(node); 

    // Перекос вправо-влево (Большой право-левый поворот)
    if (balance < -1 && key < node->right->key)
        return rightLeftRotate(node); 

    return node;
}

// Функция для красивой печати дерева (Pre-order traversal)
void preOrder(Node *root) {
    if(root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}





/*
//Функция для красивой визуализации дерева в консоли
// Параметр space хранит текущий отступ от левого края экрана
void printTree(Node* root, int space = 0) {
    // Базовый случай: если узел пустой, просто выходим
    if (root == nullptr)
        return;

    // Константа для отступа (сколько пробелов добавляем на каждом уровне)
    int COUNT = 5; 
    space += COUNT;

    // 1. Сначала идем в самое правое поддерево (оно будет печататься выше всего)
    printTree(root->right, space);

    // 2. Печатаем сам узел
    cout << endl; // Переходим на новую строку
    for (int i = COUNT; i < space; i++)
        cout << " "; // Печатаем нужные пробелы перед числом
    cout << root->key << "\n"; // Печатаем само число

    // 3. Теперь идем в левое поддерево (оно будет печататься ниже)
    printTree(root->left, space);
}
*/


int main() {
    Node *root = nullptr;

    /* Строим дерево. Если бы это было обычное дерево,
       оно бы превратилось в прямую линию вправо. */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30); // Здесь произойдет левый поворот
    root = insert(root, 40);
    root = insert(root, 50); // И здесь
    root = insert(root, 25);

    /* АВЛ дерево само сбалансируется */
    cout << "Прямой обход сбалансированного АВЛ-дерева: \n";
    preOrder(root); // Вывод: 30 20 10 25 40 50

    //cout << "Визуализация АВЛ-дерева (повернуто на 90 градусов влево):\n";
    //printTree(root); 

    return 0;
}
