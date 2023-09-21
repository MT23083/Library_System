#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>
#include<chrono>
#include "user.h"
#include "globals.h"
#include "student.h"
using namespace std;

void student::setUser(const std::string& name, const std::string& type1){
    setDetails(name);
    this -> type = "student";
}

string student::getType(){
    return type;
}