
#include<iostream> 
#include "student.h"
#include <assert.h>

using namespace std;
//comment testing 1.0(j.h)



template<class T>
   struct Node {
     Node() : m_next(this), m_prev(this) {}    
     Node(const T& val, Node<T>* n =0, Node<T>* p =0): m_val(val)
      { m_next = n? n : this; m_prev = p? p : this; }
      bool is_singleton() const { m_next == this && m_prev == this; }
     T        m_val; 
     Node<T>* m_next; // pointer to successor element. 
     Node<T>* m_prev; // pointer to predecessor element.
     //

     void set_data(const T& new_data) { m_val = new_data; }
     void set_next_link(Node<T>* new_link)             { m_next = new_link; }
     void set_prev_link(Node<T>* new_link)             { m_prev = new_link; }
     T get_data() { return m_val;}
     const Node<T>* get_next_link( ) const { return m_next;}
     Node<T>* get_next_link( )             { return m_next; }
     //we need two for next and prev	
     const Node<T>* get_prev_link( ) const { return m_prev;}
     Node<T>* get_prev_link( )             { return m_prev; }
    
   };



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
	
Node<T>* left_ptr = removed_ptr->get_prev_link();
Node<T>* right_ptr = removed_ptr->get_prev_link();//left+right node is grabbed using current Node!!! 
left_ptr->set_next_link(right_ptr);
right_ptr->set_prev_link(left_ptr);
delete removed_ptr;

}

template<class T>
int list_count(Node<T>* head_ptr){
//first test if its a single node
if(head_ptr->is_singleton()) return 1;

Node<T>* cursor_ptr = head_ptr;
int count = 0;
//DO loop GAURANTEES ITS EXECUTED ONCE. once the ball starts rolling then counting is fine
do{
cursor_ptr= cursor_ptr->get_next_link();
count++;
}while(cursor_ptr != head_ptr);

}

   template<class T>
   class SortedBag {
   public:
     SortedBag() : m_data(0), m_size(0), m_asc(true), m_curr(0) {}
     SortedBag(const SortedBag&);

     void operator =(const SortedBag&);
     //~SortedBag();

     bool erase_one(const T&);
     long erase(const T&);
     void insert(const T&);
     void operator +=(const SortedBag&);
     friend bool operator ==(SortedBag&, SortedBag&);
     long size() const { return m_size; }
     long count(const T&) const;
     // SIMPLE ITERATOR 
     void begin(){m_data=head_ptr;}
     bool end()const {return(m_data->get_next_link()==head_ptr);} 
     void operator++(){m_data = m_data->get_next_link();}
     void operator--(){m_data = m_data->get_prev_link();}
     friend bool operator<(const Node<T> node1,const Node<T> node2){
	     /*Notice!!!! i am not using pointers but actual nodes so use .get rather than
	        ->get */
	     	cout<<"in the comparison module i am comparing "<< node1.get_data().num_ssn() << "And "<<node2.get_data().num_ssn()<<endl<<endl;
		if(node1.get_data().num_ssn() <node2.get_data().num_ssn);}
     						
     T get(){return m_data->get_data();};
   private:
     Node<T>* head_ptr; //will always point to the head
     Node<T>* m_data; // pointer to ring structure. This will be my "cursor"
     long     m_size; // number of elements in the Bag. 
     bool     m_asc;  // flag to indicate iteration in ascending order or not.
     Node<T>* m_curr; // iterator's current position.
     
   };
   template<class T>
   SortedBag<T> operator+(const SortedBag<T>&, const SortedBag<T>&);

//Beggining OF CODE
  template<class T>
   SortedBag<T>::SortedBag(const SortedBag&){
  //create a linked list copy of a linked list(COPY CONSTRUCTOR) 
   
   
   }

   template<class T>
   void SortedBag<T>::insert(const T& entry){
   	if(m_size==0){
	//m_size isnt pointing to anything so we add the head
		m_data = new Node<T>();
		m_data-> set_data(entry);
		head_ptr = m_data;//the head is auto the new node
		++m_size;
		cout<<"inserted at the Head!!"<<endl;
		
		return;	
	}
	Node<T>* insert_node= new Node<T>();
	insert_node->set_data(entry);
	//node with new entry has been created but has no links
	/*******************************************************/
	//now check if we need to update the head.
	//if entry will become new head(m_data) adjust the head_pt
	cout<<"Student: "<<insert_node->get_data().num_ssn()<<endl;
	if(insert_node<head_ptr){
		cout<<"New Head & its student: "<<insert_node->get_data().num_ssn();
		head_ptr = insert_node;// the head ptr will now point to the new entry
	}
	m_data=head_ptr; //set cursor to head
	do{	
		if(m_data>insert_node){
			list_insert(m_data->get_prev_link(),entry);
			delete insert_node;
			++m_size;
			return;
		} 
		m_data=m_data->get_next_link();
	}while(m_data!=head_ptr);
	//if loop has finished that means entry is the last of the list
	list_insert(head_ptr->get_prev_link(),entry);
		delete insert_node;
		++m_size;
		return;
	
}

//----------//
template<class T>
Node<T>* list_search(Node<T>* head_ptr, const typename Node<T>::value_type& target)
{
    Node<T> *cursor;
    
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
        if (target == cursor->data( ))
            return cursor;
    return NULL;
}


template<class T>
size_t list_length(const typename SortedBag<T>::Node* head_ptr)
{
    const typename SortedBag<T>::Node *cursor;
    size_t answer;
    
    answer = 0;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
        ++answer;
    
    return answer;
}


template<class T>
bool operator ==(SortedBag<T>& bag1,SortedBag<T>& bag2 )
{
    for(int i = 0; i<bag1.size(); i++) {
        if(bag1.m_data->get_data().num_ssn() != bag2.m_data->get_data().num_ssn()) {
            return false;
        }
        ++bag1;
        ++bag2;
    }
    return true;
    
}

template<class T>
void SortedBag<T>::operator =(const SortedBag<T>& bag)
{
    SortedBag<T>x = bag;
}


template<class T>
bool SortedBag<T>::erase_one(const T& target)
{
    //make a node type pointer to target
    Node<T> *target_ptr;
    target_ptr = list_search(head_ptr, target);
    if (target_ptr == NULL)
        return false; // target isn't in the bag, so no work to do
    target_ptr->set_data( head_ptr->data( ) );
    list_head_remove(head_ptr);
    --m_size;
    return true;
    
}
template<class T>
long SortedBag<T>::erase(const T& target)
{
    int answer = 0;
    //make a node type pointer to target
    Node<T> *target_ptr;
    target_ptr = list_search(head_ptr, target);
    while (target_ptr != NULL)
    {
        // Each time that target_ptr is not NULL, we have another occurrence
        // of target. We remove this target using the same technique that
        // was used in erase_one.
        target_ptr->set_data( head_ptr->data( ) );
        target_ptr = target_ptr->link( );
        target_ptr = list_search(target_ptr, target);
        list_head_remove(head_ptr);
        --m_size;
        ++answer;
    }
    return answer;
    
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


   int main(){
       srand(time(NULL));
    SortedBag<Student>L3;
	SortedBag<Student>L1;
		for(int i = 0; i<4;++i){
		Student entry;
		L1.insert(entry);
		}
		int count=0;
		L1.end();
       
		for(int a=L1.size(); a<L1.size();--a){
			Student sample;
            L3.insert(sample);
//            sample= linked_list.get();
//            cout<<sample.string_ssn()<<endl;
			//--L1.size();
			//++count;
		}
       bool equal = (L1==L3);
       cout << equal << endl;
       
       return 0;


   }
