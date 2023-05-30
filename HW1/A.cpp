#include <iostream>

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

void List::print() {
    Node *cur = head;
    for (Node *cur = head; cur != nullptr; cur = cur->next) {
        std::cout << cur->val << ' ';
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

#include <sstream>
#include <vector>

std::vector<int> takeInput() //There was a substring method which was sent to fludilka, it is better;
{
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

void inPlacePartitionList(List &l) {
    Node *tail = findTail(l);
    Node *cur = l.head;
    Node *tailCopy = tail;
    while (cur->val == 0 && cur != tailCopy) {
        Node *curCopy = cur->next;
        tail->next = cur;
        tail->next->next = nullptr;
        tail = tail->next;
        l.head = curCopy;
        cur = curCopy;
    }
    while (cur->next && cur != tailCopy) {
        if (cur->next->val == 0) {
            tail->next = cur->next;
            tail = tail->next;
            cur->next = cur->next->next;
            tail->next = nullptr;
        }
        cur = cur->next;
    }
}

void print2(List &l) {
    Node *cur = l.head;
    while (cur->next) {
        std::cout << cur->val << "--->";
        cur = cur->next;
    }
    std::cout << cur->val;
}

int main() {
    std::vector<int> inputV = takeInput();
    //Create list;
    List l;
    for (int i: inputV) {
        l.push_back(i);
    }
    //Partition
    inPlacePartitionList(l);
    print2(l);
    return 0;
}
