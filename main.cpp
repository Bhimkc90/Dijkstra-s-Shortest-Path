// Dijkstra's Shortest Path by Bhim K C


#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


//************************* DijktraSSS CLASS *******************************/

class DijktraSSS {
public:
        int numNodes;
        int sourceNode;
        int minNode;
        int currentNode;
        int newCost;
        int **costMatrix;
        int *fatherArray;
        int *toDoArray;
        int *bestArray;
/*------------------ DijktraSSS Constructor -------------------------*/
   
   DijktraSSS(ifstream &inFile){
    inFile >> numNodes;
    costMatrix = new int*[numNodes+1];
    fatherArray = new int[numNodes+1];
    toDoArray = new int[numNodes+1];
    bestArray = new int[numNodes+1];

    for(int i = 1; i <=numNodes;i++){
        costMatrix[i] = new int [numNodes+1];
        bestArray[i] = 99999;

        for (int j = 1; j <= numNodes; j++){
            if(i == j){
                costMatrix[i][j] = 0; 
            }
            else{
                costMatrix[i][j] = 99999;
            }
        } 
    }


   }
/*------------------ Load Cost Matrix -------------------------*/

    void loadCostMatrix(ifstream &inFile){
        int src; 
        int dest; 
        int cost;
        while(!inFile.eof()){
            inFile >> src >> dest >> cost;
            costMatrix[src][dest] = cost;
        }
    }
/*------------------ Set best Array -------------------------*/
   
    void setBestArray(int sourceNode){
        for(int i=1;i<=numNodes;i++){
            bestArray[i] = costMatrix[sourceNode][i];
        }
    }
/*------------------ Set Father Array -------------------------*/

    void setFatherArray(int sourceNode){
        for(int i=1;i<numNodes+1;i++){
            fatherArray[i] = sourceNode;
        }
    }
/*------------------ Set ToDO Array-------------------------*/
   
    void setToDoArray(int sourceNode){
        for(int i=1;i<numNodes+1;i++){
            if(sourceNode == i)
                toDoArray[i] = 0;
            else
                toDoArray[i] = 1;
        }
    }
/*------------------ Find minimum Node -------------------------*/
    
    int findMinNode(){
        int minCost = 99999; 
        minNode = 0;
        int index = 1;

        while(index<=numNodes){
            if((toDoArray[index] == 1) && (bestArray[index] < minCost)){
                minCost = bestArray[index];
                minNode = index;
            }
            index++;
        }
        return minNode;
    }
/*------------------ Compute Cost -------------------------*/
    
    int computeCost(int minNode, int node){
        int totalCost;
        totalCost = bestArray[minNode] + costMatrix[minNode][node];
        return totalCost;
    }
/*------------------ Check ToDo Array -------------------------*/
    bool checkToDoArray(){
       for (int i = 1; i < numNodes + 1; i++){
           if(toDoArray[i]==1){
               return false; 
           }
       }
       return true;
    }


    
/*------------------ Debug Print -------------------------*/
    void debugPrint(ofstream &outFile){
        outFile << "The source node is: " << sourceNode <<endl;

        outFile << "The fatherAry is: ";
        for(int i=1;i<numNodes+1;i++)
            outFile << fatherArray[i] << " ";
        outFile<<endl;
        outFile << "The bestCost Array is: ";
        for(int i=1;i<numNodes+1;i++)
            outFile << bestArray[i] << " ";
        outFile<<endl;
        outFile << "The marked Array is: " ;
        for(int i=1;i<numNodes+1;i++)
            outFile << toDoArray[i] << " ";
        outFile<<endl<<endl;
    }
   
/*------------------ Print Shortest Path-------------------------*/
    void printShortestPath(int currentNode, int sourceNode, ofstream &SSSFile ){
        SSSFile << "The path from " << sourceNode << " to "<< currentNode <<": " << currentNode;
        int temp = currentNode;
        while(temp != sourceNode){
            SSSFile << " <- " << fatherArray[temp];
            temp = fatherArray[temp];
        }
        SSSFile << ":: cost = " << bestArray[currentNode] << endl;
    }


};


//************************* Main function *******************************/
int main(int argc, const char * argv[]) {
   
    ifstream inFile;
    ofstream SSSFile, debugFile;


    inFile.open(argv[1]); 
    SSSFile.open(argv[2], ofstream::out | ofstream::trunc);
    debugFile.open(argv[3], ofstream::out | ofstream::trunc);

    DijktraSSS dj(inFile);
    dj.loadCostMatrix(inFile);
    dj.sourceNode = 1;
    int childNode;


    while(dj.sourceNode <= dj.numNodes){
        dj.setBestArray(dj.sourceNode);
        dj.setFatherArray(dj.sourceNode);
        dj.setToDoArray(dj.sourceNode);

        while(!dj.checkToDoArray()){
            dj.minNode = dj.findMinNode();
            dj.toDoArray[dj.minNode] = 0;
            dj.debugPrint(debugFile);

            childNode = 1;

            while(childNode <= dj.numNodes){
            if(dj.toDoArray[childNode] == 1){
                dj.newCost = dj.computeCost(dj.minNode, childNode);
                if(dj.newCost < dj.bestArray[childNode]){
                    dj.bestArray[childNode] = dj.newCost;
                    dj.fatherArray[childNode] = dj.minNode;
                    dj.debugPrint(debugFile);
                }
            }
            childNode++;
            }
        }
        dj.currentNode = 1;
        SSSFile << endl;
        while(dj.currentNode <= dj.numNodes)
            dj.printShortestPath(dj.currentNode++, dj.sourceNode, SSSFile);
    dj.sourceNode++;
    }

    inFile.close();
    SSSFile.close();
    debugFile.close();

   return 0;
}


