/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"


MinHeap::MinHeap(){
    size=0;
    root=NULL;
}
int lhht(HeapNode* root){
    if (root==nullptr) return -1;
    return 1+lhht(root->left);
}

int rhht(HeapNode* root){
    if (root==nullptr) return -1;
    return 1+rhht(root->right);
}
int cheap(HeapNode* root){
 if (root==nullptr) return 0;
 return 1+cheap(root->left)+cheap(root->right);
}
bool fame2(HeapNode* root){
    int gk12=lhht(root);
    int gd1=rhht(root);
    if (gk12==gd1) return false;
    int hlr=rhht(root->left);
    int hrl=lhht(root->right);
    if (gk12-1>hlr) return true;
    if (gd1-1<hrl) return false;
    return true;
}
bool fame1(HeapNode* root){
    int gk12=lhht(root);
    int gd1=rhht(root);
    if (gk12==gd1) return true;
    int hlr=rhht(root->left);
    return gk12-1>hlr;
}
// void MinHeap::push_heap(int num){
//    HeapNode* newNode = new HeapNode(num);
//         size++;

//         if (root == nullptr) {
//             root = newNode;
//             return;
//         }

//         // Find the rightmost leaf node in the last level
//         HeapNode* temp = root;
//         int mask = size >> 1; // Bit mask to traverse the path
//         while (mask > 1) {
//             if (size & mask) {
//                 temp = temp->right;
//             } else {
//                 temp = temp->left;
//             }
//             mask >>= 1;
//         }

//         // Insert the new node as the child of the rightmost leaf node
//         if (size & 1) {
//             temp->right = newNode;
//         } else {
//             temp->left = newNode;
//         }
//         newNode->par = temp;

//         // Maintain the min-heap property by swapping if necessary
//         HeapNode* current = newNode;
//         while (current->par != nullptr && current->par->val > current->val) {
//             // Swap the val values
//             int tempData = current->val;
//             current->val = current->par->val;
//             current->par->val = tempData;

//             current = current->par;
//         }
// }

HeapNode* last1(HeapNode* root,int &k){
    if (root==nullptr) return root;
    if (root->val!=k && !root->left && !root->right) {
        k=root->val;
        delete root;
        return nullptr;
    }
    if (fame2(root)) root->left=last1(root->left,k);
    else root->right=last1(root->right,k);
    return root;
}

//  void MinHeap::pop() {
//     if (root == nullptr) {
//         return; // Heap is empty, nothing to pop.
//     }
//     //cout<<"hi"<<endl;
//     // Replace the root with the rightmost leaf node in the last level.
//     HeapNode* lastNode = root;
//     int mask = 1;
//     while (lastNode->left != nullptr) {
//         if (lastNode->right != nullptr) {
//             mask <<= 1;
//             //cout<<mask<<endl;
//             mask |= 1;
//             // cout<<mask<<endl;
//         } else {
//             mask <<= 1;
//         }
//         lastNode = lastNode->left;
//     }
    
//     // Swap the values of the root and the last node.
//     int tempData = root->val;
//     root->val = lastNode->val;
//     lastNode->val = tempData;

//     // Remove the last node.
//     if (lastNode->par != nullptr) {
//         if (lastNode->par->left == lastNode) {
//             delete lastNode->par->left;
//             lastNode->par->left = nullptr;
//         } else {
//             delete lastNode->par->right;
//             lastNode->par->right = nullptr;
//         }
//     } else {
//         // If the last node is the root.
//         delete root;
//         root = nullptr;
//     }

//     size--;
//    //cout<<"hi"<<endl;
//     // Restore the min-heap property by heapifying.
//     HeapNode* current = root;
//     HeapNode* current1=root;

//     while (current != nullptr) {
//         HeapNode* smallest = current;
//         if (current->left != nullptr && current->left->val < smallest->val) {
//             smallest = current->left;
//         }
//         if (current->right != nullptr && current->right->val < smallest->val) {
//             smallest = current->right;
//         }

//         if (smallest == current) {
//             break;
//         }

//         int tempData = current->val;
//         current->val = smallest->val;
//         smallest->val = tempData;

//         current = smallest;
//     }
// }



HeapNode* downn(HeapNode* root,int num){
    if (root==nullptr) return new HeapNode(num);
    if (num<root->val) {
        int m=num;
        num=root->val;
        root->val=m;
    }
    if (root->left==nullptr) {
       HeapNode* temp=downn(root->left,num);
       root->left=temp;
       temp->par=root;
    }
    else if (root->right==nullptr) {
        HeapNode* temp=downn(root->right,num);
        root->right=temp;
        temp->par=root;
    }
    else {
        if (fame1(root)) {
        HeapNode* temp=downn(root->left,num);
        root->left=temp;
        temp->par=root;
        }
        else {
            HeapNode* temp=downn(root->right,num);
            root->right=temp;
            temp->par=root;
        }
    }
    return root;
}

void dowm1(HeapNode* root){
    if (root==nullptr) return;
    if (root->left==nullptr) return;
    else if (root->right==nullptr) {
        if (root->val>root->left->val){
            int box=root->val;
            root->val=root->left->val;
            root->left->val=box;
        }
        return;
    }
    else {
            if (root->left->val<root->right->val){
                int box=root->val;
                root->val=root->left->val;
                root->left->val=box;
                dowm1(root->left);
            }
            else {
                int box=root->val;
                root->val=root->right->val;
                root->right->val=box;
                dowm1(root->right);
            }

        
    }
    return;
}

void give(HeapNode* root){
    if (root==nullptr) return;
    give(root->left);
    give(root->right);
    delete root;
    return ;
}

//  void printHeap(HeapNode* node) {
//         if (node == nullptr) {
//             return;
//         }

//         printHeap(node->left);
//         std::cout << node->val << " ";
//         printHeap(node->right);
//     }
// void MinHeap::print(){
//  printHeap(root);
// }








void MinHeap::push_heap(int num){
    root=downn(root,num);
   
}

int MinHeap::get_min(){
    if (root==nullptr) return -2;
    return root->val;
}

void MinHeap::pop(){                  
    if (root==nullptr) return;  
    int k=root->val;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    root=last1(root,k);
    // if (temp->par->left==temp) temp->par->left==nullptr;
    // else temp->par->right==nullptr;
    if (root==nullptr) return;
    root->val=k;
    // delete temp;
    dowm1(root);
}

MinHeap::~MinHeap(){
    give(root);
}

