#include "simplex.h"
using namespace std;

void input(vofv &arr, vec &cost,int m,int n)
{
	double x;
	vector <double> v;
	
	cout<<"Enter the coefficents (along with b): "<<endl;

	for(int i=0;i<m;i++)
	{
		v.clear();
		for(int j=0;j<n;j++){
		  cin>>x;
		  v.pb(x);
		}
		//---------------------Adding slack variables
		for(int k=0;k<i;k++){
			v.pb(0);
		}
		v.pb(1);
		for(int k=i+1;k<m;k++){
			v.pb(0);
		}
		//----------------------
		cin>>x;
		v.pb(x);
		arr.pb(v);
	}

	cout<<"Enter the coefficients of cost function"<<endl;
	for(int i=0;i<n;i++){
	cin>>x;cost.pb(x);
	}
	for(int i=n;i<m+n;i++){
	cost.pb(0);
	}
}
 
int main(){
vofv arr; vec cost;
int m,n;
vec minratio,delta, bvar;
cout<<"Enter the number of equations"<<endl;
cin>>m;
cout<<"Enter the number of variables"<<endl;
cin>>n;	
input(arr,cost,m,n);

//initially bvar is a vector of slack variables
for(int i=n;i<n+m;i++){
	bvar.pb(i);
}

simplex(arr,cost,bvar,delta,minratio,m,n);
cout<<endl<<"Optimum: "<<optimum(arr,bvar,cost,m,n);
return 0;	
}	
 
