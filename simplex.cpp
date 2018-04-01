#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define vofv vector <vector <double> >
#define vec vector <double>

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

void input(vofv &arr, vec &cost,int m,int n)
{
	ll x;
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
 
