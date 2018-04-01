#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define vofv vector <vector <double> >
#define vec vector <double>
#define INT_MAX 1e5

void display(vofv arr){
	cout<<endl;
	for(int i=0;i<arr.size();i++){
		for(int j=0;j<arr[0].size();j++){
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
}
void displayc(vec cost){
	cout<<endl;
	for(int i=0;i<cost.size();i++){
		cout<<cost[i]<<" ";
	}
}

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

void zj_cj(vofv arr, vec cost,vec bvar,vec &delta,int m,int n){
	delta.clear();
	double sum;
	vector <double> zjj;
	for(int i=0;i<n+m;i++){
		sum=0;
		for(int j=0;j<m;j++){
			sum+=cost[bvar[j]]*arr[j][i];
		}
		zjj.pb(sum);
	}
	for(int i=0;i<n+m;i++){
		delta.pb(zjj[i]-cost[i]);
	}
}
void simplex(vofv &arr, vec &cost,vec &bvar,vec &delta,vec minratio,int m,int n){

    zj_cj(arr,cost,bvar,delta,m,n);
	//int kk=0;
	while(*min_element(delta.begin(),delta.end())<0)
	/*For Debugging
	while(kk<6)*/
	{		
			//++kk;
			
			//displayc(delta);
			//column number which enters basis
			int enter_var = distance(delta.begin(),min_element(delta.begin(),delta.end()));
			for(int i=0;i<m;i++){
				if(arr[i][enter_var]>0)
				minratio.pb(arr[i][n+m]/arr[i][enter_var]);	
				else
				minratio.pb(INT_MAX);	
			}
			//displayc(minratio);
			
			//row number which leaves basis
			int leav_var = distance(minratio.begin(),min_element(minratio.begin(),minratio.end()));
			//cout<<endl<<arr[leav_var][enter_var]<<endl;
			bvar[leav_var]=enter_var;
			/*cout<<"\nBVAR\n";
			displayc(bvar);
			cout<<endl;*/
			
			double pivot=arr[leav_var][enter_var];
			for(int i=0;i<=n+m;i++){
				arr[leav_var][i]/=pivot;
			}
			for(int i=0;i<m;i++){
				if(i!=leav_var){
					pivot=arr[i][enter_var];
					for(int j=0;j<=n+m;j++){
						arr[i][j]-=pivot*arr[leav_var][j];
				    }
				}		
			}
			//display(arr);
			delta.clear();
			minratio.clear();
			zj_cj(arr,cost,bvar,delta,m,n);	
		}
}
double optimum(vofv arr,vec bvar,vec cost,int m,int n){
	double opt=0;
	for(int i=0;i<m;i++){
		opt+=cost[bvar[i]]*arr[i][n+m];
	}
	return opt;
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
 
