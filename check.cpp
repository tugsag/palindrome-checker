# include <iostream>
# include <vector>
# include <cstring>
# include <iomanip>
# include <chrono>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

int check_pal(vector<int> a){
    int n = a.size();
    vector<vector<int>> dp(n);
    vector<vector<bool>> p(n);
    int i;
    int j;
    for(i = 0; i < n; i++){
        dp[i] = vector<int>(n);
        for(j = 0; j < n; j++){
            dp[i][j] = 0;
        }
    }
    for(i = 0; i < n; i++){
        p[i] = vector<bool>(n);
        for(j = 0; j < n; j++){
            p[i][j] = false;
        }
    }

    for(i = 0; i < n; i++){
        p[i][i] = true;
    }

    for(i = 0; i < n-1; i++){
        if(a[i] == a[i+1]){
            p[i][i+1] = true;
            dp[i][i+1] = 1;
        }
    }
    for(int gap = 2; gap < n; gap++){
        for(i = 0; i < n-gap; i++){
            j = gap + i;
            if(a[i] == a[j] && p[i+1][j-1]){
                p[i][j] = true;
            }
            if(p[i][j]){
                dp[i][j] = (dp[i][j-1] + dp[i+1][j] + 1 - dp[i+1][j-1]);
            }
            else{
                dp[i][j] = (dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]);
            }
        }
    }

    return dp[0][n-1];
}

int check_pal_char(vector<char> a){
    int n = a.size();
    vector<vector<int>> dp(n);
    vector<vector<bool>> p(n);
    int i;
    int j;
    for(i = 0; i < n; i++){
        dp[i] = vector<int>(n);
        for(j = 0; j < n; j++){
            dp[i][j] = 0;
        }
    }
    for(i = 0; i < n; i++){
        p[i] = vector<bool>(n);
        for(j = 0; j < n; j++){
            p[i][j] = false;
        }
    }

    for(i = 0; i < n; i++){
        p[i][i] = true;
    }

    for(i = 0; i < n-1; i++){
        if(a[i] == a[i+1]){
            p[i][i+1] = true;
            dp[i][i+1] = 1;
        }
    }
    for(int gap = 2; gap < n; gap++){
        for(i = 0; i < n-gap; i++){
            j = gap + i;
            if(a[i] == a[j] && p[i+1][j-1]){
                p[i][j] = true;
            }
            if(p[i][j]){
                dp[i][j] = (dp[i][j-1] + dp[i+1][j] + 1 - dp[i+1][j-1]);
            }
            else{
                dp[i][j] = (dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]);
            }
        }
    }

    return dp[0][n-1];
}

vector<int> gen_arr(int n){
    vector<int> a;
    for(int i = 0; i < n; i++){
        a.push_back(rand() % 10);
    }

    return a;
}

vector<char> gen_str(int n){
    vector<char> a;
    for(int i = 0; i < n; i++){
        a.push_back('a' + rand() % 26);
    }

    return a;
}

int license(int epochs, int runs){
    // XXX 0000
    cout << "\n" << "---------License Sim---------" << "\n";
    vector<double> res(epochs);
    for(int e = 0; e < epochs; e++){
        int run_sum = 0;
        for(int r = 0; r < runs; r++){
            int npc = check_pal_char(gen_str(3));
            int npi = check_pal(gen_arr(4));
            run_sum += npc + npi;
        }
        res[e] = run_sum /(double) runs;
    }

    for(auto i: res){
        cout << setprecision(5) << i << " ";
    }
    return 1;
}

int arr_exp(int epochs, int runs, int n){
    cout << "\n" << "---------Int Palindromes----------" << "\n";
    vector<double> res(epochs);
    for(int e = 0; e < epochs; e++){
        int run_sum = 0;
        for(int r = 0; r < runs; r++){
            run_sum += check_pal(gen_arr(n));
        }
        res[e] = run_sum /(double) runs;
    }
    for(auto i: res){
        cout << setprecision(10) << i << " ";
    }
    return 1;
}

int str_exp(int epochs, int runs, int n){
    cout << "\n" << "-------Char Palindromes-------" << "\n";
    vector<double> res(epochs);
    for(int e = 0; e < epochs; e++){
        int run_sum = 0;
        for(int r = 0; r < runs; r++){
            run_sum += check_pal_char(gen_str(n));
        }
        res[e] = run_sum /(double) runs;
    }
    for(auto i: res){
        cout << setprecision(10) << i << " ";
    }
    return 1;
}

int main(){
    srand(time(0));
    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int epochs = 15;
    int runs = 200;
    int n = 250;
    // palindrome exps
    int l = license(epochs, runs);
    int s = str_exp(epochs, runs, n);
    int i = arr_exp(epochs, runs, n);
    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "\n" << setprecision(10) << (end -(double) start) /(double) 1000 << "\n";
    return 0;
}
