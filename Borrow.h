#include<string>
#include "prof.h"
#include "student.h"
#include "globals.h"
#include "user.h"
#ifndef BORROW_H
#define BORROW_H


class Borrow{
    public:
        com sItem(const std::string& m);
        int sIndex(const std::string& m);
        void s_borrow(student& User);
        void p_borrow(prof& User);
        void borrowUserDetails(int u_id, const std::string& m, com cObj, const std::string& type_usr);
        void find(int index);
        std::string issue_date();
        std::string return_date(const std::string& currentDate, int days);
        void Copies_update(const std::string& a, int newCopies);
        void Copies_add();
        void shiftArray(int idx);
        int sIndexById(const std::string& idx);
        void byISBN(const std::string& isbn1);
        void byAuthor(const std::string& auth);
};

#endif