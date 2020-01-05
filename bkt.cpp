#include<bits/stdc++.h>
using namespace std;


const int n = 5;
int maze[n][n];
int path[n][n];

void outputPath(){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout<<path[i][j]<<" ";
		}
		cout<<endl;
	}
}


bool ifPossible(){
	int temp[n][n];
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			temp[i][j]=0;
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(path[i][j]==0){
				if(i>0) temp[i-1][j]++;
				if(i<n-1) temp[i+1][j]++;
				if(j>0) temp[i][j-1]++;
				if(j<n-1) temp[i][j+1]++;
			}
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(maze[i][j]!=temp[i][j]){
				return false;
			}
		}
	}
	return true;
}

bool findVacant(int &row, int &col){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(path[i][j]==-1){
				row=i;
				col=j;
				return false;
			}
		}
	}

	return true;
}

bool chkone(int row, int col){
	if(row>0 && path[row-1][col]==1) return true;
	if(col>0 && path[row][col-1]==1) return true;
	if(row<n-1 && path[row+1][col]==1) return true;
	if(col<n-1 && path[row][col+1]==1) return true;

	return false;
}

bool genPath(){
	int row, col;
	if(findVacant(row, col)){
		return ifPossible();
	}
	if((row==0 || row == n-1 || col ==0 || col == n-1)&&(maze[row][col]==1)){
		path[row][col]=1;
		if(genPath()) return true;
		path[row][col]=0;
		if(genPath()) return true;
		path[row][col]=-1;
		return false;
	}else{
		path[row][col]=0;
		if(genPath()) return true;
		path[row][col]=1;
		if(genPath()) return true;

		path[row][col]=-1;
		return false;
	}
}

void setzero(int row, int col){
	if(row>0) path[row-1][col]=1;
	if(row<n-1) path[row+1][col]=1;
	if(col>0) path[row][col-1]=1;
	if(col<n-1) path[row][col+1]=1;
}

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
			path[i][j]=-1;
			if(maze[i][j]==0) setzero(i, j);
		}
	}

	path[0][0]=1;
	path[n-1][n-1]=1;
	for(int i=1; i<n-1; i++){
		for(int j=1; j<n-1; j++){
			if(maze[i][j]==4){
				path[i-1][j]=0;
				path[i+1][j]=0;
				path[i][j-1]=0;
				path[i][j+1]=0;
			}
		}
	}
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

	if(genPath()){
		//cout<<"DONE!\n";
		outputPath();
	}else{
		cout<<"OOps!\n";
		outputPath();
	}

	//cout<<"\nTime Elapsed : " << 1.0*clock() / CLOCKS_PER_SEC << " s\n";

	return 0;
}