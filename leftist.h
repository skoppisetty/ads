#include <iostream>
#include <cstdlib>
using namespace std;

class LeftistNode
{
    public:
        int data;
        int vertex;
        LeftistNode *left;
        LeftistNode *right;
        int npl;
        LeftistNode(int  vertex, int  data,  LeftistNode *lt = NULL,
                    LeftistNode *rt = NULL, int np = 0)
        {	

        		this->vertex = vertex;
            this->data = data;
            //cout << "inserting" << this->vertex << this->data <<  endl;
            right = rt;
            left = lt,
            npl =  np;
        }
};

class LeftistHeap
{
    public:
        LeftistHeap();
        LeftistHeap(LeftistHeap &rhs);
        ~LeftistHeap();
        bool empty();
        //bool isFull();
        int &findMin();
        LeftistNode * Insert(int x, int y);
        LeftistNode * RemoveMin();
        // void deleteMin(int &minItem);
        LeftistNode * DecreaseKey(LeftistNode*,int);
        int link_node(LeftistNode * origin, LeftistNode * curr, LeftistNode * child);
        void makeEmpty();
        void Merge(LeftistHeap &rhs);
        //LeftistHeap & operator=(LeftistHeap &rhs);
    private:
        LeftistNode *root;
        LeftistNode *Merge(LeftistNode *h1, LeftistNode *h2);
        LeftistNode *Merge1(LeftistNode *h1, LeftistNode *h2);
        void swapChildren(LeftistNode * t);
        //void reclaimMemory(LeftistNode * t);
        //LeftistNode *clone(LeftistNode *t);

};
 
