// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2021/02/26 Hsien-Chia Chen]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i=1 ; i<data.size(); i++){
    	int key=data[i];
    	int j=i-1;
    	while (j>=0 && data[j]>key){
    	    data[j+1]=data[j];
    	    j=j-1;
    	}
    	data[j+1]=key;
    }      
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    if (low<high){
    
    int q=Partition( data,low,high);
    QuickSortSubVector(data, low, q-1);
    QuickSortSubVector(data, q+1,high);    
    }

    // Hint : recursively call itself
    //        Partition function is needed
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int x =data[high];
    int i =low-1;
    for (int j =low;j <high;j++){
        if (data[j]<=x){
            i=i+1;
            swap(data[j],data[i]);           
            }
            }
    data[high]=data[i+1];
    data[i+1]=x;
    return i+1; 
    
   // Hint : Textbook page 171
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    if (low<high){
        int q = (low+high)/2;
        MergeSortSubVector(data,low,q);
        MergeSortSubVector(data,q+1,high);
        Merge(data,low,q,q+1,high);
    }  
    // Hint : recursively call itself
    //        Merge function is needed
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    vector<int> L;
    vector<int> R;
    L.assign(data.begin()+low,data.begin()+middle1+1);
    R.assign(data.begin()+middle2,data.begin()+high+1);
    L.push_back(1000001);       
    R.push_back(1000001);
  
    int i=0;
    int j=0;
    for (int k=low;k<=high ;k++){
        if (L[i]<=R[j]){
            data[k]=L[i];
            i=i+1;
            }
        else {
            data[k]=R[j];
            j=j+1;
        }
    }    
}
// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    data.push_back(data[0]);
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
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
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
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
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size()-1; // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i=heapSize/2;i>=1;i--)
        MaxHeapify(data,i);
    
}
