#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct ThreeAddressCode {
    string result;
    string op;
    string arg1;
    string arg2;
};

int getPrecedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

vector<ThreeAddressCode> generateThreeAddressCode(const string& expr, string& target) {
    vector<ThreeAddressCode> codes;
    stack<string> operands;
    stack<char> operators;
    int tempCount = 1;

    size_t i = 0;

    // check left side of assignment
    if (isalpha(expr[i]) && expr[i + 1] == '=') {
        target = expr[i];
        i += 2;
    } else {
        cerr << "Invalid expression format." << endl;
        return codes;
    }

    // parse right side
    for (; i < expr.length(); ++i) {
        if (isalnum(expr[i])) {
            operands.push(string(1, expr[i]));
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(expr[i])) {
                string arg2 = operands.top(); operands.pop();
                string arg1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                string result = "T" + to_string(tempCount++);
                codes.push_back({result, string(1, op), arg1, arg2});
                operands.push(result);
            }
            operators.push(expr[i]);
        }
    }

    while (!operators.empty()) {
        string arg2 = operands.top(); operands.pop();
        string arg1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        string result = "T" + to_string(tempCount++);
        codes.push_back({result, string(1, op), arg1, arg2});
        operands.push(result);
    }

    // final assignment to target variable
    string finalResult = operands.top();
    codes.push_back({target, "=", finalResult, ""});

    return codes;
}

int main() {
    string expr;
    cout << "Enter an expression: ";
    cin >> expr;

    string target;
    vector<ThreeAddressCode> threeAddressCodes = generateThreeAddressCode(expr, target);

    if (threeAddressCodes.empty()) return 1;

    cout << "\nThree-Address Code for Expression: " << expr << "\n";
    for (const auto& code : threeAddressCodes) {
        if (code.op == "=")
            cout << code.result << " = " << code.arg1 << "\n";
        else
            cout << code.result << " = " << code.arg1 << " " << code.op << " " << code.arg2 << "\n";
    }

    return 0;
}
