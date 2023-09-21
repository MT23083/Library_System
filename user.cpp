#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>
#include<chrono>
#include "globals.h"
#include "user.h"

using namespace std;

void user::setDetails(const std::string& name1){
    this -> user_id = user_count + 1;
    user_count++;
    this -> name = name1;
}

string user::getName(){
    return name;
}

int user::getId(){
    return user_id;
}

