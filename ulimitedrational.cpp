
#include "ulimitedrational.h"

UnlimitedRational::UnlimitedRational()
{
  p=new UnlimitedInt(0);
  q=new UnlimitedInt(0);
//   int sign=1;
}

bool uisg(string s1,string s2){
    if (s1.length()>s2.length()) return true;
    else if (s1.length()<s2.length()) return false;
    else {
        return s1>=s2;
    }
}

bool uise(string s1,string s2){
    return s1==s2;
}

string uits(int i){
    string s="";
    if (i<=9) return s+static_cast<char>('0'+i%10);
    
    while (i>0)
    {
        s=static_cast<char>('0'+i%10)+s;
        i/=10;
    }
    
    return s;
    
}

string utos(UnlimitedInt *u){
    // if (u==nullptr) return "";
    string s="";
    for (int i=0;i<u->get_capacity();i++){
      s=s+uits(u->get_array()[i]);
    }
    return s;
}

  //  UnlimitedInt u1;
  //  UnlimitedInt* u2;

UnlimitedInt* gcd(UnlimitedInt* i1,UnlimitedInt * i2){
  // UnlimitedInt u;
  //cout<<"hi"<<endl;
  if(i1==nullptr || i2==nullptr){
    return nullptr;
  }
  UnlimitedInt* u1=new UnlimitedInt(i1->get_array(),i1->get_capacity(),i1->get_sign(),i1->get_size());
  UnlimitedInt* u2=new UnlimitedInt(i2->get_array(),i2->get_capacity(),i2->get_sign(),i2->get_size());

    if (uise(utos(u1),utos(u2))){
        // u=UnlimitedInt(i1.get_array(),i1.get_capacity(),i1.get_sign(),i1.get_size());
       // delete u2;
        return u1;
    }
    else {
        while (true){
            if (uisg(utos(u1),utos(u2))){
                u1=UnlimitedInt::mod(u1,u2);
                if (utos(u1)=="0"){
                   // delete u1;
                  
                    return u2;
                }
            }
            else {
                u2=UnlimitedInt::mod(u2,u1);
                if (utos(u2)=="0"){
                   // delete u2;
                   // cout<<"hi"<<endl;
                    return u1;
                }
            }
        }
        //delete u2;
        return u1;
    }
}



UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    
  if((num->get_size()==0) ||((num->get_size()==1) && (num->get_array()[0]==0))){
    p=new UnlimitedInt("0");
    q=new UnlimitedInt(den->to_string());
  }
  // else if(den->get_size()==0 && den->get_array()[0]==0){
  //   p=new UnlimitedInt("0");
  //   q=new UnlimitedInt("0");
  // }
  else if(num->to_string()=="1" || den->to_string()=="1"){
    p=num;
    q=den;
  }
  else{
    UnlimitedInt* gcd2=gcd(num,den);
    if(gcd2->get_size()==1 && gcd2->get_array()[0]==1 ){
        
        p=new UnlimitedInt(num->to_string());
        q=new UnlimitedInt(den->to_string());

    }
    else{
      //cout<<"hi"<<endl;
        UnlimitedInt* division1_num=UnlimitedInt::div(num,gcd2);
        UnlimitedInt* division1_den=UnlimitedInt::div(den,gcd2);
        p=new UnlimitedInt(division1_num->to_string());
        q=new UnlimitedInt(division1_den->to_string());
        

    }
    // delete gcd2;
  }

}


UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;

}

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}

UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str()
{// cout<<"in get p"<<endl;
return p->to_string();
   
}

string UnlimitedRational::get_q_str()
{
 return q->to_string();
}

string UnlimitedRational::get_frac_str()
{ //cout<<get_p_str()<< " is string of p"<<endl;
//cout<<get_q_str()<<" is string of  q"<<endl;
UnlimitedInt* q = this->get_q();
    if(this->q->get_size()==0 || q->get_array()[0]==0){
        return "0/0";
    }

  string num_str=get_p_str();
  string den_str=get_q_str();
  return num_str + "/" +den_str;
}

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if(i1==nullptr && i2==nullptr){
        return nullptr;
    }
    UnlimitedInt* n1=i1->get_p();
     UnlimitedInt* d1=i1->get_q();
      UnlimitedInt* n2=i2->get_p();
       UnlimitedInt* d2=i2->get_q();
       UnlimitedInt* numerator1= UnlimitedInt:: add(UnlimitedInt::mul(n1,d2),UnlimitedInt::mul(n2,d1));
       UnlimitedInt* denominator1=UnlimitedInt::mul(d1,d2);
       UnlimitedRational* result=new UnlimitedRational(numerator1,denominator1);
       //delete numerator1;
       // delete denominator1;
     return result;
    
}
UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
  if(i1==nullptr && i2==nullptr){
        return nullptr;
    }
    UnlimitedInt* n1=i1->get_p();
     UnlimitedInt* d1=i1->get_q();
      UnlimitedInt* n2=i2->get_p();
       UnlimitedInt* d2=i2->get_q();
       UnlimitedInt* numerator1= UnlimitedInt:: sub(UnlimitedInt::mul(n1,d2),UnlimitedInt::mul(n2,d1));
       UnlimitedInt* denominator1=UnlimitedInt::mul(d1,d2);
       UnlimitedRational* result=new UnlimitedRational(numerator1,denominator1);
       // delete numerator1;
       // delete denominator1;
     return result;
    
}
UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
  if(i1==nullptr && i2==nullptr){
        return nullptr;
    }
     UnlimitedInt* n1=i1->get_p();
     UnlimitedInt* d1=i1->get_q();
      UnlimitedInt* n2=i2->get_p();
       UnlimitedInt* d2=i2->get_q();
       UnlimitedInt* numerator1= UnlimitedInt::mul(n1,n2);
       UnlimitedInt* denominator1=UnlimitedInt::mul(d1,d2);
       UnlimitedRational* result=new UnlimitedRational(numerator1,denominator1);
       // delete numerator1;
       // delete denominator1;
     return result;
    

}
UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if(i1==nullptr && i2==nullptr){
        return nullptr;
    }
     UnlimitedInt* n1=i1->get_p();
     UnlimitedInt* d1=i1->get_q();
      UnlimitedInt* n2=i2->get_p();
       UnlimitedInt* d2=i2->get_q();
       UnlimitedInt* numerator1= UnlimitedInt::mul(n1,d2);
       UnlimitedInt* denominator1=UnlimitedInt::mul(d1,n2);
       UnlimitedRational* result=new UnlimitedRational(numerator1,denominator1);
       // delete numerator1;
       // delete denominator1;
       return result;
}