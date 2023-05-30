#include <iostream>
#include <sstream>
#include <vector>

//It'd be kinda cool if I made it inplace -> maybe in the future
//Same goes for the substr method to take
//Also make sure there are no memory leaks -> probably sorted
struct Node {
    int val;

    Node *next;

    Node() {}

    Node(int x) : val(x), next(nullptr) {}
};

struct List {
    List() : head(nullptr) {}

    ~List();

    void push_back(int val);

    void print();

    int get(int pos);

    void insert(int val, int pos);

    void erase(int pos);

    Node *head;
};

void List::push_back(int val) {
    Node *newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node *cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
}

List::~List() {
    Node *cur = head;
    while (cur) {
        Node *temp = cur->next;
        delete cur;
        cur = temp;
    }
}

std::vector<int> takeInput() {
    std::stringstream ss;
    std::string line;
    getline(std::cin, line);
    ss << line;
    std::vector<int> kaif;

    while (getline(ss, line, '>')) {
        int cycles = line.size() - 3;
        if (line[line.size() - 1] != '-') {
            cycles += 3;
        }
        bool negativeNombre = false;
        std::string strNumber;

        for (int i = 0; i < cycles; i++) {
            if (line[i] == '-') {
                negativeNombre = true;
            }
            else {
                strNumber += line[i];
            }
        }
        int nombre;
        if (strNumber.size() > 1) {
            nombre = std::stoi(strNumber);
        }
        else {
            nombre = strNumber[0] - '0';
        }
        if (negativeNombre) {
            nombre = nombre * (-1);
        }
        kaif.push_back(nombre);
    }
    return kaif;
}

Node *findTail(List &l) {
    Node *cur = l.head;
    while (cur->next) {
        cur = cur->next;
    }
    return cur;
}

void print2(List &l) {
    Node *cur = l.head;
    while (cur->next) {
        std::cout << cur->val << "--->";
        cur = cur->next;
    }
    std::cout << cur->val;
}

void mergeTwoListsV(List &l1, List &l2, List &l3) {
    Node *cur1 = l1.head;
    Node *cur2 = l2.head;
    if (cur1->val < cur2->val) {
        l3.head = cur1;
        cur1 = cur1->next;
    }
    else {
        l3.head = cur2;
        cur2 = cur2->next;
    }

    Node *cur3 = l3.head;
    while (cur1 || cur2) {
        if (!cur1) {
            cur3->next = cur2;
            cur2 = cur2->next;
            cur3 = cur3->next;
            continue;
        }
        if (!cur2) {
            cur3->next = cur1;
            cur1 = cur1->next;
            cur3 = cur3->next;
            continue;
        }
        if (cur1->val < cur2->val) {
            cur3->next = cur1;
            cur1 = cur1->next;
            cur3 = cur3->next;
        }
        else {
            cur3->next = cur2;
            cur2 = cur2->next;
            cur3 = cur3->next;
        }
    }
    //Otherwise segfaults
    l1.head = nullptr;
    l2.head = nullptr;
}

int main() {
    int iterations;
    std::cin >> iterations;
    std::string dummy;
    std::getline(std::cin, dummy);
    std::vector<int> inputV = takeInput();
    List l1;
    List finalL;
    for (int i: inputV) {
        l1.push_back(i);
    }
    finalL = l1;

    for (int i = 1; i < iterations; i++) {
        std::vector<int> inputV2 = takeInput();
        l1.head = nullptr;
        for (int i: inputV2) {
            l1.push_back(i);
        }
        List l2 = finalL;
        finalL.head = nullptr;
        mergeTwoListsV(l1, l2, finalL);
    }
    print2(finalL);

    return 0;
}
