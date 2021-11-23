#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

enum Method { APPEND, DELETE, REPLACE, MOVE, NONE };
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

char getMovedChar(char key) {
    if (key >= 90) {
        return 'A';
    }

    return (char) ((int) key + 1);
}

class StringBuffer {

private:
    std::map<Method, int> stats = {
            {Method::APPEND, 0},
            {Method::DELETE, 0},
            {Method::REPLACE, 0},
            {Method::MOVE, 0}
    };
    std::vector<char> bufferedChars;
    std::pair<Method, int> lastCached = std::make_pair(Method::NONE, 0);

public:
    void invokeMethod(Method method, std::string &text) {
        if (lastCached.first != method) {
            lastCached = std::make_pair(method, 1);
        }
        if (stats[method] < ++lastCached.second) {
            stats[method] = lastCached.second;
        }

        switch (method) {
            default: break;
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

    int getStats(Method method) {
        return stats[method];
    }

    int getTopStat() {
        Method top = NONE;
        int max = 0;

        for (const auto& [key, value] : stats) {
            if (value >= max) {
                top = key;
            }
        }

        return top;
    }

};

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

StringBuffer loadFile(const std::string& name) {
    std::ifstream input(name);
    std::string line;
    StringBuffer buffer;

    if(input.good()) {
        while(std::getline(input, line)) {
            auto [key, value] = parseToPair(line);
            Method method = stringToEnum[key];
            buffer.invokeMethod(method, value);
        }
    }

    return buffer;
}

void printData(StringBuffer buffer) {
    std::cout << buffer.toString() << "\n";
    std::cout << buffer.toString().length() << "\n";
    std::cout << buffer.getStats(Method::APPEND);
}

int main() {
    StringBuffer przykladBuffer = loadFile("przyklad.txt");
    printData(przykladBuffer);

    StringBuffer buffer = loadFile("instrukcje.txt");
    printData(buffer);
    return 0;
}
