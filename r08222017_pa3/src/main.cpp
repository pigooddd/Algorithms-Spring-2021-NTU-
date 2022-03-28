#include <cstring>
#include <iostream>
#include <fstream>
#include<vector>
#include<algorithm>

using namespace std;

//global variable
vector<vector<int>>Graph;//0:EdgeFrom,1:EdgeTo,2:Weight
int RunTimestest=0;//remain edges#
int TotalWeight=0;

//declare
void MST_Kruskal(int& VerticeNumber,int& EdgeNumber);
bool Sorting_Weight(vector<int>& w1,vector<int>& w2);
int Find_Set(int x,vector<int>&p);
void Link(int x,int y,vector<int>&p,vector<int>&rank);
//void Find_MFAS(int& VerticeNumber,int& EdgeNumber);
void Find_Candidate(int& VerticeNumber,int& EdgeNumber,vector<vector<int>>&FinalGraph);

//for test
//vector<vector<int>>NewNewGraph;


//main
int main(int argc, char* argv[])
{

    //////////// read the input file /////////////
    
    char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    
    char GraphType;
    int VerticeNumber, EdgeNumber;
        
    fin >> GraphType>>VerticeNumber>>EdgeNumber;   
    Graph.reserve(EdgeNumber);
    
    
    int EdgeFromValue, EdgeToValue, WeightValue;    
    while (fin>>EdgeFromValue>>EdgeToValue>>WeightValue){
       Graph.push_back(vector<int>{EdgeFromValue,EdgeToValue,WeightValue});
    }    
    
    //start programming//
    
    
    if (GraphType=='u'){//undirected graph
        MST_Kruskal(VerticeNumber,EdgeNumber);
    //////////// write the output file ///////////
        
    //formal
    
    fout <<TotalWeight<<endl;
    for (int i =0; i <EdgeNumber; i++){
        if (Graph[i][0]!=-1)//!=-1 
            fout<<Graph[i][0]<<" "<<Graph[i][1]<<" "<<Graph[i][2]<<endl;
        }
    fin.close();
    fout.close();
    }
    
    
    else{//directed graph     
        vector<vector<int>>FinalGraph(EdgeNumber,vector<int>(3,0));//0:EdgeFrom,1:EdgeTo,2:Weight
        
        //Find_MFAS(VerticeNumber,EdgeNumber);
        Find_Candidate(VerticeNumber,EdgeNumber,FinalGraph);
        
        
        
    //////////// write the output file ///////////
        
    //formal
    
    fout <<TotalWeight<<endl;
    //int xxx=0;
    for (int i =0; i <EdgeNumber; i++){
        if (FinalGraph[i][0]!=-1){//!=-1 
            fout<<FinalGraph[i][0]<<" "<<FinalGraph[i][1]<<" "<<FinalGraph[i][2]<<endl;
            //xxx+=FinalGraph[i][2];
            
            }
        }
        //cout<<xxx<<endl;
    fin.close();
    fout.close();
    
    
    //test NewGraph
    /*
    fout <<NewNewGraph.size()<<endl;
    for (int i =0; i <NewNewGraph.size(); i++){
    fout<<NewNewGraph[i][0]<<" "<<NewNewGraph[i][1]<<" "<<NewNewGraph[i][2]<<endl;
        }
    fin.close();
    fout.close();
    */
    
    
    
    
    }
    


    
    


    return 0;
}


//MST_Kruskal functions
void MST_Kruskal(int& VerticeNumber,int& EdgeNumber){
    
    //initiallize
    vector<int>p(VerticeNumber,0);//vertice's father
    vector<int>rank(VerticeNumber,0);
    for (int i=0;i<VerticeNumber;i++){
        p[i]=i;
    }
    
    //sort
    sort(Graph.begin(),Graph.end(),Sorting_Weight);
    
    //find maximum tree edge
    int i;
    for(i=EdgeNumber-1;i>-1&&RunTimestest<VerticeNumber-1;i--){
    
        if (Find_Set(Graph[i][0],p)!=Find_Set(Graph[i][1],p)){
            RunTimestest+=1;
            //Union
            Link(Find_Set(Graph[i][0],p),Find_Set(Graph[i][1],p),p,rank);
            Graph[i][0]=-1;//delete the edge
        }
        else{
            TotalWeight+=Graph[i][2];
        }
        
    }
    for (i;i>-1;i--){
        TotalWeight+=Graph[i][2];
    }//run out all of weight
    
}

bool Sorting_Weight(vector<int>& w1,vector<int>& w2){
    return w1[2]<w2[2];
}

int Find_Set(int x,vector<int>&p){
    if (x!=p[x]){
        p[x]=Find_Set(p[x],p);
    }
    return p[x];
}

void Link(int x,int y,vector<int>&p,vector<int>&rank){

    if (rank[x]>rank[y]){
        p[y]=x;   
    }
    else{
        p[x]=y;
        if (rank[x]==rank[y]){
            rank[y]+=1;      
        }
    }
}


//minimum feedback arc set problem

/*
void Find_MFAS(int& VerticeNumber,int& EdgeNumber){

    //for test
    vector<vector<int>>NewGraph;

    //choose one DAG direction
    int BackwardWeight=0;
    int ForewardWeight=0;
    
    for (int i=0;i<EdgeNumber;i++){

        if (Graph[i][2]>0){
            if (Graph[i][0]>Graph[i][1]){//backward
                BackwardWeight+=Graph[i][2];
            }
            else{//foreward
                ForewardWeight+=Graph[i][2];
            }
        }
        else{//negative
            TotalWeight+=Graph[i][2];
        }
    }


    //MST initiallize
    vector<int>p(VerticeNumber,0);//vertice's father
    vector<int>rank(VerticeNumber,0);
    for (int i=0;i<VerticeNumber;i++){
        p[i]=i;
    }
    //sort
    sort(Graph.begin(),Graph.end(),Sorting_Weight);

    
    //BackwardWeight,ForewardWeight->choose small one
    if (ForewardWeight>BackwardWeight){//BackwardWeight small

        TotalWeight+=BackwardWeight;
        for (int i=0;i<EdgeNumber;i++){

        if (Graph[i][2]>0){
            if (Graph[i][0]>Graph[i][1]){//backward
            }
            else{//foreward
                if (Find_Set(Graph[i][0],p)!=Find_Set(Graph[i][1],p)){
                    //Union
                    Link(Find_Set(Graph[i][0],p),Find_Set(Graph[i][1],p),p,rank);
                }
                NewGraph.push_back(Graph[i]);
                Graph[i][0]=-1;//leave edges
            }
        }
        }
    }
    else{//ForewardWeight small

        TotalWeight+=ForewardWeight;
       for (int i=0;i<EdgeNumber;i++){

        if (Graph[i][2]>0){
            if (Graph[i][0]>Graph[i][1]){//backward
                if (Find_Set(Graph[i][0],p)!=Find_Set(Graph[i][1],p)){
                    //Union
                    Link(Find_Set(Graph[i][0],p),Find_Set(Graph[i][1],p),p,rank);
                }
                NewGraph.push_back(Graph[i]);
                Graph[i][0]=-1;//leave edges
            }
            else{//foreward
            }
        }
        }
    }
    
  

    //MST

    int i;
    for(i=EdgeNumber-1;i>-1;i--){
    
        if ((Graph[i][0]!=-1)&&                                       (Find_Set(Graph[i][0],p)!=Find_Set(Graph[i][1],p))){
            NewGraph.push_back(Graph[i]);
            //Union
            Link(Find_Set(Graph[i][0],p),Find_Set(Graph[i][1],p),p,rank);
            Graph[i][0]=-1;//delete the edge
            TotalWeight-=Graph[i][2];
        }    
    }

}
*/

//Find_Candidate

void Find_Candidate(int& VerticeNumber,int& EdgeNumber,vector<vector<int>>&FinalGraph){

    //choose positive
    vector<vector<int>>GraphCandidate; 
    for (int i=0;i<EdgeNumber;i++){
        if (Graph[i][2]>0){
            GraphCandidate.push_back(Graph[i]);//positive weight
        }
    }



    //forloop
    
    for(double WeightWeight1=-1;WeightWeight1<1.1;WeightWeight1+=0.2){//0,1
    for(double WeightWeight2=-1;WeightWeight2<1.1;WeightWeight2+=0.5){//0,1
	
    
    //for test
    //vector<vector<int>>NewGraph;
    
    
    //vertice pruority
    vector<int>VerticeWeight(VerticeNumber,0);

    for (int i=0;i<GraphCandidate.size();i++){
        VerticeWeight[GraphCandidate[i][1]]-=GraphCandidate[i][2]*WeightWeight1;//*1.2
    	VerticeWeight[GraphCandidate[i][0]]+=GraphCandidate[i][2]*WeightWeight2;
    }
    
    //find neighbor
    vector<vector<int>> AdjacencyMatrix                      (VerticeNumber,vector<int>(VerticeNumber,0));
    vector<vector<int>> AdjacencyMatrixLocation                      (VerticeNumber,vector<int>(VerticeNumber,-1));
    for (int i=0;i<GraphCandidate.size();i++){
            AdjacencyMatrix[GraphCandidate[i][0]]               [GraphCandidate[i][1]]=GraphCandidate[i][2];
            AdjacencyMatrixLocation[GraphCandidate[i][0]]          [GraphCandidate[i][1]]=i;
    }
    
    //greedy choise
    vector<int>VerticeTransform(VerticeNumber,-1);
    vector<int>reVerticeTransform(VerticeNumber,-1);
    for (int i=0;i<VerticeNumber;i++ ){
    
        int MaxIndex=max_element    (VerticeWeight.begin(),VerticeWeight.end())-VerticeWeight.begin();
        //int MaxElement=*max_element    (VerticeWeight.begin(),VerticeWeight.end());
        
        VerticeTransform[MaxIndex]=i;
        reVerticeTransform[i]=MaxIndex;
        //cout <<MaxIndex<< " "<<i<<" "<<" "<<MaxElement<<endl;
        VerticeWeight[MaxIndex]=-1000001;
        for (int i=0;i<VerticeNumber;i++ ){
            if (AdjacencyMatrixLocation[MaxIndex][i]!=-1){
                VerticeWeight[i]+=AdjacencyMatrix[MaxIndex][i]*WeightWeight2;
                AdjacencyMatrixLocation[MaxIndex][i]=-1;
            }
            if (AdjacencyMatrixLocation[i][MaxIndex]!=-1){
                VerticeWeight[i]-=AdjacencyMatrix[i][MaxIndex]*WeightWeight1;//*1.2
                AdjacencyMatrixLocation[i][MaxIndex]=-1;
            }
        }
    }

    //find best graph
    vector<vector<int>>FindGraph(EdgeNumber,vector<int>(3,0));
    for (int i=0;i<EdgeNumber;i++){
    FindGraph[i]={VerticeTransform[Graph[i][0]],       VerticeTransform[Graph[i][1]],Graph[i][2]};
    }
    int FindTotalWeight=0;
    
    
 
    
    //choose one DAG direction
    int BackwardWeight=0;
    int ForewardWeight=0;
    
    for (int i=0;i<EdgeNumber;i++){

        if (FindGraph[i][2]>0){
            if (FindGraph[i][0]>FindGraph[i][1]){//backward
                BackwardWeight+=FindGraph[i][2];
            }
            else{//foreward
                ForewardWeight+=FindGraph[i][2];
            }
        }
        else{//negative
            FindTotalWeight+=FindGraph[i][2];
        }
    }







    //MST initiallize
    vector<int>p(VerticeNumber,0);//vertice's father
    vector<int>rank(VerticeNumber,0);
    for (int i=0;i<VerticeNumber;i++){
        p[i]=i;
    }
    //sort
    sort(FindGraph.begin(),FindGraph.end(),Sorting_Weight);

    
    //BackwardWeight,ForewardWeight->choose small one
    if (ForewardWeight>BackwardWeight){//BackwardWeight small

        FindTotalWeight+=BackwardWeight;
        for (int i=0;i<EdgeNumber;i++){

        if (FindGraph[i][2]>0){
            if (FindGraph[i][0]>FindGraph[i][1]){//backward
            }
            else{//foreward
                if (Find_Set(FindGraph[i][0],p)!=Find_Set(FindGraph[i][1],p)){
                    //Union
                    Link(Find_Set(FindGraph[i][0],p),Find_Set(FindGraph[i][1],p),p,rank);
                }
                //NewGraph.push_back(FindGraph[i]);
                FindGraph[i][0]=-1;//leave edges
            }
        }
        }
    }
    else{//ForewardWeight small

        FindTotalWeight+=ForewardWeight;
       for (int i=0;i<EdgeNumber;i++){

        if (FindGraph[i][2]>0){
            if (FindGraph[i][0]>FindGraph[i][1]){//backward
                if (Find_Set(FindGraph[i][0],p)!=Find_Set(FindGraph[i][1],p)){
                    //Union
                    Link(Find_Set(FindGraph[i][0],p),Find_Set(FindGraph[i][1],p),p,rank);
                }
                //NewGraph.push_back(FindGraph[i]);
                FindGraph[i][0]=-1;//leave edges
            }
            else{//foreward
            }
        }
        }
    }
    
  

    //MST

    int i;
    for(i=EdgeNumber-1;i>-1;i--){
    
        if ((FindGraph[i][0]!=-1)&&                                       (Find_Set(FindGraph[i][0],p)!=Find_Set(FindGraph[i][1],p))){
            //NewGraph.push_back(FindGraph[i]);
            //Union
            Link(Find_Set(FindGraph[i][0],p),Find_Set(FindGraph[i][1],p),p,rank);
            FindGraph[i][0]=-1;//delete the edge
            FindTotalWeight-=FindGraph[i][2];
        }    
    }
    
    //cout <<WeightWeight1<<","<<WeightWeight2<<" :"<<FindTotalWeight<<endl;
    if (FindTotalWeight<TotalWeight||TotalWeight==0){
        TotalWeight=FindTotalWeight;
    
    	//cout <<"update |up|"<<endl;
        for (int i=0;i<EdgeNumber;i++){
        if (FindGraph[i][0]!=-1)
            FinalGraph[i]={reVerticeTransform[FindGraph[i][0]],        reVerticeTransform[FindGraph[i][1]],FindGraph[i][2]};
            else
            FinalGraph[i][0]=-1;
        }
      /*  
    NewNewGraph.resize(NewGraph.size(),vector<int>{0,0,0});
    for (int i=0;i<NewGraph.size();i++){
    
    NewNewGraph[i][0]= reVerticeTransform[NewGraph[i][0]];
    NewNewGraph[i][1]= reVerticeTransform[NewGraph[i][1]];
    NewNewGraph[i][2]=NewGraph[i][2];
    
    
    }*/
    
    
    }
    
    

    
    //forloop
    }}

}
