/* Yichen Huang
*Name: Yichen Huang
*CWID: 11906882
*Course: CS-101-001
*/
#include <iostream>

using namespace std;

typedef struct _node{
    float time;
    float fuel;
    struct _node *next;
    struct _node *prev;
}Node;

class dList {
    private:
        Node *head;
        Node *tail;
        Node **arraypointer;
        int capacity;
        int counter;
    public:
        dList(float times[], float fuels[],int size);
        void out(char instruct);
        void out ();
        void out(int i, char instruct);
        void out(int i);
        int insert(float Ntimes, float Nfuels);
        int index_before(int i);
        int index_after(int i);
        void increase_time(int i, float t);
        void decrease_time(int i, float t);
        void decrease_fuel(int i, float f);
};


    /**
     *  Take 2 Node Pointers, each pointing at the head of sorted sublist,
     *      merge them, and return the Node pointer to the head node of the merged list.
     *  @param a Node* Pointer to the head of the first sorted list
     *  @param b Node* Pointer to the head of the second sorted list
     *  @return Node* head of the merged list (nullptr if both given nodes are empty)
     */
    Node* timesortedMerge( Node* a , Node* b )
    {
        Node* headOfMerged;

        // If one of the node is nullptr, return the other node
        // No merging occurs this this case
        if( a == NULL ) {
            return b;
        }
        else if( b == NULL ) {
            return a;
        }

        // First element in list, a, is less than the first element in b
        if( a->time <= b->time ) {
            headOfMerged = a;

            while( b != NULL ) {
                if( a->time <= b->time ) {
                    if( a->next == NULL ) {
                        a->next = b;
                        b->prev = a;
                        break;
                    }
                    a = a->next;
                }
                else {
                    Node* toAdd = b;
                    b = b->next;
                    toAdd->prev = a->prev;
                    a->prev->next = toAdd;
                    toAdd->next = a;
                    a->prev = toAdd;
                }
            }
        }
        // First element in list, b, is less than the first element in a
        else {
            headOfMerged = b;

            while( a != NULL ) {
                if( b->time <= a->time ) {
                    if( b->next == NULL ) {
                        b->next = a;
                        a->prev = b;
                        break;
                    }
                    b = b->next;
                }
                else {
                    Node* toAdd = a;
                    a = a->next;
                    toAdd->prev = b->prev;
                    b->prev->next = toAdd;
                    toAdd->next = b;
                    b->prev = toAdd;
                }
            }
        }

        return headOfMerged;
    }

    /**
     *  Utility function for merge sort
     *  @param frontRef Node* reference pointer that will point to the head of first sorted half
     *  @param backRef Node* reference pointer that will point to the head of second sorted half
     */
    void frontBackSplit( Node* theHead , Node* &frontRef , Node* &backRef )
    {
        Node* fast;
        Node* slow;

        // If the list is empty, both front and back points to null
        // If there is only one element, front points to it and back points
        //  to null.
        if( theHead == NULL || theHead->next == NULL ) {
            frontRef = theHead;
            backRef = NULL;
        }
        else {
            slow = theHead;
            fast = theHead->next;

            // Fast advances 2 nodes while slow advances 1 node
            while( fast != NULL ) {
                fast = fast->next;

                if( fast != NULL ) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }

            // slow should be pointing right before midpoint. Split at this point
            frontRef = theHead;
            backRef = slow->next;

            // Update the prev and next pointers
            backRef->prev = NULL;
            slow->next = NULL;
        }
    }

    void sorttime( Node* &theHead )
    {
        Node* a = NULL;
        Node* b = NULL;

        // Base case
        if( theHead == NULL || theHead->next == NULL ) {
            return;
        }

        // Split the list in half
        // For odd number of nodes, the extra node will be in the first half.
        frontBackSplit( theHead , a , b );

        // Recursively break the list down until the sublist contains 1 element (Sorted)
        sorttime( a );
        sorttime( b );

        // Merge the two sorted lists
        theHead = timesortedMerge( a , b );
    }

    
char determine (Node *ptr) { // D:Dominated G:Dominating N:None
    if(ptr->prev == NULL) { //head 
        
        if(ptr->next == NULL) {
                
            return 'N';
        }
        if(ptr->time == ptr->next->time) {
            //cout << "Same\n";
            if(ptr->fuel < ptr->next->fuel) {
                return 'G';
            }
            else {
                return 'D';
            }
        }
        else {
            if(ptr->fuel > ptr->next->fuel) {
                return 'N';
            }
            else {
                return 'G';
            }
        }
    }
    else if(ptr->next == NULL) { //tail
        if(ptr->time == ptr->prev->time) {
            if(ptr->fuel < ptr->prev->fuel) {
                return 'G';
            }
            else {
                return 'D';
            }
        }
        else {
            if(ptr->fuel < ptr->prev->fuel) {
                return 'N';
            }
            else {
                return 'D';
            }
        }
    }
    else { //other
        if(ptr->time == ptr->next->time) {
            if(ptr->fuel < ptr->next->fuel) {
                return 'G';
            }
            else {
                return 'D';
            }
        }
        else {
            if(ptr->fuel <= ptr->next->fuel) {
                return 'G';
            }
            else {
                return 'N';
            }
        }
    }
}

dList :: dList (float times[], float fuels[],int size) {
    //inport all element
    counter = size -1;
    capacity = size;
    arraypointer = new Node*[size];
    Node *curNode;
    curNode = new Node;
    curNode->time = times[0];
    curNode->fuel = fuels[0];
    curNode->prev = NULL;
    curNode->next = NULL;
    arraypointer[0] = curNode;
    head = curNode;
    tail = curNode;
    
    for(int i =1;i<size ;i++) {
        curNode = new Node;
        arraypointer[i] = curNode;
        curNode->time = times[i];
        curNode->fuel = fuels[i];
        curNode->prev = tail;
        tail->next = curNode;
        tail = curNode;
        if(i==(size-1)) {
            tail->next = NULL;
        }
    }
    
    
    
        //merge sort for time
        sorttime(head);
        //find tail
        for(Node *ptr=head;ptr!=NULL;ptr=ptr->next) {
            if(ptr->next==NULL) {
                tail = ptr;
            }
        }
    
    
    cout << endl;
    char c;

    //sort dominate use two pointers
    for(Node *ptr=head;ptr!=NULL;ptr=ptr->next) {
        //cout << ptr->fuel << endl;
        c = determine(ptr);
        //cout << c << endl;
        while(c!='N') {
            if(ptr->prev == NULL) { //head
                if(c == 'G') {
                    if(ptr->next->next == NULL) {
                        ptr->next = NULL;
                        tail = ptr;
                    }
                    else {
                        ptr->next->next->prev = ptr;
                        ptr->next = ptr->next->next;
                    }
                }
                else { // Dominated
                    ptr = ptr->next;
                    head = ptr;
                    ptr->prev = NULL;
                }
            }
            else if (ptr->next == NULL) { //tail
                if(c == 'G') {
                    ptr = ptr->prev->prev; // back to pervous
                }
                else { // Dominated
                    ptr = ptr->prev;
                    tail = ptr;
                    ptr->next = NULL;
                }
            }
            else { //other
                if(c == 'G') {
                    if(ptr->next->next == NULL) {
                        ptr->next = NULL;
                        tail = ptr;
                    }
                    else {
                        ptr->next->next->prev = ptr;
                        ptr->next = ptr->next->next;
                    }
                }
                else { // Dominated
                    ptr->next->prev = ptr->prev;
                    ptr=ptr->prev;
                    ptr->next = ptr->next->next;
                }
            }
            c = determine(ptr);
        }
    }
    
    
}
void dList :: out(char instruct) {
    if (instruct == 'd') { 
        for(Node*ptr=tail;ptr!=NULL;ptr=ptr->prev) {
            cout << "Time: " << ptr->time << "\t";
            cout << "Fuel: " << ptr->fuel << endl;
        }
    }
    else { 
         for(Node*ptr=head;ptr!=NULL;ptr=ptr->next) {
            cout << "Time: " << ptr->time << "\t";
            cout << "Fuel: " << ptr->fuel << endl;
        }
    }

}
void dList :: out () {
    for(Node*ptr=head;ptr!=NULL;ptr=ptr->next) {
            cout << "Time: " << ptr->time << "\t";
            cout << "Fuel: " << ptr->fuel << endl;
    }
}
void dList :: out(int i, char instruct) {
    int j=0;
    if (instruct == 'd') { 
        Node *ptr = tail;
        for(int j=0;j<i;j++) {
            cout << "Time: " << ptr->time << "\t";
            cout << "Fuel: " << ptr->fuel << endl;
            ptr=ptr->prev;
            if(ptr==NULL) break;
        }
    }
    else { 
        Node *ptr = head;
        for(int j=0;j<i;j++) {
            cout << "Time: " << ptr->time << "\t";
            cout << "Fuel: " << ptr->fuel << endl;
            ptr=ptr->next;
            if(ptr==NULL) break;
        }
        
    }
}
void dList :: out(int i) {
    Node *ptr = head;
    for(int j=0;j<i;j++) {
        cout << "Time: " << ptr->time << "\t";
        cout << "Fuel: " << ptr->fuel << endl;
        ptr=ptr->next;
        if(ptr==NULL) break;
    }
}

int dList :: insert(float Ntimes, float Nfuels) {
    
    //create a Node
    Node *Nnode = new Node;
    Nnode->time = Ntimes;
    Nnode->fuel = Nfuels;
    Nnode->next = NULL;
    Nnode->prev = NULL;
    //expand the array
    counter++;
    if (counter == capacity) {
         Node **temp = new Node*[capacity];
        capacity = capacity * 2;
        //cout << "Doubling to: " << capacity << endl;
        for(int i=0;i<counter;i++) {
            temp[i]=arraypointer[i];
        }
        delete arraypointer;
        arraypointer = new Node*[capacity];
        for(int i=0;i<counter;i++) {
            arraypointer[i]=temp[i];
        }  
        delete[] temp;
    }
    arraypointer[counter] = Nnode;
    
    
    //add the front
    if(Nnode->time <= head->time) {
        Nnode->next = head;
        head->prev = Nnode;
        head = Nnode;
    }
    //add at the end
    else if(Nnode->time >= tail->time) {
        tail->next = Nnode;
        Nnode->prev = tail;
        tail = Nnode;
    }
    else if ((Nnode->time > head->time)&&(Nnode->time < tail->time)){//add in the middle
        for(Node *ptr=head;ptr!=NULL;ptr=ptr->next) {
            if(ptr->next->time > Nnode->time) {
                Node *nptr = ptr->next;
                Nnode->prev = ptr;
                Nnode->next = nptr;
                ptr->next = Nnode;
                nptr->prev = Nnode;
                break;
            }
        }
    }
    
    
    char c;
    //sort dominate use two pointers
    //Node *ptr = Nnode;
    for(Node *ptr=head;ptr!=NULL;ptr=ptr->next) {   
        c = determine(ptr);
        while(c!='N') {
            //cout << endl;
            /*for(Node*ptr=head;ptr!=NULL;ptr=ptr->next) {
                cout << "Time: " << ptr->time << "\t";
                cout << "Fuel: " << ptr->fuel << endl;
            }*/
            if(ptr->prev == NULL) { //head
                //cout << "head\n";
                //cout << c << endl;
                if(c == 'G') {
                    if(ptr->next->next == NULL) {
                        
                        ptr->next = NULL;
                        tail = ptr;
                        
                        
                    }
                    else {
                        ptr->next->next->prev = ptr;
                        ptr->next = ptr->next->next;
                    }
                }
                else { // Dominated
                    ptr = ptr->next;
                    head = ptr;
                    ptr->prev = NULL;
                }
            }
            else if (ptr->next == NULL) { //tail
                
                if(c == 'G') {
                    ptr = ptr->prev->prev; // back to pervous
                }
                else { // Dominated
                    ptr = ptr->prev;
                    tail = ptr;
                    ptr->next = NULL;
                }
            }
            else { //other
                if(c == 'G') {
                    if(ptr->next->next == NULL) {
                        ptr->next = NULL;
                        tail = ptr;
                    }
                    else {
                        ptr->next->next->prev = ptr;
                        ptr->next = ptr->next->next;
                    }
                }
                else { // Dominated
                    ptr->next->prev = ptr->prev;
                    ptr=ptr->prev;
                    ptr->next = ptr->next->next;
                }
            }
            
            c = determine(ptr);
            
        }
    }
        
    
    
    
    
    return counter;
}

int dList :: index_before(int i) {
    Node *ptr = arraypointer[i];
    ptr=ptr->prev;
    int index = -1;
    for(int i=0;i<=counter;i++) {
        if (ptr == arraypointer[i]) {
            index = i;
        }
    }
    return index;
}
int dList :: index_after(int i) {
    Node *ptr = arraypointer[i];
    ptr=ptr->next;
    int index = -1;
    for(int i=0;i<=counter;i++) {
        if (ptr == arraypointer[i]) {
            index = i;
        }
    }
    return index;
}

void dList :: increase_time(int i, float t) {
    Node *ptr = arraypointer[i];
    ptr->time = ptr->time + t;

    if(ptr->next == NULL) { // Last of the list
        return;
    }
    else {
        while (ptr->time > ptr->next->time && ptr->next != NULL) {
            if(ptr->prev == NULL) { // head of the list
                Node *sucptr = ptr->next;
                head = sucptr;
                head->prev = NULL;
            }
            else { // middle of the list
                Node *prevptr = ptr->prev;
                Node *sucptr = ptr->next;
                prevptr->next = sucptr;
                sucptr->prev = prevptr;
            }
            ptr = ptr->next;
        }
    }
}

char deterprev (Node *ptr) { // D:Dominated G:Dominating N:None
    if(ptr->prev == NULL) { //head
        return 'N';
    }
    else {
        Node *prev = ptr->prev;
        if(prev->time > ptr->time) {
            return 'G';
        } 
        else {
            return 'N';
        }
    }
    
}
void dList :: decrease_time(int i, float t) {
    Node *curptr = arraypointer[i];
    curptr->time = curptr->time - t;
    
    if(curptr->prev == NULL) { // head
        return;
    }
    else { //Not Head
        char c = deterprev(curptr);
        while (c!='N') {
            if(curptr->prev->prev == NULL) {
                curptr->prev = NULL;
                head = curptr;
            }
            else {
                Node *prevptr = curptr->prev->prev;
                prevptr->next = curptr;
                curptr->prev = prevptr;
            }
            c = deterprev(curptr);
        }
    }
    
    
}
void dList :: decrease_fuel(int i, float f) {
    Node *ptr = arraypointer[i];
    ptr->fuel = ptr->fuel - f;
    char c = determine(ptr);
        while(c!='N') {
            //cout << endl;
            /*for(Node*ptr=head;ptr!=NULL;ptr=ptr->next) {
                cout << "Time: " << ptr->time << "\t";
                cout << "Fuel: " << ptr->fuel << endl;
            }*/
            if(ptr->prev == NULL) { //head
                //cout << "head\n";
                //cout << c << endl;
                if(c == 'G') {
                    if(ptr->next->next == NULL) {
                        
                        ptr->next = NULL;
                        tail = ptr;
                        
                        
                    }
                    else {
                        ptr->next->next->prev = ptr;
                        ptr->next = ptr->next->next;
                    }
                }
                else { // Dominated
                    ptr = ptr->next;
                    head = ptr;
                    ptr->prev = NULL;
                }
            }
            else if (ptr->next == NULL) { //tail
                
                if(c == 'G') {
                    ptr = ptr->prev->prev; // back to pervous
                }
                else { // Dominated
                    ptr = ptr->prev;
                    tail = ptr;
                    ptr->next = NULL;
                }
            }
            else { //other
                if(c == 'G') {
                    if(ptr->next->next == NULL) {
                        ptr->next = NULL;
                        tail = ptr;
                    }
                    else {
                        ptr->next->next->prev = ptr;
                        ptr->next = ptr->next->next;
                    }
                }
                else { // Dominated
                    ptr->next->prev = ptr->prev;
                    ptr=ptr->prev;
                    ptr->next = ptr->next->next;
                }
            }
            
            c = determine(ptr);
            
        }

}