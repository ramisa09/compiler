#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

bool checkDivideByZero(const string& line) {
    regex divideRegex(R"((\/)\s*0)");
    return regex_search(line, divideRegex);
}

bool checkUnreachableCode(const vector<string>& lines, int lineIndex) {
    if (lines[lineIndex].find("return") != string::npos) {
        if (lineIndex + 1 < lines.size() && !lines[lineIndex + 1].empty()) {
            return true;
        }
    }
    return false;
}

bool checkInfiniteLoop(const string& line) {
    regex forLoopRegex(R"(for\s*\([^;]*;[^;]*;[^)]*\))");
    regex whileLoopRegex(R"(while\s*\([^;]+\))");

    if (regex_search(line, forLoopRegex) || regex_search(line, whileLoopRegex)) {
        if (line.find("break") == string::npos && line.find("return") == string::npos) {
            return true;
        }
    }
    return false;
}

bool checkForMisuseOfLogicalOperators(const string& line) {
    regex misuseRegex(R"(\bif\s*\(.*(\&\&|\&|\|\|)\s*.*\))");
    return regex_search(line, misuseRegex);
}

int main() {
    vector<string> lines;
    string line;

    cout << "Enter C++ code (type 'END' to finish):\n";

    while (getline(cin, line)) {
        if (line == "END") break;
        lines.push_back(line);
    }

    bool hasLogicalError = false;

    for (size_t i = 0; i < lines.size(); ++i) {
        if (checkDivideByZero(lines[i])) {
            cout << "Logical Error: Divide by zero detected on line " << (i + 1) << ".\n";
            hasLogicalError = true;
        }

        if (checkUnreachableCode(lines, i)) {
            cout << "Logical Error: Unreachable code detected on line " << (i + 2) << ".\n"; // Adjusted for next line
            hasLogicalError = true;
        }

        if (checkInfiniteLoop(lines[i])) {
            cout << "Logical Error: Potential infinite loop on line " << (i + 1) << ".\n";
            hasLogicalError = true;
        }

        if (checkForMisuseOfLogicalOperators(lines[i])) {
            cout << "Logical Error: Possible misuse of logical operators on line " << (i + 1) << ".\n";
            hasLogicalError = true;
        }
    }

    if (!hasLogicalError) cout << "No logical errors detected in the code.\n";

    return 0;
}
