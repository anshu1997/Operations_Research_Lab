#include "simplex.h"
using namespace std;

void input(vofv &arr, vec &cost,int m,int n,int p)
{
	double x;
	vec v;
	
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

	cout<<"Feeding coefficients of cost function for PHASE 1 : . . .   . . . "<<endl;
	for(int i=0;i<n;i++){
	//cin>>x;
	cost.pb(0);
	}
	for(int i=n;i<n+m+p;i++){
	 cost.pb(0);
	}
	
	for(int j=m-p;j<m;j++){
		for(int i=n;i<n+m+p;i++){
			if(arr[j][i]==1)
			    cost[i]=-1;	
	   }	
	}
	
	//displayc(cost);cout<<endl;
}
 
int main(){
vofv arr; vec cost;
double x;
int m,n,p;
vec minratio,delta, bvar;
cout<<"Enter the number of equations"<<endl;
cin>>m;
cout<<"Enter the number of variables"<<endl;
cin>>n;	
cout<<"Enter the number of equations with >= sign: "<<endl;
cin>>p;
input(arr,cost,m,n,p);
cout<<"\nPHASE1\n";
display(arr);

/*initially bvar is a vector of basis vector variables*/
for(int j=0;j<m;j++){
	for(int i=n;i<n+m+p;i++){
	if(arr[j][i]==1)
	   bvar.pb(i);
   }	
}
//displayc(bvar);

simplex(arr,cost,bvar,delta,minratio,m,n+p);

//get positions of artificial vars from cost array
//Delete ^these columns
//Make new cost array
//Run simplex again
vec pos;
for(int i=0;i<cost.size();i++){
	if(cost[i]==-1)
	   pos.pb(i);
}
/*cout<<"\nPOSITIONS of artificial vars\n";
displayc(pos);*/
for(int j=0;j<pos.size();j++){
	for (int i = 0; i < arr.size(); ++i)
	{
	    arr[i].erase(arr[i].begin() + pos[j]-j);
	}
}
cout<<"\nPHASE2\n";
display(arr);	
cost.clear();
cout<<"Enter the coefficients of cost function: "<<endl;
for(int i=0;i<n;i++){
	cin>>x;cost.pb(x);
}
for(int i=n;i<n+m;i++){
	 cost.pb(0);
}

//displayc(cost);
simplex(arr,cost,bvar,delta,minratio,m,n);
cout<<endl<<"Optimum: "<<optimum(arr,bvar,cost,m,n);

return 0;	
}	
 
