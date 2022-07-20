//#include <bits/stdc++.h>
#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<limits>
using namespace std;

#define ll long long
#define typeof(x) __typeof__(x)
#define tr(container, it)\
for (typeof (container.begin()) it = container.begin(); it != container.end(); it++)


class user{
    public:
        string name;
        string ID;
        string password;
        int no;         //1- student, 2-prof, 3-librarian
        friend void display_all_books();
        virtual int increase_book_count(){return 0;}
        virtual void calculate_fine(){return;}
        virtual void clear_fine(){return;}
        virtual void add_user(){return;}
        virtual void update_user(){return;}
        virtual void delete_user(){return;}
        virtual void add_book(){return;}
        virtual void update_book(){return;}
        virtual void delete_book(){return;}
        virtual void check_book_user(){return;}
        virtual void check_issued_books(){return;}
        virtual void pass_days(){return;}
};

class book{
    public:
        string title;
        string author;
        ll ISBN;
        string publication;
        string owner="";
        int duedate=0;
        void Book_Request(user *newown);
        void Show_DueDate(){
            if(owner==""){
                cout << "\nNo one has issued the book currently\n" << endl;
            }
            else{
                cout << "The book is due in " << duedate << "days\n" << endl;
            }
        }
        book(string tit, string auth, ll isbn, string pub){
            title=tit; author=auth; ISBN=isbn; publication=pub;
        }
};

class professor: public user{
    int fine=0;
    
    public:
        professor(string tname, string tID, string pass){
            name=tname; password=pass; ID=tID; no=2;
        }
        void calculate_fine();
        void clear_fine();
};

class student: public user{
    int fine=0;
    int total_books=0;

    public:
        student(string tname, string tID, string pass){
            name=tname; password=pass; ID=tID; no=1;
        }
        int increase_book_count(){
            if(total_books<5){
                total_books++;
                return 1;
            }
            else{
                cout << "\nYou already have the maximum number of books issued.\n" << endl;
                return 0;
            }
        }
        void calculate_fine();
        void clear_fine();
};

class librarian: public user{
    public:
        librarian(string tname, string tID, string pass){
            name=tname; password=pass; ID=tID; no=3;
        }
        void add_user();
        void update_user();
        void delete_user();
        void add_book();
        void update_book();
        void delete_book();
        void check_book_user();
        void check_issued_books();
        void pass_days();
        friend void list_all_users();
};

vector < user* > users;
vector < book > books;

void login();
void mainmenu(user *cur);

void book::Book_Request(user *newown){
    if(owner!=""){
        cout << "\n\tThis book is already issued\n" <<endl;
    }
    else{
        if((*newown).no==2){
            owner=(*newown).ID;
            duedate=60;
            cout << "You have successfully issued this book" << endl;
        }
        else if((*newown).no==1){
            if((*newown).increase_book_count()){
                owner=(*newown).ID;
                duedate=30;
                cout << "You have successfully issued this book" << endl;
            }
        }
        else{
            cout << "\nYou already are a librarian, how many more books do you need\n" << endl;
        }
    }
    return;
}

void professor::calculate_fine(){
    tr(books, b1){
        if((*b1).owner==ID && (*b1).duedate<0){
            fine=-5*(*b1).duedate;
        }
    }
    cout << "Your fine is: Rs " << fine << endl;
    return;
}

void student::calculate_fine(){
    tr(books, b1){
        if((*b1).owner==ID && (*b1).duedate<0){
            fine=-2*(*b1).duedate;
        }
    }
    cout << "Your fine is: Rs " << fine << endl;
    return;
}

void professor::clear_fine(){
    fine=0;
    tr(books, it){
        if((*it).owner==ID && (*it).duedate<0){
            (*it).owner="";
            (*it).duedate=0;
        }
    }
    cout << "\n\tYou have paid your fine and returned the due books\n" << endl;
    return;
}

void student::clear_fine(){
    fine=0;
    tr(books, it){
        if((*it).owner==ID && (*it).duedate<0){
            (*it).owner="";
            (*it).duedate=0;
        }
    }
    cout << "\n\tYou have paid your fine and returned the due books\n" << endl;
    return;
}

void librarian::add_user(){
    int choice,flag;
    string tuname, tID, tpass;
    while(cout <<"\nSelect who do you want to add: \n  1-Student\n  2-Professor\n  3-Librarian\n \n\n" && !(cin>>choice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please re-enter.";
    }
    if(choice==1||choice==2||choice==3){
        cout <<  "\nEnter name: ";
        cin.ignore();
        getline(cin,tuname);
        // cin >> tuname;
        while(true){
            flag=1;
            cout << "\nEnter ID: ";
            cin >> tID;
            tr(users, it4){
                if((**it4).ID==tID){
                    flag=0;
                    cout << "This userID already exists!";
                    break;
                }
            }
            if(flag){break;}
        }
        cout << "\nEnter password: ";
        cin>>tpass;
        if(choice==1){
            user *puse;
            puse=new student(tuname,tID,tpass);
            users.push_back(puse);
        }
        if(choice==2){
            user *puse;
            puse=new professor(tuname,tID,tpass);
            users.push_back(puse);
        }
        if(choice==3){
            user *puse;
            puse=new librarian(tuname,tID,tpass);
            users.push_back(puse);
        }
        cout << "\nThe user has been added successfully\n" << endl;
    }
    else{
        cout << "\nIncorrect choice" << endl;
    }
    return;
}

void librarian::update_user(){
    string tID;
    cout << "\nEnter UserID: ";
    cin>>tID;
    tr(users, it2){
        if((**it2).ID==tID){
            string tuname, tpass;
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin,tuname);
            cout << "Enter new password: ";
            cin>>tpass;
            (**it2).name=tuname;
            (**it2).password=tpass;
            cout << "This user has been updated successfully\n" << endl;
            return;
        }
    }
    cout << "No user with such ID was found\n" << endl;
    return;
}

void librarian::delete_user(){
    string tID;
    cout << "\nEnter UserID: ";
    cin>>tID;
    tr(users, it2){
        if((**it2).ID==tID){
            user *temp=*it2;
            users.erase(it2);
            delete(temp);
            cout << "This user has been deleted successfully\n" << endl;
            return;
        }
    }
    cout << "No user with such ID was found\n" << endl;
    return;
}

void librarian::add_book(){
    string tit, aut, pub;
    int flag;
    ll isbn;
    cout << "\nEnter title: ";
    cin.ignore();
    getline(cin,tit);
    cout << "\nEnter author: ";
    getline(cin,aut);
    while(true){
        flag=1;
        while(cout << "\nEnter ISBN: " && !(cin>>isbn)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ISBN is a number, not a string. Please re-enter.";
        }
        tr(books, it4){
            if((*it4).ISBN==isbn){
                flag=0;
                cout << "A book with such ISBN already exists!";
                break;
            }
        }
        if(flag){break;}
    }
    cout << "\nEnter publisher: ";
    cin.ignore();
    getline(cin,pub);
    book b(tit,aut,isbn,pub);
    books.push_back(b);
}

void librarian::update_book(){
    ll isbn;
    while(cout << "\nEnter ISBN: " && !(cin>>isbn)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ISBN is a number, not a string. Please re-enter.";
    }
    tr(books, it2){
        if((*it2).ISBN==isbn){
            string tit,aut,pub;
            cout << "Enter new title: ";
            cin.ignore();
            getline(cin,tit);
            cout << "Enter new author: ";
            getline(cin,aut);
            cout << "Enter new publication: ";
            getline(cin,pub);
            (*it2).title=tit;
            (*it2).author=aut;
            (*it2).publication=pub;
            cout << "\nThe book has been updated successfully\n" << endl;
            return;
        }
    }
    cout << "\nThe book with that ISBN was not found\n" << endl;
    return;
}

void librarian::delete_book(){
    ll isbn;
    while(cout << "\nEnter ISBN: " && !(cin>>isbn)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ISBN is a number, not a string. Please re-enter.";
    }
    tr(books, it2){
        if((*it2).ISBN==isbn){
            books.erase(it2);
            cout << "\nThe book has been deleted successfully\n" << endl;
            return;
        }
    }
    cout << "\nThe book with that ISBN was not found\n" << endl;
    return;
}

void librarian::check_book_user(){
    ll isbn;
    while(cout << "\nEnter ISBN: " && !(cin>>isbn)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ISBN is a number, not a string. Please re-enter.";
    }
    tr(books, it2){
        if((*it2).ISBN==isbn){
            if((*it2).owner==""){
                cout << "\nThis book has not been issued to anyone\n" << endl;
            }
            else{
                cout << "\nThis book has been issued to UserID "<< (*it2).owner << endl << endl;
            }
            return;
        }
    }
    cout << "\nThe book with that ISBN was not found\n" << endl;
    return;
}

void librarian::check_issued_books(){
    string uid;
    int flag=0;
    cout << "\nEnter userID: ";
    cin>>uid;
    tr(books, it2){
        if((*it2).owner==uid){
            flag=1;
            cout << "\nTitle: " << (*it2).title << "\tISBN: " << (*it2).ISBN << endl<<endl;
        }
    }
    if(!flag){
        cout << "This user has no books issued or the userID is incorrect" << endl << endl;
    }
    return;
}

void librarian::pass_days(){
    int days;
    while(cout << "\nEnter days to pass(max=30): " && !(cin>>days)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please re-enter.";
    }
    if(days>30){
        cout << "\nMaximum limit reached\n" << endl;
        return;
    }
    tr(books, it){
        if((*it).owner!=""){
            (*it).duedate-=days;
        }
    }
    cout << "\nWith your godly powers, you have advanced "<<days<<" days\n" << endl;
    return;
}

void display_all_books(){
    cout << "All the books are: \n" << endl;
    tr(books, it1){
        cout<<"Title: "<<(*it1).title<<"\tAuthor: "<<(*it1).author<<"\tISBN: "<<(*it1).ISBN<<"\tPublication: "<<(*it1).publication<<endl;
    }
    return;
}

void list_all_users(){
    cout << "All the users are: \n" << endl;
    tr(users, it2){
        cout <<"Name: "<<(**it2).name << "\tUserID: " <<(**it2).ID;
        if((**it2).no==1){
            cout<<"\tStudent" << endl;
        }
        else if((**it2).no==2){
            cout<<"\tProfessor" << endl;
        }
        else if((**it2).no==3){
            cout<<"\tLibrarian" << endl;
        }
    }
    return;
}

void login(){
    int choice;
    cout << "\n\t\tLIBRARY MANAGEMENT SYSTEM" << endl;
    while(true){
        while(cout << "\nEnter your choice \n  1-Login\n  2-Exit\n \n\n" && !(cin>>choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please re-enter.";
        }
        if(choice==2){
            break;
        }
        else if(choice==1){
            string tuid, tpass;
            int flag=0;
            cout << "Enter your userID: " << endl;
            cin >> tuid;
            cout << "Enter your password: " << endl;
            cin >> tpass;
            tr(users, it){
                if((**it).ID==tuid && (**it).password==tpass){
                    flag=1;
                    mainmenu(*it);
                    break;
                }
            }
            if(!flag){
                cout << "\n\tYour credentials are incorrect" << endl;
            }
        }
        else{
            cout << "Please enter a valid number" << endl;
        }
    }
}

void mainmenu(user *cur){
    if((*cur).no==1||(*cur).no==2){
        if((*cur).no==1){
            cout << "\n\tYou are logged in as student\n" << endl;
        }
        else{
            cout << "\n\tYou are logged in as professor\n" << endl;
        }
        int flag1=1;
        while(flag1){
            int choice;
            while(cout <<"\nEnter your choice: \n1-See all books\t\t\t2-See my books\n3-Check if book is not issued\t4-Issue book\n5-Return book\t\t\t6-Calculate fine\n7-Clear fine\t\t\t8-Logout\n" && !(cin>>choice)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please re-enter.";
            }
            switch (choice){
                case 1:{
                    display_all_books();
                    break;
                }
                case 2:{
                    tr(books, it3){
                        if((*it3).owner==(*cur).ID){
                            cout << "\nTitle: " << (*it3).title << "\tISBN: " << (*it3).ISBN << endl;
                            (*it3).Show_DueDate();
                        }
                    }
                    break;
                }
                case 3:{
                    ll isbn;
                    int flag=0;
                    while(cout << "\nEnter ISBN: " && !(cin>>isbn)){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "ISBN is a number, not a string. Please re-enter.";
                    }
                    tr(books, it2){
                        if((*it2).ISBN==isbn){
                            flag=1;
                            if((*it2).owner==""){
                                cout << "\nThis book has not been issued to anyone\n" << endl;
                            }
                            else{
                                cout << "\nThis book has already been issued to someone"<< endl << endl;
                            }
                            break;
                        }
                    }
                    if(!flag){
                        cout << "\nThe book with that ISBN was not found\n" << endl;
                    }
                    break;
                }
                case 4:{
                    ll isbn;
                    int flag=0;
                    while(cout << "\nEnter ISBN: " && !(cin>>isbn)){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "ISBN is a number, not a string. Please re-enter.";
                    }
                    tr(books, it2){
                        if((*it2).ISBN==isbn){
                            flag=1;
                            (*it2).Book_Request(cur);
                            break;
                        }
                    }
                    if(!flag){
                        cout << "\nThe book with that ISBN was not found\n" << endl;
                    }
                    break;
                }
                case 5:{
                    ll isbn;
                    int flag=0;
                    while(cout << "\nEnter ISBN: " && !(cin>>isbn)){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "ISBN is a number, not a string. Please re-enter.";
                    }
                    tr(books, it2){
                        if((*it2).ISBN==isbn){
                            flag=1;
                            if((*it2).owner==(*cur).ID){
                                if((*it2).duedate<0){
                                    cout << "\nYou need to pay your fine and return the book together." << endl;
                                }
                                else{
                                    (*it2).owner="";
                                    (*it2).duedate=0;
                                    cout << "\nYou have successfully returned the book.\n";
                                }
                            }
                            else{
                                cout << "\nYou have not issued this book." << endl;
                            }
                            break;
                        }
                    }
                    if(!flag){
                        cout << "\nThe book with that ISBN was not found\n" << endl;
                    }
                    break;
                }
                case 6:{
                    (*cur).calculate_fine();
                    break;
                }
                case 7:{
                    (*cur).clear_fine();
                    break;
                }
                case 8:{
                    flag1=0;
                    break;
                }
                default:{
                    cout << "\nPlease enter a valid choice\n";
                    break;
                }
            }
        }
    }
    else{
        cout << "\n\tYou are logged in as librarian\n" << endl;
        int flag1=1;
        while(flag1){
            int choice;
            // cout <<"Enter your choice: \n1-Add user\n2-Update user\n3-Delete user\n4-Add book\n5-Update book\n6-Delete book\n7-See all users\n8-See all books\n9-Check user of a book\n10-Check books of a user\n11-Logout\n";
            while(cout <<"\nEnter your choice: \n1-Add user\t\t\t2-Update user\n3-Delete user\t\t\t4-Add book\n5-Update book\t\t\t6-Delete book\n7-See all users\t\t\t8-See all books\n9-Check user of a book\t\t10-Check books of a user\n11-Pass days(HACK)\t\t12-Logout\n" && !(cin>>choice)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please re-enter.\n";
            }
            switch(choice){
                case 1:{
                    (*cur).add_user();
                    break;
                }
                case 2:{
                    (*cur).update_user();
                    break;
                }
                case 3:{
                    (*cur).delete_user();
                    break;
                }
                case 4:{
                    (*cur).add_book();
                    break;
                }
                case 5:{
                    (*cur).update_book();
                    break;
                }
                case 6:{
                    (*cur).delete_book();
                    break;
                }
                case 7:{
                    list_all_users();
                    break;
                }
                case 8:{
                    display_all_books();
                    break;
                }
                case 9:{
                    (*cur).check_book_user();
                    break;
                }
                case 10:{
                    (*cur).check_issued_books();
                    break;
                }
                case 11:{
                    (*cur).pass_days();
                    break;
                }
                case 12:{
                    flag1=0;
                    break;
                }
                default:{
                    cout << "\nPlease enter a valid choice\n" << endl;
                    break;
                }
            }
        }
    }
    return;
}

int main(){
    user *puse;
    puse=new librarian("Libra", "123","pass");
    users.push_back(puse);
    login();
    return 0;
}