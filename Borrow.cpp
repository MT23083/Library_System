#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>
#include<chrono>
#include "user.h"
#include "student.h"
#include "prof.h"
#include "User_utility.h"
#include "globals.h"
#include "Borrow.h"
using namespace std;

com Borrow::sItem(const std::string& m){
    string a1 = "\"" + m + "\"";
    for(int i = 0; i < (2 * MAXB + MAXM); i++){
        if(i >= 99 && i <= 179){
            if(c_arr[i].name.compare(a1) == 0){
            cout << "Name: " << c_arr[i].name << endl;
            cout << "Location / Identifier: ";
            find(i);
            if(!(c_arr[i].max_count == -1)){
               cout << "Max Availability: " << c_arr[i]. max_count << endl;
               cout << "Current Availability: " << c_arr[i].max_count - c_arr[i].curr_count << endl;
            }

            return c_arr[i];
            }
        }
        else{
            if(c_arr[i].name.compare(a1) == 0){
            cout << "Name: " << c_arr[i].name << endl;
            cout << "Location / Identifier: ";
            find(i);
            if(!(c_arr[i].max_count == -1)){
                cout << "Max Availability: " << c_arr[i]. max_count << endl;
                cout << "Current Availability: " << c_arr[i].max_count - c_arr[i].curr_count << endl;
            }

            return c_arr[i];
           }
        }

    }

    cout << "Item doesn't exist";
    com obj;
    obj.name = "";
    obj.identifier = "";
    obj.max_count = -1;
    obj.curr_count = -1;
    return obj;
}

void Borrow::byISBN(const std::string& isbn1){
    for(int i = 0; i < MAXB; i++){
        if(b_arr[i].isbn.compare(isbn1) == 0){
            cout << "Name: " << b_arr[i].title << endl;
            cout << "Location / Identifier: ";
            find(i);
            cout << "Max Availability: " << b_arr[i].book_count << endl;
            return;
        }
    }
}

int Borrow::sIndex(const std::string& m){
    for(int i = 0; i < (2 * MAXB + MAXM); i++){
    //add condition here
        if(c_arr[i].name.compare(m) == 0){
            return i;
        }
    }
    return -1;

}

int Borrow::sIndexById(const std::string& idx){
    for(int i = 0; i < (2 * MAXB + MAXM); i++){
    //add condition here
        if(c_arr[i].identifier.compare(idx) == 0){
            return i;
        }
    }
    return -1;
}

void Borrow::s_borrow(student& User){
    cout << "Please enter Item Name to be Borrowed: ";
    string a;
    cin.ignore();
    getline(cin, a);

    com cObj = sItem(a);

    if(cObj.name.compare("") == 0)
        return;
    else{
        borrowUserDetails(User.getId(), a, cObj, "student");
    }
}

void Borrow::p_borrow(prof& User){
    cout << "Please enter Item Name to be Borrowed: ";
    string s1;
    cin.ignore();
    getline(cin, s1);
    com cObj = sItem(s1);

    if(cObj.name.compare("") == 0)
        return;
    else{
        borrowUserDetails(User.getId(), s1, cObj, "prof");
    }
}

void Borrow::borrowUserDetails(int u_id, const std::string& m, com cObj, const std::string& type_usr){
    mb_arr[borrow_count].user_id = u_id;
    mb_arr[borrow_count].item_id = cObj.identifier;
    mb_arr[borrow_count].issue_time = issue_date();
    if(type_usr.compare("student") == 0){
        mb_arr[borrow_count].due_time = return_date(mb_arr[borrow_count].issue_time, 30);
    }
    if(type_usr.compare("prof") == 0){
        mb_arr[borrow_count].due_time = return_date(mb_arr[borrow_count].issue_time, 180);
    }

    borrow_count++;

    //reduce count from original array and comparing it with original count
    if(c_arr[sIndex(m)].curr_count == c_arr[sIndex(m)].max_count && !(c_arr[sIndex(m)].identifier.find("J") == 0)){
       cout << "No copies available to be lent." << endl;
       return;
    }

    c_arr[sIndex(m)].curr_count++;
    cout << "Item Borrowed Successfully" << endl;
    //give due date here
    cout << "Due Date: " << mb_arr[borrow_count - 1].due_time << endl;
}

void Borrow::Copies_add(){
    cout<<"Please select the relevant reading material : \n 1.BOOK  \n 2.MAGAZINE \n 3.JOURNAL"<< endl;
    int id;
    cin >> id;

    int max;
    cin.ignore();
    cout << "Please enter name: " << endl;
    string n;
    std::getline(cin, n);

    //add for book later
    if(id == 1 || id == 2){
        cout << endl << "Please enter number of copies: ";
        cin >> max;
    }

    if(id == 1){
        current_books++;
        combined_length++;
        string ide = "B" + to_string(current_books);
        shiftArray(current_books);
        c_arr[current_books].name = n;
        c_arr[current_books].max_count = max;
        c_arr[current_books].curr_count = 0;
        c_arr[current_books].identifier = ide;
        cout << "Item added successfully" << endl;
    }

    if(id == 2){
        current_magazine++;
        combined_length++;
        string ide = "M" + to_string(current_magazine);
        shiftArray(current_magazine);
        c_arr[current_books + current_magazine].name = "\"" + n + "\"";
        c_arr[current_books + current_magazine].max_count = max;
        c_arr[current_books + current_magazine].curr_count = 0;
        c_arr[current_books + current_magazine].identifier = ide;
        cout << "Item added successfully" << endl;
    }

    if(id == 3){
        current_journal++;
        combined_length++;
        string ide = "J" + to_string(current_journal);
        shiftArray(current_journal);
        c_arr[combined_length].name = n;
        c_arr[combined_length].max_count = -1;
        c_arr[combined_length].curr_count = -1;
        c_arr[combined_length].identifier = ide;
        cout << "Item added successfully" << endl;
    }

    cout << "Final Value: " << c_arr[combined_length].name;
}

std::string Borrow::issue_date(){
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    return std::ctime(&currentTime);
}

std::string Borrow::return_date(const std::string& currentDate, int days){
    std::chrono::system_clock::time_point afterMonth = std::chrono::system_clock::now() + std::chrono::hours(days * 24);

    std::time_t afterDaysTime = std::chrono::system_clock::to_time_t(afterMonth);
    std::string afterDaysDate = std::ctime(&afterDaysTime);
    return afterDaysDate;
}

void Borrow::Copies_update(const std::string& m, int newCopies){
    int idx = sIndex(m);
    if(idx == -1){
        cout << "Item Not Found" << endl;
        return;
    }
    else{
        c_arr[idx].max_count += newCopies;
        cout << "Item " << c_arr[idx].name << " updated." << endl;
        cout << "Max Availability: " << c_arr[idx].max_count;
    }
}

void Borrow::shiftArray(int idx){
    for(int i = idx; i < combined_length - 1; i++){
        c_arr[i + 1] = c_arr[i];
    }
}

void Borrow::byAuthor(const std::string& auth){
    for(int i = 0; i < MAXB; i++){
        if(b_arr[i].authors.compare(auth) == 0){
            cout << "Name: " << b_arr[i].title << endl;
            cout << "Location / Identifier: ";
            find(i);
            cout << "Max Availability: " << b_arr[i].book_count << endl;
            return;
        }
    }
}

void Borrow::find(int index){
    int shelf_idx = index % 5;
    cout<< "Shelf No: " << shelf_idx << " ";

    int book_no = index % 56;
    cout << "Book No: " << book_no << endl;
}

