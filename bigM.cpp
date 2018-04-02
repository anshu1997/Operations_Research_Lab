#include "simplex.h"
using namespace std;
#define INT_MAX 1e5


void input(vofv &arr, vec &cost,int m,int n,int p)
{
	double x;
	vector <double> v;
	
	cout<<"Enter the coefficents (along with b) of equations with <= sign: "<<endl;
    //m+n+p
	for(int i=0;i<m-p;i++)
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
		for(int k=i+1;k<m+p;k++){
			v.pb(0);
		}
		//----------------------
		cin>>x;
		v.pb(x);
		arr.pb(v);
	}
	
	cout<<"Enter the coefficents (along with b) of equations with >= sign: "<<endl;

	for(int i=0,kk=0;i<p;i++,kk++)
	{
		v.clear();
		for(int j=0;j<n;j++){
		  cin>>x;
		  v.pb(x);
		}
		//---------------------Adding surplus variables
		for(int k=0;k<i+m-p+kk;k++){
			v.pb(0);
		}
		v.pb(-1);
		v.pb(1);
		for(int k=i+m-p+kk+1;k<m+p-1;k++){
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
	for(int i=n;i<n+m+p;i++){
	 cost.pb(0);
	}
	
	for(int j=m-p;j<m;j++){
		for(int i=n;i<n+m+p;i++){
			if(arr[j][i]==1)
			    cost[i]=-INT_MAX;	
	   }	
	}
	//displayc(cost);
}
 
int main(){
vofv arr; vec cost;
int m,n,p;
vec minratio,delta, bvar;
cout<<"Enter the number of equations"<<endl;
cin>>m;
cout<<"Enter the number of variables"<<endl;
cin>>n;	
cout<<"Enter the number of equations with >= sign: "<<endl;
cin>>p;
input(arr,cost,m,n,p);
//display(arr);

/*initially bvar is a vector of basis vector variables*/
for(int j=0;j<m;j++){
	for(int i=n;i<n+m+p;i++){
	if(arr[j][i]==1)
	   bvar.pb(i);
   }	
}
//displayc(bvar);

simplex(arr,cost,bvar,delta,minratio,m,n+p);
cout<<endl<<"Optimum: "<<optimum(arr,bvar,cost,m,n+p);

return 0;	
}	
 
