#include <iostream>
using namespace std;
#include "dList.cpp"

int main(){
    	const int size = 1000000;
    	int count;
	float* avgTime = new float[size];
   	float* fuelEfficiency = new float[size];
   	for(int i=0;i<size;i++){
	   avgTime[i]= 100+i%47 - (i%10001)/251.1 - .000001*i;
	   fuelEfficiency[i]= 100 - i%91 + i%13 + .0001*i;
   	}
   	
	dList dl = dList(avgTime,fuelEfficiency,size);
	cout << "First Output"<<endl;
	dl.out('a');
	        

    	cout << endl << "Second Output"<<endl;
	dl.out(10,'d');

	count= dl.insert(97,70);
	cout << endl << "Third Output"<<endl;
        cout <<endl<< "Current Count is " << count <<endl;
	dl.out('d');


	for(int i=0;i<100;i++) dl.insert(10 - .00001*i, 50 *(i%10)+ .0001*i);
	cout << endl <<"Fourth Output"<<endl;
	dl.out();
	

	cout << endl << "Fifth Output"<<endl;
	dl.out(6,'d');
	return 0;
}
