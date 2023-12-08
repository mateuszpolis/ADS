#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void printVector(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

int compute(vector<int>& board, int n, int m) {
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    for (int i = 1; i <= n; i++) {        
        if (board[i - 1] == 0) {
            continue;
        }        
        for (int j = 1; j <= 6; j++) {
            int nextCell = i + j;
            
            if (nextCell <= n) {
                dp[nextCell] = (dp[nextCell] + dp[i]) % m;
            }
        }
    }

    return dp[n];
}


int main()
{
	vector<int> board; 
	
	int z,n,m;
	cin >> z;
	while(z)
	{
		board.clear();		
		cin >> n >> m;
		for(int i=0; i<n; i++)
		{
			int x;
			cin >> x;
			board.push_back(x);
		}
		int sol = compute(board, n, m);
		cout << sol <<"\n";
		z--;
	}
	return 1;
}