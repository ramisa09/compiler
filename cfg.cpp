#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>

using namespace std;

int main() {
    string line;
    vector<string> productions;
    set<string> nonTerminals;
    set<string> terminals;

    cout << "Enter CFG production rules (type 'END' to finish):\n";

    while (getline(cin, line)) {
        if (line == "END") break;
        productions.push_back(line);
    }

    for (const auto& production : productions) {
        istringstream iss(production);
        string lhs, arrow, rhs;

        iss >> lhs >> arrow;

        if (arrow != "->") {
            cout << "Invalid production rule format: " << production << endl;
            continue;
        }

        nonTerminals.insert(lhs);

        while (iss >> rhs) {
            if (rhs == "|") continue;

            if (rhs[0] == '<' && rhs.back() == '>') {
                nonTerminals.insert(rhs);
            } else {
                for (char c : rhs) {
                    if (islower(c) || isdigit(c)) {
                        terminals.insert(string(1, c));
                    }
                }
            }
        }
    }

    cout << "\nNon-terminal symbols:\n";
    for (const auto& nt : nonTerminals) {
        cout << nt << endl;
    }

    cout << "\nTerminal symbols:\n";
    for (const auto& t : terminals) {
        cout << t << endl;
    }

    return 0;
}
