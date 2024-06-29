#include"ulimitedint.h"
string abs1(string d)
{
  string b;
  int sizex = d.length();

  if (sizex > 0 && d[0] == '-')
  {
    for (int i = 1; i < sizex; i++)
    {
      b = b + d[i];
    }
    return b;
  }

  return d;
}
bool check(UnlimitedInt *i1){
  int* a1=i1->get_array();
  int s=i1->get_size();
  
  while(s--){
    if(a1[s]!=0){
      return false;
    }
  }
  return true;
}
UnlimitedInt ::UnlimitedInt()
{
  
  size = 0;
    capacity = size;

  sign = 1;
  unlimited_int = new int[size]();
}
UnlimitedInt ::UnlimitedInt(string s)
{
  
  size = s.length();
  capacity =size;
  sign = 1;
  // unlimited_int = new int[capacity]();



  // int arr[size];
  // if (size == 1 && s[0] == '0')
  // {
  //   size = 1;
  //   sign = 0;
  //   unlimited_int[0] = 0;

  //   return;
  // }
  int i=0;
  while(i<size){
    if(s[i]!='0'){
      break;
    }
    i++;
  }
  if(i==size){
    
    size = 1;
    sign = 1;
    capacity=size;

    unlimited_int = new int[1];
    unlimited_int[0] = 0;

    return;
  }
  unlimited_int = new int[size]();
  // while (size > capacity)
  // {
  //   capacity *= 2;
  //   delete[] unlimited_int;
  //   unlimited_int = new int[capacity]();
  // }
  
  if (s[0] == '-')
  {
    sign = -1;
    int m = 1;
    while (m < size && s[m] == '0')
    {
      m++;
    }

    if (m == size)
    {

      size = 1;
      sign = 1;

      unlimited_int[0] = 0;
      return;
    }

    for (int i = m; i < size; i++)
    {
      int x = s[i] - '0';
      unlimited_int[i - m] = x;
    }
    size -= m;
  }
  else
  {
    // for (int i = 0; i < size; i++)
    // {
    //   int x = s[i] - '0';
    //   unlimited_int[i] = x;
    // }
    int m=0;
     while (m < size && s[m] == '0')
    {
      m++;
    }

    if (m == size)
    {

      size = 1;
      sign = 1;

      unlimited_int[0] = 0;
      return;
    }

    for (int i = m; i < size; i++)
    {
      int x = s[i] - '0';
      unlimited_int[i - m] = x;
    }
    size -= m;
  }
}

UnlimitedInt ::UnlimitedInt(int i)
{
  // capacity = 1000;
  size = 0;
  capacity=size;
  sign = 1;
  unlimited_int = new int[size]();
  if (i == 0)
  {
    size = 1;
    sign = 1;

    unlimited_int[0] = 0;
    return;
  }

  if (i < 0)
  {

    sign = -1;
    i = (-i);
  }

  int numDigits = 0;
  int temp = i;

  while (temp > 0)
  {
    temp /= 10;
    numDigits++;
  }

  
  size = numDigits;
  for (int j = numDigits - 1; j >= 0; j--)
  {
    unlimited_int[j] = i % 10;

    i /= 10;
  }
}

UnlimitedInt ::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{

  if (cap < 0)
  {
    cap = 1000;
  }
  size = sz;

  sign = sgn;

  capacity = cap;

  if (size > capacity)
  {

    capacity = size;
  }
  this->unlimited_int = new int[size]();
  for (int i = 0; i < size; i++)
  {

    this->unlimited_int[i] = ulimited_int[i];
  }
}

UnlimitedInt ::~UnlimitedInt()
{
  delete[] unlimited_int;
}

int UnlimitedInt ::get_size()
{
  return size;
}

int *UnlimitedInt ::get_array()
{
  return unlimited_int;
}

int UnlimitedInt ::get_sign()
{

  return sign;
}
int UnlimitedInt ::get_capacity()
{
  return capacity;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{

  int *a1 = i1->get_array();
  int *a2 = i2->get_array();
  int size1 = i1->get_size();
  int size2 = i2->get_size();
  int sign1 = i1->get_sign();
  int sign2 = i2->get_sign();
  string s1 = abs1(i1->to_string());
  string s2 = abs1(i2->to_string());

  if (i1->get_sign() == 1 && i2->get_sign() == 1)
  { // add if both have same sign
    int diff = size1 - size2;
    string d;
    if (diff > 0)
    {
      int i = i2->get_size();
      int carry = 0;
      while (i--)
      {
        int num = a1[i + diff] + a2[i] + carry;
        d = std::to_string(num % 10) + d;
        carry = num / 10;
      }
      while (diff--)
      {
        int num = a1[diff] + carry;
        carry = num / 10;
        d = std::to_string(num % 10) + d;
      }

      UnlimitedInt *final = new UnlimitedInt(d);
      return final;
    }
    else if (diff == 0)
    {
      int i = i2->get_size();
      int carry = 0;
      while (i--)
      {
        int num = a1[i + diff] + a2[i] + carry;
        d = std::to_string(num % 10) + d;
        carry = num / 10;
      }
      d = std::to_string(carry) + d;
      UnlimitedInt *final = new UnlimitedInt(d);
      return final;
    }
    else
    {
      UnlimitedInt *final = add(i2, i1);
      return final;
    }
  }
  else if (sign1 != 1 && sign2 == 1)
  {
    UnlimitedInt *test = new UnlimitedInt(s1);
    UnlimitedInt *final = sub(test, i2);
    final->sign = -1*(final->sign);
    return final;
  }

  else if (sign1 == 1 && sign2 != 1)
  {

    UnlimitedInt *test = new UnlimitedInt(s2);
    UnlimitedInt *final = sub(i1, test);
   //  final->sign = -1*(final->sign);
    return final;
  }
  else if (sign1 != 1 && sign2 != 1)
  {
    UnlimitedInt *test1 = new UnlimitedInt(s1);
    UnlimitedInt *test2 = new UnlimitedInt(s2);
    UnlimitedInt *final = add(test1, test2);
    final->sign = -1;
    return final;
  }
  return nullptr;
}

UnlimitedInt *UnlimitedInt ::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
  int *a1 = i1->get_array();
  int *a2 = i2->get_array();
  int size1 = i1->get_size();
  int size2 = i2->get_size();
  int sign1 = i1->get_sign();
  int sign2 = i2->get_sign();
  string s1 = abs1(i1->to_string());
  string s2 = abs1(i2->to_string());

  if (i1->get_sign() == 1 && i2->get_sign() == 1)
  { // add if both have same sign
    int diff = size1 - size2;

    if (diff >= 0)
    {
      if (diff == 0)
      {
        int j = 0;
        while (j < size1)
        {
          if(a1[j]>a2[j]){
            break;
          }
          if (a1[j] < a2[j])
          {
            UnlimitedInt *final = sub(i2, i1);
            final->sign = -1;
            return final;
          }
          j++;
        }
      }
      string d;
      int i = size2;
      while (i--)
      {
        if (a1[i + diff] < a2[i])
        {
          a1[i + diff - 1]--;
          a1[i + diff] = a1[i + diff] + 10;
        }
        int n = a1[i + diff] - a2[i];
        string m = std::to_string(n);
        d = m + d;
      }

      while (diff--)
      {
        if (a1[diff] < 0)
        {
          a1[diff - 1]--;
          a1[diff] = a1[diff] + 10;
        }
        int n = a1[diff];
        string m = std::to_string(n);
        d = m + d;
      }

      UnlimitedInt *final = new UnlimitedInt(d);

      final->sign = 1;
      return final;
    }

    else
    {
      UnlimitedInt *final = sub(i2, i1);
      //cout<<final->to_string();
      final->sign = -1;
      return final;
    }
  }
  else if (sign1 != 1 && sign2 == 1)
  {
    UnlimitedInt *test = new UnlimitedInt(s1);
    UnlimitedInt *final = add(test, i2);
    final->sign = -1;
    return final;
  }

  else if (sign1 == 1 && sign2 != 1)
  {
    UnlimitedInt *test = new UnlimitedInt(s2);
    UnlimitedInt *final = add(i1, test);
    final->sign = 1;
    return final;
  }
  else if (sign1 != 1 && sign2 != 1)
  {
    UnlimitedInt *test1 = new UnlimitedInt(s1);
    UnlimitedInt *test2 = new UnlimitedInt(s2);
    UnlimitedInt *final = sub(test1, test2);
    final->sign = (-1)*(final->sign);
    return final;
  }
return nullptr;
  
}

UnlimitedInt *UnlimitedInt ::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{

  if (i1 == nullptr || i2 == nullptr)
  {
    return nullptr;
  }

  int size1 = i1->get_size();

  int size2 = i2->get_size();
  int sizex = size1 + size2;
  int *test = new int[sizex]();

  for (int i = size1 - 1; i >= 0; i--)
  {
    int c = 0;
    int d1 = i1->get_array()[i];

    for (int j = size2 - 1; j >= 0; j--)
    {
      int d2 = i2->get_array()[j];
      int p = d1 * d2 + test[i + j + 1] + c;
      c = p / 10;
      test[i + j + 1] = p % 10;
    }
    
    test[i] += c;
    

  }
  string g="";
  //bool lead=true;
  for(int i=0;i<sizex;i++ ){
    g=g+std::to_string(test[i]);
  }

 int signx = (i1->get_sign() * i2->get_sign());
 if (signx==-1) g="-" +g;
 // UnlimitedInt *final = new UnlimitedInt(test, sizex, signx, sizex);

 UnlimitedInt *final = new UnlimitedInt(g);


  return final;
}


//////////////////////////////////////////////


string checkmiddle(string s) {
    string ans = "";
    int carrrrrry = 0;

    for (char digit : s) {
        int currentDigit = digit - '0';
        int quotient = (currentDigit + 10 * carrrrrry) / 2;
        carrrrrry = (currentDigit + 10 * carrrrrry) % 2;
        ans += to_string(quotient);
    }

    // Remove leading zeros
    while (ans.size() > 1 && ans[0] == '0') {
        ans.erase(0, 1);
    }

    return ans;
}


///////////////////////////////////////////////
















UnlimitedInt *UnlimitedInt ::div(UnlimitedInt *i1, UnlimitedInt *i2)
{

 
     

     int size1,size2,sign1,sign2;
    size1 = i1->get_size(),size2 = i2->get_size();
    sign1 = i1->get_sign(),sign2= i2->get_sign();
    string d1,d2;
    string finalanswer;
    if(sign1 == -1){
            i1->sign = -1*i1->sign;
            d1 = i1->to_string();
            i1->sign = -1*i1->sign;
    }
    else d1 = i1->to_string();
    if(sign2 == -1){
            i2->sign = -1*i2->sign;
            d2 = i2->to_string();
            i2->sign = -1*i2->sign;
    }
    else d2 = i2->to_string();
    int flag = 0;
    if(d2=="0") finalanswer = "0";
    else if(d1 == d2) finalanswer = "1";    
    else if(d2 == "1") finalanswer = d1;   
    else if(d1 == "0" || size1<size2) finalanswer = "0";    
    else{
        UnlimitedInt* r1 = new UnlimitedInt(d2);
        UnlimitedInt* r2 = new UnlimitedInt(d1); 
        string D0 = d1,ze = "0";
        string mid;
        UnlimitedInt* t1 = new UnlimitedInt(D0);
        UnlimitedInt* t2 = new UnlimitedInt(ze);
        UnlimitedInt* check = sub(t1,t2);
        UnlimitedInt* sbt = nullptr;
        UnlimitedInt* myu = nullptr;
        UnlimitedInt* ad = nullptr;
        while(check->get_sign() == 1){
            ad = UnlimitedInt::add(t1,t2);
            string naughty = ad->to_string();
            mid = checkmiddle(naughty);
            UnlimitedInt* midd = new UnlimitedInt(mid);
            myu = mul(midd,r1);
            sbt = sub(myu,r2);
            if(mid == ze || mid == D0 || sbt->to_string() == "0"){
               // delete midd;
                break;
            }
            if(sbt->get_sign() == 1){

                D0 = mid;
            }
            else if(sbt->get_sign()== -1){
                ze = mid;
            }
            else{
                //delete midd;
                break;
            }
            t1 = new UnlimitedInt(D0);
            t2 = new UnlimitedInt(ze);
            check = sub(t1,t2);
            //delete midd;
            
        }
        finalanswer = mid;
        UnlimitedInt *t = new UnlimitedInt(finalanswer);
        if(mul(t,r1)->to_string() != r2->to_string()){
            flag = 1;
        }
        // delete ad;
        // delete t;
        // delete sbt;
        // delete check;
        // delete t1;
        // delete t2;
        // delete myu;
        // delete r1;
        // delete r2;
    }
    int sign = sign1*sign2;

    if(sign == -1){
        if(flag == 1){
            UnlimitedInt *t = new UnlimitedInt(finalanswer);
            UnlimitedInt* one = new UnlimitedInt("1");
            UnlimitedInt* res = UnlimitedInt::add(t,one);
            finalanswer = res->to_string();
            // delete t;
            // delete one;
            // delete res;
        }
        finalanswer = "-" + finalanswer;
    }
    UnlimitedInt* result = new UnlimitedInt(finalanswer);
    return result;



}


UnlimitedInt *UnlimitedInt ::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
  if (i1 == nullptr || i2 == nullptr)
  {
    return nullptr;
  }
  UnlimitedInt *a = i1;
  // cout<<a->to_string()<<endl;
  UnlimitedInt *b = i2;
  //cout<<b->to_string()<<endl;
  UnlimitedInt *result =div(a, b);
 // cout<<result->to_string();
  UnlimitedInt *prod = prod->mul(b, result);
//  cout<<prod->to_string()<<endl;
 // cout<<prod->to_string();
  UnlimitedInt *r = r->sub(a, prod);
  // cout<<r->to_string();
  // // delete a;
  // // delete b;
  // delete result;
  // delete prod;



  return r;
}

string UnlimitedInt ::to_string()
{
  if (size == 1 && unlimited_int[0] == 0)
  {
    return "0";
  }
  if (sign == -1)
  {

    string d = "-";
    for (int i = 0; i < size; i++)
    {

      char final = '0' + unlimited_int[i];
      d = d + final;
    }
    return d;
  }
  else
  {
    string d="";
    for (int i = 0; i < size; i++)
    {
      char final = '0' + unlimited_int[i];
      d = d + final;
    }
    return d;
  }
}