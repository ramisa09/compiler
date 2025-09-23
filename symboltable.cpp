  #include<iostream>
  #include<string>
  #include<vector>
  #include<sstream>
  #include<regex>
  using namespace std;
  struct Symbol {string name, idType, dataType, scope, value; };
  vector<Symbol>symbolTable;

  void insert(string name, string idType, string dataType, string scope, string value){
  for(auto &sym:symbolTable)
    if(sym.name == name)
  {
      cout<< "Error identifiers ' " << name <<" 'exists." << endl;
      return;
  }
  symbolTable.push_back({name, idType, dataType, scope, value});
  cout<< "Inserted" << name << endl;
      }

 void update(string name, string value){
 for(auto &sym:symbolTable)
    if(sym.name == name){
        sym.value = value;
        cout<< "Updated" << name << "to" << value << endl;
        return;
    }
    cout<< "Not found" << endl;
 }

 void deleteSymbol(string name) {
    for (size_t i = 0; i < symbolTable.size(); ++i)
        if (symbolTable[i].name == name)
        {
            symbolTable.erase(symbolTable.begin() + i);
            cout << "Deleted: " << name << endl;
            return;
        }
    cout << "Identifier not found." << endl;
}

void search(string name){
for(auto &sym:symbolTable)
    if(sym.name == name)
    {
       cout<< "Found: " << name << "[Type: " <<sym.idType
       << ", Datatype: " << sym.dataType << ", Scope: "
       << sym.scope << ", Value: " << sym.value << "]" << endl;
       return;
    }
    cout<< "Not found" << endl;
}

void display(){
cout << "Symbol Table: \nName\tidType\tdatatype\tScope\tValue\n" << endl;
for(auto &sym:symbolTable)
      cout<< sym.name << "\t" << sym.idType
      << "\t" << sym.dataType << "\t"
      <<sym.scope << "\t" << sym.value << endl;

}
void parseCode(string code) {
    istringstream codeStream(code);
    string line, scope = "global";
    regex identifierPattern("(int|float|double|char|void)\\s+([a-zA-Z_][a-zA-Z0-9_]*)(\\s*=\\s*([^;]+))?");

    while (getline(codeStream, line)) {
        smatch match;
        if (regex_search(line, match, identifierPattern)) {
            string dataType = match[1], name = match[2];
            string value = match[4].matched ? match[4].str() : "";
            if (line.find('(') != string::npos && line.find(')') != string::npos) {
                insert(name, "func", dataType, scope, ""); scope = name;
            } else insert(name, "var", dataType, scope, value);
        }
        if (line.find('}') != string::npos) scope = "global";
    }
}

int main()
{
    int choice;
    do{
        cout<< "\nSymbol Table Options.\n1. Insert Manually.\n2. Update.\n3. Delete.\n4. Search.\n5. Display.\n6. Input code.\n7. Exit.\nEnter your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                   string name, idType, dataType, scope, value;
                   cout << "Enter your name: ";  cin>> name;
                   cout << "Enter id type: ";  cin>> idType;
                   cout<< "Enter data type: "; cin>> dataType;
                   cout<< "Enter scope: "; cin>> scope;
                   cout<< "Enter value: "; cin.ignore();
                   getline(cin, value);
                   insert(name, idType, dataType, scope, value);
                   break;
                   }

            case 2: {
                   string name, value;
                   cout<< "Enter name to update: "; cin>> name;
                   cout<< "Enter new value: "; cin>> value;
                   update(name, value);
                   break;
                   }

            case 3: {
                   string name;
                   cout<< "Enter name to delete: "; cin>> name;
                   deleteSymbol(name);
                   break;
                   }

            case 4: {
                   string name;
                   cout<< "Enter name to search: "; cin>> name;
                   search(name);
                   break;
                   }

            case 5: display();
                   break;

            case 6: {
                    string code;
                    cout<< "Enter code (type '.' to end): \n";
                    cin.ignore();
                    string line;
                    while(getline(cin, line) && line!= ".")
                        code += line + "\n";
                    parseCode(code);
                    break;
                    }

            case 7: cout<< "Exiting." << endl;
                    break;
            default: cout<< "Invalid choices. Please try again." << endl;
    }
}

while(choice != 7);
    return 0;
}
