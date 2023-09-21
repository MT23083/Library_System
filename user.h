#include "globals.h"

#ifndef USER_H
#define USER_H

class user{
    private:
       int user_id;
       std::string name;

    public:
        void setDetails(const std::string& name1);
        std::string getName();
        int getId();
};
#endif