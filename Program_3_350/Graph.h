#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <limits>
namespace Graphs{

	template<class T> class Node{
	public:
		Node(T value): val(value){}
		T val;
	};

	//no source -- used in adjacency list
	template<class T, class W> class DirectedEdge{
	public:
		T source;
		T target;
		W weight;
		DirectedEdge(T s, T t, W w): source(s),target(t),weight(w){}
	};

	template <class T, class W>
	class DirectedWeightedGraph{
		typedef DirectedEdge<T,W> DE;
		//std::map<T, std::vector<DirectedEdge<T,W> > > verts;
		std::map<T, std::vector<DE > > verts;
	public:
		void addVertex(T v){
			verts[v]=std::vector<DirectedEdge<T,W> >();
		}

		void addEdge(T source, T target, W weight){
			DirectedEdge<T,W> e(source,target,weight);
			verts[source].push_back(e);
		}

		std::vector< DE > getEdges(T vert){
			return verts[vert];
		}

		std::map< T, int> getIndexMap(){
			std::map< T, int> im;
			std::vector<T> vs = getVertices();
			for(int i = 0;i<vs.size();++i){
				im[vs[i]]=i;
			}
			return im;
		}

		std::vector<T> getVertices(){
			std::vector<T> vs;
			for(typename std::map<T, std::vector<DE > >::iterator it = verts.begin();it!=verts.end();++it){
				vs.push_back(it->first);
			}
			return vs;
		}

		/***************************************
		*Returns adjacency matrix 
		*
		****************************************/
		std::vector<std::vector<W> > getAdjacencyMatrix(W non_adj_filler=W(0)){
			std::vector<std::vector<W> > am;
			std::vector<T> vs = getVertices();
			int n = vs.size();
			for(int i =0;i<n;++i){
				am.push_back(std::vector<W>() );
				for(int j =0;j<n;++j){
					am[i].push_back(non_adj_filler);
				}
			}
			std::map<T,int> im = getIndexMap();
			for(T v:vs){
				for(int i =0; i<verts[v].size();++i){
					DE e = verts[v][i];
					am[im[v]][im[e.target]] = e.weight; 
				}
			}
			return am;
		}


		std::vector<std::vector<bool> > getBooleanAdjacencyMatrix(){
			std::vector<std::vector<bool> > bam;
			std::vector<T> vs = getVertices();
			int n = vs.size();
			for(int i =0;i<n;++i){
				bam.push_back(std::vector<bool>() );
				for(int j =0;j<n;++j){
					bam[i].push_back(false);
				}
			}
			std::map<T,int> im = getIndexMap();
			for(T v:vs){
				for(int i =0; i<verts[v].size();++i){
					DE e = verts[v][i];
					bam[im[e.source]][im[e.target]] = true; 
				}
			}
			return bam;
		}

		/***************************************
		* Get Transitive closure 
		* define this with Warshall's
		* careful: this is accessed like a regular matrix (row, then column)
		********************************************/
		std::vector<std::vector<bool> > getTransitiveClosure(){
			std::vector<std::vector<bool> > R = getBooleanAdjacencyMatrix();
			int n = R.size();
			for ( int k = 0; k < n; k++){
				for(int i = 0; i < n; i++){
					for(int j = 0; j < n; j++){
						R[i][j] = R[i][j] || (R[i][k] && R[k][j]);
						//R[i][j] & R[i][j]; // bitwise and operator
					}
				} 
			}
			return R;
		}

		/***************************************
		* Get All Pairs Shortests Paths 
		* define this with Floyd's
		* careful: this is accessed like a regular matrix (row, then column)
		********************************************/
		
		std::vector<std::vector<W> > getAllPairsShortestPaths(){
			//parameter is to indicate "filler"
			std::vector<std::vector<W> > D = getAdjacencyMatrix(std::numeric_limits<double>::infinity());
			int n = D.size();
			//Floyd's doesn't start with a regular adjacency matrix (look at diagonal)
			 for ( int k = 0; k < n; k++){
                                for(int i = 0; i < n; i++){
                                        for(int j = 0; j < n; j++){
						if(i == j) 
						{
							D[i][j] = 0;
						}else{
							if(D[i][j] > D[i][k] + D[k][j]){
								D[i][j] = D[i][k] + D[k][j];
							}
						}
					 }
                                }
                        }
			return D;
		}
	};

	template<typename T, typename W>
	std::string adjMatrix2String(const std::vector<T> & vs, const std::vector<std::vector<W> > & am){
		using std::endl;
		std::stringstream ss;
		int setwidth = 4;
		ss<<"\t"/*setw(setwidth)*/<<" ";
		for(T v:vs) {ss << "\t"/*setw(setwidth)*/ <<v;}
		ss<<"\n";
		for(int i = 0;i<vs.size();++i){
			T v = vs[i];
			ss<<"\t"/*setw(setwidth)*/<<v;
			for(W w:am[i]) {ss << "\t"/*setw(setwidth)*/<<w;}
			ss<<"\n";
		}

		return ss.str();
	}

}
#endif
