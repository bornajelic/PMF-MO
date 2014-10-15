#include<iostream>
#include"surd.h"
using namespace std;

int main(){
  Surd a(0,1,2),b(2,-1,-3);
//  cout<<a+3<<'|'<<~(3-a)<<'|'<<Surd::NaS*0<<endl;
//  cout<<(b*~b==*b)<<endl;
//  cout<<(a<2)<<(2<a)<<(a<1)<<(1<a)<<endl;
//  cout<<(b<2)<<(2<b)<<(a<b)<<(b<a)<<endl;
  cout<<(Surd::NaS==b)<<endl;
  cout<<Surd::NaS*a<<endl;
  cout<<(Surd::NaS^4)<<endl;
  
  return 0;
}