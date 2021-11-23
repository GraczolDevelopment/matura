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
    std::vector<char> bufferedChars;

public:
    void invokeMethod(Method method, std::string &text) {
        switch (method) {
            case REPLACE: bufferedChars.pop_back();
            case APPEND: bufferedChars.push_back(text[0]); break;
            case DELETE: bufferedChars.pop_back(); break;
            case MOVE:
                char key = text[0];

                for (auto &item : bufferedChars) {
                    if (item != key) {
                        continue;
                    }

                    item = getMovedChar(item);
                    return;
                }

                break;
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
