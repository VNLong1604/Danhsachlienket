#include <iostream>

using namespace std; 

struct Node {
    int data;
    Node* next;
};

struct ListInt {
    Node* head;
};

// Khởi tạo danh sách
void init(ListInt& list) {
    list.head = nullptr;
}

// Hủy danh sách, giải phóng bộ nhớ
void destroy(ListInt& list) {
    Node* current = list.head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    list.head = nullptr;
}

// Thêm phần tử vào cuối danh sách
void add(ListInt& list, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (list.head == nullptr) {
        list.head = newNode;
    } else {
        Node* current = list.head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Xóa phần tử có giá trị value
void remove(ListInt& list, int value) {
    if (list.head == nullptr) return;

    if (list.head->data == value) {
        Node* temp = list.head;
        list.head = list.head->next;
        delete temp;
        return;
    }

    Node* current = list.head;
    while (current->next != nullptr) {
        if (current->next->data == value) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}

// Thêm một danh sách các phần tử từ mảng
void addList(ListInt& list, int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        add(list, arr[i]);
    }
}

// Xuất danh sách
void printList(const ListInt& list) {
    Node* current = list.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    ListInt list1, list2;
    init(list1);
    init(list2);

    // Nhập 10 số nguyên vào list1
    cout << "Nhap 10 so nguyen cho list 1: ";
    for (int i = 0; i < 10; ++i) {
        int num;
        cin >> num;
        add(list1, num);
    }

    // In danh sách list1
    cout << "Danh sach 1: ";
    printList(list1);

    // Nhập k và xóa k khỏi list1
    int k;
    cout << "Nhap so k can xoa: ";
    cin >> k;
    remove(list1, k);

    // In danh sách list1 sau khi xóa
    cout << "Danh sach 1 sau khi xoa " << k << ": ";
    printList(list1);

    // Nhập 5 số nguyên vào list2
    cout << "Nhap 5 so nguyen cho list 2: ";
    for (int i = 0; i < 5; ++i) {
        int num;
        cin >> num;
        add(list2, num);
    }

    // Thêm list2 vào list1
    Node* current = list2.head;
    while (current != nullptr) {
        add(list1, current->data);
        current = current->next;
    }

    // In danh sách list1 sau khi thêm list2
    cout << "Danh sach 1 sau khi them danh sach 2: ";
    printList(list1);

    // Giải phóng bộ nhớ
    destroy(list1);
    destroy(list2);

    return 0;
}