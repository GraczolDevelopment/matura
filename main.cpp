#include <iostream>
#include <vector>
#include <map>

enum Method { APPEND, DELETE, REPLACE, MOVE };
std::map<Method, std::string> enumMap = {
        {Method::APPEND, "DOPISZ"},
        {Method::DELETE, "USUN"},
        {Method::REPLACE, "ZMIEN"},
        {Method::MOVE, "PRZESUN"}
};


char getMovedChar(char key) {
    if (key >= 90) {
        return 'A';
    }

    return (char) ((int) key + 1);
}

class StringBuffer {

private:
    int appendRows = 0;
    std::vector<char> bufferedChars;

public:
    void append(std::string &text) {
        bufferedChars.push_back(text[0]);
        appendRows++;
    }

    void replaceLast(std::string &text) {
        this->deleteLast();
        this->append(text);
    }

    void deleteLast() {
        bufferedChars.pop_back();
    }

    void moveChar(std::string &text) {
        char key = text[0];

        for (auto &item : bufferedChars) {
            if (item != key) {
                continue;
            }

            item = getMovedChar(item);
            return;
        }
    }

    std::string toString() {
        std::string text(bufferedChars.begin(), bufferedChars.end());
        return text;
    }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
