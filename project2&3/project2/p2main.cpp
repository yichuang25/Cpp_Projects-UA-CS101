#include <iostream>
using namespace std;
#include "dList.cpp"

int main(){
	const int size = 10;
	float avgTime[size]  =       {93, 99, 96, 97, 95,100, 94, 98, 92, 98};
	float fuelEfficiency[size] = {194,201,196,156,193,100,194,198,200,140};

	dList dl = dList(avgTime,fuelEfficiency,size);
	
	cout << "First Output"<<endl;
	dl.out('a');
	//  92, 93,  95,  97,  98, 100
	//200, 194, 193, 156, 140, 100

	dl.insert(96,145);
	
	cout << endl <<"Second Output"<<endl;
	dl.out('a');
	//  92, 93,  95,  96,  98, 100
	//200, 194, 193, 145, 140, 100

	dl.insert(50,300);
	dl.insert(110,75);
	cout <<endl<< "Third Output"<<endl;
	dl.out();
	// 50,  92,  93,  95,  96,  98, 100, 110
	//300, 200, 194, 193, 145, 140, 100,  75	

	dl.insert(97,70);
	cout << endl << "Fourth Output"<<endl;
	dl.out();
	// 50,  92,  93,  95,  96,  97
	//300, 200, 194, 193, 145,  70
	cout << endl << "Fifth Output"<<endl;
	dl.out('d');
	// 97,  96,  95,  93,  92,  50
	// 70, 145, 193, 194, 200, 300	
	return 0;
}

/*
Output should be:

First Output
Time 92  Fuel 200
Time 93  Fuel 194
Time 95  Fuel 193
Time 97  Fuel 156
Time 98  Fuel 140
Time 100  Fuel 100

Second Output
Time 92  Fuel 200
Time 93  Fuel 194
Time 95  Fuel 193
Time 96  Fuel 145
Time 98  Fuel 140
Time 100  Fuel 100

Third Output
Time 50  Fuel 300
Time 92  Fuel 200
Time 93  Fuel 194
Time 95  Fuel 193
Time 96  Fuel 145
Time 98  Fuel 140
Time 100  Fuel 100
Time 110  Fuel 75

Fourth Output
Time 50  Fuel 300
Time 92  Fuel 200
Time 93  Fuel 194
Time 95  Fuel 193
Time 96  Fuel 145
Time 97  Fuel 70

Fifth Output
Time 97  Fuel 70
Time 96  Fuel 145
Time 95  Fuel 193
Time 93  Fuel 194
Time 92  Fuel 200
Time 50  Fuel 300
*/