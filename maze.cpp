#include<bits/stdc++.h>
using namespace std;


const int n = 6;
int maze[n][n];
int path[n][n];

int main(){
	freopen("prob.txt", "r", stdin);
	freopen("genmaze.txt", "w", stdout);

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin>>maze[i][j];
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			path[i][j]=1;
		}
	}


	// considering all 4 pts
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(maze[i][j]==4){
				path[i-1][j]=0;
				path[i+1][j]=0;
				path[i][j-1]=0;
				path[i][j+1]=0;
			}
		}
	}
	//corner pieces
	if(maze[0][0]==2){
		path[0][1]=0;
		path[1][0]=0;
	}

	if(maze[n-1][0]==2){
		path[n-1][1]=0;
		path[n-2][0]=0;
	}

	if(maze[0][n-1]==2){
		path[0][n-2]=0;
		path[1][n-1]=0;
	}

	if(maze[n-1][n-1]==2){
		path[n-1][n-2]=0;
		path[n-2][n-1]=0;
	}


	for(int i=1; i<=4; i++){
		if(maze[i][0]==3){
			path[i-1][0]=0;
			path[i+1][0]=0;
			path[i][1]=0;
		}
		if(maze[i][n-1]==3){
			path[i-1][n-1]=0;
			path[i+1][n-1]=0;
			path[i][n-2]=0;
		}
	}

	for(int i=1; i<=4; i++){
		if(maze[0][i]==3){
			path[0][i-1]=0;
			path[0][i+1]=0;
			path[1][i]=0;
		}
		if(maze[n-1][i]==3){
			path[n-1][i-1]=0;
			path[n-1][i+1]=0;
			path[n-2][i]=0;
		}
	}

	return 0;
}