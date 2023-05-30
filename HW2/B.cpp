#ifndef HW2_TRIE_H
#define HW2_TRIE_H

#include <iostream>
#include <vector>

const int R = 26;

struct Node {
    Node() {
        endOfWord = false;
        for (int i = 0; i < R; i++) {
            children[i] = nullptr;
        }
    }

    bool endOfWord;
    Node *children[R];
    Node *parent;
};

struct Trie {
    Trie() {
        root = new Node();
    };
    Node *root;

    void insert(std::string str) {
        Node *cur = root;
        for (int i = 0; i < str.size(); i++) {
            if (!cur->children[str[i] - 'a']) {
                cur->children[str[i] - 'a'] = new Node();
            }
            Node *temp = cur;
            cur = cur->children[str[i] - 'a'];
            cur->parent = temp;
        }
        cur->endOfWord = true;
    }

    void print(Node *cur, std::string s) {
        if (cur->endOfWord) {
            std::cout << s << std::endl;
        }
        for (int i = 0; i < R; i++) {
            if (cur->children[i]) {
                char ch = i + 'a';
                print(cur->children[i], s + ch);
            }
        }

    }

    void dig(Node *cur, const std::string &str, std::string &empty, int index) {
        if (empty == str) {
            return;
        }
        for (int i = 0; i < R; i++) {
            char ch = i + 'a';
            if (str[index] == ch) {
                empty += ch;
                dig(cur->children[i], str, empty, ++index);
                return;
            }
        }
    }

    bool find(std::string pattern) {
        Node *cur = root;
        std::string empty;
        dig(cur, pattern, empty, 0);
        if (empty == pattern) {
            return true;
        }
        else {
            return false;
        }
    }

    void insertV(Node *cur, std::string s, std::vector <std::string> &v, std::string prefix) {
        if (cur && cur->endOfWord) {
            v.push_back(prefix + s);
        }
        for (int i = 0; i < R; i++) {
            if (cur && cur->children[i]) {
                char ch = i + 'a';
                insertV(cur->children[i], s + ch, v, prefix);
            }
        }
    }

    void dig2(Node *cur, const std::string &str, std::string &empty, int index, Node *&answer) {
        for (int i = 0; i < R; i++) {
            char ch = i + 'a';
            if (str[index] == ch) {
                empty += ch;
                if (cur->children[i]) {
                    dig2(cur->children[i], str, empty, ++index, answer);
                }
            }
            if (empty == str) {
                if (!answer) {
                    answer = cur;
                }
                return;
            }
        }
    }

    Node *find2(std::string pattern) {
        Node *cur = root;
        std::string empty;
        Node *answer = nullptr;
        dig2(cur, pattern, empty, 0, answer);
        if (answer != root) {
            return answer;
        }
        else {
            return nullptr;
        }
    }

    std::vector <std::string> startsWith(std::string prefix) {
        std::vector <std::string> ansV;
        Node *cur = find2(prefix);
        insertV(cur, "", ansV, prefix);
        return ansV;
    }

    std::vector <std::string> matches(std::string str) {
        int i = 0;
        std::vector <std::string> ansV;
        insertV2(root, "", ansV, str, i);
        return ansV;
    }

    void insertV2(Node *cur, std::string s, std::vector <std::string> &v, std::string prefix, int k) {
        if (k == prefix.length() && cur->endOfWord) {
            v.push_back(s);
        }
        if (prefix[k] == '.') {
            for (int i = 0; i < R; i++) {
                if (cur->children[i]) {
                    char ch = i + 'a';
                    insertV2(cur->children[i], s + ch, v, prefix, k + 1);
                    int a = 42;
                }
            }
        }
        else {
            for (int i = 0; i < R; i++) {
                if (i + 'a' == prefix[k] && cur->children[i]) {
                    char ch = i + 'a';
                    insertV2(cur->children[i], s + ch, v, prefix, k + 1);
                }
            }
        }
    }

    ~Trie() {
        _erase(root);
    }

    void _erase(Node *cur) {
        for (int i = 0; i < R; i++) {
            if (cur->children[i]) {
                _erase(cur->children[i]);
            }
        }
        delete cur;
    };
};

#endif //HW2_TRIE_H

std::string takeInputLine() {
    std::string inpLine;
    getline(std::cin, inpLine);
    return inpLine;
}

Trie deserialize(std::string &l1) {
    Trie t;
    Node *cur = t.root;
    for (char a: l1) {
        if (a == '$') {
            cur->endOfWord = true;
        }
        else if (a == '#') {
            cur = cur->parent;
        }
        else {
            if (!cur->children[a - 'a']) {
                cur->children[a - 'a'] = new Node();
            }
            Node *temp = cur;
            cur = cur->children[a - 'a'];
            cur->parent = temp;
        }
    }
    return t;
}

int main() {
    std::string serializedStr = takeInputLine();
    std::string prefix = takeInputLine();
    Trie ansT = deserialize(serializedStr);
    std::vector <std::string> answer = ansT.startsWith(prefix);
    for (std::string s: answer) {
        std::cout << s << std::endl;
    }
    if (answer.size() == 0) {
        std::cout << -1;
    }

    return 0;
}

