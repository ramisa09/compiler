#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

map<string, vector<vector<string>>> grammar;
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;

bool isTerminal(const string& symbol) {
    return !(symbol[0] >= 'A' && symbol[0] <= 'Z');  // Terminals are not uppercase
}

void calculateFirst() {
    bool changed;
    do {
        changed = false;
        for (auto& rule : grammar) {
            string nonTerminal = rule.first;
            for (auto& production : rule.second) {
                for (const string& symbol : production) {
                    if (isTerminal(symbol)) {
                        if (FIRST[nonTerminal].insert(symbol).second) {
                            changed = true;
                        }
                        break;
                    } else {
                        bool hasEpsilon = false;
                        for (const string& firstSymbol : FIRST[symbol]) {
                            if (firstSymbol != "epsilon") {
                                if (FIRST[nonTerminal].insert(firstSymbol).second) {
                                    changed = true;
                                }
                            } else {
                                hasEpsilon = true;
                            }
                        }
                        if (!hasEpsilon) break;
                    }
                }
            }
        }
    } while (changed);
}

void calculateFollow() {
    FOLLOW["E"].insert("$");  // Start symbol's FOLLOW includes end of input symbol

    bool changed;
    do {
        changed = false;
        for (auto& rule : grammar) {
            string nonTerminal = rule.first;
            for (auto& production : rule.second) {
                for (size_t i = 0; i < production.size(); ++i) {
                    if (!isTerminal(production[i])) {
                        bool hasEpsilon = true;
                        for (size_t j = i + 1; j < production.size() && hasEpsilon; ++j) {
                            hasEpsilon = false;
                            for (const string& firstSymbol : FIRST[production[j]]) {
                                if (firstSymbol != "epsilon") {
                                    if (FOLLOW[production[i]].insert(firstSymbol).second) {
                                        changed = true;
                                    }
                                } else {
                                    hasEpsilon = true;
                                }
                            }
                        }
                        if (hasEpsilon || i == production.size() - 1) {
                            for (const string& followSymbol : FOLLOW[nonTerminal]) {
                                if (FOLLOW[production[i]].insert(followSymbol).second) {
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (changed);
}

void printSet(const map<string, set<string>>& sets, const string& setName) {
    cout << "The " << setName << " set is:\n";
    for (const auto& entry : sets) {
        cout << setName << "(" << entry.first << ") = {";
        bool first = true;
        for (const string& symbol : entry.second) {
            if (!first) cout << ", ";
            cout << symbol;
            first = false;
        }
        cout << "}\n";
    }
    cout << endl;
}

int main() {
    int numRules;
    cout << "Enter the number of production rules: ";
    cin >> numRules;
    cin.ignore();  // Ignore newline after the integer input

    cout << "Enter the production rules in the format 'NonTerminal -> production1 | production2 | ...':\n";
    for (int i = 0; i < numRules; ++i) {
        string line;
        getline(cin, line);

        // Parse non-terminal and productions
        stringstream ss(line);
        string nonTerminal, arrow;
        ss >> nonTerminal >> arrow;  // Get non-terminal and '->'

        vector<vector<string>> productions;
        string production;
        while (getline(ss, production, '|')) {
            vector<string> productionSymbols;
            stringstream prodStream(production);
            string symbol;
            while (prodStream >> symbol) {
                productionSymbols.push_back(symbol);
            }
            productions.push_back(productionSymbols);
        }
        grammar[nonTerminal] = productions;
    }

    calculateFirst();
    calculateFollow();

    printSet(FIRST, "FIRST");
    printSet(FOLLOW, "FOLLOW");

    return 0;
}

/*
E → TE'
E' → +TE' | epsilon
T → FT'
T' → *FT' | epsilon
F → (E) | id
*/
