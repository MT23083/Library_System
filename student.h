#include<string>
#include "user.h"
#include "globals.h"
#ifndef STUDENT_H
#define STUDENT_H

class student : public user{
    private:
        std::string type;
    public:
        void setUser(const std::string& name, const std::string& type1);
        std::string getType();
};

#endif //STUDENT_H