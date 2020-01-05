//Level 1
// Basically u input the path on the inpmaze.txt and u get the prob.txt which will the values 
// given in the RFID tags

#include<bits/stdc++.h>
using namespace std;
const int n=5;
char arr[n][n];
int maze[n][n];
int main()
{
	freopen("inpmaze.txt", "r", stdin);
	freopen("prob.txt", "w", stdout);

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin>>arr[i][j];
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			maze[i][j]=0;
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(arr[i][j]=='.'){
				if(i>0) maze[i-1][j]++;
				if(i<n-1) maze[i+1][j]++;
				if(j>0) maze[i][j-1]++;
				if(j<n-1) maze[i][j+1]++;
			}
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout<<maze[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;	
}