#include<iostream>
#include<string>
#include<random>
#include "journal_sub.h"
#include "globals.h"

using namespace std;

journo* journal_s = new journo[40];
double bud = 450000.0;
int sub_count = 0;

void journal_sub::textsub(){
    int c = 0;
    for(int i = 0; i < MAXB; i+=5){
        journal_s[c].jtitle = j_arr[i].name;
        journal_s[c].price = budget();
        c++;
        sub_count++;
    }

    int sum = 0;
    std::string jname[sub_count];
    int count = 0;
    for(int i = 0; i < sub_count; i++){
        if(sum + journal_s[i].price <= bud){
            jname[count] = journal_s[i].jtitle;
            sum+= journal_s[i].price;
            count++;
        }else
            break;
    }

    cout << "The Journals subscribed for the year 2023 are " << endl;
    for(int i = 0; i < count; i++){
        cout << jname[i] << endl;
    }
}


int journal_sub::budget(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(100000, 200000);
    int randomNum = distribution(gen);
    return randomNum;

}