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

};

void split(Node* head,Node** a,Node** b) {
	Node* slow = head;
	Node* fast = head->next;

	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	*b = slow->next;
	slow->next = NULL;
}


Node* merge(Node* a,Node* b) {
	// Base cases
	if (a == NULL)
		return b;

	if (b == NULL)
		return a;

	// Pick either a or b, and recur
	if (a->time <= b->time) {
		a->next = merge(a->next, b);
		a->next->prev = a;
		a->prev = NULL;
		return a;
	}
	else {
		b->next = merge(a, b->next);
		b->next->prev = b;
		b->prev = NULL;
		return b;
	}
}

// Function to sort a doubly linked list using merge sort algorithm
void mergeSort(Node** head) {
	// base case: 0 or 1 node
	if (*head == NULL || (*head)->next == NULL)
		return;

	// split head into 'a' and 'b' sublists
	Node *a = *head, *b = NULL;
	split(*head, &a, &b);

	// recursively sort the sub-lists
	mergeSort(&a);
	mergeSort(&b);

	// merge the two sorted lists together
	*head = merge(a, b);
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
        mergeSort(&head);
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