/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    left=nullptr;
    par=nullptr;
  
    right=nullptr;
     val=-1;
}

HeapNode::HeapNode(int _val){
    val=_val;
    par=nullptr;
    left=nullptr;
    right=nullptr;
}

HeapNode::~HeapNode(){
  par=nullptr;
  left=nullptr;
  right=nullptr;
}
