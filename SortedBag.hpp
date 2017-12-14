//
//  SortedBag.hpp
//  
//
//  Created by Yukkee chang on 12/12/17.
//

#ifndef SortedBag_hpp
#define SortedBag_hpp
#include "Node.hpp"
#include <stdio.h>

using namespace std;

template<class T>
class SortedBag {
public:
    SortedBag() : head_ptr(0), m_data(0), m_size(0), m_asc(true), m_curr(0) {}
    SortedBag(SortedBag&);
    
    void operator =(SortedBag&);
    //~SortedBag();
    bool erase_one(const T&);
    long erase(const T&);
    void insert(const T&);
    long size() const { return m_size; }
    long count(const T&) const;
    void display();
    // SIMPLE ITERATOR
    void begin(){m_data=head_ptr;}
    bool end()const {return(m_data->get_next_link()==head_ptr);}
    //OVERLOADED OPERATORS
    void operator++(){m_data = m_data->get_next_link();}
    void operator--(){m_data = m_data->get_prev_link();}
    void operator +=( SortedBag&);
    friend bool operator ==(SortedBag&, SortedBag&);
    //friend bool operator<(const Node<T> &,const Node<T> &);
    T& get(){return m_data->get_data();}
private:
    Node<T>* head_ptr; //will always point to the head
    Node<T>* m_data; // pointer to ring structure. This will be my "cursor"
    long     m_size; // number of elements in the Bag.
    bool     m_asc;  // flag to indicate iteration in ascending order or not.
    Node<T>* m_curr; // iterator's current position.
    
};


//---------------DECONSTRUCTOR/CONSTRUCTOR-----------------
//template<class T>
//SortedBag<T>::~SortedBag<T>() {
//    list_remove(head_ptr);
//    head_ptr=0;
//    m_data=0;
//}

template<class T>
SortedBag<T>::SortedBag( SortedBag& Bag2) {
    Bag2.begin();
    do {
        this->insert(Bag2.get());
        ++Bag2;
    } while(Bag2.m_data!=Bag2.head_ptr);
}


//----------------MEMBER FUNCTIONS---------------------------

template<class T>
void SortedBag<T>::insert(const T& entry){
    if(m_size==0){
        //m_size isnt pointing to anything so we add the head
        m_data = new Node<T>();
        m_data-> set_data(entry);
        head_ptr = m_data;//the head is auto the new node
        ++m_size;
        //cout<<"inserted at the Head!!"<<endl;
        
        return;
    }
    //node with new entry has been created but has no links
    /*******************************************************/
    //now check if we need to update the head.
    //if entry is smaller it will become new head(m_data) adjust the head_pt
    if(entry.num_ssn()<head_ptr->get_data().num_ssn()){
        //    cout<<"New Head & its student: "<<entry.num_ssn()<<endl;
        // the head ptr will now point to the new entry
        list_insert(head_ptr->get_prev_link(),entry);
        head_ptr = head_ptr->get_prev_link();
        ++m_size;
        return;
    }
    
    m_data=head_ptr; //set cursor to head
    do{
        if(m_data->get_data().num_ssn()>entry.num_ssn()){
            list_insert(m_data->get_prev_link(),entry);
            ++m_size;
            return;
        }
        m_data=m_data->get_next_link();
    }while(m_data!=head_ptr);
    //if loop has finished that means entry is the last of the list
    //cout<<"New tail & its student: "<<entry.num_ssn()<<endl;
    list_insert(head_ptr->get_prev_link(),entry);
    ++m_size;
    return;
    
}

template<class T>
long SortedBag<T>::erase(const T& student) {
    long count = 0;
    if(m_size == 0) return 0;
    Node<T>* remove;
    remove = list_search(head_ptr, student);
    while(remove != NULL) {
        if(remove == head_ptr) {
            head_ptr = head_ptr->get_next_link();
        } else {
            delete remove;
            remove = list_search(head_ptr, student);
            ++count;
        }
    }
}



template<class T>
bool SortedBag<T>::erase_one(const T& target)
{
    //make a node type pointer to target
    Node<T> *target_ptr;
    target_ptr = list_search(head_ptr,target);
    if (target_ptr == NULL) return false; // target isn't in the bag, so no work
    list_remove(target_ptr);
    --m_size;
    return true;
    
}
template<class T>
long SortedBag<T>::count(const T& t) const
{
    int answer;
    const Node<T> *cursor;
    answer = 0;
    cursor = head_ptr;
    
    do {
        cursor = cursor->link( );
        ++answer;
    }
    while(cursor != head_ptr);
    return answer;
}




//--------------OVERLOADED OPERATORS------------------
template<class T>
SortedBag<T> operator+(const SortedBag<T>&, const SortedBag<T>&);

template<class T>
bool operator ==(SortedBag<T>& bag1,SortedBag<T>& bag2 )
{
    if(bag1.size() != bag2.size()) return false;
    return((bag1.size()==0) && (bag2.size()==0));
    bag1.begin();
    bag2.begin();
    for(int i = 0; i<bag1.size(); i++) {
        if(bag1.m_data->get_data().num_ssn() != bag2.m_data->get_data().num_ssn())return false;
        
        ++bag1;
        ++bag2;
    }
    return true;
    
}


template<class T>
void SortedBag<T>::operator +=(SortedBag<T>& bag)
{
    if(bag.size() == 0) {
        return;
    } else {
        bag.begin();
        for(int i=0; i < bag.size(); ++bag) {
            this->insert(bag.get());
        }
    }
    
}

template<class T>
void SortedBag<T>::operator =(SortedBag<T>& bag2)
{
    if(bag2.size() == 0) {
        
        list_clear(this->head_ptr);
        head_ptr=0;
        m_data=0;
        m_size = 0;
        return;
    } else {
        list_clear(this->head_ptr);
        bag2.begin();
        for(int i=0; i < bag2.size(); ++bag2) {
            this->insert(bag2.get());
        }
        m_size = bag2.size();
    }
}

template<class T>
void SortedBag<T>::display(){
    if(!(head_ptr)){
        cout<<"list is empty!\n";
        return;
    }
    m_data = head_ptr;
    do{
        cout<<m_data->get_data().string_ssn()<<endl;
        m_data = m_data->get_next_link();
    }while(m_data!=head_ptr);
}



#endif /* SortedBag_hpp */
