/*
Author: Harry Faust
Quick Sort with Hoare's Partition and Median of 3
CSCE350 
3.26.18
*/
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>
//#include <iostream>
//using namespace std;	//For testing output
using std::swap;

//note returns INDEX of median
template<typename T> inline
int medianOf3(T A[], int l, int r){
	//this is overcommented... also, try and avoid using pointers
	T* a = A + l;//array name is just pointer to 1st (0 index) elem., + l shifts l*(T size)
	T* b = A + l + (r-l)/2;//middle item... int division rounds down
	T* c = A + r;

	//when a is a pointer, *a is the dereference operator (gives value a points to)
	T* m;
	if(*a < *b){
		if(*b < *c) m=b; 
		else if(*c < *a) m=a;
		else m=c;
	} else{ //b <=a
		if(*a < *c) m=a;
		else if(*c < *b) m=b;
		else m=c;
	}
	return m-A; //m-A is the number of elements from A[0]

}

//remember: l and r are INLCUSIVE (just like Lomuto)
template<typename T>
int hoarePartition(T A[], int l, int r){
	//T p = A[l];
	//T p = medianOf3(A, l, r);
	int m = medianOf3(A , l , r);
	swap(A[m], A[l]);
	T p = A[l];
	int i = l;
	int j = r+1;		
	while(i < j)			//until i >= j
	{
		do {			
			i++;				
		} while( i < r  && A [i] < A[l]);	//until A[j] >= p
		do {	
			j--;
		} while(A[j] > A[l]);	//A[l} = p	until A[j] <= p
		
		swap(A[i],A[j]);
	}
//	if(A[i]>=A[j]){
	swap(A[i],A[j]);
//	}
	swap(A[l], A[j]);
	return j;	
}

template<typename T>
void quicksort(T A[], int l, int r){
	if(l<r){
		int pivot = hoarePartition(A, l ,r);
	//	int i, j;
/* //For testing output
for (int i = r - 1; i >= 0; i--) {
    cout << A[i];
    cout << '\n';
}
*/
		quicksort(A, l , pivot-1);
		quicksort(A, pivot+1, r);
	}
}


#endif
