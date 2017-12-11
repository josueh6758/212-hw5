
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
    Node<T>* list_search(Node<T>* head_ptr, T& target)
    {
        return head_ptr;
        /*Node<T> *cursor;
        cursor = head_ptr;
        do {
            if (target.num_ssn() == cursor->get_data().num_ssn()) return cursor;
            cursor = cursor->get_next_link();
        }while(cursor != head_ptr);*/
    }

//-----------------------------SortedBag Header

   template<class T>
   class SortedBag {
   public:
     SortedBag() : m_data(0), m_size(0), m_asc(true), m_curr(0) {}
     //copy constructor
       SortedBag(const SortedBag& sb) {m_data=sb.m_data; m_size=sb.m_size; m_asc=sb.m_asc; m_curr=sb.m_curr;}
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
     Node<T>* endPointer() {if(m_data->get_next_link()==head_ptr) {return m_data->get_next_link();} }
     Node<T>* beginPointer() {return m_data=head_ptr; }
     
     //bag only points to one object in the linked list
     void operator++(){m_data = m_data->get_next_link();}
     void operator--(){m_data = m_data->get_prev_link();}
     bool boolforequal(SortedBag<T>&, SortedBag<T>&);
     T get() {return m_data->get_data();};
     void remove(const T&);
     
//   friend bool operator<(const Node<T> &,const Node<T> &);

//     friend bool operator<(const Node<T> node1,const Node<T> node2){
//         /*Notice!!!! i am not using pointers but actual nodes so use .get rather than
//            ->get */
//             cout<<"in the comparison module i am comparing "<< node1.get_data().num_ssn() << "And "<<node2.get_data().num_ssn()<<endl<<endl;
//        if(node1.get_data().num_ssn() <node2.get_data().num_ssn);}
//        //pointer that returns a student
     
   private:
     Node<T>* head_ptr; //will always point to the head
     Node<T>* m_data; // pointer to ring structure. This will be my "cursor"
     long     m_size; // number of elements in the Bag. 
     bool     m_asc;  // flag to indicate iteration in ascending order or not.
     Node<T>* m_curr; // iterator's current position.
     
   };





//-----------------------------------SortedBag Declaration
   template<class T>
    long SortedBag<T>::erase(const T& student) {
        if(student.num_ssn()==head_ptr->get_data().num_ssn()) {
            Node<T>* curr=head_ptr;
            head_ptr = head_ptr.get_next_link();
            delete curr;
            curr = NULL;
            --m_size;
            return true;
        } else {
            
            list_remove(student);
        }
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
	//	cout<<"New Head & its student: "<<entry.num_ssn()<<endl;
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
    size_t list_length(const Node<T>* head_ptr)
    {
        const Node<T> *cursor;
        int answer = 0;
        cursor = head_ptr;
        do{
            cursor = cursor->get_next_link();
            answer++;
        }while(cursor->get_next_link() != head_ptr);
        
        return answer+1;
    }


    template<class T>
    bool operator ==(SortedBag<T>& bag1,SortedBag<T>& bag2 )
    {
        for(int i = 0; i<bag1.size(); i++) {
            if(bag1.m_data->get_data().num_ssn() != bag2.m_data->get_data().num_ssn())
            {
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

/*template<class T>
bool operator <(Node<T>& node1, Node<T>& node2){
Notice!!!! i am not using pointers but actual nodes so use .get rather than
	        ->get *
	     	cout<<"in the comparison module i am comparing "<< node1.get_data().num_ssn() << "And "<<node2.get_data().num_ssn()<<endl<<endl;
		return(node1.get_data().num_ssn() <node2.get_data().num_ssn);}

*/

    template<class T>
    bool SortedBag<T>::erase_one(const T& target)
    {
        //make a node type pointer to target
        Node<T> *target_ptr;
      //  target_ptr = list_search(head_ptr,target);
        if (target_ptr == NULL)
            return false; // target isn't in the bag, so no work to do
        target_ptr->set_data( head_ptr->get_data() );
        remove(head_ptr->get_data());
        --m_size;
        return true;
        
    }
//    template<class T>
//    long SortedBag<T>::erase(const T& target)
//    {
//        int answer = 0;
//        //make a node type pointer to target
//        Node<T> *target_ptr;
//       // target_ptr = list_search(head_ptr, target);
//        while (target_ptr != NULL)
//        {
//            // Each time that target_ptr is not NULL, we have another occurrence
//            // of target. We remove this target using the same technique that
//            // was used in erase_one.
//            target_ptr->set_data( head_ptr->get_data( ) );
//            target_ptr = target_ptr->get_next_link( );
//           // target_ptr = list_search(target_ptr, target);
//            remove(head_ptr->get_data());
//            --m_size;
//            ++answer;
//        }
//        return answer;
//
//    }
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

    //This function is testing the == operator. Currently a linker issue
    template<class T>
    bool SortedBag<T>::boolforequal(SortedBag<T>& bag1, SortedBag<T>& bag2) {
        if (bag1 == bag2) {
            cout << "true" << endl;
            return true;
        }
        else
            cout << "false" << endl;
        return false;
        
    }

//-------------------------------------End of SortedBag functions


   int main(){
       srand(time(NULL));

	SortedBag<Student> linked_list;
		for(int i = 0; i<200;++i){
		Student entry;
		//cout<<"created a new student with SSID OF "<<entry.string_ssn()<<endl;
		linked_list.insert(entry);	
		}
	
	SortedBag<Student>   list_2;
	linked_list.begin();
	for(int i=0; i<linked_list.size();i++){
        //insert into list 2 from list 1
		list_2.insert(linked_list.get());
		--linked_list;
	}
	
	linked_list.begin();
	list_2.begin();
	cout<<"      L1                L2\n";
	for(int x=0;x<linked_list.size();++x){
	Student l1,l2;
	l1=linked_list.get(); 
	l2=list_2.get();

	cout<<x+1<<": "<<l1.string_ssn()<< "| "<<l2.string_ssn()<<endl;
	++linked_list;
	++list_2;	
	
	}
       //    Attempting to use overload equal operator but get linker errors both times
       //    cout << (linked_list == list_2) << endl;
       //    linked_list.boolforequal(linked_list, list_2);
       
       //#2
       //Remove first and last node in list 1 and list 2. Would use == operator to check if bags are equivalent but linker issue. Use for-loop to check equality
       linked_list.erase_one(linked_list.beginPointer()->get_data());
       for(int i=0; i<linked_list.size();i++){
           cout<<"remove the first node of the 1st list "<<linked_list.get().string_ssn()<<endl;
       }

       list_2.erase_one(linked_list.beginPointer()->get_data());
       for(int i=0; i<list_2.size();i++){
           cout<<"remove the first node of the 2nd list "<<list_2.get().string_ssn()<<endl;
       }
       //While linked_list is at the end
       while(linked_list.end()) {
           linked_list.erase(linked_list.endPointer()->get_data());
           for(int i=0; i<linked_list.size();i++){
               cout<<"remove the last node of the 1st list "<<linked_list.get().string_ssn()<<endl;
           }
       }

       //While list_2 is at the end
       while(list_2.end()) {
           list_2.erase(linked_list.endPointer()->get_data());
           for(int i=0; i<linked_list.size();i++){
            cout<<"remove the last node of the 2st list "<<linked_list.get().string_ssn()<<endl;
           }
       }

//       for(int i=0; i<list_2.size(); i++){
//           linked_list.erase(++linked_list);
//           //check if size of list is 0
//           if(linked_list.size() == 0) {
//           //Alt method but has errors because of data types:
//           //check if the data pointed by head pointer is null
//           //if(linked_list.beginPointer()->get_data == NULL) {
//               cout << "list empty" << endl;
//           } else {
//               //what was not removed in linked_list
//               cout<<"empty linked_list from list_2: "<<linked_list.get().string_ssn()<<endl;
//           }
       
 //      }
       
       
       




   }
