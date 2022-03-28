#include <cstring>
#include <iostream>
#include <fstream>
#include<vector>
#include "../lib/tm_usage.h"

using namespace std;

void Max_PS(vector<int>& data,int data_size,vector<vector<int>>& M,vector<vector<int>>& N);
void Find_Max_PS(vector<int>& data,vector<vector<int>>& N,int i, int j, vector<int>& Choosed_Chord);
void BuildMaxHeap(vector<int>& data);
void MaxHeapify(vector<int>& data, int root);
void HeapSort(vector<int>& data);
int heapSize;

int main(int argc, char* argv[])
{
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //////////// read the input file /////////////
    tmusg.periodStart();
    
    char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    
    int num_left,num_right,data_size;
    vector<int> data;
    vector<int> data_left;
    vector<int> data_right;
    
    fin >> data_size;
    data_left.reserve(data_size/2);
    data_right.reserve(data_size/2);
    data.reserve(data_size);
    
    while (fin >> num_left >> num_right){
        data_left.push_back(num_left); 
        data_right.push_back(num_right); 
    }
    
    for (int i=0;i<data_size/2;i++){
        data[data_left[i]]=data_right[i];
        data[data_right[i]]=data_left[i];
    }   

    //start programming//
    
    vector<vector<int>> M(data_size,vector<int>(data_size));//mps in range
    vector<vector<int>> N(data_size,vector<int>(data_size));//choose or not
    vector<int> Choosed_Chord;
    
    Max_PS(data,data_size,M,N);//find mps in each range by it.
    Find_Max_PS(data,N,0,data_size-1,Choosed_Chord);//find each mps choosen
    
    //sort Choosed_Chord//
    HeapSort(Choosed_Chord);

    //record CPU time and Memory//
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    //////////// write the output file ///////////
    fout << M[0][data_size-1] <<endl;
    for (int i = 0; i < Choosed_Chord.size(); i++)
        fout << Choosed_Chord[i] << " " <<data[Choosed_Chord[i]] << endl;
    fin.close();
    fout.close();
    return 0;
}

void Max_PS(vector<int>& data,int data_size,vector<vector<int>>& M,vector<vector<int>>& N) {

    for (int l=1; l<data_size;l++){
        for (int i=0; i<data_size-l;i++){
            int j= i+l;
            int k=data[j];
            if (i>k || k>j){
                M[i][j]=M[i][j-1];
            }
            else if (k==i){
                M[i][j]=M[i+1][j-1]+1;
                N[i][j]=1; 
            }
            else {
                if ((M[i][j-1])>(M[i][k-1]+1+M[k+1][j-1]))
                    M[i][j]=M[i][j-1];
                else {
                    M[i][j]=M[i][k-1]+1+M[k+1][j-1]; 
                    N[i][j]=2; 
                }        
            }
        }
    }
}
    
void Find_Max_PS(vector<int>& data,vector<vector<int>>& N,int i, int j, vector<int>& Choosed_Chord) {

    while (i<j){
    
	int k=data[j];
	if (N[i][j]==2) {
	    Find_Max_PS(data,N,i,k-1,Choosed_Chord);
	    Find_Max_PS(data,N,k+1,j-1,Choosed_Chord);
	    Choosed_Chord.push_back(k); 
	    break;
	}
	else {
	    if (N[i][j]==1) {
	        Choosed_Chord.push_back(k); 
	    }
	    j--;
	}    
    }
}

//sort alg//

void HeapSort(vector<int>& data) {
    // Build Max-Heap
    data.push_back(data[0]);
    BuildMaxHeap(data);
    //HeapSort
	int tmp = 0;
    for (int i = data.size()-1 ; i >= 2; i--) {
		tmp = data[i];
		data[i] = data[1];
		data[1] = tmp;
        heapSize--;
        MaxHeapify(data,1);
    }

    data.erase(data.begin());
}

//Max heapify
void MaxHeapify(vector<int>& data, int root) {

    int L= 2*root;
    int R= 2*root+1;
    int largest;
    if (L<=heapSize && data[L]>data[root])
        largest= L;
    else 
        largest= root;
    if (R<=heapSize && data[R]>data[largest])
        largest= R;
    if (largest!=root){
        swap(data[root],data[largest]);
        MaxHeapify(data, largest);
    } 
}

//Build max heap
void BuildMaxHeap(vector<int>& data) {
    heapSize = data.size()-1; // initialize heap size

    for (int i=heapSize/2;i>=1;i--)
        MaxHeapify(data,i);
    
}

