#include <iostream>

using namespace std;

#include "dList.cpp"

 

int main(){

         const int size = 30;

        int count;

        float avTime[size] ={ 93, 99,93.1, 10,102, 97, 95, 50,100,  0.1,499, 94, 98, 92, 98, 92.9, 45, 98,499,200,278,105, 10,345,498,220, 96,196, 89, 30};

        float flEfficiency[size] ={194,201, 196,280,206,156,193,270,100,499.9,1,194,198,240,140,196.0,450,200, 40, 99,100,101,280,453,0.9,296,180,120,467,399};

        float* avgTime = new float[size];

        float* fuelEfficiency = new float[size];

        for(int i=0;i<size;i++){

            avgTime[i]= avTime[i];

            fuelEfficiency[i]= flEfficiency[i];

        }

             

             

        dList dl = dList(avgTime,fuelEfficiency,size);

        cout << "First Output"<<endl;

        dl.out('a');

                          

 

        dl.insert(50,300);

        count=dl.insert(110,75);

        cout <<endl<< "Second Output"<<endl;

        cout <<endl<< "Current number of inserts: "<< count<< endl;

        dl.out(10,'a');    

 

        for(int i=0;i<500000;i++) dl.insert(500 - .0009*i, 100 +(i/499999.0)+ .01*(15009 - ((i+22700)%25003)));

        cout << endl <<"Third Output"<<endl;

        dl.out();

 

        cout << endl << "Fourth Output"<<endl;

        dl.out(10,'d');

             

        count= dl.insert(0.1,0.1);

        cout << endl << "Fifth Output"<<endl;

        cout <<endl<< "Current Count is " << count <<endl;

        dl.out();

        return 0;

}