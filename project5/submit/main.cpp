#include<iostream>
#include<fstream>
#include<stdlib.h>
//#include<bits/stdc++.h>

using namespace std;



typedef struct _egde {
    int start;
    int end;
    int cost;
    int time;   
}Edge;

typedef struct _vertex {
    Edge *adj;
    int count;
    int time;
    int cost;
    int prev;
    int *path;
    int length;
}Vertex;

class Graph{
    private:
        int edgeCount;
        int vertexCount;
        int totalcost;
        Edge *edgelist;
        Vertex *vertexlist;
    public:
    Graph(int cost, int edge, int vertex);
    void insertedge(int index, int from, int to, int cost, int time);
    void printedge();
    void bellman_ford(int start,int end, int budget);
    void printvertex();
    void result(int end);


};
Graph :: Graph(int cost, int edge, int vertex) {
    totalcost = cost;
    edgeCount = edge;
    vertexCount = vertex;
    edgelist = new Edge[edge];
    vertexlist = new Vertex[vertex];
    for (int i=0;i<vertexCount;i++) {
        vertexlist[i].time = INT_MAX;
        vertexlist[i].cost = -1;
        vertexlist[i].prev = -1;
        vertexlist[i].adj = new Edge[edgeCount];
        vertexlist[i].count = 0;
    }   
}

void Graph :: insertedge (int index, int from, int to, int price, int time) {
    
    edgelist[index].start = from;
    edgelist[index].end = to;
    edgelist[index].cost = price;
    edgelist[index].time = time;
    //add to vertex
    vertexlist[from].adj[vertexlist[from].count] = edgelist[index];
    vertexlist[from].count++;


}

void Graph :: printedge() {
    cout << "Index" << "\t"
        << "start" <<"\t"
        << "end" <<"\t"
        << "cost" <<"\t"
        << "time" <<endl;
    for(int i=0;i<edgeCount;i++) {
        cout << i << "\t"
            << edgelist[i].start << "\t"
            << edgelist[i].end << "\t"
            << edgelist[i].cost << "\t"
            << edgelist[i].time << endl;
    }
}

void Graph :: printvertex () {
    //cout <<vertexCount << endl;
    cout << "Index" << "\t"
        << "prev" <<"\t"
        << "cost" <<"\t"
        << "time" << "\t"
        << "count" <<endl;
    for(int i=0;i<vertexCount;i++) {
        cout << i << "\t"
            << vertexlist[i].prev << "\t"
            << vertexlist[i].cost << "\t"
            << vertexlist[i].time << "\t"
            << vertexlist[i].count << endl;
            
    }
    cout << endl;
}

void Graph :: bellman_ford (int start,int end, int budget) {
    int v = vertexCount;
    int e = edgeCount;
    for(int i=0;i<v;i++) {
        vertexlist[i].time = INT_MAX;
        vertexlist[i].cost = 0;
        vertexlist[i].prev = -1;
        vertexlist[i].length = 0;
        vertexlist[i].path = new int[vertexCount - 1];
    }
    // set 0
    vertexlist[start].time = 0;
    vertexlist[start].cost = 0;
    vertexlist[start].prev = -1;

    int duration,cost;
    for(int i=1;i<v;i++) {
        for(int j=0;j<v;j++) {
            for(int k=0;k<vertexlist[j].count;k++) {
                //Vertex adjVer = vertexlist[curVer.adj[k].end];
                //cout << curVer.adj[k].end << endl;
                duration = vertexlist[j].adj[k].time;

                cost = vertexlist[j].adj[k].cost;
                int altercost = vertexlist[j].cost + cost;
                //cout << altercost << endl;
                int altertime = vertexlist[j].time + duration;
                if((vertexlist[j].time != INT_MAX) && (altertime < vertexlist[vertexlist[j].adj[k].end].time) && (altercost <= budget) ) {
                    //cout << altercost << endl;
                    //cout << altertime << endl<< endl;
                    vertexlist[vertexlist[j].adj[k].end].time = altertime;
                    vertexlist[vertexlist[j].adj[k].end].cost = altercost;
                    vertexlist[vertexlist[j].adj[k].end].prev = j;
                    //add path to the vertex
                    vertexlist[vertexlist[j].adj[k].end].length = 0;
                    delete(vertexlist[vertexlist[j].adj[k].end].path);
                    vertexlist[vertexlist[j].adj[k].end].path = new int[vertexCount - 1];
                    Vertex cur = vertexlist[vertexlist[j].adj[k].end];
                    while (cur.prev != -1) {
                        vertexlist[vertexlist[j].adj[k].end].path[vertexlist[vertexlist[j].adj[k].end].length] = cur.prev;
                        vertexlist[vertexlist[j].adj[k].end].length++;
                        cur = vertexlist[cur.prev];
                    }
                    
                    

                }

            }
        }
    }


    /*int v = vertexCount;
    int e = edgeCount;
    //initial time
    for(int i=0;i<v;i++) {
        vertexlist[i].time = INT_MAX;
        vertexlist[i].cost = -1;
        vertexlist[i].prev = -1;
    }
    // set 0
    vertexlist[start].time = 0;
    vertexlist[start].cost = 0;
    Edge edge;
    int a,b,duration,cost;
    for(int i=1;i<v;i++) {
        for(int j=0;j<e;j++) {
            edge = edgelist[j];
            a = edgelist[j].start;
            b = edgelist[j].end;
            duration = edgelist[j].time;
            cost = edgelist[j].cost;
            int altercost = vertexlist[a].cost + cost;
            int altertime = vertexlist[a].time + duration;
            //cout << endl << a << "\t" << b << "\t" << cost << "\t" << duration << endl;
            if(vertexlist[a].time != INT_MAX) {
                if( (altercost <= budget)) {
                    //cout << endl << a << "\t" << b << "\t" << cost << "\t" << duration << endl;
                    if ((altertime < vertexlist[b].time) || (altercost < vertexlist[b].cost) ) {
                        cout << endl << a << "\t" << b << "\t" << cost << "\t" << duration << endl;
                        //cout << vertexlist[3].time << endl;
                        vertexlist[b].time = altertime;
                        vertexlist[b].cost = altercost;
                        vertexlist[b].prev = a;
                        //cout << vertexlist[3].time << endl << endl;
                    }
                }
            }
        }
        //printvertex();
    }*/
}

void Graph :: result (int end) {
    int cost = vertexlist[end].cost;
    int duration = vertexlist[end].time;
    //cout << end;
    int count = 1;
    int path[vertexCount];
    path[0] = end;
    if (duration == INT_MAX) {
        cout << "No path" << endl;

    }
    else {
        cout << "Cost " << cost << " " << "Duration " << duration << endl;
        Vertex ptr = vertexlist[end];
        //cout << vertexlist[end].length << endl;
        for (int i=ptr.length-1;i>=0;i--) {
            cout << ptr.path[i] << ", ";
        }
        cout << end << endl;
    }
}



int main (int argc, char *argv[]) {
    fstream input;
    input.open(argv[1]);
    if(!input.is_open()) {
        cout << "Can not open file.\n";
        return 1;
    }
    //cout << argc << endl;
    if(argc < 3) {
        cout << "Error!" << endl;
        return 2;
    }
    int start = atoi(argv[2]);
    int finish = atoi(argv[3]);
    int cost = atoi(argv[4]);
    
    int vertex;
    input >> vertex;
    int edge;
    input >> edge;
    
    //add edge
    Graph graph = Graph(cost, edge, vertex);
    int end;
    //graph.printvertex();
    for(int i=0;i<edge;i++) {
        int from;
        input >> from;
        int dest;
        input >> dest;
        end = dest;
        int price;
        input >> price;
        int duration;
        input >> duration;
        //cout << from << " " << dest << " " << price << " " << duration << endl;
        graph.insertedge(i,from,dest,price,duration);
    }
    //graph.printedge();
    //graph.printvertex();
    graph.bellman_ford(start,finish,cost);
    //graph.printvertex();
    graph.result(finish);
    

    input.close();
    return 0;
}