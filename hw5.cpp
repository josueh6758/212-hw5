#include<iostream>
#include "student.h"
#include <assert.h>
#include "SortedBag.hpp"
#include "Node.hpp"

using namespace std;

int main(){
    //srand(time(NULL));
cout<<"TASK 1:\n";    
SortedBag<Student> list_one;
for(int i = 0; i<5;++i){
	Student entry;
        //cout<<"created a new student with SSID OF "<<entry.string_ssn()<<endl;
        list_one.insert(entry);
    }
SortedBag<Student> list_two;
list_one.begin();
for(int x=0;x<list_one.size();x++){

	list_two.insert(list_one.get());
	++list_one;
}
if(list_one==list_two){ cout<<"they are the same\n";}
else{cout<<"they are not the same\n";}
cout<<"L1:\n";
list_one.display();
cout<<"L2:\n";
list_two.display();


SortedBag<Student> list_three;
list_one.begin();
for(int x=0;x<list_one.size();x++){

	list_three.insert(list_one.get());
	--list_one;

}
if(list_one==list_three){ cout<<"they are the same\n";}
else{cout<<"they are not the same\n";}
cout<<"L1:\n";
list_one.display();
cout<<"L3:\n";
list_three.display();

// end of task 1;
}


