#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "quicksort.h"

using namespace std;
using std::string;

/*
//MedianOf3 tests
TEST(med3_test_case123_1, med3_test){
	int A[3];
	A[0] = 1;
	A[1] = 2;
	A[2] = 3;
	string msg = "A = ["+to_string(A[0])+","+to_string(A[1])+","+to_string(A[2])+"]\n";
	EXPECT_EQ(1,medianOf3(A,0,2))<<msg;
}

TEST(med3_test_case213_0, med3_test){
	int A[3];
	A[0] = 2;
	A[1] = 1;
	A[2] = 3;
	string msg = "A = ["+to_string(A[0])+","+to_string(A[1])+","+to_string(A[2])+"]\n";
	EXPECT_EQ(0,medianOf3(A,0,2))<<msg;
}

TEST(med3_test_case231_0, med3_test){
	int A[3];
	A[0] = 2;
	A[1] = 3;
	A[2] = 1;
	string msg = "A = ["+to_string(A[0])+","+to_string(A[1])+","+to_string(A[2])+"]\n";
	EXPECT_EQ(0,medianOf3(A,0,2))<<msg;
}

TEST(med3_test_case221_01, med3_test){
	int A[3];
	A[0] = 2;
	A[1] = 2;
	A[2] = 1;
	string msg = "A = ["+to_string(A[0])+","+to_string(A[1])+","+to_string(A[2])+"]\n";
	int m = medianOf3(A,0,2);
	EXPECT_TRUE(m==1||m==0)<<msg;
}


TEST(med3_test_case222_012, med3_test){
	int A[3];
	A[0] = 2;
	A[1] = 2;
	A[2] = 2;
	string msg = "A = ["+to_string(A[0])+","+to_string(A[1])+","+to_string(A[2])+"]\n";
	int m = medianOf3(A,0,2);
	EXPECT_TRUE(m==2||m==1||m==0)<<msg;
}
*/

template<typename T>
bool validPartition(T A[], int l, int r, int s){
	T p = A[s];
	for(int i = l;i<s;++i){
		if(A[i]>p) return false;
	}
	for(int i = s+1;i<=r;++i){
		if(A[i]<p)return false;
	}
	return true;
}

TEST(hoare_no_dup, hoare_test){
	int A[7]={1,2,3,4,5,6,7};
	int s = hoarePartition(A,0,6);
	ASSERT_EQ(s,3)<<"Your split position is in the wrong place";
	ASSERT_TRUE(validPartition(A,0,6,s));

}

TEST(hoare_no_dup_rev, hoare_test){
	int A[7]={7,6,5,4,3,2,1};
	int s = hoarePartition(A,0,6);
	ASSERT_EQ(s,3)<<"Your split position is in the wrong place";
	ASSERT_TRUE(validPartition(A,0,6,s));

}

TEST(hoare_dups, hoare_test){
	int A[7]={1,4,1,3,2,3,2};
	int s = hoarePartition(A,0,6);
	ASSERT_TRUE(s==2||s==3)<<"Your split position is in the wrong place";
	ASSERT_TRUE(validPartition(A,0,6,s));

}

TEST(hoare_rand, hoare_test){
	srand(time(0));
	const int arr_sz = 20;
	for(int i = 0;i<300;++i){
		int A[arr_sz];
		for(int j=0;j<arr_sz;++j){
			A[j] = rand()%15;
		}
		int orig_A[arr_sz];
		for(int j = 0; j<arr_sz;++j){
			orig_A[j] = A[j];
		}
		int l = rand()%5;
		int r = rand()%5+(arr_sz-5);//15-19

		int s = hoarePartition(A,l,r);
		string arr_cmp;
		arr_cmp+="\nA (yours):[";
		for(int j = 0;j<arr_sz;++j) arr_cmp+=to_string(A[j])+",";
		arr_cmp+="]\n";
		arr_cmp+="\nA (orig.):[";
		for(int j = 0;j<arr_sz;++j) arr_cmp+=to_string(orig_A[j])+",";
		arr_cmp+="]\n";
		arr_cmp+="Your code returned s=" + to_string(s)+"\n";
		arr_cmp+="l=" + to_string(l)+"\n";
		arr_cmp+="r=" + to_string(r)+"\n";

		ASSERT_TRUE(validPartition(A,l,r,s))<<"Invalid Partition on random test" <<arr_cmp;

	}
}

TEST(quicksort_just_1,quicksort_test){
	int A[1]={42};

	ASSERT_NO_THROW(quicksort(A,0,0))<<"Your code threw an exception on a single item subarray";
	ASSERT_EQ(A[0],42)<<"On a single item array, no exception BUT changed array";
}

TEST(quicksort_rand,quicksort_test){
	srand(time(0));
	const int arr_sz = 20;
	for(int i = 0;i<300;++i){
		int A[arr_sz];
		int A_lib_sorted[arr_sz];
		for(int j=0;j<arr_sz;++j){
			A[j] = rand()%15;
		}
		int orig_A[arr_sz];
		for(int j = 0; j<arr_sz;++j){
			orig_A[j] = A[j];
			A_lib_sorted[j] = A[j];
		}
		std::sort(A_lib_sorted, A_lib_sorted + arr_sz);

		ASSERT_NO_THROW(quicksort(A,0,arr_sz-1))<<"Your code threw an exception (probably segmentation fault)";

		string arr_cmp;
		arr_cmp+="\nA ( yours):[";
		for(int j = 0;j<arr_sz;++j) arr_cmp+=to_string(A[j])+",";
		arr_cmp+="]\n";
		arr_cmp+="\nA (target):[";
		for(int j = 0;j<arr_sz;++j) arr_cmp+=to_string(A_lib_sorted[j])+",";
		arr_cmp+="]\n";
		arr_cmp+="\nA ( orig.):[";
		for(int j = 0;j<arr_sz;++j) arr_cmp+=to_string(orig_A[j])+",";
		arr_cmp+="]\n";

		
		for(int j = 0;j<arr_sz;++j){
			ASSERT_EQ(A[j],A_lib_sorted[j]) << "Your code doesn't properly sort:\n"<<arr_cmp;
		}

	}	
}



