#include<iostream>  
using namespace std;
//comment testing


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
     T get_data( ) const { return m_val;} 	
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
n_node = new Node<T>(left_ptr, entry, right_ptr);
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
     ~SortedBag();

     bool erase_one(const T&);
     long erase(const T&);
     void insert(const T&);
     void operator +=(const SortedBag&);
     long size() const { return m_size; }
     long count(const T&) const;
     // SIMPLE ITERATOR 
     void begin(const bool ascending =true);
     bool end() const;
     void operator++(){m_data = m_data->get_next_link();}
     void operator--(){m_data = m_data->get_prev_link();}
     friend bool operator<(const Node<T> node1,const Node<T> node2){
		if(node1.get_data <node2.get_data()) return true;
			return false;}
     						
     T& get();
   private:
     Node<T>* head_ptr; //will always point to the head
     Node<T>* m_data; // pointer to ring structure. This will be my "cursor"
     long     m_size; // number of elements in the Bag. 
     bool     m_asc;  // flag to indicate iteration in ascending order or not.
     Node<T>* m_curr; // iterator's current position.
     
   };
   template<class T>
   SortedBag<T> operator+(const SortedBag<T>&, const SortedBag<T>&);

//BEG OF CODE


   template<class T>
   void SortedBag<T>::insert(const T& entry){
   	if(m_size==0){
	//m_size isnt pointing to anything so we add the head
		m_data = new Node<T>();
		m_data-> set_data(entry);
		head_ptr = m_data;//the head is auto the new node
		++m_size;	
	}
	Node<T>* insert_node= new Node<T>();
	insert_node->set_data(entry);
	//node with new entry has been created but has no links
	/*******************************************************/
	//now check if we need to update the head.
	//if entry will become new head(m_data) adjust the head_pt
	if(insert_node<head_ptr){
		head_ptr = insert_node;// the head ptr will now point to the new entry
	}
	m_data=head_ptr; //set cursor to head
	do{	
		if(m_data>insert_node){
			list_insert(m_data->get_prev_link(),entry);
			delete insert_node;
			return;
		} 
		++m_data;
	}while(m_data!=head_ptr);
	//if loop has finished that means entry is the last of the list
	list_insert(head_ptr->get_prev_link(),entry);
		delete insert_node;
		return;
	
}




   int main(){
   
   }
