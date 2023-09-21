#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>
#include<chrono>
#include "user.h"
#include "globals.h"
#include "User_utility.h"
using namespace std;

int User_utility::searchUser(user& User){
    int id = User.getId();

    for(int i = 0; i < MAXU; i++){
        if(id == t_arr[i].user_id){
            return i;
        }
    }
    return -1;
}

void User_utility::saveData(int id, std::string n, std::string t){
    t_arr[user_count].name = n;
    t_arr[user_count].user_id = id;
    t_arr[user_count].type = t;
}