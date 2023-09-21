#ifndef LIB_BORROW
#define LIB_BORROW
#include "lib_borrow.h"

class lib_borrow{
    public:
    void item_borrow(int id, int search_name);
    void return_mat(int usridx, const std::string& itm);
    void check(const std::string& n);
    void check(int a);
};

#endif //LIB_BORROW