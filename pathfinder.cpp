#include<bits/stdc++.h>
using namespace std;

const int n=5;
int maze[n][n];
char finalPath[n][n];
int vis[n][n];

bool findPath(int row, int col){
	if(row==n-1 && col==n-1){
		finalPath[row][col]='E';
		//cout<<"Path Found\n";
		return true;
	}


	if(row<n-1 && maze[row+1][col]==1 && vis[row+1][col]==0){
		vis[row+1][col]=1;
		if(findPath(row+1, col)){
			finalPath[row][col]='D';
			return true;
		}
	} 
	if(col<n-1 && maze[row][col+1]==1 && vis[row][col+1]==0){
		vis[row][col+1]=1;
		if(findPath(row, col+1)){
			finalPath[row][col]='R';
			vis[row][col]=1;
			return true;
		}
	}
	if(row>0 && maze[row-1][col]==1 && vis[row-1][col]==0){
		vis[row-1][col]=1;
		if(findPath(row-1, col)){
			finalPath[row][col]='U';
			vis[row][col]=1;
			return true;
		}
	} 
	if(col>0 && maze[row][col-1]==1 && vis[row][col-1]==0) {
		vis[row][col-1]=1;
		if(findPath(row, col-1)){
			finalPath[row][col]='L';
			vis[row][col]=1;
			return true;
		}
	}
	vis[row][col]=1;
	return false;
}


int main(){

	freopen("genmaze.txt", "r", stdin);
	freopen("finalPath.txt", "w", stdout);

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin>>maze[i][j];
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			vis[i][j]=0;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			finalPath[i][j]='X';
		}
	}
	char currentState='D';
	finalPath[0][0]='S';
	vis[0][0]=1;
	if(findPath(0, 0)){
		//cout<<"Done!";
		int row=0, col=0;
		while(finalPath[row][col]!='E'){
			
			char direction = finalPath[row][col];
			if(direction == 'L'){
				col--;
				if(currentState == 'D'){
					cout<<"90 Right\nForward\n";
				}else if(currentState == 'U'){
					cout<<"90 Left\nForward\n";
				}else if(currentState =='L'){
					cout<<"Forward\n";
				}
				currentState = 'L';
			} 
			else if(direction == 'R') {
				col++;
				if(currentState == 'D'){
					cout<<"90 Left\nForward\n";
				}else if(currentState == 'U'){
					cout<<"90 Right\nForward\nForward\n";
				}else if(currentState =='R'){
					cout<<"Forward\n";
				}
				currentState = 'R';
			}
			else if(direction == 'U') {
				row--;
				if(currentState == 'R'){
					cout<<"90 Left\nForward\n";
				}else if(currentState == 'L'){
					cout<<"90 Right\nForward\nForward\n";
				}else if(currentState =='U'){
					cout<<"Forward\n";
				}
				currentState = 'U';
			}
			else if(direction == 'D') {
				row++;
				if(currentState == 'R'){
					cout<<"90 Right\nForward\n";
				}else if(currentState == 'L'){
					cout<<"90 Left\nForward\n";
				}else if(currentState =='D'){
					cout<<"Forward\n";
				}
				currentState = 'D';
			}
		}
		cout<<"Stop";
	}else{
		cout<<"Sorry!";
	}
 	
	return 0;
}