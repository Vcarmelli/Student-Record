// Student Record Program by Vashti Karmelli V. Camu
// Link list in C++

#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;

//REC node using self-referential structure
typedef struct student {
    string name;
    int q1, q2, q3;
    struct student *next;
} REC;

class MyClass {
private:
    REC *head;
    bool isEmpty();
    float average(int Q1, int Q2, int Q3);
public:
    void init();
    void addRec(string nm, int Q1, int Q2, int Q3);
    void delRec(string nm);
    void display();
    void retrieve();
    void save();
};

void gotoxy(int x,int y)
{
    COORD coord = {0,0};
    coord.X=x; coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//private methods in MyClass
bool MyClass::isEmpty(){
    return (head==NULL);
}

float MyClass::average(int Q1, int Q2, int Q3){
    return ((Q1+Q2+Q3)/3.0);
}

//public methods in MyClass
void MyClass::init(){
    head = NULL;
}

void MyClass::addRec(string nm, int Q1, int Q2, int Q3){
    REC  *pre, *cur, *newNode;
    cur=pre=head;
    newNode = new REC;
    newNode->name = nm;
    newNode->q1 = Q1;
    newNode->q2 = Q2;
    newNode->q3 = Q3;
    newNode->next = NULL;

    while (cur!=NULL && cur->name<nm){
        pre = cur;
        cur = cur->next;
    }
    if (head==cur){
        head = newNode; 
    } else {
        pre->next = newNode;
        newNode->next = cur;
    }
}

void MyClass::delRec(string nm){
    REC *pre, *cur;
    cur=pre=head;
    if (isEmpty()){
        gotoxy(40, 10); cout << "The list is empty.";
        gotoxy(40, 12); system("pause");
    } else {
        while (cur!=NULL && cur->name!=nm){
            pre = cur;
            cur = cur->next;
        }
        if (cur==NULL){
            gotoxy(40, 10); cout << "Name not found.";
            gotoxy(40, 12); system("pause");
        } else {
            if (head==cur)
                head = cur->next;
            else
                pre->next = cur->next;
            free(cur);
        }
    }
}

void MyClass::display(){
    REC *cur;
    int i = 1;
    float ave;
    cur = head;
    system("cls");
    gotoxy(28, 6); cout << "=========================== RECORD TABLE ===========================";
    gotoxy(30, 8); cout << "Name";
    gotoxy(50, 8); cout << "Quiz #1";
    gotoxy(60, 8); cout << "Quiz #2";
    gotoxy(70, 8); cout << "Quiz #3";
    gotoxy(80, 8); cout << "Average";
    gotoxy(90, 8); cout << "Remarks";
    while (cur!=NULL){
        ave = average(cur->q1, cur->q2, cur->q3);
        gotoxy(25, 9+i); cout << i << ".)";
        gotoxy(30, 9+i); cout << cur->name;
        gotoxy(52, 9+i); cout << cur->q1;
        gotoxy(62, 9+i); cout << cur->q2;
        gotoxy(72, 9+i); cout << cur->q3;
        gotoxy(82, 9+i); cout << fixed << setw(6) << setprecision(2) << ave << "  ";
        if (ave>=75)
            cout << "PASSED";
        else
            cout << "FAILED";
        cur = cur->next; i++;
    }
    gotoxy(25, 10+i); system("pause");
}

void MyClass::retrieve(){
    fstream fp;
    fp.open("records.vkvc", ios::in);
    if (!fp){
        gotoxy(40, 10); cout << "File not found.";
        gotoxy(40, 12); system("pause");
    } else {
        string nm;
        int q1, q2, q3;
        while(true){
            getline(fp, nm);
            fp >> q1;
            fp >> q2;
            fp >> q3;
            fp.ignore();
            if (!fp.eof())
                addRec(nm, q1, q2, q3);
            else
                break;
        }
    }
    fp.close();
}

void MyClass::save(){
    fstream fp;
    REC *x;
    x= head;
    fp.open("records.vkvc", ios::out);
    if (!fp){
        gotoxy(40, 10); cout << "File Error.";
        gotoxy(40, 12); system("pause");
    } else {
        while (x!=NULL){
            fp << x->name << endl << x->q1 << endl << x->q2 << endl << x->q3 << endl;
            x = x->next;
        }
        fp.close();
        gotoxy(40, 15); cout << "File successfully saved as records.vkvc" << endl;
    }
}

//function
int menu(){
    int op;
    system("cls");
    gotoxy(30, 5); cout << "==================================================================";
    gotoxy(30, 6); cout << "|                     STUDENT RECORD - MENU                      |";
    gotoxy(30, 7); cout << "==================================================================";
    gotoxy(30, 8); cout << "|        Press 1: Add a student record                           |";
    gotoxy(30, 9); cout << "|        Press 2: Delete a student record                        |";
    gotoxy(30, 10); cout << "|        Press 3: Display the table of student records           |";
    gotoxy(30, 11); cout << "|        Press 4: Exit                                           |";
    gotoxy(30, 12); cout << "==================================================================";
    gotoxy(40, 13); cout << "Enter your choice: ";
    scanf("%d", &op);
    return op;
}

int main()
{
    system("COLOR 0B");
    string nm;
    int q1, q2, q3;
    MyClass stud;
    stud.init();
    stud.retrieve();
    while(true){
        switch(menu()){
            case 1: system("cls"); gotoxy(35, 5); cout << "=================== ADD A STUDENT RECORD ===================";
                                   gotoxy(40, 7); cout << "Input Name: "; cin.ignore(); getline(cin, nm);
                                   gotoxy(43, 8); cout << "Input score in Quiz #1: "; cin >> q1;
                                   gotoxy(43, 9); cout << "Input score in Quiz #2: "; cin >> q2;
                                   gotoxy(43, 10); cout << "Input score in Quiz #3: "; cin >> q3;
                                   stud.addRec(nm, q1, q2, q3); break;
            case 2: system("cls"); gotoxy(35, 5); cout << "================= DELETE A STUDENT RECORD =================";
                                   gotoxy(40, 7); cout << "Input Name: "; cin.ignore(); getline(cin, nm);
                                   stud.delRec(nm); break;
            case 3: stud.display(); break;
            case 4: stud.save(); exit(0);
            default: gotoxy(45, 15); cout << "\n\t\tEnter 1 to 4 only." << endl; system("pause");
        }
    }
    return 0;
}
