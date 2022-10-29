#include <iostream>
#include <unordered_set>

/*************Алгоритм Флойда - поиск зацикленности в односвязном списке**********/
struct Node {
    int data;
    Node* next;
};

void push(Node*& ref_head, int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = ref_head;
    ref_head = newNode;
}

bool detect_cycle(Node* head) {
    Node* slow = head;              // Медленный указатель
    Node* fast = head;              // Быстрый

    while (fast && fast->next) {    // Пока не null
        slow = slow->next;          // Двинуть вперед
        fast = fast->next->next;    // Тоже перейти вперед
        if (slow == fast) {         // Если адреса равны - значит список зациклен
            return true;
        }
    }
    return false;
}
/*********************************************************************************/

/****** Hash_search *****/
int find_duplicate_hash(int* nums, int n) {
    // Create a HashSet
    std::unordered_set<int> set;
    for (int i = 0; i < n; i++) {
        // If the HashSet contains the element, then this is the duplicate
        if (set.find(nums[i]) != set.end())
            return nums[i];
        // Else add the element to the set
        set.insert(nums[i]);
    }
    // Duplicate not found
    return -1;
}


int main() {

    int arrayd[] = { 1, 2, 3, 4, 5 };
    int n = sizeof(arrayd) / sizeof(arrayd[0]);

    Node* head = nullptr;
    for (int i = n - 1; i >= 0; i--) {
        push(head, arrayd[i]);
    }
    // insert cycle
    head->next->next->next->next->next = head->next->next;

    detect_cycle(head) ? std::cout << "Cycle found\n" : std::cout << "No cycle found\n";

    find_duplicate_hash(arrayd, n) != -1 ? std::cout << "Dupl found\n" : std::cout << "No dupl found\n";

    return 0;
}