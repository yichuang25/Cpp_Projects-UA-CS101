/*
* Name: Yichen Huang
* CWID: 11906882
* Course: CS-101-001
*
* Function of the program:
* 1. Read the text file by command argumment.(Uppercase change to the lowercase, digit and punct are convert to the blankspace and seperate two word)
* 2. Count the words in the file.
* 3. Find the unique word in the text.
* 4. Let user find the word their inout
* 5. If user's input contain '?', ? means is wildmatch can be any character and empty
*/

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <stdlib.h>
using namespace std;
typedef struct _word{
    char word[200];
    int freq;
    struct _word *next;
} Word;
Word *searchTerm(Word *head,char word[]) {
    for(Word *ptr=head;ptr!=NULL;ptr=ptr->next) {
        if(strcmp(ptr->word,word)==0) {
            return ptr;
        }
    }
    return NULL;
}

Word *findLast(Word *head) {
    for(Word *ptr=head;ptr!=NULL; ptr=ptr->next) {
        if (ptr->next==NULL) return ptr;
    }
    return NULL;
}
Word *addTerm (char word[] , Word* head) {
    Word *pnew = (Word*)malloc(sizeof(Word));
    pnew->freq = 1;
    strcpy(pnew->word,word);
    pnew->next = NULL;
    
    //cout << pnew->word << endl;
    //searchTerm
    Word *pExist = searchTerm(head,word);
    if (pExist != NULL) {
        pExist->freq++;
        return head;
    }
    
    if(head == NULL) {
        return pnew;
    }
    else {
        Word *pLast = findLast(head);
        pLast->next = pnew;
    }
    

    return head;
}

bool isMatch(char *search, char *need) {
    char *scur = search, *pcur = need, *sstop = NULL, *pstop = NULL;
    while (*scur) {
        //cout << *pcur << " " << *scur << endl;
        if (*scur == *pcur) {
            //cout << "1" << endl;
            ++scur;
            ++pcur;
        } 
        else if (*pcur == '?') {
           // cout << "2" << endl;
            pstop = pcur++;
            sstop = scur;
        } 
        else if (pstop) {
            //cout << "3" << endl;
            pcur = pstop + 1;
            scur = ++sstop;
        } 
        else {
            return false;
        }
    } 
    while (*pcur == '?') {
        ++pcur;
    }
    return !*pcur;
}


int main (int argc, char *argv[]) {
    char wordlist[20000][200];
    char input[200];

    // open the file
    if (argc != 2) {
        cout << "Usage: file" << endl;
        return 1;
    }
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.is_open()) {
        cout << "File open failed!" << endl;
        return 2;
    }

    //read the file
    int count = 0;
    int puncindex;
    int a;
    while(!infile.eof()) {
        infile >> input;
        if (infile.fail()){
            break;
        }
        puncindex = -1;
        a = -1;
        
        for (int i=0;i<(int)strlen(input);i++) {
            if(!isalpha(input[i])){ // has punct&num
                
                puncindex = i;
                a = i;
                
            }
            if (a>0 && a < (int)strlen(input)-1) { // in the middle
                if (isalpha(input[i+1]) && strlen(wordlist[count])!=0){
                    count++;
                }
                a = -1;
                //count++;
            }
            if (i != puncindex) {
                wordlist[count][i-(puncindex+1)] = input[i];
            }
            
        }
        if (strlen(wordlist[count])!=0) {
            count++;
        }
        
    }

    //change uppercase to lowercase
    for(int i=0;i<count;i++) {
        for(int j=0;j<(int)strlen(wordlist[i]);j++) {
            if(isupper(wordlist[i][j])) {
                wordlist[i][j] = wordlist[i][j] + 32;
            }
        }
    }
    /*for(int i=0;i<count;i++) {
        cout << wordlist[i] << " ";
    }
    cout << endl << count << endl;*/
    
    // build list
    Word *head = NULL;
    for (int i=0; i<count ;i++) {
        head = addTerm(wordlist[i],head);
        //cout << endl;
    }
    int unique=0;
    for(Word *ptr = head; ptr!=NULL;ptr=ptr->next) {
        unique++;
        //cout << ptr->word << " " << ptr->freq << endl;
    }
    cout << "The number of words find in the file was " << count << endl;
    cout << "The number of unique words found in the file was " << unique << endl;
    
    // let user input
    char wordneed[200];
    
    while (!feof(stdin)) {
        cout << "Please enter the a word: \n";
        cin >> wordneed;
        int appear =0;
        for(Word *ptr=head;ptr!=NULL;ptr=ptr->next) {
            
            if(isMatch(ptr->word,wordneed) == true) {
                
                //cout << "The word " << ptr->word << " appears " << ptr->freq << " times in the document\n";
                if(strlen(ptr->word)<=strlen(wordneed)){
                    appear++;
                    if(ptr->freq>1) {
                        cout << "The word " << ptr->word << " appears " << ptr->freq << " times in the document\n";
                    }
                    else {
                        cout << "The word " << ptr->word << " appears " << ptr->freq << " time in the document\n";
                    }
                }

                
            }
            
        }
        if(appear == 0) {
            cout << "The word " << wordneed << " do not appear in the document\n";
        }
        
    }


    
   
    



return 0;
}