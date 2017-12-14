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
    linked_list.display();
//    SortedBag<Student> list2 = linked_list;
//    list2.begin();
        for(int i = 0; i<linked_list.size();++i){
           // cout<<"list2 "<<linked_list.get().string_ssn()<<endl;
        }
    
//    for(int i = 0; i<list2.size();++i){
//        cout<<"list2 "<<list2.get().string_ssn()<<endl;
//    }
//    if(linked_list == list2) {
//        cout << "true" <<endl;
//    } else {
//        cout << "false" << endl;
//    }
    //    SortedBag<Student> l2;
    //    l2=linked_list;
    //    cout<<l2.size()<<endl;
    /*linked_list.begin();
     l2.begin();
     cout<<"L1             L2 \n";
     for(int x=0;x<linked_list.size();x++){
     Student one;
     one=linked_list.get();
     cout<< one.string_ssn()<<" | "<<endl;
     ++linked_list;
     }
     */
}



