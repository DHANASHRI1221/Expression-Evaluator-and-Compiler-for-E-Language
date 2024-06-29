/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"


string start(ExprTreeNode* node,SymbolTable* symtable1){
    if (node->type=="VAL"){
        return "PUSH " + std::to_string(node->num);
    }
    else if (node->type=="VAR"){
        return "PUSH mem[" + std::to_string(symtable1->search(node->id)) + "]";
    }
    else{
        return node->type;
    }
}



EPPCompiler::EPPCompiler(){
    // targ=Parser();
    memory_size=125;
    output_file="bye.txt";
    least_mem_loc=MinHeap();
    for (int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    // targ=Parser();
//     memory_size= mem_limit;
// output_file= out_file;
// mem_loc.resize(memory_size);
//   for(int i=0;i<memory_size;i++){
//   //  least_mem_loc.push_heap(i);
//     mem_loc.push_back(i);
//   }
    memory_size=mem_limit;
    output_file=out_file;
    least_mem_loc=MinHeap();
    for (int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    ofstream f(output_file);
    f.clear();
    f.close();
    for (int i=0;i<code.size();i++){
        targ.parse(code[i]);
        vector<string> v=generate_targ_commands();
        write_to_file(v);
    }
  //    for(int y=0;y<code.size();y++){
  // targ.parse(code[y]);
  // vector<string>command4= generate_targ_commands();
  
  // write_to_file( command4);
  // }
  
}

// void recursive_traverse(ExprTreeNode *root, vector<string> &command11, Parser targ,vector<int>& mem_loc)
// {
//     //cout<<"hello"<<endl;
//   if (root == NULL)
//   {
//     return;
//   }
//    //targ.parse(vector<string> command11);
//   recursive_traverse(root->left, command11, targ,mem_loc);
//   ExprTreeNode *temp = targ.expr_trees.back();
//   if (temp->type == "VAR")
//   {
//     int address = targ.symtable->search(temp->id);
//     if(address==-1){
//       // address=least_mem_loc.get_min();
//        address=mem_loc.front();
//        targ.symtable->assign_address(temp->left->id,address);
//        mem_loc.pop_back();
//     }
//     else{
//         targ.symtable->assign_address(temp->left->id,address);
//     }
//     string command1 = "PUSH mem[" + std::to_string(address) + "]";
//     command11.push_back(command1);
//   }
//   else if (temp->type == "VAL")
//   {
//       //cout<<"hi"<<endl;
//     int val1 = temp->num;
//     string command1 = "PUSH " + std::to_string(val1);
//     command11.push_back(command1);
//   }
//   else if (temp->type == "ADD")
//   {
//     string command1 = "ADD";
//     command11.push_back(command1);
//   }
//   else if (temp->type == "MUL")
//   {
//     string command1 = "MUL";
//     command11.push_back(command1);
//   }
//   else if (temp->type == "SUB")
//   {
//     string command1 = "SUB";
//     command11.push_back(command1);
//   }
//   else if (temp->type == "DIV")
//   {
//     string command1 = "DIV";
//     command11.push_back(command1);
//   }
//    recursive_traverse(root->right, command11, targ,mem_loc);

// }











vector<string> EPPCompiler::generate_targ_commands(){

  
    ExprTreeNode*root=targ.expr_trees.back();
    vector<string> v;
    vector<ExprTreeNode*> important;
    if (root->left->type=="DEL"){

        v.push_back("DEL = mem[" + to_string(targ.last_deleted) + "]");
   
        least_mem_loc.push_heap(targ.last_deleted);
        return v;
    }

    else if (root->left->type=="RET"){
        v.push_back("RET = POP");
    }
    else if (root->left->type=="VAR"){
        int k=targ.symtable->search(root->left->id);
        if (k==-2 || k==-1) {
            k=least_mem_loc.get_min();
            least_mem_loc.pop();
            targ.symtable->assign_address(root->left->id,k);
        }
        v.push_back("mem[" + to_string(k) + "] = POP");
    }

    
    important.push_back(root->right);
    while (!important.empty()){
        ExprTreeNode* node=important.back();
        important.pop_back();
        if (node==nullptr) continue;
     
        else{
            ExprTreeNode* left=node->left;
            ExprTreeNode* right=node->right;
            node->left=nullptr;
            node->right=nullptr;
            v.push_back(start(node,targ.symtable));
            important.push_back(right);
            important.push_back(left);
        }
    }
    return v;

//     ExprTreeNode *temp = targ.expr_trees.back();
   
//   vector<string> commands;
//  // targ.parse(commands);
//   if (temp->left->type == "DEL")
//   {
//    // int address = targ.symtable->search(temp->id);
//   int address=targ.last_deleted;
//     mem_loc.push_back(address);
//     string command1 = "DEL = mem[" + std::to_string(address) + "]";
//     commands.push_back(command1);
    
//   }
//   else if (temp->left->type == "VAR")
//   {
//     int address = targ.symtable->search(temp->id);
//     if(address==-1){
//        address=mem_loc.front();
//        targ.symtable->assign_address(temp->left->id,address);
//        mem_loc.pop_back();
//     }
//     else{
//         targ.symtable->assign_address(temp->left->id,address);
//     }
//     string command1 = "mem[" + std::to_string(address) + "] = POP";
//     commands.push_back(command1);
}

void EPPCompiler::write_to_file(vector<string> commands){
     ofstream mask(output_file, std::ios::app); 
    while (!commands.empty()){
        mask<<commands.back()<<endl;
        commands.pop_back();
    }
    mask.close();
}

EPPCompiler::~EPPCompiler(){
  
}



