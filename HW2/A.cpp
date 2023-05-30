#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

std::string inputLine() {
    std::string s;
    getline(std::cin, s);
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return s;
}

int badCharacterRule(std::vector<int> &v, char a) {
    int shift = v[(int) tolower(a)];
    return shift;
}

std::vector<int> badCharacterPrep(std::string pat) {
    std::vector<int> v(128, 0);

    for (int i = 0; i < pat.size(); i++) {
        v[(int) tolower(pat[i])] = i;
    }
    return v;
}

void countWordsnLines(std::string &text, std::vector<int> tempV) {
    int words = 1;
    int lines = 0;
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ' && text[i + 1] != ' ') {
            ++words;
        }
        else if (text[i] == '\n') {
            ++lines;
            words = 1;
        }
        for (int number: tempV) {
            if (i == number) {
                std::cout << lines << ", " << words << std::endl;
            }
        }
    }
}

void preprocessCase1(std::string &pattern, std::vector<int> &bpos, std::vector<int> &shift) {
    int i = pattern.size();
    int j = pattern.size() + 1;
    bpos[i] = j;
    while (i > 0) {
        while (j <= pattern.size() && pattern[i - 1] != pattern[j - 1]) {
            if (shift[j] == 0) {
                shift[j] = j - i;
            }
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j;
    }
    for (int i: shift) {
        if (i == 0) {
            i = pattern.size();
        }
    }
}

//
int main() {
    std::string pattern = inputLine();
    std::string textline;
    std::string dummy;
    while (getline(std::cin, dummy) && dummy != "") {
        textline += '\n' + dummy;
    }

    std::transform(textline.begin(), textline.end(), textline.begin(),
                   [](unsigned char c) { return std::tolower(c); });


    int pointerText = 0;
    std::vector<int> BCR = badCharacterPrep(pattern);

    ///New stuff
    std::vector<int> bpos(pattern.size() + 1, 0);
    std::vector<int> shifter(pattern.size() + 1, 0);
    preprocessCase1(pattern, bpos, shifter);
    std::vector<int> tempV; //Stores answers

    if (textline.size() < pattern.size()) {
        return 0;
    }
    std::vector<int> newLinesIndex;
    std::string cleanXtraSpaces = "";
    for (int i = 0; i < textline.size(); i++) {
        if (textline[i] == ' ' && textline[i + 1] == ' ') {
            continue;
        }
        if (textline[i] == ' ' && textline[i + 1] == '\n') {
            continue;
        }
        else {
            cleanXtraSpaces += textline[i];
        }
    }
    textline = cleanXtraSpaces;
    for (int i = 0; i < textline.size(); i++) {
        if (textline[i] == '\n') {
            newLinesIndex.push_back(i);
            textline[i] = ' ';
            cleanXtraSpaces += textline[i];
        }
    }

    while (pointerText <= textline.size() - pattern.size()) //nado by eto kak functions perepisat' lol
    {
//        std::string WATCH = textline.substr(pointerText, std::string::npos);
        std::string WATCH2 = textline.substr(pointerText, pattern.size());

        int j = pattern.size();
        while (j > 0) {
            j--;
            char c1 = pattern[j];
            char c2 = textline[pointerText + j];
            if (pattern[j] != textline[pointerText + j]) {
                int BCRshift = (pattern.size() - 1) - badCharacterRule(BCR, textline[pointerText + j]);
                ///New stuff
                int GSRshift = shifter[j + 1];
//                int shift = std::max(GSRshift,1);
                int shift = std::max(GSRshift, std::max(BCRshift, 1));
                pointerText += shift;
                break;
            }
            if (j == 0) {
                tempV.push_back(pointerText);
            }
        }
        if (WATCH2 == pattern) {
            pointerText += 1;
        }
    }

    for (int i: newLinesIndex) {
        textline[i] = '\n';
    }
    countWordsnLines(textline, tempV);
    return 0;
}