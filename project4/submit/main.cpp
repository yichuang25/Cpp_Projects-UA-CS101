#include<iostream>
#include<string>
#include<fstream>

using namespace std;

typedef struct _element {
    int letter;
    int freq;
    
    
}Element;

typedef struct _tree {
    char *huffman;
    int size;

    int letter;
    int value;
    int weight;
    char code;
    int lchild, rchild,parent;
}Tree;

class code {
    private:
        Element *list;
        Tree *tree;
        int capacity;
        int count;
        int root;

    public:
        code();
        void addlist (char letter);
        void print();
        void createtree();
        void inorder1();
        void preorder1();
        void code1(fstream *file);
        void createcode();

};

code :: code () {
    count = 0;
    capacity = 2;
    list = new Element[capacity];
}

void code :: addlist(char letter) {
    if(count == 0) { //empty list
        list[count].letter = letter;
        //cout << list[count].letter << endl;
        list[count].freq = 1;
        count++;
    }
    else {
        int index = -1;
        for(int i=0;i<count;i++) {
            if(list[i].letter == letter) {
                index = i;
            }
        }
        if(index == -1) {
            if(count == capacity) {
                capacity = 2 * capacity;
                //cout << "Doubling to " << capacity << endl;
                Element *temp ;
                temp = new Element[count];
                for(int i=0;i<count;i++) {
                    temp[i].freq = list[i].freq;
                    temp[i].letter = list[i].letter;
                }
                delete list;
                list = new Element[capacity];
                for(int i=0;i<count;i++) {
                    list[i].freq = temp[i].freq;
                    list[i].letter = temp[i].letter;
                }           
                
                delete temp;
            }
            list[count].letter = letter;
            //cout << list[count].letter << endl;
            list[count].freq = 1;

            count++;
            /*for(int i=0;i<count;i++) {
                cout << list[i].letter << "\t" << list[i].freq << endl;
            }*/
        }
        else {
            list[index].freq++;
        }
    }
}

void code :: print(){
    for(int i=0;i<count;i++) {
        cout << i << "\t" <<list[i].letter << "\t" << list[i].freq << endl;
    }
    cout << endl;
    
}
void select(Tree *tree, int n, int *s1, int *s2) {
    int min;
    for(int i=0;i<n;i++) {
        if(tree[i].parent == -1) {
            min = i;
            break;
        }
    }
    for(int i=0;i<n;i++) {
        if(tree[i].parent == -1) {
            if(tree[i].weight < tree[min].weight) {
                min = i;
            }
        }
    }
    *s1 = min;
    for(int i=0;i<n;i++) {
        if(tree[i].parent == -1 & i != *s1) {
            min = i;
        }
    }
    for(int i=0;i<n;i++) {
        if (tree[i].parent == -1 && i != *s1) {
            if(tree[i].weight < tree[min].weight) {
                min = i;
            }
        }
    }
    *s2 = min;
}

void code :: createtree() {
    //cout << count << endl;
    int m = 2 * count - 1;
    int s1;
    int s2;
    tree = new Tree[m+1];
    // import leaves
    for(int i=0;i<count;i++) {
        tree[i].letter = list[i].letter;
        tree[i].weight = list[i].freq;
        tree[i].code = 's';
        tree[i].value = list[i].letter;
        tree[i].lchild = -1;
        tree[i].rchild = -1;
        tree[i].parent = -1;
    }
    //import intersect
    for(int i=count;i<m;i++) {
        tree[i].weight = -1;
        tree[i].value = -1;
        tree[i].code = 'i';
        tree[i].lchild = -1;
        tree[i].rchild = -1;
        tree[i].parent = -1;
    }
    /*for(int i=0;i<m;i++) {
        cout << tree[i].weight << " " << tree[i].value << " " << tree[i].code << endl;
    }*/
    //printf("\n HuffmanTree: \n");
    for(int i=count;i<m;i++) {
        select(tree,i,&s1,&s2);
        //cout << i << "\t" << s1 << "\t" << s2 << endl;
        tree[s1].parent = i;
        tree[s2].parent = i;
        tree[i].lchild = s1;
        tree[i].rchild = s2;
        tree[i].weight = tree[s1].weight + tree[s2].weight;
        tree[i].value = 128 + (i-count);
    }
    root = m-1;
    /*
    //print
    cout << "index" << "\t" 
    << "Value" << "\t" 
    << "ASCII" << "\t" 
    << "Weight" << "\t" 
    << "Parent" << "\t" 
    << "Left" << "\t" 
    << "Right" << "\n";

    for(int i=0;i<m;i++) {
        cout << i << "\t" 
        << tree[i].code <<"\t"
        << tree[i].value << "\t" 
        <<tree[i].weight << "\t" 
        << tree[i].parent << "\t" 
        << tree[i].lchild << "\t" 
        << tree[i].rchild<< endl;
    }
    */
}

void code :: createcode() {
    for(int i=0;i<count;i++) {
        //initial 
        tree[i].size = 0;
        tree[i].huffman = new char[count];
        // find the code (Back)
        int start = i;
        int parent = tree[i].parent;
        //cout << tree[i].letter << endl;
        while (parent != -1) {
            if(start == tree[parent].lchild) {
                tree[i].huffman[tree[i].size] = '0';
                tree[i].size++;
            }
            else {
                tree[i].huffman[tree[i].size] = '1';
                tree[i].size++;
            }

            //cout << parent << endl;
            start = parent;
            parent = tree[parent].parent;
        }
        //cout << endl;
        /*cout << endl << tree[i].letter << endl;
        for(int j=tree[i].size-1;j>=0;j--) {
            cout << tree[i].huffman[j];
        }
        cout << endl;*/

    }
}

void printinorder1 (Tree *list, ofstream *file, int index) {
    if(index == -1 ) {
        return;
    }
    printinorder1(list,file,list[index].lchild);
    *file << list[index].code << " " << list[index].value << endl;
    printinorder1(list,file,list[index].rchild);
}
void code :: inorder1() {
    ofstream inorder1;
    inorder1.open("inorder1.txt",ios::trunc);
    printinorder1(tree,&inorder1, root);
    inorder1.close();
}

void printpreorder1 (Tree *list, ofstream *file, int index) {
    if(index == -1 ) {
        return;
    }
    *file << list[index].code << " " << list[index].value << endl;
    printpreorder1(list,file,list[index].lchild);
    printpreorder1(list,file,list[index].rchild);
}

void code :: preorder1() {
    ofstream preorder1;
    preorder1.open("preorder1.txt",ios :: trunc);
    printpreorder1(tree,&preorder1,root);
    preorder1.close();
}

void code :: code1(fstream *file) {
    ofstream code1;
    code1.open("code1.txt",ios::trunc);
    *file >> noskipws;
    int number = 0;
    char letter;
    while (! (file->eof())) {
        *file >> letter;
        if(file->fail()) {
            break;
        }
        //find letter
        int index;
        for(int i=0;i<count;i++) {
            if(letter == tree[i].letter) {
                index = i;
            }
        }
        for(int i=tree[index].size-1;i>=0;i--) {
            code1 << tree[index].huffman[i];
            number++;
        }
        //code1 << " ";
    }
    code1 << endl;
    cout << "Phase 1 code length: " << number << " bits\n";
    


    code1.close();
}

int main (int argc, char *argv[]) {
    code encode = code();
    fstream input;
    fstream read;
    input.open (argv[1]);
    read.open (argv[1]);
    if(!input.is_open()) {
        cout << "Can not open file.\n";
        return 1;
    }
    char letter;
    input >> noskipws;
    while (!input.eof()) {
        input >> letter;
        if (input.fail()){
            break;
        }
        int in = letter;
        //cout << in << endl;
        encode.addlist(letter);
    
    }
    
    //encode.print();
    encode.createtree();
    encode.createcode();
    encode.inorder1();
    encode.preorder1();
    encode.code1(&read);
    


    input.close();
    return 0;
}