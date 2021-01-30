#include <iostream>
using namespace std;
#include "dList.cpp"

int main(){
	const int size = 20;
        int count;
	float avgTime[size]  =       {93,99,10,102,97,95,50,100,0.2,499,94,98.3,92.1,98,93.2,10.1,67.7,300,60,94.4};
	float fuelEfficiency[size] = {194,201,280,206,156,193,270,100,499.9,1,194.1,198,240,140,196.0,280,268,45,300,189.9};

	dList dl = dList(avgTime,fuelEfficiency,size);
	cout << "First Output"<<endl;
	dl.out('a');
	
	
        cout << endl << "Second Output"<<endl;
	dl.out('d');


	dl.insert(96,145);
        dl.insert(50,300);
	dl.insert(110,75);
	cout << endl <<"Third Output"<<endl;
	dl.out(5,'a');
	

	count= dl.insert(97,70);
	cout << endl << "Fourth Output"<<endl;
        cout <<endl<< "Current Count is " << count <<endl;
	dl.out();
	

	cout << endl << "Fifth Output"<<endl;
	dl.out(6,'d');
	return 0;
}
