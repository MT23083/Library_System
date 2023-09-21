#include "user.h"
#include "globals.h"

#ifndef USER_UTI_H
#define USER_UTI_H

class User_utility{
    public:
        int searchUser(user& User);
        void saveData(int id, std::string n, std::string t);
};
#endif //USER_UTI_H