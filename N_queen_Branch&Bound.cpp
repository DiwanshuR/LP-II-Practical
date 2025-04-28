#include<iostream>
using namespace std;

bool columns[10] = {false};
bool left_diagonal[20] = {false};
bool right_diagonal[20] = {false};

void printBoard(int board[][10], int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(board[i][j] == 1)
                cout<<"Q ";
            else
                cout<<". ";
        }
        cout<<endl;
    }
}

bool solve(int n, int board[][10], int i) {
    //Base Case
    if(i >= n) {
        cout<<"Board after placing queens"<<endl;
        printBoard(board, n);
        
    }

    //for this row traverse it completely to find if there is a safe place to put a queen
    for(int j=0; j<n; j++) {
        if( !columns[j] && !left_diagonal[i-j + n-1] && !right_diagonal[i+j]) {
            board[i][j] = 1;
            columns[j] = true;
            left_diagonal[i-j + n-1] = true;
            right_diagonal[i+j] = true;

            //move to next subproblem (next row)
            bool subProblemsuccess = solve(n, board, i+1);
            if(subProblemsuccess) {
                return true;  
            }
            //else check for next col index for this row
            //but remove this queen before only and reverse all the changes
            board[i][j] = 0;
            columns[j] = left_diagonal[i-j + n-1] = right_diagonal[i+j] = false;
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