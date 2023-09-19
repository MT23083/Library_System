#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>
#include<chrono>
using namespace std;

const int MAX_BOOKS = 99;
const int MAX_MAG = 80;
const int MAX_USERS = 100;
int user_count = 0;
int borrow_count = 0;

int current_books = MAX_BOOKS;
int current_magazine = MAX_MAG;
int current_journal = MAX_BOOKS;
//change MAX BOOKS to current_books .....
int combined_length = current_books + current_magazine + current_journal;


struct bookData {
    int book_id;
    int book_count;
    std::string isbn;
    std::string isbn13;
    std::string authors;
    std::string title;
};

struct magData{
    std::string name;
    std::string rank;
    int count;
};

struct journal{
    std::string name;
};

struct combined{
    string name;
    string identifier;
    int max_count;
    int curr_count;
};

struct borrowed{
    int user_id;
    string item_id;
    string issue_time;
    string due_time;
};

bookData bookArray[MAX_BOOKS];
journal jArray[MAX_BOOKS];
magData magArray[MAX_MAG];
combined comArray[2 * MAX_BOOKS + 2 * MAX_MAG];
borrowed borrowArray[MAX_USERS];

class user{
    private:
        int user_id;
        string name;

    public:
        void setDetails(string name1){
            this -> user_id = user_count + 1;
            user_count++;
            this -> name = name1;
        }

        string getName(){
            return name;
        }

        int getId(){
            return user_id;
        }
};

class student: public user{
    private:
        string type;

    public:
        void setUser(string name, string type1){
            setDetails(name);
            this -> type = "student";
        }

        string getType(){
            return type;
        }
};

class prof : public user{
    private:
        string type;

    public:
        void setUser(string name){
            setDetails(name);
            this -> type = "prof";
        }

        string getType(){
            return type;
        }
};

user user_array[MAX_USERS];
class User_utility{
    public:
        int searchUser(user User){
            int id = User.getId();

            for(int i = 0; i < MAX_USERS; i++){
                if(id == user_array[i].getId()){
                    return i;
                }
            }
            return -1;
        }


};

class Borrow{
    public:
        combined searchItem(string a){
        string a1 = "\"" + a + "\"";
            for(int i = 0; i < (2 * MAX_BOOKS + MAX_MAG); i++){
                if(i >= 99 && i <= 179){
                    if(comArray[i].name.compare(a1) == 0){
                    cout << "Name: " << comArray[i].name << endl;
                    cout << "Location / Identifier: ";
                    hash(i);
                    if(!(comArray[i].max_count == -1)){
                       cout << "Max Availability: " << comArray[i]. max_count << endl;
                       cout << "Current Availability: " << comArray[i].max_count - comArray[i].curr_count << endl;
                    }

                    return comArray[i];
                    }
                }else{
                    if(comArray[i].name.compare(a) == 0){
                    cout << "Name: " << comArray[i].name << endl;
                    cout << "Location / Identifier: ";
                    hash(i);
                    if(!(comArray[i].max_count == -1)){
                        cout << "Max Availability: " << comArray[i]. max_count << endl;
                        cout << "Current Availability: " << comArray[i].max_count - comArray[i].curr_count << endl;
                    }

                    return comArray[i];
                   }
                }

            }

            cout << "Item doesn't exist";
            combined obj;
            obj.name = "";
            obj.identifier = "";
            obj.max_count = -1;
            obj.curr_count = -1;
            return obj;

        }

        int searchIndex(string a){
            for(int i = 0; i < (2 * MAX_BOOKS + MAX_MAG); i++){
            //add condition here
                if(comArray[i].name.compare(a) == 0){
                    return i;
                }
            }
            return -1;

        }

        void borrowed(student User){
            cout << "Please enter Item Name to be Borrowed: ";
            string a;
            getline(cin, a);

            combined comObj = searchItem(a);

            if(comObj.name.compare("") == 0)
                return;
            else{
                setBorrowDetails(User.getId(), a, comObj, "student");
            }
        }

        void borrowed(prof User){
            cout << "Please enter Item Name to be Borrowed: ";
            string a;
            getline(cin, a);

            combined comObj = searchItem(a);

            if(comObj.name.compare("") == 0)
                return;
            else{
                setBorrowDetails(User.getId(), a, comObj, "prof");
            }
        }

        void setBorrowDetails(int user_id, string a, combined comObj, string type){
            borrowArray[borrow_count].user_id = user_id;

            borrowArray[borrow_count].item_id = comObj.identifier;
            borrowArray[borrow_count].issue_time = current_date();
            if(type.compare("student") == 0){
                borrowArray[borrow_count].due_time = date_after_1_month(borrowArray[borrow_count].issue_time);
            }
            if(type.compare("prof") == 0){
                borrowArray[borrow_count].due_time = date_after_6_month(borrowArray[borrow_count].issue_time);
            }

            borrow_count++;

            //reduce count from original array and comparing it with original count
            if(comArray[searchIndex(a)].curr_count == comArray[searchIndex(a)].max_count && !(comArray[searchIndex(a)].identifier.find("J") == 0)){
               cout << "No copies available to be lent." << endl;
               return;
            }

            comArray[searchIndex(a)].curr_count++;
            cout << "Item Borrowed Successfully" << endl;
            //give due date here
            cout << "Due Date: " << borrowArray[borrow_count - 1].due_time << endl;
        }


        void hash(int index){
            int shelf_idx = index % 5;
            cout<< "Shelf No: " << shelf_idx << " ";

            int book_no = index % 56;
            cout << "Book No: " << book_no << endl;
        }


        string current_date(){
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

            return std::ctime(&currentTime);
        }

        string date_after_1_month(string currentDate){
            std::chrono::system_clock::time_point afterMonth = std::chrono::system_clock::now() + std::chrono::hours(30 * 24);

            std::time_t afterDaysTime = std::chrono::system_clock::to_time_t(afterMonth);
            std::string afterDaysDate = std::ctime(&afterDaysTime);
            return afterDaysDate;
        }

        string date_after_6_month(string currentDate){
            std::chrono::system_clock::time_point afterMonth = std::chrono::system_clock::now() + std::chrono::hours(180 * 24);

            std::time_t afterDaysTime = std::chrono::system_clock::to_time_t(afterMonth);
            std::string afterDaysDate = std::ctime(&afterDaysTime);
            return afterDaysDate;
        }

        void updatePurchase(string a, int new_copies){
            int index = searchIndex(a);
            if(index == -1){
                cout << "Item Not Found" << endl;
                return;
            }else{
                comArray[index].max_count += new_copies;
                cout << "Item " << comArray[index].name << " updated." << endl;
                cout << "Max Availability: " << comArray[index].max_count;
            }
        }

        void newPurchase(){
            cout<<"Please select the relevant reading material : "<< endl;
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
                adjustArray(current_books);
                comArray[current_books].name = n;
                comArray[current_books].max_count = max;
                comArray[current_books].curr_count = 0;
                comArray[current_books].identifier = ide;
                cout << "Item added successfully" << endl;
            }

            if(id == 2){
                current_magazine++;
                combined_length++;
                string ide = "M" + to_string(current_magazine);
                adjustArray(current_magazine);
                comArray[current_books + current_magazine].name = "\"" + n + "\"";
                comArray[current_books + current_magazine].max_count = max;
                comArray[current_books + current_magazine].curr_count = 0;
                comArray[current_books + current_magazine].identifier = ide;
                cout << "Item added successfully" << endl;
            }

            if(id == 3){
                current_journal++;
                combined_length++;
                string ide = "J" + to_string(current_journal);
                adjustArray(current_journal);
                comArray[combined_length].name = n;
                comArray[combined_length].max_count = -1;
                comArray[combined_length].curr_count = -1;
                comArray[combined_length].identifier = ide;
                cout << "Item added successfully" << endl;
            }


            cout << "Final Value: " << comArray[combined_length].name;
        }

        void adjustArray(int index){
            for(int i = index; i < combined_length - 1; i++){
                comArray[i + 1] = comArray[i];
            }
        }


};

//class purchase{
//    public:
//        void newPurchase(string a, int new_copies){
//
//        }
//};


int main(){
        string line, word;

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
                    bookArray[numBooks].book_id = id;
                }
                if(count == 5){
                    int id = std::stoi(token);
                    bookArray[numBooks].book_count = id;
                }

                if(count == 6){
                    bookArray[numBooks].isbn = token;
                }

                if(count == 7){
                    bookArray[numBooks].isbn13 = token;
                }

                if(count == 8){
                    bookArray[numBooks].authors = token;
                }

                if(count == 11){
                    bookArray[numBooks].title = token;
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
                    magArray[numMag].name = token;
                }

                if(count == 2){
                    magArray[numMag].rank = token;
                }

             }
             numMag++;

        }


        for(int i = 0; i < MAX_MAG; i++){
            magArray[i].count = 10;
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
                 jArray[numBooks].name = token;
             }
             numBooks++;

        }
        sample_journals.close();

        //combining all 3 arrays
        for(int  i = 0; i < MAX_BOOKS; i++){
            comArray[i].name = bookArray[i].title;
            comArray[i].identifier = "B" + std::to_string(i);
            comArray[i].max_count = bookArray[i].book_count;
            comArray[i].curr_count = 0;
        }

        for(int i = 0; i < MAX_MAG; i++){
            comArray[i + MAX_BOOKS].name = magArray[i].name;
            comArray[i + MAX_BOOKS].identifier = "M" + std::to_string(i);
            comArray[i + MAX_BOOKS].max_count = magArray[i].count;
            comArray[i + MAX_BOOKS].curr_count = 0;
        }

        for(int i = 0; i < MAX_BOOKS; i++){
            comArray[i + MAX_BOOKS + MAX_MAG].name = jArray[i].name;
            comArray[i + MAX_BOOKS + MAX_MAG].identifier = "J" + std::to_string(i);
            comArray[i + MAX_BOOKS + MAX_MAG].max_count = -1;
            comArray[i + MAX_BOOKS + MAX_MAG].curr_count = -1;
        }

        student newStudent;
        newStudent.setDetails("ABC");
        user_array[user_count - 1] = newStudent;

        prof newProf;
        newProf.setDetails("BCD");
        user_array[user_count - 1] = newProf;

        Borrow br;
        //br.borrowed(newProf);

        br.newPurchase();



        return 0;
}
