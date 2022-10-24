#include <iostream>

/********Сортировка бинарным деревом - tree_sort*******/
struct Node {
    int key;
    Node* left, * right;
};

// A utility function to create a new BST Node
Node* new_node(int item) {
    struct Node* temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Stores inorder traversal of the BST in arr[]
void store_sorted(Node* root, int arr[], int& i) {
    if (root != NULL) {
        store_sorted(root->left, arr, i);
        arr[i++] = root->key;
        store_sorted(root->right, arr, i);
    }
}

/* A utility function to insert a new
   Node with given key in BST */
Node* insert_node(Node* node, int key) {
    /* If the tree is empty, return a new Node */
    if (node == NULL) return new_node(key);

    /* Otherwise, recur down the tree */
    if (key <= node->key)
        node->left = insert_node(node->left, key);
    else if (key >= node->key)
        node->right = insert_node(node->right, key);

    /* return the (unchanged) Node pointer */
    return node;
}

// This function sorts arr[0..n-1] using Tree Sort
void tree_sort(int arr[], int n) {
    struct Node* root = NULL;
    // Construct the BST
    root = insert_node(root, arr[0]);
    for (int i = 1; i < n; i++)
        root = insert_node(root, arr[i]);

    int i = 0;
    store_sorted(root, arr, i);
}
/*******************************************************/

void sort_test(int size_array) {
	setlocale(LC_ALL, "Russian");
	if (size_array < 1) { std::cout << "AAA";  return; }
	clock_t time = clock();
	int size = size_array;
	int* my_array = new int[size];
    std::cout << "Идёт заполнение массива: ";
	for (int i = 0; i < size; ++i) {
		my_array[i] = rand() % 1'000'000;
    }
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	std::cout << "Идёт сортировка массива на " << size << " элементов: ";
    tree_sort(my_array, size);
    time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
    /*
    for (int i = 0; i < size_array; ++i) {
        std::cout << my_array[i] << " ";
    }
    */
    delete[] my_array;
}

int main() {
    sort_test(100'000);
	return 0;
}