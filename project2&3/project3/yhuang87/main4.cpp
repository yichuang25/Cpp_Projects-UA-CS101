#include <iostream>
using namespace std;
#include "dList.cpp"

int main(){
    const int size = 1000000;
    int count;
	float* avgTime = new float[size];
   	float* fuelEfficiency = new float[size];
   	for(int i=0;i<size;i++){
	   //avgTime[i]= 100+i%47 - (i%10001)/251.1 - .000001*i;
	   //fuelEfficiency[i]= 100 - i%41 + i%13 + .0001*i;
	   avgTime[i]= 100+i%47 - (i%10001)/251.1 - .000001*i;
	   fuelEfficiency[i]= 100 - i%91 + i%13 + .0001*i;
   	}
   	
	dList dl = dList(avgTime,fuelEfficiency,size);
	cout << "First Output"<<endl;
	dl.out('a');
	        

	int x,y,z;
	for(int i=50;i<100;i++){
		x = dl.index_before(i);
		y= dl.index_after(i*2);
		z= i*2;
		cout << endl << "index before " << i << " is "<< x << endl;
		cout << endl << "index after " << z << " is "<< y << endl;
	}
	
	return 0;
}
