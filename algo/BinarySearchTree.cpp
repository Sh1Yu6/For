
/************************************************
#
#      Filename: BinarySearchTree.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-02-21 16:06:36
# Last Modified: 2021-02-21 17:25:54
#***********************************************/
#include <functional>
#include <iostream>
using namespace std;

template <typename Object, typename Comparator=less<Object>>
class BinarySearchTree{
public:
    BinarySearchTree();

    BinarySearchTree(const BinarySearchTree& rhs)
        : root{ nullptr }{
        root = clone(rhs.root);
    }

    BinarySearchTree(BinarySearchTree&& rhs);

    ~BinarySearchTree(){
        makeEmpty();
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs);

    BinarySearchTree& operator=(BinarySearchTree&& rhs);

    const Object& findMin() const{
        findMin(root);
    }

    const Object& findMax() const{
        findMax(root);
    }

    bool contains(const Object& x) const{
        return contains(x, root);
    }

    bool isEmpty() const{
        return root == nullptr;
    }

    void printTree(ostream& out = cout) const;

    void makeEmpty(){
        makeEmpty(root);
    }

    void insert(const Object& x){
        insert(x, root);
    }

    void insert(Object&& x){
        insert(move(x), root);
    }

    void remove(const Object& x){
        remove(x, root);
    }



private:
    struct BinaryNode{
        Object element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Object& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{theElement}, left{lt}, right{rt} {  }

        BinaryNode(Object&& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{move(theElement)}, left{lt}, right{rt} {  }
    };

    BinaryNode* root;
    Comparator isLessThan;
    
    void insert(const Object& x, BinaryNode*& t){
        if(t == nullptr){
            t = new BinaryNode{x, nullptr, nullptr};
        }else if(isLessThan(x, t->element)){
            insert(x, t->left);
        }else if(isLessThan(t->element, x)){
            insert(x, t->right);
        }else{

        }
    }

    void insert(Object&& x, BinaryNode*& t){
        if(t == nullptr){
            t = new BinaryNode{move(x), nullptr, nullptr};
        }else if(isLessThan(x, t->element)){
            insert(move(x), t->left);
        }else if(isLessThan(t->element, x)){
            insert(move(x), t->right);
        }else{

        }

    }

    void remove(const Object& x, BinaryNode*& t){
        if(t == nullptr){
            return;
        }
        if(isLessThan(x < t->element)){
            remove(x, t->left);
        }else if(isLessThan(t->element, x)){
            remove(x, t->right);
        }else if(t->left != nullptr && t->right != nullptr){
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }else{
            BinaryNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    BinaryNode* findMin(BinaryNode* t) const{
        if(t == nullptr){
            return nullptr;
        }
        if(t->left == nullptr){
            return t;
        }
        return findMin(t->left);
    }

    BinaryNode* findMax(BinaryNode* t) const{
        if(t != nullptr){
            while(t->right != nullptr){
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Object& x, BinaryNode* t) const{
        if(t == nullptr){
            return false;
        }else if(isLessThan(x, t->element)){
            return contains(x, t->left);
        }else if(isLessThan(t->element, x)){
            return contains(x, t->right);
        }else{
            return true;
        }

        //auto temp = t;
        //while(temp){
            //if(x < temp->element){
                //temp = temp->left;
            //}else if(x > temp->element){
                //temp = temp->right;
            //}else{
                //return true;
            //}
        //}
    }

    void makeEmpty(BinaryNode*& t){
        if(t != nullptr){
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(BinaryNode* t, ostream& out) const;

    BinaryNode* clone(BinaryNode* t) const{
        if( t == nullptr ){
            return nullptr;
        }else{
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
        }
    }
};



int main(int argc, char *argv[])
{
    return 0;
}

