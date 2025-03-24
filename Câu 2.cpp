#include <iostream>
#include <string.h> // Thay vì <string> để sử dụng strcmp

using namespace std;

struct SinhVien {
    char hoTen[51];
    char diaChi[71];
    char lop[11];
    int khoa;
};

struct Node {
    SinhVien data;
    Node* next;
};

struct ListSV {
    Node* head;
};

// Hàm so sánh sinh viên
int soSanhTheoHoTen(const SinhVien& sv1, const SinhVien& sv2) {
    return strcmp(sv1.hoTen, sv2.hoTen);
}

int soSanhTheoDiaChi(const SinhVien& sv1, const SinhVien& sv2) {
    return strcmp(sv1.diaChi, sv2.diaChi);
}

int soSanhTheoLop(const SinhVien& sv1, const SinhVien& sv2) {
    return strcmp(sv1.lop, sv2.lop);
}

int soSanhTheoKhoa(const SinhVien& sv1, const SinhVien& sv2) {
    return sv1.khoa - sv2.khoa;
}

// Hàm nhập và xuất sinh viên
void nhapSinhVien(SinhVien& sv) {
    cout << "Nhap ho ten: ";
    cin.ignore();
    cin.getline(sv.hoTen, 51);
    cout << "Nhap dia chi: ";
    cin.getline(sv.diaChi, 71);
    cout << "Nhap lop: ";
    cin.getline(sv.lop, 11);
    cout << "Nhap khoa: ";
    cin >> sv.khoa;
}

void xuatSinhVien(const SinhVien& sv) {
    cout << "Ho ten: " << sv.hoTen << endl;
    cout << "Dia chi: " << sv.diaChi << endl;
    cout << "Lop: " << sv.lop << endl;
    cout << "Khoa: " << sv.khoa << endl;
}

// Các phép toán trên ListSV
void init(ListSV& list) {
    list.head = nullptr;
}

void destroy(ListSV& list) {
    Node* current = list.head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    list.head = nullptr;
}

void add(ListSV& list, const SinhVien& sv) {
    Node* newNode = new Node;
    newNode->data = sv;
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

void remove(ListSV& list, const SinhVien& sv, int (*compare)(const SinhVien&, const SinhVien&)) {
    if (list.head == nullptr) return;

    if (compare(list.head->data, sv) == 0) {
        Node* temp = list.head;
        list.head = list.head->next;
        delete temp;
        return;
    }

    Node* current = list.head;
    while (current->next != nullptr) {
        if (compare(current->next->data, sv) == 0) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}

void addList(ListSV& list, SinhVien arr[], int size) {
    for (int i = 0; i < size; ++i) {
        add(list, arr[i]);
    }
}

void printList(const ListSV& list) {
    Node* current = list.head;
    while (current != nullptr) {
        xuatSinhVien(current->data);
        cout << "------------------------" << endl;
        current = current->next;
    }
}

void selectionSort(ListSV& list, int (*compare)(const SinhVien&, const SinhVien&)) {
    Node* current = list.head;
    while (current != nullptr) {
        Node* min = current;
        Node* temp = current->next;
        while (temp != nullptr) {
            if (compare(temp->data, min->data) < 0) {
                min = temp;
            }
            temp = temp->next;
        }
        swap(current->data, min->data);
        current = current->next;
    }
}

int main() {
    ListSV list;
    init(list);

    // Nhập 10 sinh viên
    cout << "Nhap 10 sinh vien:" << endl;
    for (int i = 0; i < 10; ++i) {
        SinhVien sv;
        nhapSinhVien(sv);
        add(list, sv);
        cout << "------------------------" << endl;
    }

    // In danh sách
    cout << "Danh sach sinh vien:" << endl;
    printList(list);

    // Xóa sinh viên theo tên
    SinhVien svXoaTheoTen = {"Nguyen Van Teo", "", "", 0};
    remove(list, svXoaTheoTen, soSanhTheoHoTen);

    // Xóa sinh viên theo địa chỉ
    SinhVien svXoaTheoDiaChi = {"", "Nguyen Van Cu", "", 0};
    remove(list, svXoaTheoDiaChi, soSanhTheoDiaChi);

    // Thêm sinh viên
    SinhVien svThem = {"Tran Thi Mo", "25 Hong Bang", "TT0901", 2009};
    add(list, svThem);

    // In danh sách sau khi xóa và thêm
    cout << "Danh sach sinh vien sau khi xoa va them:" << endl;
    printList(list);

    // Sắp xếp theo lớp và in
    selectionSort(list, soSanhTheoLop);
    cout << "Danh sach sinh vien sau khi sap xep theo lop:" << endl;
    printList(list);

    destroy(list);

    return 0;
}