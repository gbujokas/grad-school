#include<iostream>

using namespace std;

int main(){
  int m,dim;
  for(int d=1;d<=37;d++){
    m=(19*d-2)/60;
    if(60*m+3-19*d<=0)
      m++;
    dim=d*d+3*d+2-10*m*m-10*m;
    dim/=2;
    cout<<"Case d="<<d<<" m="<<m<<" degree left:"<<d-3*(2*(10*m-3*d)+1)<<" dim="<<dim<<endl;
    if(dim>0)
      cout<<"Found exceptional case!";
    cout<<endl;

  }
  cout<<"No more cases."<<endl<<endl;

  
  cout<<"Computing cases not coveres by conjecture:"<<endl;
  int d,counter=1;
  for(int m=37;m<=300;m++){
    d=(19*m-1)/6;
    if(19*d-60*m-3 >=0)
      cout<<"Case "<<counter++<<": d="<<d<<" m="<<m<<" gap:"<<d*d-10*m*m<<endl;
  }
  cout<<"All cases up to m=300"<<endl;
}
