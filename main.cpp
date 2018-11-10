#include <iostream>
#include <windows.h>
using namespace std;

void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

class db {
    public:
        string password;
        string website;
        string password;
};

void passwordStrength(int len) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (len > 15) {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "Password strong!\n";
    }

    else if (len <= 15 && len > 10) {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "Moderately strong!\n";
    }

    else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Weak password!\n";
    }

    SetConsoleTextAttribute(hConsole, 15);
}

string generateString() {
    int len;
    cout << "Enter length: ";
    cin >> len;

    char x[len];

    gen_random (x, len);

    passwordStrength(len);
    return x;
}

int main() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    
    int x;
    string dbname;

    // string x = generateString();
    // cout << x;

    for (;;) {
        cout << "1. Open file\n2. Create new file\n3. Exit\nEnter choice: ";
        cin >> x;

        switch (x) {
            case 2:
                cout << "Enter name of file: ";
                cin >> dbname;

                ofstream ofile (dbname.c_str())
                
                break;
            default:
                cout << "Wrong option!\n";
                break;
        }
    }
}
