#include<iostream>
#include "student.h"
#include <assert.h>

using namespace std;


template<class T>

struct Node {
    Node() : m_next(this), m_prev(this) {}
    Node(const T& val, Node<T>* n =0, Node<T>* p =0): m_val(val)
    { m_next = n? n : this; m_prev = p? p : this; }
    bool is_singleton() const { m_next == this && m_prev == this; }
    T        m_val;
    Node<T>* m_next; // pointer to successor element.
    Node<T>* m_prev; // pointer to predecessor element.
    void set_data(const T& new_data) { m_val = new_data; }
    void set_next_link(Node<T>* new_link)             { m_next = new_link; }
    void set_prev_link(Node<T>* new_link)             { m_prev = new_link; }
    T& get_data() { return m_val;}
    const Node<T>* get_next_link( ) const { return m_next;}
    Node<T>* get_next_link( )             { return m_next; }
    //we need two for next and prev
    const Node<T>* get_prev_link( ) const { return m_prev;}
    Node<T>* get_prev_link( )             { return m_prev; }
    
    
};
//-------TOOLKIT NODE METHODS---------------------------

template<class T>
void list_insert(Node<T>* left_ptr, const T& entry){
    //pre-condition: requires atleast one node in the node list.
    //post-malone: will attatch the node in between the prior node and the next node gauranteed!
    //             this is because we are getting the right node through the left node's link!
    Node<T>* right_ptr = left_ptr->get_next_link();
    Node<T>* n_node;
    n_node = new Node<T>(entry, right_ptr,left_ptr);
    left_ptr->set_next_link(n_node);
    right_ptr->set_prev_link(n_node);
}

template<class T>
void list_remove(Node<T>* removed_ptr){
    //PRE-CONDITION: pass in the node you want to remove of the list!!!!!!
    
    //set the left pointer to the node before the one you're about to delete
    Node<T>* left_ptr = removed_ptr->get_prev_link();
    //set the right pointer to the node after the one you're about to delete
    Node<T>* right_ptr = removed_ptr->get_next_link();//left+right node is grabbed using current Node!!!
    //set the next link of the left node (left of node that removeptr is pointing at) to node that right_ptr is pointing at
    left_ptr->set_next_link(right_ptr);
    //set the prev link of the right node (right of the node that removeptr is pointing at) to node that left_ptr is pointing at
    right_ptr->set_prev_link(left_ptr);
    //now the left and right node's links are no longer set to remove pointer's so the node can be deleted and the pointer can be set to NULL
    delete removed_ptr;
    removed_ptr = NULL;
}


template<class T>
Node<T>* list_search(Node<T>* head_ptr,const T& target)
{
    Node<T>* curr;
    curr=head_ptr;
    do {
        if (curr->get_data().num_ssn == target.num_ssn()) return curr;
        curr = curr->get_next_link();
    }while(curr != head_ptr);
    return NULL;
}

template<class T>
void list_clear(Node<T>* cursor){
    //give a pointer and delete everything that is connected to that noder
    while(!(cursor->is_singleton())){
        list_remove(cursor->get_next_link());
    }
    delete cursor;
    cursor = NULL;
}


//-------SORTED BAG HEADER---------------------------

template<class T>
class SortedBag {
public:
    SortedBag() : m_data(0), m_size(0), m_asc(true), m_curr(0) {}
    SortedBag(SortedBag&);
    
    void operator =(SortedBag&);
    ~SortedBag();
    friend bool operator ==(SortedBag&, SortedBag&);
    bool erase_one(const T&);
    long erase(const T&);
    void insert(const T&);
    void operator +=( SortedBag&);
    long size() const { return m_size; }
    long count(const T&) const;
    // SIMPLE ITERATOR
    void begin(){m_data=head_ptr;}
    bool end()const {return(m_data->get_next_link()==head_ptr);}
    void operator++(){m_data = m_data->get_next_link();}
    void operator--(){m_data = m_data->get_prev_link();}
    //     friend bool operator<(const Node<T> &,const Node<T> &);
    T& get(){return m_data->get_data();}
private:
    Node<T>* head_ptr; //will always point to the head
    Node<T>* m_data; // pointer to ring structure. This will be my "cursor"
    long     m_size; // number of elements in the Bag.
    bool     m_asc;  // flag to indicate iteration in ascending order or not.
    Node<T>* m_curr; // iterator's current position.
    
};


template<class T>
SortedBag<T>::~SortedBag<T>() {
    list_remove(head_ptr);
    head_ptr=0;
    m_data=0;
}

template<class T>
SortedBag<T> operator+(const SortedBag<T>&, const SortedBag<T>&);

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
SortedBag<T>::SortedBag( SortedBag& Bag2) {
    Bag2.begin();
    do {
        this->insert(Bag2.get());
        ++Bag2;
    } while(Bag2.m_data!=Bag2.head_ptr);
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

//-------------------------------------End of SortedBag functions

int main(){
    srand(time(NULL));
    
    SortedBag<Student> linked_list;
//    for(int i = 0; i<5;++i){
//        Student entry;
//        cout<<"created a new student with SSID OF "<<entry.string_ssn()<<endl;
//        linked_list.insert(entry);
//    }
//    SortedBag<Student> list2 = linked_list;
//    list2.begin();
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



