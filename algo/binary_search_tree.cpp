
/************************************************
#
#      Filename: binary_search_tree.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-26 10:17:36
# Last Modified: 2021-03-26 12:25:12
#***********************************************/
#include <iostream>
#include <queue>
using namespace std;

template<typename T>
int binarySearch(T* arr, int n, T target){
    int left = 0, right = n - 1;
    while( left <= right ){
        int mid = left + (right - left) / 2;
        if( arr[mid] < target ){
            left = mid + 1;
        }else if( target < arr[mid] ){
            right = mid - 1;
        }else{
            return mid;
        }
    }
    return -1;
}


template<typename Key, typename Value>
class BST{
    public:
        BST(): root{ nullptr }, count{ 0 }{

        }
        ~BST(){
            destory(root);
        }

        int size() const{
            return count;
        }

        bool isEmpty() const{
            return count == 0;
        }

        void insert(Key k, Value v){
            root = insert(root, k, v);
        }

        Value* search(Key k){
            return search(root, k);
        }
        void bfsOrder(){
            queue<Node*> q;
            q.push(root);
            while(!q.empty()){
                auto node = q.front();
                q.pop();
                if(node->left != nullptr){
                    q.push(node->left);
                }
                if(node->right != nullptr){
                    q.push(node->right);
                }
                cout << node->key << " " << node->value << endl;
            }
        }

        void removeMin(){
            if( root ){
                root = removeMin( root );
            }
        }

        void removeMax(){
            if( root ){
                root = removeMax( root );
            }
        }
        
        void remove(Key k){
            root = remove(root, k);
        }

    private:
        struct Node{
            Key key;
            Value value;
            Node* left;
            Node* right;

            Node(Key k, Value v): key{ k }, value{ v },
                left{ nullptr }, right{ nullptr }{

            }

            Node(Node* node): key{ node->key }, value{ node->value },
                left{ node->left }, right{ node->right }{

            }

        };

        Node* root;
        int count;

    private:

        Node* insert(Node* node, Key k, Value v){
            if( node == nullptr ){
                ++count;
                return new Node(k, v);
            }

            if( k == node->key ){
                node->value = v;
            }else if( k < node->key ){
                node->left = insert( node->left, k, v );
            }else{
                node->right = insert( node->right, k, v );
            }

            return node;
        }

        Value* search(Node* node, Key k){
            if( node == nullptr ){
                return nullptr;
            }

            if( k == node->key ){
                return &node->value;
            }else if( k < node->key ){
                return search(node->left, k);
            }else{
                return search(node->right, k);
            }
        }

        void destory(Node* node){
            if(node != nullptr){
                destory(node->left);
                destory( node->right );
                delete node;
                node = nullptr;
                --count;
            }
        }

        Node* removeMin(Node* node){
            if( node->left == nullptr ){
                Node* rightNode = node->right;
                delete node;
                node = nullptr;
                --count;
                return rightNode;
            }
            node->left = removeMin(node->left);
            return node;
        }

        Node* removeMax(Node* node){
            if( node->right == nullptr ){
                Node* leftNode = node->left;
                delete node;
                node = nullptr;
                --count;
                return leftNode;
            }
            node->right = removeMax( node->right );
            return node;
        }

        Node* remove(Node* node, Key k){
            if( node == nullptr ){
                return nullptr;
            }
            if( k < node->key ){
                node->left =  remove( node->left, k );
                return node;
            }else if( k > node->key ){
                node->right = remove( node->right, k );
                return node;
            }else{
                if( node->left == nullptr ){
                    Node* rightNode = node->right;
                    delete node;
                    --count;
                    return rightNode;
                }
                if( node->right == nullptr ){
                    Node* leftNode = node->left;
                    delete node;
                    --count;
                    return leftNode;
                }

                Node* successor = new Node(minimum(node->right));
                ++count;

                successor->right = removeMin( node->right );
                successor->left = node->left;
                delete node;
                node = nullptr;
                --count;
                return successor;
            }
        }

        Node* minimum(Node* node){
            if( node->left == nullptr ){
                return node;
            }
            return minimum( node->left );
        }
};
int main(int argc, char *argv[])
{
    BST<int, int> b;
    srand(time(nullptr));
    for(int i = 0; i < 10; ++i){
        int k = rand() % 20;
        b.insert(k, i * 10);
        cout << k << " ";
    }
    cout << endl;
    b.bfsOrder();
    return 0;
}

