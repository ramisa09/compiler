#include<iostream>
#include<string>
#include<cctype>

using namespace std;

string keyword[]
{
    "int","float","double","char","if","else","switch","break","return","void","static","struct",
    "for","while","do","case"
};

bool is_keyword(const string & s)
{
    for (auto &k:keyword)
        if(s==k)
        return true;
    return false;
}

int main()
{
    cout<< "Enter C program (Crlt+z to end) :\n";
    string line;
    int total_lines=0;

    char c;
    while(cin.get(c))
    {
        if(c=='\n')
        {
            total_lines++;
            continue;
        }
        if(isalpha(c)||c=='_')
        {
            string token;
            token+=c;
            while(cin.peek()&&(isalnum(cin.peek())|| cin.peek()=='_'))
            {
                cin.get(c);
                token+=c;
            }
            if(is_keyword(token))
                cout<< token<<"  -> keyword"<<endl;
            else
                cout<<token<< "  -> identifier"<<endl;
            continue;
        }
        if(isdigit(c)||(c=='.'&& isdigit(cin.peek())))
        {
            string token;
            token=token+c;
            while (cin.peek() && (isdigit(cin.peek())|| cin.peek()=='.'))
                   {
                       cin.get(c);
                       token=token+c;
                   }
                   cout<< token<< "  ->constant"<<endl;
                   continue;
        }
        if(!isspace(c))
            cout<<c<< "   -> special character"<<endl;

    }
    cout<< "Total lines:"<<total_lines<<endl;
    return 0;
}
