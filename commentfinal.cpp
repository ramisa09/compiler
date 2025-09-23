#include<bits/stdc++.h>
#include <string>
using namespace std;

int main() {
    string line;
    int lineNo = 0;

    cout << "Enter lines of code (type END to stop):" << endl;

    while (true) {
        getline(cin, line);
        lineNo++;

        if (line == "END")
            break;  // input শেষ করার জন্য END লিখবে

        // ---- Single line comment ----
        if (line.size() >= 2 && line[0] == '/' && line[1] == '/') {
            cout << "Line " << lineNo << ": Single-line comment found!" << endl;
            cout << "Comment text: " << line.substr(2) << endl;
            cout << "Letters in comment: " << line.substr(2).size() << endl;
        }
        // ---- Multi line comment ----
        else if (line.size() >= 2 && line[0] == '/' && line[1] == '*')
            {
            cout << "Line " << lineNo << ": Multi-line comment start!" << endl;

            int letters = 0;
            string commentText = line.substr(2);

            // যতক্ষণ না '*/' পাওয়া যায় ততক্ষণ পড়বে
            while (line.find("*/") == string::npos) {
                getline(cin, line);
                lineNo++;
                commentText += "\n" + line;
            }

            // comment শেষ হওয়ার জায়গা
            size_t endPos = commentText.find("*/");
            if (endPos != string::npos) {
                commentText = commentText.substr(0, endPos);
            }

            // letter গোনা
            for (char c : commentText) {
                if (isalpha(c))
                letters++;
            }

            cout << "Multi-line comment text:\n" << commentText << endl;
            cout << "Letters in comment: " << letters << endl;
        }
        else {
            cout << "Line " << lineNo << ": Not a comment." << endl;
        }
    }

    return 0;
}
