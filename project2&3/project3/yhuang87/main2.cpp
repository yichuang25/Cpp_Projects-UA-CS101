#include <iostream>
using namespace std;
#include "dList.cpp"

int main(){
	const int size = 20;
    int count;
	float avgTime[size]={93,99,10,102,97,95,50,100,0.2,499,94,98.3,92.1,98,93.2,10.1,67.7,300,60,94.4};
	float fuelEfficiency[size] = {194,201,280,206,156,193,270,100,499.9,1,194.1,198,240,140,196.0,280,268,45,300,189.9};

	dList dl = dList(avgTime,fuelEfficiency,size);
	cout << "First Output"<<endl;
	dl.out('a');
	
	dl.increase_time(4,3.6);
	dl.increase_time(8,4.9);
	dl.decrease_time(2,8.6);
	dl.decrease_time(7,1.9);  
	
	cout << endl <<"Second Output"<<endl;
	dl.out('a');
	
    
	dl.decrease_fuel(19,2.6);
	dl.decrease_fuel(1,0.9);
	cout <<endl<< "Third Output"<<endl;
	dl.out('a');
	
	int x,y;
	for(int i=3;i<7;i++){
		x= dl.index_before(i);
		y= dl.index_after(i);
		cout << endl << "index before " << i << " is "<< x << endl;
		cout << endl << "index after " << i << " is "<< y << endl;
	}
	
	return 0;
}
