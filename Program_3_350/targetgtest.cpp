#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "Graph.h"

using namespace std;
using std::string;
using std::vector;
using Graphs::adjMatrix2String;

typedef Graphs::DirectedWeightedGraph<int,double> DWG;
typedef Graphs::DirectedWeightedGraph<string,double> sDWG;
typedef Graphs::DirectedEdge<int,double> DE;
typedef vector<vector<double> > AdjMat;
typedef vector<vector<bool  > > BAdjMat;


sDWG build_8_11(){
	sDWG g;
	g.addVertex("a");
	g.addVertex("b");
	g.addVertex("c");
	g.addVertex("d");
		//g.
	g.addEdge("a","b",1.0);
	g.addEdge("b","d",1.0);
	g.addEdge("d","a",1.0);
	g.addEdge("d","c",1.0);
	return g;
}

TEST(ex_8_11_Warshalls, ex_8_11){
	sDWG g = build_8_11();
	BAdjMat R0=g.getBooleanAdjacencyMatrix();
	string s = adjMatrix2String(g.getVertices(),R0);
	stringstream ss;
	ss<<"Ex_8_11_Warshalls message:\n";
	ss<<s;
	BAdjMat Rf = g.getTransitiveClosure();
	string sRf = adjMatrix2String(g.getVertices(),Rf);
	ss <<"\nTransitive Closure=\n"<<sRf;
	
	BAdjMat gtRf;//gt == ground truth
	vector<string> vs = g.getVertices();
	for(string v:vs){
		vector<bool> trues;
		for(string v:vs){
			trues.push_back(true);
		}
		gtRf.push_back(trues);
	}
	for(int i =0;i<gtRf.size();++i){
		gtRf[2][i]=false;
	}
	string sgtRf = adjMatrix2String(g.getVertices(),gtRf);
	ss <<"\nTarget Transitive Closure=\n"<<sgtRf;
	bool match = true;
	ASSERT_EQ(gtRf.size(),Rf.size())
	 	<<"Your 1st dimension of the Adj.Matrix doesn't match target";
	for(int i = 0;i<gtRf.size();++i){
		ASSERT_EQ(gtRf[i].size(),Rf[i].size()) 
				<<"Your 2nd dimension of the Adj.Matrix doesn't match target (on row "<<i<<")";
		for(int j=0;j<gtRf[i].size();++j){
			if(gtRf[i][j]!=Rf[i][j]) match = false;
			ASSERT_TRUE(match)<<"Your result doesn't match target at "<<"["<<i<<","<<j<<"]\n"<<ss.str();
		}
	}
	
}

sDWG build_Warshalls_ex_1(){
	sDWG g;
	g.addVertex("a");
	g.addVertex("b");
	g.addVertex("c");
	g.addVertex("d");
	g.addVertex("e");
	g.addEdge("b","a",1.0);
	g.addEdge("b","c",1.0);
	g.addEdge("d","b",1.0);
	g.addEdge("d","c",1.0);
	g.addEdge("e","a",1.0);
	g.addEdge("e","d",1.0);
	return g;
}

TEST(run_Slides_War_1, run_slides_War_1){
	sDWG g=build_Warshalls_ex_1();
	BAdjMat R0=g.getBooleanAdjacencyMatrix();
	stringstream ss;
	string s = adjMatrix2String(g.getVertices(),R0);
	ss<<s;
	BAdjMat Rf = g.getTransitiveClosure();
	string sRf = adjMatrix2String(g.getVertices(),Rf);
	ss <<"\nTransitive Closure=\n"<<sRf;

	BAdjMat gtRf;//gt == ground truth
	vector<string> vs = g.getVertices();
	for(string v:vs){
		vector<bool> falses;
		for(string v:vs){
			falses.push_back(false);
		}
		gtRf.push_back(falses);
	}
	gtRf[1][0] = true;
	gtRf[1][2] = true;
	gtRf[3][0] = true;
	gtRf[3][1] = true;
	gtRf[3][2] = true;
	gtRf[4][0] = true;
	gtRf[4][1] = true;
	gtRf[4][2] = true;
	gtRf[4][3] = true;
	string sgtRf = adjMatrix2String(g.getVertices(),gtRf);
	ss <<"\nTarget Transitive Closure=\n"<<sgtRf;
	bool match = true;
	ASSERT_EQ(gtRf.size(),Rf.size())
	 	<<"Your 1st dimension of the Adj.Matrix doesn't match target";
	for(int i = 0;i<gtRf.size();++i){
		ASSERT_EQ(gtRf[i].size(),Rf[i].size()) 
				<<"Your 2nd dimension of the Adj.Matrix doesn't match target (on row "<<i<<")";
		for(int j=0;j<gtRf[i].size();++j){
			if(gtRf[i][j]!=Rf[i][j]) match = false;
			ASSERT_TRUE(match)<<"Your result doesn't match target at "<<"["<<i<<","<<j<<"]\n"<<ss.str();
		}
	}
}

/*
DWG build_Floyd_Slide_1(){
	DWG g;
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	g.addEdge(1,3,3.0);
	g.addEdge(2,1,2.0);
	g.addEdge(3,2,7.0);
	g.addEdge(3,4,1.0);
	g.addEdge(4,1,6.0);
	return g;
}
*/

//this one is with numbers
sDWG build_Floyd_Slide_1(){
	sDWG g;
	g.addVertex("a");
	g.addVertex("b");
	g.addVertex("c");
	g.addVertex("d");
	g.addVertex("e");
	g.addEdge("b","a",3.0);
	g.addEdge("b","c",2.0);
	g.addEdge("d","b",7.0);
	g.addEdge("d","c",6.0);
	g.addEdge("e","a",1.0);
	g.addEdge("e","d",2.0);
	return g;
}

bool doubleEquals(double a,double b){
	if( abs(a-b)<1e-10 ) return true;
	else return false;
}

TEST(test_Floyd_slide_1,run_Floyd_1){
	sDWG g = build_Floyd_Slide_1();
	AdjMat AM = g.getAdjacencyMatrix();
	string s = adjMatrix2String(g.getVertices(),AM);
	stringstream ss;
	ss<<s;
	AdjMat Df = g.getAllPairsShortestPaths();
	string sDf = adjMatrix2String(g.getVertices(),Df);
	ss <<"\nAll-Pairs ShortestPaths\n"<<sDf<<endl;

	AdjMat gtDf;//gt == ground truth
	vector<string> vs = g.getVertices();
	for(string v:vs){
		vector<double> infs;
		for(string v:vs){
			infs.push_back(std::numeric_limits<double>::infinity());
		}
		gtDf.push_back(infs);
	}
	for(int i=0;i<vs.size();++i) 
		gtDf[i][i] = 0.0;

	gtDf[1][0] = 3.0;
	gtDf[1][2] = 2.0;
	gtDf[3][0] = 10.0;
	gtDf[3][1] = 7.0;
	gtDf[3][2] = 6.0;
	gtDf[4][0] = 1.0;
	gtDf[4][1] = 9.0;
	gtDf[4][2] = 8.0;
	gtDf[4][3] = 2.0;

	string sgtDf = adjMatrix2String(g.getVertices(),gtDf);
	ss <<"\nTarget All-Pairs ShortestPaths=\n"<<sgtDf;
	bool match = true;
	ASSERT_EQ(gtDf.size(),Df.size())
	 	<<"Your 1st dimension of the Adj.Matrix doesn't match target";
	for(int i = 0;i<gtDf.size();++i){
		ASSERT_EQ(gtDf[i].size(),Df[i].size()) 
				<<"Your 2nd dimension of the Adj.Matrix doesn't match target (on row "<<i<<")";
		for(int j=0;j<gtDf[i].size();++j){
			if(gtDf[i][j]!=Df[i][j]) match = false;
			ASSERT_TRUE(match)<<"Your result doesn't match target at "<<"["<<i<<","<<j<<"]\n"<<ss.str();
		}
	}
}

sDWG build_floyd_slide_2(){
	sDWG g;
	g.addVertex("a");
	g.addVertex("b");
	g.addVertex("c");
	g.addVertex("d");
	g.addEdge("a","c",3.0);
	g.addEdge("b","a",2.0);
	g.addEdge("c","b",7.0);
	g.addEdge("c","d",1.0);
	g.addEdge("d","a",6.0);
	return g;
}

TEST(test_Floyd_slide_2,run_Floyd_2){
	sDWG g = build_floyd_slide_2();
	AdjMat AM = g.getAdjacencyMatrix();
	string s = adjMatrix2String(g.getVertices(),AM);
	stringstream ss;
	ss<<s;
	AdjMat Df = g.getAllPairsShortestPaths();
	string sDf = adjMatrix2String(g.getVertices(),Df);
	ss <<"\nAll-Pairs ShortestPaths\n"<<sDf<<endl;

	AdjMat gtDf;//gt == ground truth
	vector<string> vs = g.getVertices();
	for(string v:vs){
		vector<double> zeroes;
		for(string v:vs){
			zeroes.push_back(0.0);
		}
		gtDf.push_back(zeroes);
	}
	gtDf[0][1] = 10.0;
	gtDf[0][2] = 3.0;
	gtDf[0][3] = 4.0;
	gtDf[1][0] = 2.0;
	gtDf[1][0] = 2.0;
	gtDf[1][2] = 5.0;
	gtDf[1][3] = 6.0;
	gtDf[2][0] = 7.0;
	gtDf[2][1] = 7.0;
	gtDf[2][3] = 1.0;
	gtDf[3][0] = 6.0;
	gtDf[3][1] = 16.0;
	gtDf[3][2] = 9.0;
	string sgtDf = adjMatrix2String(g.getVertices(),gtDf);
	ss <<"\nTarget All-Pairs ShortestPaths=\n"<<sgtDf;
	bool match = true;
	ASSERT_EQ(gtDf.size(),Df.size())
	 	<<"Your 1st dimension of the Adj.Matrix doesn't match target";
	for(int i = 0;i<gtDf.size();++i){
		ASSERT_EQ(gtDf[i].size(),Df[i].size()) 
				<<"Your 2nd dimension of the Adj.Matrix doesn't match target (on row "<<i<<")";
		for(int j=0;j<gtDf[i].size();++j){
			if(gtDf[i][j]!=Df[i][j]) match = false;
			ASSERT_TRUE(match)<<"Your result doesn't match target at "<<"["<<i<<","<<j<<"]\n"<<ss.str();
		}
	}
}
/*
TEST(get_vertices, check_valid){
	DWG g;
	vector<int> vs ={1,2,4,3};
	for(int v :vs){
		g.addVertex(v);
	}
	vector<int> rvs = g.getVertices();
	for(int rv:rvs){
		cout<<rv;
	}

}

//not a real test...
TEST(build_and_print, build_print){
	DWG g;
	vector<int> ivs ={1,2,3,4};
	for(int v :ivs){
		g.addVertex(v);
	}
	g.addEdge(1,2,1.5);
	g.addEdge(3,4,2.5);
	g.addEdge(1,4,2.0);
	g.addEdge(3,2,0.5);
	vector<int> vs = g.getVertices();

	BAdjMat bam = g.getBooleanAdjacencyMatrix();
	cout << "aftergetBooleanAdj matrix..."<<endl;
	string bs = Graphs::adjMatrix2String(g.getVertices(),bam);
	cout << bs <<endl;

	AdjMat am = g.getAdjacencyMatrix();
	string s = adjMatrix2String(g.getVertices(),am);
	cout << s;
	cout << am[0][3];
}
*/





