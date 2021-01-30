#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct treenode {
    int data;
    string s;
    treenode *left, *right;
};

int location(treenode in[], treenode pre[], int pos) {
    int i=0;
    while(in[i].data != pre[pos].data || (pre[pos].data == -1 && in[i].data==-1 && in[i].s != pre[pos].s)) i++;
    return i;
}

treenode * treebuild(treenode pre[], treenode in[], int & pos, int size) {
    if (size==pos) return NULL;
    treenode *t = new treenode;
    t->data = pre[pos].data; t->left = NULL; t->right = NULL;
    if (t->data == -1) t->s = pre[pos].s;
    int loc = location(in, pre, pos++);
    in[loc].data = -2;
    if (loc > 0 && in[loc-1].data != -2) 
        t->left = treebuild(pre, in, pos, size);
    if (loc < size-1 && in[loc+1].data != -2) 
        t->right = treebuild(pre,in,pos, size);
    return t;
}

void parse(string c, treenode *t) {
    treenode *p = t;
    for(int pos=0; pos < c.length(); pos++) {
        p = c[pos]=='0' ? p->left : p->right;
        if (p->left == NULL) {
            cout << p->s;
            p = t;
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream prefile(argv[1]), infile(argv[2]), codefile(argv[3]);
    treenode pre[10000], in[10000];
    string read;
    char c;
    int j=0;
    while (getline(prefile,read)) {
        stringstream ss(read.substr(1));
        if (read[0]=='i') ss >> pre[j].data;
        if (read[0]=='s') {
            pre[j].data = -1;
            int ascii;  ss >> ascii; c = ascii;
            pre[j].s += c;
            if (ss >> ascii) {
                c = ascii;
                pre[j].s += c;
            }
        }
        j++;
    }
    j=0;
    while (getline(infile,read)) {
        stringstream ss((string) read.substr(1));
        if (read[0]=='i') ss >> in[j].data;
        if (read[0]=='s') {
            in[j].data = -1;
            int ascii;  ss >> ascii; c = ascii;
            in[j].s += c;
            if (ss >> ascii) {
                c = ascii;
                in[j].s += c;
            }
        }
        j++;
    }
    string code;
    getline(codefile,code);
    int pos = 0;
    treenode *tree = treebuild(pre,in,pos,j);
    parse(code,tree);
    cout << endl;
}
    