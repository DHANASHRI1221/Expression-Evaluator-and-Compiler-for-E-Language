#include"evaluator.h"




  

Evaluator::Evaluator() {
    symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
    // Clean up resources
    delete symtable;
    for (ExprTreeNode* node : expr_trees) {
        delete node;
    }
    expr_trees.clear();
}


ExprTreeNode* parse1(vector<string> d){
  
  vector<ExprTreeNode*>f;
  for(int i=2;i<d.size();i++){
   // cout<<"hi"<<endl;
    if(d[i]=="("|| d[i]==")"){
      ExprTreeNode* n=new ExprTreeNode();
      //cout<<"hi"<<endl;
      n->type="B";
      
      n->id=d[i];
      f.push_back(n);
    }
    else if(d[i]=="+"){
     ExprTreeNode* n=new ExprTreeNode();
      n->type="ADD";
      //cout<<"hi1"<<endl;
      f.push_back(n);
    }
     else if(d[i]=="-"){
     ExprTreeNode* n=new ExprTreeNode();
      n->type="SUB";
       //cout<<"hi2"<<endl;
      f.push_back(n);
    }
     else if(d[i]=="*"){
     ExprTreeNode* n=new ExprTreeNode();
      n->type="MUL";
       //cout<<"hi3"<<endl;
      f.push_back(n);
    }
    else if(d[i]=="/"){
     ExprTreeNode* n=new ExprTreeNode();
      n->type="DIV";
      // cout<<"hi4"<<endl;
      f.push_back(n);
    }
    else if(d[i][0]<'A'){
     ExprTreeNode* n=new ExprTreeNode();
n->type="VAL";
     //cout<<" my value is : "<<n->val->get_frac_str();
      // n->type="DIV";
      UnlimitedInt* num=new UnlimitedInt(d[i]);
      UnlimitedInt* num2=new UnlimitedInt(1);
      UnlimitedRational* frac=new UnlimitedRational(num,num2);
      n->val=frac;
      f.push_back(n);
      //cout<<"hi5"<<endl;
    }
    else{
     //cout<<"hello"<<endl;
      ExprTreeNode*n =new ExprTreeNode();
       n->type="VAR";
        //cout<<"hi6"<<endl;
       n->id=d[i];
      // cout<<n->id<<endl;
      // cout<<n->val<<endl;
        //cout<<a->val<<endl;
      f.push_back(n);
    }
  } 
 
  vector<ExprTreeNode*>yd;
  for(int k=0;k<f.size();k++){
    if(f[k]->type=="B" && f[k]->id=="("){
      // cout<<"hi10"<<endl;
      yd.push_back(f[k]);

    }
    else if(f[k]->type=="B" && f[k]->id==")"){
       //cout<<"hi11"<<endl;
      ExprTreeNode*b=yd.back();
      //cout<<b->type<<endl;
      //cout<<b->val->get_frac_str()<<endl;
      yd.pop_back();
      ExprTreeNode*o=yd.back();
      yd.pop_back();
       ExprTreeNode*a1=yd.back();
      yd.pop_back();
      yd.pop_back();//bracket "("
      
      //yd.pop_back();
      o->left=a1;
      o->right=b;
      yd.push_back(o);
      //cout<<yd.back()->type<<endl;     
    }
    else{
      yd.push_back(f[k]);
       //cout<<"hi18"<<endl;
    }
  }
  //cout<<yd[0]->type<<endl;
 return yd[0];
  
}
void Evaluator::parse(vector<string> code){
  ExprTreeNode* node=new ExprTreeNode();
  node->type = ":=";
  node->id=":=";
  node->left=new ExprTreeNode();
  node->left->type="VAR";
  node->left->id=code[0];
 // node->left->evaluated_value=symtable->search(node->id);
  //cout<<node->left->id<<endl;
  
  node->right=parse1(code);
 
  expr_trees.push_back(node);

}

UnlimitedRational* Evaluator1(ExprTreeNode* node,SymbolTable* symtable){
 
  if(node->left==nullptr && node->right==nullptr){
    if(node->type=="VAL"){
         node->evaluated_value = node->val;
         return node->val;
    }
  else if(node->type=="VAR"){
     //cout<<"dragon1"<<endl;
    node->val=symtable->search(node->id);
  
    node->evaluated_value = node->val;
   
    return node->evaluated_value;                                                                                 
  }
  }
   
  UnlimitedRational* d;

  if(node->type=="VAL"){

   UnlimitedRational* a=node->val;
    UnlimitedInt*p=new UnlimitedInt(a->get_p()->get_array(),a->get_p()->get_capacity(),a->get_p()->get_sign(),a->get_p()->get_size());
    UnlimitedInt*q=new UnlimitedInt(a->get_q()->get_array(),a->get_q()->get_capacity(),a->get_q()->get_sign(),a->get_q()->get_size());
    node->evaluated_value=new UnlimitedRational(p,q);
    //delete p;
    //delete q;
    return node->evaluated_value;
    // cout<<"alert"<<endl;
    // cout<<node->val->get_frac_str()<<endl;
  }
  else if(node->type=="VAR"){
    // cout<<"alert"<<endl;
    // cout<<node->val->get_frac_str()<<endl;
   node->evaluated_value=symtable->search(node->id);
   UnlimitedRational* a=node->evaluated_value;
    UnlimitedInt*p=new UnlimitedInt(a->get_p()->get_array(),a->get_p()->get_capacity(),a->get_p()->get_sign(),a->get_p()->get_size());
    UnlimitedInt*q=new UnlimitedInt(a->get_q()->get_array(),a->get_q()->get_capacity(),a->get_q()->get_sign(),a->get_q()->get_size());
    node->evaluated_value=new UnlimitedRational(p,q);
    //delete p;
    //delete q;
    return node->evaluated_value;
  }
  else if(node->type=="ADD"){
   // cout<<"alert"<<endl;
   // cout<<node->val->get_frac_str()<<endl;
    node->evaluated_value=d->add(Evaluator1(node->left,symtable),Evaluator1(node->right,symtable));
    return node->evaluated_value;
  }
   else if(node->type=="SUB"){
    node->evaluated_value=d->sub(Evaluator1(node->left,symtable),Evaluator1(node->right,symtable));
    return node->evaluated_value;
  }
   else if(node->type=="MUL"){
    //cout<<"hi01"<<endl;
    node->evaluated_value=d->mul(Evaluator1(node->left,symtable),Evaluator1(node->right,symtable));
    return node->evaluated_value;
  }
  else if(node->type=="DIV"){
    //cout<<"start"<<endl;
    node->evaluated_value=d->div(Evaluator1(node->left,symtable),Evaluator1(node->right,symtable));
    return node->evaluated_value;
  }
  

}
void Evaluator:: eval(){
    
   
    ExprTreeNode* temp=expr_trees.back();
    expr_trees.pop_back();
    UnlimitedRational* a1=Evaluator1(temp->right,symtable);
    temp->left->evaluated_value = a1;
    symtable->insert(temp->left->id,a1);
    expr_trees.push_back(temp);
   
}