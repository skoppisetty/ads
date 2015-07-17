#include "leftist.h"

/*
 * Construct the leftist heap.
 */
LeftistHeap::LeftistHeap()
{
    root = NULL;
}
 
/*
 * Copy constructor.
 */
LeftistHeap::LeftistHeap(LeftistHeap &rhs)
{
    root = NULL;
    *this = rhs;
}
 
/*
 * Destruct the leftist heap.
 */
LeftistHeap::~LeftistHeap()
{
    makeEmpty( );
}
 
/*
 * Merge rhs into the priority queue.
 * rhs becomes empty. rhs must be different from this.
*/
void LeftistHeap::Merge(LeftistHeap &rhs)
{
    if (this == &rhs)
        return;
    root = Merge(root, rhs.root);
    rhs.root = NULL;
}
 
/*
 * Internal method to merge two roots.
 * Deals with deviant cases and calls recursive Merge1.
 */
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
 
/*
 * Internal method to merge two roots.
 * Assumes trees are not empty, and h1's root contains smallest item.
 */
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
 
/*
 * Swaps t's two children.
 */
void LeftistHeap::swapChildren(LeftistNode * t)
{
    LeftistNode *tmp = t->left;
    t->left = t->right;
    t->right = tmp;
}
 
/*
 * Insert item x into the priority queue, maintaining heap order.
 */
LeftistNode *  LeftistHeap::Insert(int x, int y)
{   
    LeftistNode * node = new LeftistNode(x,y);
    root = Merge(node, root);
    return node;
}
 
/*
 * Find the smallest item in the priority queue.
 * Return the smallest item, or throw Underflow if empty.
 */
int &LeftistHeap::findMin()
{
    return root->data;
}
 
/*
 * Remove the smallest item from the priority queue.
 * Throws Underflow if empty.
 */
LeftistNode * LeftistHeap::RemoveMin()
{
    LeftistNode *oldRoot = root;
    root = Merge(root->left, root->right);
    return oldRoot;
}
 
int LeftistHeap::link_node(LeftistNode * origin, LeftistNode * curr, LeftistNode * child){
  /*  if(origin == NULL){
        return 0;
    }
    else{
        if(origin == curr){
            cout << "Seriosu mistake " << endl;
        }
        else{
            if(origin->left == curr){
                cout << "left deleted" << endl;
                origin->left = child;
                cout << "left deleted done" << endl;
                return 1;
            }
            if(origin->right == curr){
                cout << "right deleted" << endl;
                origin->right = child;
                return 1;
            }
        }
    }
    */

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


/*
 * Remove the smallest item from the priority queue.
 * Pass back the smallest item, or throw Underflow if empty.
 
void LeftistHeap::deleteMin(int &minItem)
{
    if (empty())
    {
        cout<<"Heap is Empty"<<endl;
        return;
    }
    minItem = findMin();
    deleteMin();
}
 */

/*
 * Test if the priority queue is logically empty.
 * Returns true if empty, false otherwise.
 */
bool LeftistHeap::empty()
{
    return root == NULL;
}
 
/*
 * Test if the priority queue is logically full.
 * Returns false in this implementation.
 */
bool LeftistHeap::isFull()
{
    return false;
}
 
/*
 * Make the priority queue logically empty.
 */
void LeftistHeap::makeEmpty()
{
    reclaimMemory(root);
    root = NULL;
}
 
/*
 * Deep copy.
 */
LeftistHeap &LeftistHeap::operator=(LeftistHeap & rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}
 
/*
 * Internal method to make the tree empty.
 */
void LeftistHeap::reclaimMemory(LeftistNode * t)
{
    if (t != NULL)
    {
        reclaimMemory(t->left);
        reclaimMemory(t->right);
        delete t;
    }
}
 
/*
 * Internal method to clone subtree.
 */
LeftistNode *LeftistHeap::clone(LeftistNode * t)
{
    if (t == NULL)
        return NULL;
    else
        return new LeftistNode(t->vertex, t->data, clone(t->left), clone(t->right), t->npl);
}
 
