#include<iostream>
#include<chrono>
#include<string>
#include<fstream>
#include<sstream>
#include "prof.h"
#include "student.h"
#include "user.h"
#include "User_utility.h"
#include "Borrow.h"
#include "globals.h"
#include "lib_borrow.h"
#include "journal_sub.h"

using namespace std;

const int MAXB = 99;
const int MAXM = 80;
const int MAXU = 100;
int user_count = 0;
int borrow_count = 0;

int current_books = MAXB;
int current_magazine = MAXM;
int current_journal = MAXB;
//change MAX BOOKS to current_books .....
int combined_length = current_books + current_magazine + current_journal;

bcsv* b_arr = new bcsv[MAXB];
jcsv* j_arr = new jcsv[MAXB];
mcsv* m_arr = new mcsv[MAXM];
com* c_arr = new com[2 * MAXB + 2 * MAXM];
mat_borrow* mb_arr = new mat_borrow[MAXU];
tempUser* t_arr = new tempUser[MAXU];

void lib_borrow::check(const std::string& n){
    if(cin.fail()){
        cout << "Please enter a valid input" << endl;
        cin.clear();
    }
}

void lib_borrow::check(int a){
    if(cin.fail()){
        cout << "Please enter a valid input" << endl;
        cin.clear();
    }
}

void lib_borrow::item_borrow(int id, int search_name){
    std::string n;
    switch(search_name){
        case 1:
            cin.ignore();
            cout << "Enter Journal Name: ";
            getline(cin,n);
            check(n);
            for(int i = 0; i < MAXB; i++){
                if(c_arr[i + MAXB + MAXM].name.compare(n) == 0){
//                    if(c_arr[i + MAXB + MAXM].curr_count < c_arr[i + MAXB + MAXM].max_count){
//                        c_arr[i + MAXB + MAXM].curr_count++;
                        //borrow store
                        Borrow br;
                        mb_arr[++borrow_count].user_id = id;
                        mb_arr[borrow_count].item_id = c_arr[i + MAXB + MAXM].identifier;
                        //cout << "Identifier: " << mb_arr[borrow_count].item_id << endl;
                        mb_arr[borrow_count].issue_time = br.issue_date();
                        mb_arr[borrow_count].due_time = br.return_date(mb_arr[borrow_count].issue_time, 7);
                        cout << "Item borrowed successfully." << endl;
                        cout << "Item available on date: " << mb_arr[borrow_count].due_time;
                        return;
//                    }else{
//                        cout << "Item limit exceeded." << endl;
//                        return;
//                    }
                }
            }
            cout << "Item not found in any library" << endl;
        break;

        case 2:
            cin.ignore();
            cout << "Enter magazine name: ";
            getline(cin,n);
            check(n);
            n = "\"" + n + "\"";
            for(int i = 0; i < MAXM; i++){
                if(c_arr[i + MAXB].name.compare(n) == 0){
                    if(c_arr[i + MAXB].curr_count < c_arr[i + MAXB].max_count){
                        Borrow br;
                        c_arr[i + MAXB].curr_count++;
                        mb_arr[++borrow_count].user_id = id;
                        mb_arr[borrow_count].item_id = c_arr[i + MAXB].identifier;
                        mb_arr[borrow_count].issue_time = br.issue_date();
                        mb_arr[borrow_count].due_time = br.return_date(mb_arr[borrow_count].issue_time, 7);
                        cout << "Item borrowed successfully." << endl;
                        cout << "Item available on date: " << mb_arr[borrow_count].due_time;
                        return;
                    }else{
                         cout << "Item limit exceeded." << endl;
                         return;
                    }
                }
            }
                cout << "Item doesn't exist in any library" << endl;
        break;

        case 3:
            cin.ignore();
            cout << "Enter Book Name: ";
            getline(cin,n);
            check(n);
            for(int i = 0; i < MAXB; i++){
                if(c_arr[i].name.compare(n) == 0){
                    if(c_arr[i].curr_count < c_arr[i].max_count){
                        Borrow br;
                        c_arr[i].curr_count++;
                        mb_arr[++borrow_count].user_id = id;
                        mb_arr[borrow_count].item_id = c_arr[i].identifier;
                        mb_arr[borrow_count].issue_time = br.issue_date();
                        mb_arr[borrow_count].due_time = br.return_date(mb_arr[borrow_count].issue_time, 7);
                        cout << "Item borrowed successfully." << endl;
                        cout << "Item available on date: " << mb_arr[borrow_count].due_time;
                        return;
                    }else{
                          cout << "Item limit exceeded." << endl;
                          return;
                    }
                }
            }
               cout << "Item doesn't exist in any library" << endl;
        break;
    }

}

void lib_borrow:: return_mat(int usridx, const std::string& itm){
    Borrow br;
    for(int i=0; i<borrow_count; i++){
                if(mb_arr[i].user_id == usridx && mb_arr[i].item_id.compare(itm)){
                    cout<<"Item is returned !!"<<endl;
                    int borrowed_idx = br.sIndexById(itm);
                    c_arr[borrowed_idx].curr_count--;
                    cout << "Value of i " << i << endl;
                    for(int a=i; a<borrow_count - 1; a++){
                        mb_arr[a] = mb_arr[a+1];
                    }
                    borrow_count --;
                    return;
                }
                else{
                    cout<<"Item is not returned....still due !!!"<<endl;
                }

    }
}


int main(){
        int select;
        string line, word;
        Borrow br;
        User_utility u;
        tempUser ut;
        lib_borrow b;

        fstream books ("sample_books.csv", ios::in);

        std::getline(books, line);
        int numBooks = 0; int count;

        while(getline(books, line)){
            std::stringstream st(line);
            string token;
            count = 0;

             while(getline(st, token, ',')){
                count++;
                if(count == 1){
                    int id = std::stoi(token);
                    b_arr[numBooks].book_id = id;
                }
                if(count == 5){
                    int id = std::stoi(token);
                    b_arr[numBooks].book_count = id;
                }

                if(count == 6){
                    b_arr[numBooks].isbn = token;
                }

                if(count == 7){
                    b_arr[numBooks].isbn13 = token;
                }

                if(count == 8){
                    b_arr[numBooks].authors = token;
                }

                if(count == 11){
                    b_arr[numBooks].title = token;
                }

             }
             numBooks++;

        }

        books.close();

        fstream magazine ("sample_magazine.csv", ios::in);

        std::getline(magazine, line);
        int numMag = 0;

        while(getline(magazine, line)){
            std::stringstream st(line);
            string token;
            count = 0;

             while(getline(st, token, ',')){
                count++;

                if(count == 1){
                    m_arr[numMag].name = token;
                }

                if(count == 2){
                    m_arr[numMag].rank = token;
                }

             }
             numMag++;

        }


        for(int i = 0; i < MAXM; i++){
            m_arr[i].count = 10;
        }

        magazine.close();

        fstream sample_journals ("sample_journals.csv", ios::in);

        std::getline(sample_journals, line);
        int numJ = 0;
        numBooks = 0;

        while(getline(sample_journals, line)){
            std::stringstream st(line);
            string token;

             while(getline(st, token, ',')){
                 j_arr[numBooks].name = token;
             }
             numBooks++;

        }

        //combining all 3 arrays
        for(int  i = 0; i < MAXB; i++){
            c_arr[i].name = b_arr[i].title;
            c_arr[i].identifier = "B" + std::to_string(i);
            c_arr[i].max_count = b_arr[i].book_count;
            c_arr[i].curr_count = 0;
        }

        for(int i = 0; i < MAXM; i++){
            c_arr[i + MAXB].name = m_arr[i].name;
            c_arr[i + MAXB].identifier = "M" + std::to_string(i);
            c_arr[i + MAXB].max_count = m_arr[i].count;
            c_arr[i + MAXB].curr_count = 0;
        }

        for(int i = 0; i < MAXB; i++){
            c_arr[i + MAXB + MAXM].name = j_arr[i].name;
            c_arr[i + MAXB + MAXM].identifier = "J" + std::to_string(i);
            c_arr[i + MAXB + MAXM].max_count = -1;
            c_arr[i + MAXB + MAXM].curr_count = -1;
        }

        int main_ch = 1;
        string n;
        string x;
        student user1;
        prof user2;
        int type;
        int ch;
        int copies;
        int co;

        while(main_ch == 1){
            cout<<"Please select any one choice below : \n 1.USER \n 2.BORROW \n 3.RETURN \n 4.BORROW BOOK FROM LIBRARIES \n 5.SUBSCRIBE \n 6.SEARCH_BY_NAME \n 7.SEARCH_BY_ISBN \n 8.SEARCH_BY_AUTHOR \n 9.PURCHASE NEW ITEM"<<endl;
            cin >> select;
            b.check(select);
            cout << "Please select type: 1.STUDENT  2.PROF:  ";
            cin >> type;
            b.check(type);
            switch(select){
                case 1:
                    cout << "Please select the following: 1.REGISTER  2.LOGIN:  ";
                    cin >> ch;
                    b.check(ch);
                    if(ch == 1){
                        cin.ignore();
                        cout << "Enter name: ";
                        getline(cin, n);
                        b.check(n);
                        if(type == 1){
                            user1.user::setDetails(n);
                            u.saveData(user1.getId(), user1.getName(), "student");
                            ut.name = n;
                            ut.user_id = user1.getId();
                            ut.type = "student";
                            t_arr[user_count - 1] = ut;
                            cout << "Registered successfully. Your user id is " << user1.getId() << endl;
                        }
                        if(type == 2){
                             user2.user::setDetails(n);
                             u.saveData(user2.getId(), user2.getName(), "prof");
                             ut.name = n;
                             ut.user_id = user2.getId();
                             ut.type = "prof";
                             t_arr[user_count - 1] = ut;
                             cout << "Registered successfully. Your user id is " << user2.getId() << endl;
                        }
                    }
                    if(ch == 2){
                        cout << "Please enter user id: ";
                        cin >> ch;
                        b.check(ch);
                        co = 0;
                        for(int i = 0; i < user_count; i++){
                            if(t_arr[ch].user_id == ch){
                                cout << "Logged in successfully" << endl;
                                break;
                            }
                            co++;
                        }

                        if(co == user_count)
                            cout << "Login Failed. Please enter correct user id" << endl;

                    }
                    break;

                case 2:
                    if(type == 1){
                        br.s_borrow(user1);
                    }
                    if(type == 2){
                        br.p_borrow(user2);
                    }
                    break;

                case 3:
                    cin.ignore();
                    cout << "Please enter the item you want to return: ";
                    getline(cin, n);
                    b.check(n);
                    ch = br.sIndex(n);
                    x = c_arr[ch].identifier;
                    if(type == 1){
                        b.return_mat(user1.getId(), x);
                    }
                    if(type == 2){
                        b.return_mat(user2.getId(), x);
                    }
                    break;

                case 4:
                    cout << "Please select an item to be borrowed: 1. JOURNAL 2. MAGAZINE 3. BOOK:  ";
                    cin >> ch;
                    b.check(n);
                    if(type == 1){
                        b.item_borrow(user1.getId(), ch);
                    }
                    if(type == 2){
                        b.item_borrow(user2.getId(), ch);
                    }
                    break;

                case 5:
                    journal_sub j;
                    j.textsub();
                    break;

                case 6:
                    cin.ignore();
                    cout << "Enter item name to be searched: ";
                    getline(cin, n);
                    b.check(n);
                    br.sItem(n);
                    break;

                case 7:
                    cin.ignore();
                    cout << "ISBN: " << b_arr[7].isbn << endl;
                    cout << "Enter book name to be searched using ISBN: ";
                    getline(cin, n);
                    b.check(n);
                    br.byISBN(n);
                    break;

                case 8:
                    cin.ignore();
                    cout << "Enter book name to be searched using Author name: ";
                    getline(cin, n);
                    b.check(n);
                    br.byAuthor(n);
                    break;

                case 9:
                    cout << "Please enter the following: 1.UPDATE BOOK COPIES    2.ADD NEW BOOK";
                    cin >> ch;

                    if(ch == 1){
                        cin.ignore();
                        cout << "Please enter name of the book: ";
                        getline(cin, n);
                        b.check(n);
                        cout << endl << "Please enter number of new copies: ";
                        cin >> copies;
                        b.check(copies);
                        br.Copies_update(n, copies);
                    }
                    if(ch == 2){
                        br.Copies_add();
                    }
                    break;
            }
            cout << "Do you want to continue (1 for Y, 2 for N): ";
            cin >> main_ch;
            b.check(main_ch);
        }

        return 0;
}