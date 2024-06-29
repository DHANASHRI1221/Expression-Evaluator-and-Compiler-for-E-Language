/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line
void clear1(ExprTreeNode* &root){
    if (root==nullptr) return;
    clear1(root->left);
    clear1(root->right);
    delete root;
    root=nullptr;
    return;
}

Parser::Parser(){
    symtable=new SymbolTable();
    last_deleted=-3;
}


vector<ExprTreeNode*> parse1(vector<string> d){
    vector<ExprTreeNode*> f;
    for (int i=2;i<d.size();i++){
        if (d[i]=="(" || d[i]==")"){
            ExprTreeNode*n=new ExprTreeNode();
            n->type="B";
            n->id=d[i];
            f.push_back(n);
        }
        else if (d[i]=="+"){
            ExprTreeNode* n=new ExprTreeNode();
            n->type="ADD";
            f.push_back(n);
        }
        else if (d[i]=="-"){
            ExprTreeNode* n=new ExprTreeNode();
            n->type="SUB";
            f.push_back(n);
        }
        else if (d[i]=="*"){
            ExprTreeNode* n=new ExprTreeNode();
            n->type="MUL";
            f.push_back(n);
        }
        else if (d[i]=="/"){
            ExprTreeNode* n=new ExprTreeNode();
            n->type="DIV";
            f.push_back(n);
        }
        else if (d[i]=="del"){
            ExprTreeNode* n =new ExprTreeNode();
            n->type="DEL";
            f.push_back(n);
        }
        else if (d[i]=="ret"){
            ExprTreeNode* n =new ExprTreeNode();
            n->type="RET";
            f.push_back(n);
        }
        else if (d[i][0]<'A'){
            ExprTreeNode* n=new ExprTreeNode("VAL",stoi(d[i]));
            // n->type="VAL";
            f.push_back(n);
        }
        else {
            ExprTreeNode*n=new ExprTreeNode();
            n->type="VAR";
            n->id=d[i];
            f.push_back(n);
        }
    }
    return f;
}

ExprTreeNode* parse2(vector<string> dt){
    vector<ExprTreeNode*> dim=parse1(dt);
    vector<ExprTreeNode*> yd;
    for (int i=0;i<dim.size();i++){
        if (dim[i]->type=="B" && dim[i]->id=="("){
            yd.push_back(dim[i]);
        }
        else if(dim[i]->type=="B" && dim[i]->id==")"){
            ExprTreeNode*b=yd.back();
            yd.pop_back();
            ExprTreeNode*o=yd.back();
            yd.pop_back();
            ExprTreeNode*a=yd.back();
            yd.pop_back();
            yd.pop_back();
            o->left=a;
            o->right=b;
            yd.push_back(o);
        }
        else {
            yd.push_back(dim[i]);
        }
    }
    return yd.back();

    
}


void Parser::parse(vector<string> expression){
    ExprTreeNode*root=new ExprTreeNode();
    root->type=":=";
    root->left=new ExprTreeNode();
    if (expression[0]!="del" && expression[0]!="ret"){
    root->left->id=expression[0];
    root->left->type="VAR";
    symtable->insert(root->left->id);
    }
    else {
        if (expression[0]=="del") {
            last_deleted=symtable->search(expression[2]);
            root->left->type="DEL";
            symtable->remove(expression[2]);
        }
        else root->left->type="RET";
    }
    root->right=parse2(expression);
    expr_trees.push_back(root);
}


Parser::~Parser(){
    int v=expr_trees.size();
    for (int i=v-1;i>=0;i--){
        clear1(expr_trees[i]);
    }
    delete symtable;
}


