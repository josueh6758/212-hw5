#include<iostream>
#include "student.h"
#include <assert.h>
#include "SortedBag.hpp"
#include "Node.hpp"

using namespace std;

int main(){
    //srand(time(NULL));
    
    SortedBag<Student> linked_list;
    for(int i = 0; i<5;++i){
        Student entry;
        //cout<<"created a new student with SSID OF "<<entry.string_ssn()<<endl;
        linked_list.insert(entry);
    }
    Student two;
    cout<<"Student 2:"<< two.string_ssn()<<endl;
    linked_list.insert(two);
    linked_list.display();
    cout<< linked_list.erase(two)<<endl;
    linked_list.display();
	
}


