#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

enum Method { APPEND, DELETE, REPLACE, MOVE };
std::map<Method, std::string> enumMap = {
        {Method::APPEND, "DOPISZ"},
        {Method::DELETE, "USUN"},
        {Method::REPLACE, "ZMIEN"},
        {Method::MOVE, "PRZESUN"}
};
std::map<std::string, Method> stringToEnum = {
        {"DOPISZ", Method::APPEND},
        {"USUN", Method::DELETE},
        {"ZMIEN", Method::REPLACE},
        {"PRZESUN", Method::MOVE}
};


void loadFile(std::string name);
std::pair<std::string, std::string> parseToPair(std::string &line);

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
    loadFile("przyklad.txt");
    return 0;
}

void loadFile(std::string name) {
    std::ifstream input(name);
    std::string line;
    StringBuffer buffer;

    if(input.good()) {
        while(std::getline(input, line)) {
            auto pair = parseToPair(line);
            Method method = stringToEnum[pair.first];

        }
    }
}

std::pair<std::string, std::string> parseToPair(std::string &line) {
    std::stringstream ssin(line);
    std::string arr[2];
    for(auto & i : arr) {
        if(ssin.good()) {
            ssin >> i;
        }
    }
    return std::make_pair(arr[0], arr[1]);
}
