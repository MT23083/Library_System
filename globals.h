#ifndef GLOBALS_H
#define GLOBALS_H
#include<string>

struct tempUser{
    std::string name;
    int user_id;
    std::string type;
};

struct bcsv {
    int book_id;
    int book_count;
    std::string isbn;
    std::string isbn13;
    std::string authors;
    std::string title;
};

struct mcsv{
    std::string name;
    std::string rank;
    int count;
};

struct jcsv{
    std::string name;
};

struct com{
    std::string name;
    std::string identifier;
    int max_count;
    int curr_count;
};

struct mat_borrow{
    int user_id;
    std::string item_id;
    std::string issue_time;
    std::string due_time;
};

struct journo{
    std::string jtitle;
    int price;
};

extern double budget;
extern int sub_count;
extern const int MAXB;
extern const int MAXM;
extern const int MAXU;
extern int user_count;
extern int borrow_count;
extern bcsv* b_arr;
extern jcsv* j_arr;
extern mcsv* m_arr;
extern com* c_arr;
extern mat_borrow* mb_arr;
extern journo* journal_s;
extern tempUser* t_arr;
extern int current_books;
extern int current_magazine;
extern int current_journal;
//change MAX BOOKS to current_books .....
extern int combined_length;


#endif // GLOBALS_H