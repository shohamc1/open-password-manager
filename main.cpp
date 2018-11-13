#include <iostream>
#include <windows.h>
#include <fstream>
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
        char pw[20];
        char website[100];
        char password[100];
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

void createList() {
    HANDLE hConsole = GetStdHandle (STD_INPUT_HANDLE);
    DWORD mode = 0;

    string db_name;
    db db_object;
    string pass, pw, website;

    cout << "Enter name of the list: ";
    cin >> db_name;
    
    cout << "Enter password for list (max 20 characters): ";
    GetConsoleMode (hConsole, &mode);
    SetConsoleMode (hConsole, mode & (~ENABLE_ECHO_INPUT));
    cin >> pw;
    SetConsoleMode (hConsole, mode | (~ENABLE_ECHO_INPUT));
    cout << endl;

    cout << "Enter name of website: ";
    cin >> website;

    pass = generateString();
    strcpy (db_object.pw, pw.c_str());
    strcpy (db_object.website, website.c_str());
    strcpy (db_object.password, pass.c_str());

    ofstream ofile ((db_name+".list").c_str(), ios::binary);
    ofile.write((char*) &db_object, sizeof(db_object));
    ofile.close();

    cout << endl;
}

void readList() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;

    string db_name;
    string passkey, webname;
    db db_object;
    bool check = FALSE;

    cout << "Enter name of list: ";
    cin >> db_name;

    ifstream ifile ((db_name+".list").c_str(), ios::binary);

    if (ifile.fail()) {
        cout << "List doesn't exist!\n";
        return;
    }

    ifile.seekg (0);
    //ifile.read ((char*) &db_object, sizeof (db_object));
    
    cout << "Enter password of the list: ";

    GetConsoleMode (hConsole, &mode);
    SetConsoleMode (hConsole, mode & (~ENABLE_ECHO_INPUT));
    cin >> passkey;
    SetConsoleMode (hConsole, mode | (~ENABLE_ECHO_INPUT));

    cout << "Enter website to search: ";
    cin >> webname;

    while (!ifile.eof()) {
        ifile.read ((char*) &db_object, sizeof (db_object));

        if (db_object.pw == passkey && db_object.website == webname) {
            SetConsoleTextAttribute(hConsole, 11);
            cout << "Password: " << db_object.password << endl << endl;
            SetConsoleTextAttribute(hConsole, 15);
            check = TRUE;
            break;
        }

        else if (db_object.pw != passkey) {
            cout << "Wrong password!\n";
            check = TRUE;
            break;
        }

        
    }

    ifile.close();

    if (check == FALSE) {
        cout << "Website not found!\n";
    }

    // if (db_object.pw == passkey) {
    //     cout << "Website name: " << db_object.website << endl << "Password: " << db_object.password << endl;
    // }

    ifile.close();
}

void addList() {
    string db_name;
    cout << "Enter name of the list: ";
    cin >> db_name;

    db db_object;
    string pass, pw, website;
    
    cout << "Enter password of list (max 20 characters): ";
    cin >> pw;

    cout << "Enter name of website: ";
    cin >> website;

    pass = generateString();
    strcpy (db_object.pw, pw.c_str());
    strcpy (db_object.website, website.c_str());
    strcpy (db_object.password, pass.c_str());


    ofstream ofile ((db_name + ".list").c_str(), ios::binary|ios::app);
    ofile.write ((char*) &db_object, sizeof (db_object));
    ofile.close();
    
}

int main() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 3);
    cout << "OPEN PASSWORD MANAGER\nSHOHAM CHAKRABORTY 2018\nLICENSED UNDER GNU GPL v3.0\n";
    SetConsoleTextAttribute(hConsole, 15);
    
    db dbobject;
    int x;
    string dbname;
    char pw[20];


    for (;;) {
        cout << "----------------------------\n";
        cout << "1. Open file\n2. Create new file\n3. Edit File\n4. Exit\nEnter choice: ";
        cin >> x;

        switch (x) {
            case 1:
                readList();
                break;
            case 2:
                createList();
                break;
            case 3:
                addList();
            case 4:
                SetConsoleTextAttribute(hConsole, 10);
                cout << "Bye bye!" << endl;
                SetConsoleTextAttribute(hConsole, 7);
                return 0;
            default:
                cout << "Wrong option!\n";
                break;
        }
    }

    SetConsoleTextAttribute(hConsole, 7);
}
