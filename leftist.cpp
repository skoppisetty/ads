#include "leftist.h"

LeftistHeap::LeftistHeap()
{
    root = NULL;
}

LeftistHeap::LeftistHeap(LeftistHeap &rhs)
{
    root = NULL;
    *this = rhs;
}
 

LeftistHeap::~LeftistHeap()
{
    makeEmpty( );
}
 
void LeftistHeap::Merge(LeftistHeap &rhs)
{
    if (this == &rhs)
        return;
    root = Merge(root, rhs.root);
    rhs.root = NULL;
}
 
LeftistNode *LeftistHeap::Merge(LeftistNode * h1, LeftistNode * h2)
{
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;
    if (h1->data < h2->data)
        return Merge1(h1, h2);
    else
        return Merge1(h2, h1);
}
 
LeftistNode *LeftistHeap::Merge1(LeftistNode * h1, LeftistNode * h2)
{
    if (h1->left == NULL)
        h1->left = h2;
    else
    {
        h1->right = Merge(h1->right, h2);
        if (h1->left->npl < h1->right->npl)
            swapChildren(h1);
        h1->npl = h1->right->npl + 1;
    }
    return h1;
}
 
void LeftistHeap::swapChildren(LeftistNode * t)
{
    LeftistNode *tmp = t->left;
    t->left = t->right;
    t->right = tmp;
}
 
LeftistNode *  LeftistHeap::Insert(int x, int y)
{   
    LeftistNode * node = new LeftistNode(x,y);
    root = Merge(node, root);
    return node;
}
 

int &LeftistHeap::findMin()
{
    return root->data;
}
 

LeftistNode * LeftistHeap::RemoveMin()
{
    LeftistNode *oldRoot = root;
    root = Merge(root->left, root->right);
    return oldRoot;
}
 
int LeftistHeap::link_node(LeftistNode * origin, LeftistNode * curr, LeftistNode * child){
    if(origin){
        if(origin == curr){
            cout << "Seriosu mistake " << endl;
        }
        if(origin->left == curr){
            //cout << "left deleted" << endl;
            origin->left = child;
            //cout << "left deleted done" << endl;
            return 1;
        }
        if(origin->right == curr){
            //cout << "right deleted" << endl;
            origin->right = child;
            return 1;
        }

        int k = link_node(origin->left,curr,child);
        if(k == 1){
            return 1;
        }
        else{
            k =  link_node(origin->right,curr,child); 
            //cout << k << endl;
            return k;
        }
        
    }
    return 0;

}

LeftistNode * LeftistHeap::DecreaseKey(LeftistNode * curr, int newdist){
    LeftistNode * temp = curr;
    //cout << "decrease key " << curr->vertex << endl;
    LeftistNode * new_root = Merge(curr->left, curr->right);
    if(root == curr){
        root = new_root;
    }
    else{
        //cout << "calling linker " << endl;
        // cout << "data : " << root->data << curr->data << new_root->data << endl;
        // cout << "vertex : " << root->vertex << curr->vertex << new_root->vertex << endl;
        int k = link_node(root, curr, new_root);
        if(k == 0){
            cout << "error " << endl;
            exit(0);
        }
        //cout << "linked" << endl;
    }
    //cout << "inserting " << endl;
    new_root = Insert(temp->vertex, newdist);
    delete curr;
    return new_root;
    //cout << "Decrease key done" << endl;
}


bool LeftistHeap::empty()
{
    return root == NULL;
}
 

bool LeftistHeap::isFull()
{
    return false;
}
 

void LeftistHeap::makeEmpty()
{
    reclaimMemory(root);
    root = NULL;
}
 

LeftistHeap &LeftistHeap::operator=(LeftistHeap & rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}
 

void LeftistHeap::reclaimMemory(LeftistNode * t)
{
    if (t != NULL)
    {
        reclaimMemory(t->left);
        reclaimMemory(t->right);
        delete t;
    }
}
 

LeftistNode *LeftistHeap::clone(LeftistNode * t)
{
    if (t == NULL)
        return NULL;
    else
        return new LeftistNode(t->vertex, t->data, clone(t->left), clone(t->right), t->npl);
}
 
