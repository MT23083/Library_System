#include<string>
#include "user.h"
#include "globals.h"

#ifndef PROF_H
#define PROF_H

using namespace std;


class prof : public user{
    private:
        std::string type;
    public:
        void setUser(const std::string& name);
        std::string user_type();
};
#endif //PROF_H