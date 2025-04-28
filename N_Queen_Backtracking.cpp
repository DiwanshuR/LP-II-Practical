#include<iostream>
using namespace std;

void printBoard(int board[][10], int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool canPlace(int n, int board[][10], int i, int j) {
    //as we r putting queens from top to bottom so check only for these
    // 1. Top rows
    for(int k=i; k>=0; k--) {
        if(board[k][j] == 1) {
            return false;
        }
    }

    // 2.Top Left Diagonals
    int x = i, y=j;
    while(x>=0 && y>=0) {
        if(board[x][y] == 1) {
            return false;
        }
        x--;
        y--;
    }

    // 3. Top Right Digonals
    x = i, 
    y = j;
    while(x>=0 && y<n) {
        if(board[x][y] == 1) 
            return false;
            x--;
            y++;
    }

    return true;
}
bool solve(int n, int board[][10], int i) {
    //Base Case
    if(i >= n) {
        cout<<"Board after placing queens"<<endl;
        printBoard(board, n);
        
    }

    //for this row traverse it completely to find if there is a safe place to put a queen
    for(int j=0; j<n; j++) {
        if(canPlace(n, board, i, j)) {
            board[i][j] = 1;
            //move to next subproblem (next row)
            bool subProblemsuccess = solve(n, board, i+1);
            if(subProblemsuccess) {
                return true;  
            }
            //else check for next col index for this row
            //but remove this queen before only
            board[i][j] = 0;
        }
    }


    return false;

}
int main() {

    int board[10][10];   
    int n;
    cout<<"Enter n: ";
    cin>>n;

    //Initialize board with 0
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            board[i][j] = 0;
        }
    }

    solve(n, board, 0);

    
}