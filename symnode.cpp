
// #include "symnode.h"





// SymNode::SymNode(string k){
//     key=k;
//     height=0;
//     par=nullptr;
//     right=nullptr;
//     left=nullptr;
// }
// SymNode::SymNode(){
//     key="try";
//     height=-1;
//     par=nullptr;
//     right=nullptr;
//     left=nullptr;

// }

// SymNode* SymNode::RightLeftRotation(){
//     return nullptr;
// }
// SymNode* SymNode::LeftRightRotation(){
//     return nullptr;
// }
// SymNode* SymNode::LeftLeftRotation(){
//     return nullptr;
// }

// SymNode* SymNode::RightRightRotation(){
//     return nullptr;
// }




// SymNode::~SymNode(){
//     par=nullptr;
//     right=nullptr;
//     left=nullptr;
// }

/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line
int height2(SymNode* root){
  if(root==NULL){
    return 0;

  }
  return root->height;
}
int max1(int a,int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
SymNode::SymNode(){
  par=NULL;
 right=NULL;
 left=NULL; 
 

}

SymNode::SymNode(string k){
 key=k;
 height=1;
 par=NULL;
 right=NULL;
 left=NULL; 
}

// SymNode* SymNode::LeftLeftRotation(){
//   SymNode* temp=this->left;
//   this->left=temp->right;
//    temp->right=this;
//   this->height=1+max(height2(this->left),height2(this->right));
//   temp->height=1+max(height2(temp->left),this->height);
//   return temp;

  
// }
SymNode* SymNode::LeftLeftRotation(){
  SymNode* temp=this->left;
  SymNode* temp2=temp->right;
  
 // this->left=temp->right;
   temp->right=this;
   this->left=temp2;
  this->height=max1(height2(this->left),height2(this->right))+1;
  temp->height=max1(height2(temp->left),height2(temp->right))+1;
  return temp;

  
}

// SymNode* SymNode::RightRightRotation(){
// SymNode* temp=this->right;
//   this->right=temp->left;
//   temp->left=this;
//   this->height=max(height2(this->left),height2(this->right))+1;
//   temp->height=max(height2(temp->right),this->height)+1;
//   return temp;

// }
SymNode* SymNode::RightRightRotation(){

SymNode* temp=this->right;
SymNode* temp2=this->left;
 temp->left=this;
 
  this->right=temp2;
  //temp->left=this;
  this->height=max1(height2(this->left),height2(this->right))+1;
  temp->height=max1(height2(temp->left),height2(temp->right))+1;
  
 
  return temp;
  // cout<<"hi"<<endl; 

}

SymNode* SymNode::LeftRightRotation(){
this->left=this->left->RightRightRotation();
return LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){
this->right=this->right->LeftLeftRotation();

return RightRightRotation();

}

SymNode::~SymNode(){
 par=NULL;
 right=NULL;
 left=NULL;
}