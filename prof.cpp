#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string>
#include<chrono>
#include "user.h"
#include "globals.h"
#include "prof.h"
using namespace std;

void prof::setUser(const std::string& name){
    setDetails(name);
    this -> type = "prof";
}

string prof::user_type(){
    return type;
}
