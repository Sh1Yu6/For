
/************************************************
#
#      Filename: union.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-26 15:11:26
# Last Modified: 2021-03-26 21:18:12
#***********************************************/
#include <iostream>
using namespace std;

class UnionFind{
    public:
        UnionFind( int n ): count{ n }, id{ new int[n] }{
            for( int i = 0; i < n; ++i ){
                id[i] = i;
            }
        }
        ~UnionFind(){
            delete [] id;
        }

        int find( int p ){
            return id[p];
        }

        bool isConnected( int p, int q ){
            return find(p) == find(q);
        }

        void unionElements( int p, int q ){
            int pId = find(p);
            int qId = find(q);
            if( pId == qId ){
                return;
            }
            for( int i = 0; i < count; ++i ){
                if( id[i] == pId ){
                    id[i] = qId;
                }
            }
        }

    private:
        int* id;
        int count;
};

class UnionFindTwo{
    public:
        UnionFindTwo( int co ): parent{ new int[co] }, 
            count{ co }, rank{ new int[co] } {
            for( int i = 0; i < count; ++i ){
                parent[i] = i;
                rank[i] = 1;
            }
        }
        ~UnionFindTwo(){
            delete [] parent;
            delete [] rank;
        }

        int find(int p){//  find root
            //while( p != parent[p] ){
                //parent[p] = parent[parent[p]];
                //p = parent[p];
            //}
            //return p;
            //
            if( p != parent[p] ){
                parent[p] = find( parent[p] );
            }
            return parent[p];
        }

        bool isconnected( int p, int q ){
            return find(p) == find(q);
        }

        void unionElements( int p, int q ){
            int pRoot = find(p);
            int qRoot = find(q);
            if( pRoot == qRoot ){
                return;
            }
            if( rank[pRoot] < rank[qRoot] ){
                parent[pRoot] = qRoot;
            }else if( rank[qRoot] < rank[pRoot] ){
                parent[qRoot] = pRoot;
            }else{
                parent[pRoot] = qRoot;
                rank[qRoot] += 1;
            }
        }

    private:
        int* parent;
        int count;
        int* rank;
};
int main(int argc, char *argv[])
{
    return 0;
}

