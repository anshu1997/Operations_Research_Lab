#include "simplex.h"
using namespace std;

int input(vofv &arr, vec &cost,vec &costphase2,int m,int n)
{
	double x;
	//initially all are >= equations
	int p=n;
	vec v,b,flag;
	vofv arrtemp;
	for(int i=0;i<n;i++){
	flag.pb(1);
	}
	cout<<"Enter the coefficents (along with b): "<<endl;

	for(int i=0;i<m;i++)
	{
		v.clear();
		for(int j=0;j<n;j++){
		  cin>>x;
		  v.pb(x);
		}
		cin>>x;
		costphase2.pb(-x);//-x because maximization is converted to minimization
		arrtemp.pb(v);
	}
	cout<<"Enter the coefficients of cost function"<<endl;
	for(int i=0;i<n;i++){
	cin>>x;b.pb(x);
		if(x<0){
			flag[i]=-1;
			--p;
			//counts the number of equations which will become <=, i.e. 'n-p'
		}	
	}
	
	for(int g=0,kk=0;g<flag.size();g++){
		if(flag[g]==-1){
			// <= sign
				v.clear();
				for(int j=0;j<m;j++){
				  v.pb(-arrtemp[j][g]);
				}
				//---------------------Adding slack variables
				for(int k=0;k<kk;k++){
					v.pb(0);
				}
				v.pb(1);
				for(int k=kk+1;k<n+p;k++){
					v.pb(0);
				}
				//----------------------
				v.pb(-b[g]);
				arr.pb(v);
				++kk;			
		}
		else{
			// >= sign
				v.clear();
				for(int j=0;j<m;j++){
					v.pb(arrtemp[j][g]);
				}
				for(int k=0;k<kk;k++){
					v.pb(0);
				}
				v.pb(-1);
				v.pb(1);
				for(int k=kk+1;k<n+p-1;k++){
					v.pb(0);
				}
				v.pb(b[g]);
				arr.pb(v);
				kk+=2;	
		}
	}
	
	
	cout<<"Feeding coefficients of cost function for PHASE 1 : . . .   . . . "<<endl;
	for(int i=0;i<m+n+p;i++){
	cost.pb(0);
	}
	
	for(int j=0;j<n;j++){
		for(int i=m+1;i<n+m+p;i++){
			if((arr[j][i]==1)&&(arr[j][i-1]==-1))
			    cost[i]=-1;	
	   }	
	}
	return p;
}

int main()
{
	vofv arr; vec cost,costphase2;
	int m,n,p;
	vec minratio,delta, bvar;
	cout<<"Enter the number of equations"<<endl;
	cin>>m;
	cout<<"Enter the number of variables"<<endl;
	cin>>n;	
	p=input(arr,cost,costphase2,m,n);
	display(arr);
	//displayc(cost);	 
	//displayc(costphase2);
	cout<<"\nPHASE1\n";
	/*initially bvar is a vector of basis vector variables*/
	for(int j=0;j<n;j++){
		for(int i=m;i<n+m+p;i++){
		if(arr[j][i]==1)
		   bvar.pb(i);
	   }	
	}
	//displayc(bvar);
	simplex(arr,cost,bvar,delta,minratio,n,m+p);
	display(arr);
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
	displayc(pos);
	Delete artificials for Phase 2*/
	for(int j=0;j<pos.size();j++){
		for (int i = 0; i < arr.size(); ++i)
		{
		    arr[i].erase(arr[i].begin() + pos[j]-j);
		}
	}
	cout<<"\nPHASE2\n";	
	for(int i=m;i<n+m;i++){
		 costphase2.pb(0);
	}
	
	//displayc(costphase2);
	//Update bvar because some columns were deleted
	for(int i=0;i<bvar.size();i++){
		if(bvar[i]>=m){
			bvar[i]-=p;
		}
	}
	simplex(arr,costphase2,bvar,delta,minratio,n,m);
	display(arr);
	cout<<endl<<"Optimum: "<<optimum(arr,bvar,costphase2,n,m);
		
}
