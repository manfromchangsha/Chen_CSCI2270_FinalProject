#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <fstream>
#include <cstring>

using namespace std;


struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    string key;
	  bool visited;
    vector<adjVertex> adj;
    int distance;
    bool solved;
    vertex *parent;
};

class Airport
{
    public:
        Airport();
        ~Airport();
        void ReadFileAndBuildGraph();
        void addEdge(string v1, string v2, int weight);
        void addVertex(string name);
		    int ShortestDistance(string a,string b);
        void PrintAirportInfo(string airpot);
        void PrintPaths(string depart,string arrival);
        void printAllPathsUtil(string depart, string arrival, bool visited[],int path[], int &path_index);
		    int BFSFind(string start);
        vector<vertex> vertices;
    protected:
    private:
};

Airport::Airport(){
}

Airport::~Airport(){
}

int Airport::BFSFind(string start){
  bool foundStartVertex=false;
   for (int i=0;i<vertices.size(); i++){
        if (vertices[i].key == start){
            return i;
        }
   }
   cout<<"error"<<endl;
   return -1;
}

void Airport::PrintPaths(string depart,string arrival){
  // Mark all the vertices as not visited
    int V = vertices.size();
    bool *visited = new bool[V];
    // Create an array to store paths
    int *path = new int[V];
    int path_index = 0; // Initialize path[] as empty
    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++){
        visited[i] = false;}
    cout<<"depart1:"<<depart<<endl;
    cout<<"arrival1:"<<arrival<<endl;
    // Call the recursive helper function to print all paths
    printAllPathsUtil(depart, arrival, visited, path, path_index);
}

void Airport::printAllPathsUtil(string depart, string arrival, bool visited[],int path[], int &path_index)
{
    // Mark the current node and store it in path[]
    //cout<<"depart2:"<<depart<<endl;
    //cout<<"arrival2:"<<arrival<<endl;
    int u = BFSFind(depart);
    int d = BFSFind(arrival);
    visited[u] = true;
    path[path_index] = u;
    path_index++;
    cout<<vertices[10].adj[0].v->key<<endl;
    // If current vertex is same as destination, then print
    // current path[]
    if (u == d)
    {
        for (int i = 0; i<path_index; i++)
            cout << path[i] << " ";
        cout << endl;
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
           for(int i = 0; i < vertices.size(); i++)
        {
            if(vertices[i].adj.size() > 0)
            {
                for (int j = 0; j < vertices[i].adj.size(); j++)
                {

                   // printAllPathsUtil(vertices[i].adj[0].v->key, arrival, visited, path, path_index);
                    //cout<<vertices[i].adj[j].v->key<<endl;


                }
            }
        }
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}

void Airport::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].key == n){
            found = true;

        }
    }
    if(found == false){
        vertex v;
        v.key = n;
		v.visited = false;
		v.distance = 0;
        vertices.push_back(v);

    }
}

void Airport::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].key == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].key == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);

                }
            }
        }
    }
}



int Airport::ShortestDistance(string a,string b){
    vertex startV = vertices[BFSFind(a)];
    vertex endV = vertices[BFSFind(b)];
    startV.solved = true;
    startV.distance = 0;
    vector<vertex> solved ;
    solved.push_back(startV);
    //int count = 1;
    while(!endV.solved){
        int minDistance = 10000000;
        vertex *solvedV = NULL;
        vertex parent;
        //list<vertex>::iterator it = solved.begin();
        //cout<<"abdssfd"<<(*it).key<<endl;
        for(int x = 0; x < solved.size(); x++){
            vertex s = solved[x];
            for (int y = 0 ; y < s.adj.size() ; y++){

                if(!s.adj[y].v->solved){
                    int dist = s.distance + s.adj[y].weight;
                    if(dist < minDistance){
                        solvedV = s.adj[y].v;
                        minDistance = dist;
                        parent = s;
                    }
                }
            }
        }

        solvedV->distance = minDistance;
        solvedV->parent = &parent;
        solvedV->solved = true;

        solved.push_back(*solvedV);
        //count++;
    }

    return endV.distance;

}



struct AirportInfo{
  string Depart;
  string Arrival;
  string distance;
};

void Airport::ReadFileAndBuildGraph(){
  ifstream in;
  in.open("file.csv");
  vector<AirportInfo> airports;
  AirportInfo A;
  int index = 0;
  string temp,temp1,De,Ar,Ds;
  int count = 0;
  while(!in.eof()){
    getline(in,temp,'\n');
    istringstream input(temp);
    while(getline(input,temp1,',')){
      if (count == 0){
       A.Depart = temp1;
       count++;
      }
      if (count == 1){
       A.Arrival = temp1;
       count++;
      }
      else {
        A.distance = temp1;
        count++;
      }
    }
    count = 0;
    //vertices[index].push_back(A);
    //index ++ ;
    addVertex(A.Depart);
    addVertex(A.Arrival);
    addEdge(A.Depart,A.Arrival,stoi(A.distance));
}
}

int main(){
  Airport A;
  string a1,a2,air,dis;
  int option;
  do
     {
        cout << "======Main Menu======"<< endl;
        cout << "1. Build the whole graph from file"<< endl;
        cout << "2. Print all possiable paths between two airports"<< endl;
        cout << "3. Print the shortest between two airports"<< endl;
        cout << "4. Add an airport to the graph" << endl;
        cout << "5. Add connection between two airports" << endl;
        cout << "6. Quit" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            A.ReadFileAndBuildGraph();
            cout<<"==============================================="<<endl;
            cout<<"The file is imported and the graph was created!"<<endl;
            cout<<"==============================================="<<endl;
            break;
        case 2:
            cout << "Enter the first airport:"<< endl;
            getline(cin, a1);
            cout << "Enter the second airport:"<< endl;
            getline(cin, a2);
            A.PrintPaths(a1,a2);
            break;
        case 3:
          cout << "Enter the first airport:"<< endl;
          getline(cin,a1);
          cout << "Enter the first airport:"<< endl;
          getline(cin,a2);
          A.ShortestDistance(a1,a2);
          break;
        case 4:
          cout<<"Enter the airport you want to add: "<<endl;
          getline(cin,air);
          A.addVertex(air);
          break;

        case 5:
        cout << "Enter the first airport:"<< endl;
        getline(cin,a1);
        cout << "Enter the first airport:"<< endl;
        getline(cin,a2);
        cout << "Enter the distance:"<< endl;
        getline(cin,dis);
        A.addEdge(a1,a2,stoi(dis));
        break;
            }
        }
    while (option != 6);
    cout << "Goodbye!" << endl;

   return 0;


}
