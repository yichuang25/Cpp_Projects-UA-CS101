#include <iostream>
using namespace std;
#include "dList.cpp"

int main(){
	const int size = 10;
	float avgTime[size]  =       { 93, 96, 97, 95,100, 99, 101,92,98,102};
	float fuelEfficiency[size] = {194,186,156,193,120,138,113,200,148,102};

	dList dl = dList(avgTime,fuelEfficiency,size);
	cout << "First Output"<<endl;
	dl.out('a');
	

        
	cout << endl <<"Second Output"<<endl;
	dl.out('d');
	

	cout <<endl<< "Third Output"<<endl;
	dl.out(3,'a');
	

	dl.insert(50,300);
        dl.insert(110,75);
        cout << endl << "Fourth Output"<<endl;
	dl.out('d');
		

	dl.insert(87,201);
	cout << endl << "Fifth Output"<<endl;
	dl.out();
	

	return 0;
}

