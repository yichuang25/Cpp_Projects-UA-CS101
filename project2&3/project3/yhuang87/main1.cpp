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
	

    dl. increase_time(4,0.6);
	dl. increase_time(2,0.9);
	dl. decrease_time(6,0.6);
	dl. decrease_time(1,0.9);    
	cout << endl <<"Second Output"<<endl;
	dl.out('a');
	
    //dl. increase_fuel(3,0.6);
	//dl. increase_fuel(2,0.9);
	dl. decrease_fuel(3,0.6);
	dl. decrease_fuel(5,0.9);
	cout <<endl<< "Third Output"<<endl;
	dl.out('a');
	

	int count=0;
	count= dl.index_before(5);
    cout << endl << "index before 5 is "<< count << endl;
	
    count= dl.index_after(5);
	cout << endl << "index after 5 is "<< count << endl;
	
	count= dl.index_before(2);
    cout << endl << "index before 2 is "<< count << endl;
	
    count= dl.index_after(7);
	cout << endl << "index after 7 is "<< count << endl;
	
	cout <<endl<< "Final Output"<<endl;
	dl.out('d');
	

	return 0;
}

