#include<iostream>
#include<chrono>
#include<string.h>
#include<fstream>
#include<sstream>
using namespace std;

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

bookData bookArray[MAX_BOOKS];
journal jArray[MAX_BOOKS];
magData magArray[MAX_MAG];
combined comArray[2 * MAX_BOOKS + 2 * MAX_MAG];

struct libraries{
    bookData;
    journal;
    magData;
};

class library : public Borrow{
    public:
    //function in order to borrow books from library
    Borrow borrow;
    borrow.borrowed();
};


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
}