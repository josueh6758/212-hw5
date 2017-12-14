#ifndef node_h
#define node_h

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
     if(cursor==0 || cursor == NULL){ 
	     cout<<"list is already empty\n";
	     return;}
     
	
     while(!(cursor->is_singleton())){	
	list_remove(cursor->get_next_link()); 
     }
	delete cursor;
	return;
}

#endif
