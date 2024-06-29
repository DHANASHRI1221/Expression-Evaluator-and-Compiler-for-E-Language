/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
SymbolTable::SymbolTable(){
  size=0;
  root=nullptr;
}
void clear(SymEntry* root){
    if (root != nullptr) {
        clear(root->left);
        clear(root->right);
            delete root->val; 
            delete root;
        }
    }

SymbolTable::~SymbolTable(){
    clear(root);
    
}
SymEntry* insert1(SymEntry* root,string k,UnlimitedRational*v){
    if(root==nullptr){
    //  SymEntry* result1= new  SymEntry(k,v);
    root = new  SymEntry(k,v);
        return root ;
    }
    if(k<root->key){
        root->left=insert1(root->left,k,v);
    }
    else if(k>root->key){
      root->right=insert1(root->right,k,v);
    }
    // else{
    //    // Key already exists
    // }
    return root;
    
}
void SymbolTable::insert(string k, UnlimitedRational *v)
{
    root=insert1(root,k,v);
    size=size+1;
}
SymEntry*  min(SymEntry* root){
     SymEntry* final=root;
     while(final->left!=nullptr){
        final=final->left;

     }
     return final;

}
SymEntry*  remove1(SymEntry* root,string k){
   if(root==nullptr){
    return root;
   }
   if(k<root->key){
        root->left=remove1(root->left,k);
    }
    else if(k>root->key){
      root->right=remove1(root->right,k);
    }
    else{
       if(root->left==nullptr){
        SymEntry* temp= root->right;
        delete root;
        return temp;
       }
       else if(root->right==nullptr){
        SymEntry* temp=root->left;
        delete root;
        return temp;
       }
      SymEntry* temp=min(root->right);
      root->key=temp->key;
      root->val=temp->val;
      root->right=remove1(root->right,temp->key);
    }

  return root;







}
void SymbolTable::remove(string k)
{
    root=remove1(root,k);
    size=size-1;
}
UnlimitedRational* search1(SymEntry* root,string k){
  if(root==nullptr){
     return nullptr;
  }
  else{
    if(root->key==k){
        return root->val;
    }
    else{
  if(k<root->key){
    return search1(root->left,k);

  }
  else{
    return search1(root->right,k);
  }
    }
}
}
UnlimitedRational *SymbolTable::search(string k)
{
    return search1(root,k);
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
    
}