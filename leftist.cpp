/**
 * This is a Leftist tree implementation. 
 *
 **/
#include "leftist.h"

/**
* Constructor
**/
LeftistHeap::LeftistHeap()
{
    root = NULL;
}

/**
* Constructor
**/
LeftistHeap::LeftistHeap(LeftistHeap &rhs)
{
    root = NULL;
    *this = rhs;
}
 
/**
* Destructor
**/
LeftistHeap::~LeftistHeap()
{
    makeEmpty( );
}
 

/**
 * Melds two leftist nodes and their childrn 
 *
 * @param h1
 *   node1 to be melded
 * @param h2
 *   node 2 to be melded
 * 
 * @return
 *   pointer to the root of the merged tree
 **/
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

/**
* Helper Function used by merge
**/
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

/**
* Helper function used by Merge1 hence by merge()
**/
void LeftistHeap::swapChildren(LeftistNode * t)
{
    LeftistNode *tmp = t->left;
    t->left = t->right;
    t->right = tmp;
}
 

/**
 * Inserts a new node into the leftist tree
 *
 * @param x
 *    vertes
 * @param y
 *   distance from source node
 * 
 * @return
 *   pointer to the root of the merged tree
 **/
LeftistNode *  LeftistHeap::Insert(int x, int y)
{   
    LeftistNode * node = new LeftistNode(x,y);
    root = Merge(node, root);
    return node;
}
 
/**
 * Find min in the leftist tree
 *
 *  
 * @return
 *   distance from source node
 **/
int &LeftistHeap::findMin()
{
    return root->data;
}
 
/**
 * Remove min in the leftist tree
 *
 *  
 * @return
 *   Pointer to the min node that is deleted
 **/
LeftistNode * LeftistHeap::RemoveMin()
{
    LeftistNode *oldRoot = root;
    root = Merge(root->left, root->right);
    return oldRoot;
}
 
/**
 * Find the parent of the node that is deleted and join the 
 * child of deleted node with parent. 
 *
 * @param origin
 *    recursive root to start searching from 
 * @param curr
 *    the node being deleted
 * @param child 
 *    the subtree under the curr. 
 *
 * @return
 *   1 if curr deletion is done else 0
 **/
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

/**
 * Decreases the key value. This is implemented
 * by deleting that key and inserting a new node 
 * with the new value. 
 *
 * @param curr
 *    The node whose value needs to be decreased. 
 * @param newdist
 *    the new distance value.
 *
 * @return
 *   root node
 **/
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

/* Checks if leftist heap is empty */
bool LeftistHeap::empty()
{
    return root == NULL;
}
 
void LeftistHeap::makeEmpty()
{
    reclaimMemory(root);
    root = NULL;
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
 
 
