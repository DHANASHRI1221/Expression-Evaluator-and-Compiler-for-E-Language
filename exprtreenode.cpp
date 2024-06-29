/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
ExprTreeNode ::ExprTreeNode()
{
    type="";
    val=nullptr;
    evaluated_value=nullptr;
    left=nullptr;
    right=nullptr;


}

ExprTreeNode ::ExprTreeNode(string t, UnlimitedInt *v)
{
  type=t;

    

  if(t=="VAL"){
      val=new UnlimitedRational(v,new UnlimitedInt("1"));
      evaluated_value=nullptr;
     id="";
    left=nullptr;
    right=nullptr;
    }
    else if(t=="VAR"){
      // id="";
      val=nullptr;
      evaluated_value=new UnlimitedRational(v,new UnlimitedInt("1"));
       id="";
    left=nullptr;
    right=nullptr;
    }
    else{
      evaluated_value=new UnlimitedRational(v,new UnlimitedInt("1"));
      val=nullptr;
      id="";
    left=nullptr;
    right=nullptr;
    }
     


}
ExprTreeNode ::  ExprTreeNode(string t, UnlimitedRational* v){
    type=t;
    if(t=="VAL"){
      val=v;
      evaluated_value=nullptr;
      
        id="";   
    left=nullptr;
    right=nullptr;
     
    }
     else if(t=="VAR"){
      
      // id="";
      val=nullptr;
      evaluated_value=v;
      
        id="";   
    left=nullptr;
    right=nullptr;
    }
    else{
      evaluated_value=v;
      val=nullptr;
      
        id="";   
    left=nullptr;
    right=nullptr;
    
    }
    
    
  

}


ExprTreeNode ::~ExprTreeNode()
{
   delete val;
   delete evaluated_value;
   delete left;
   delete right; 
}