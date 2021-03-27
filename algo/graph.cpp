
/************************************************
#
#      Filename: graph.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-27 07:43:03
# Last Modified: 2021-03-27 11:54:07
#***********************************************/
#include <c++/7/bits/c++config.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

class DenseGraph{
    public:
        class adjIterator{
            public:
                DenseGraph& G;
                int vertex;
                int index;
            private:
                adjIterator(DenseGraph& graph, int v): G{ graph }, 
                    vertex{ v }, index{ -1 }{

                }

                int begin(){
                    index = -1;
                    return next();
                }

                int next(){
                    for( index += 1; index < G.V(); ++index ){
                        if( G.g[vertex][index] ){
                            return index;
                        }
                    }
                }

                bool end(){
                    return index >= G.V();
                }
        };
        DenseGraph( int n, bool dir ): vertex{ n }, edge{ 0 }, directed{ dir }{
            for( int i = 0; i < n; ++i ){
                g.push_back( vector<bool>(n, false) );
            }
        }

        int V(){
            return vertex;
        }

        int E(){
            return edge;
        }

        void addEdge( int v, int w ){
            assert( v >= 0 && v < vertex );
            assert( w >= 0 && w < vertex );

            if( hasEdge( v, w ) ){
                return;
            }
            g[v][w] = true;
            if( !directed ){
                g[w][v] = true;
            }
            ++edge;
        }

        bool hasEdge( int v, int w ){
            assert( v >= 0 && v < vertex );
            assert( w >= 0 && v < vertex );
            return g[v][w];
        }

        void show(){
            for( int i = 0; i < vertex; ++i ){
                for( int j = 0; j < vertex; ++j ){
                    cout << g[i][j] << "\t";
                }
                cout << endl;
            }

        }

    private:
        int vertex, edge;
        bool directed;
        vector<vector<bool>> g;

};

class SparseGraph{
    public:
        class adjIterator{
            public:
                adjIterator( SparseGraph& graph, int v ): G{ graph }, 
                    vertex{ v }, index{ 0 }{

                }

                int begin(){
                    index = 0;
                    if(G.g[vertex].size()){
                        return G.g[vertex][index];
                    }
                    return -1;
                }

                int next(){
                    ++index;
                    if( index < G.g[vertex].size() ){
                        return G.g[vertex][index];
                    }
                    return -1;
                }

                bool end(){
                    return index >= G.g[vertex].size();
                }
                
            private:
                SparseGraph& G;
                int vertex;
                int index;
        };

        SparseGraph( int n, bool dir ):vertex{ n }, edge{ 0 }, 
            directed{ dir }{
                for( int i = 0; i < n; ++i ){
                    g.push_back( vector<int>{} );
                }
        }

        int V(){
            return vertex;
        }

        int E(){
            return edge;
        }

        void addEdge( int v, int w ){
            assert( v >= 0 && v < vertex );
            assert( w >= 0 && w < vertex );

            if( hasEdge(v, w) ){
                return;
            }

            g[v].push_back(w);
            if( v != w && !directed ){
                g[w].push_back(v);
            }
            ++edge;
        }

        bool hasEdge( int v, int w ){
            assert( v >= 0 && v < vertex );
            assert( w >= 0 && w < vertex );

            for(int i = 0; i < g[v].size(); ++i){
                if( g[v][i] == w ){
                    return true;
                }
            }
            return false;
        }

        void show(){
            for( int i = 0; i < vertex; ++i ){
                cout << "vertex " << i << ":\t";
                for( int j = 0; j < g[i].size(); ++j ){
                    cout << g[i][j] << "\t";
                }
                cout << endl;
            }
        }
    private:
        int vertex, edge;
        bool directed;
        vector<vector<int>> g;
};

template<typename Graph>
class ReadGraph{
    public:
        ReadGraph( Graph& graph, const string& filename ){
            ifstream file( filename );
            string line;
            int V, E;

            assert( file.is_open() );
            assert( getline( file, line ) );
            stringstream ss{ line };
            ss >> V >> E;

            assert( V == graph.V() );

            for( int i = 0; i < E; ++i ){
                assert( getline( file, line ) );
                stringstream ss( line );
                int a, b;
                ss >> a >> b;
                assert( a >= 0 && a < V );
                assert( b >= 0 && b < V );
                graph.addEdge( a, b );
            }
        }
};

template<typename Graph>
class Component{
    public:
        Component(Graph& graph): G{ graph }, visited{ new bool[G.V()] },
            ccount{ 0 }, id{ new int[G.V()] }{
                for( int i = 0; i < G.V(); ++i ){
                    visited[i] = false;
                    id[i] = -1;
                }
                for( int i = 0; i < G.V(); ++i ){
                    if( !visited[i] ){
                        dfs(i);
                        ++ccount;
                    }
                }
        }
        ~Component(){
            delete [] visited;
            delete [] id;
        }

        bool isConnected(int v, int w){
            return id[v] == id[w];
        }
    private:
        Graph& G;
        bool* visited;
        int* id;
        int ccount;

        void dfs(int v){
            visited[v] = true;
            id[v] = ccount;
            typename Graph::adjIterator adj(G, v);
            for( int i = adj.begin(); !adj.end(); i = adj.next() ){
                if( !visited[i] ){
                    dfs(i);
                }
            }
        }

};

template<typename Graph>
class ShortestPath{

    public:
        Graph& G;
        int sour;
        bool* visited;
        int* from;
        int* ord;
    private:
        ShortestPath(Graph& graph, int s): G{ graph }, 
            visited{ new bool[graph.V()] }, from{ new int[graph.V()] },
            ord{ new int[graph.V()] }, sour{ s }{

            for(int i = 0; i < graph.V(); ++i){
                visited[i] = false;
                from[i] = -1;
                ord[i] = -1;
            }
            queue<int> q;
            q.push( s );
            visited[s] = true;
            ord[s] = 0;
            while( !q.empty() ){
                int v = q.front();
                q.pop();

                typename Graph::adjIterator adj(G, v);
                for( int i = adj.begin(); !adj.end(); i = adj.next() ){
                    if( !visited[i] ){
                        q.push(i);
                        visited[i] = true;
                        from[i] = v;
                        ord[i] = ord[v] + 1;
                    }
                }
            }
        }
        ~ShortestPath(){
            delete [] visited;
            delete [] from;
            delete [] ord;
        }

        bool hasPath(int w){
            return visited[w];
        }

        void path(int w, vector<int>& vec){
            asert( w >= 0 && w < G.V() );
            stack<int> s;
            int p = w;
            while( p != -1 ){
                s.push(p);
                p = from[p];
            }
            vec.clear();
            while( !s.empty() ){
                vec.push_back( s.top() );
                s.pop();
            }

        }

        void showPath(int w){
            assert( w >= 0 && w < G.V() );
            vector<int> vec;
            path(w, vec);
            for( int i = 0; i < vec.size(); ++i ){
                cout << vec[i];
                if( i == vec.size() - 1 ){
                    cout << endl;
                }else{
                    cout << " -> ";
                }
            }
        }


};

int main(int argc, char *argv[])
{
    string filename{ "test.txt" };
    SparseGraph g1( 13, false );
    ReadGraph<SparseGraph> readGraph1( g1, filename );
    g1.show();

    DenseGraph g2( 13, false );
    ReadGraph<DenseGraph> readGraph2( g2, filename );
    g2.show();

    return 0;
}

