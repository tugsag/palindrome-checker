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
    // possible formats for IL: XXX 0000, XX 00000, 000 0000, X00 0000, 000 000
    cout << "\n" << "---------License Sim---------" << "\n";
    int x, y; // x letters, y numbers
    vector<double> res(epochs);
    for(int e = 0; e < epochs; e++){
        int run_sum = 0;
        for(int r = 0; r < runs; r++){
            int li = rand() % 5;
            int npc = 0;
            switch(li){
                case 0:
                    x = 3, y = 4;
                    break;
                case 1:
                    x = 2, y = 5;
                    break;
                case 2:
                    x = 0, y = 7;
                    break;
                case 3:
                    x = 1, y = 6;
                    break;
                case 4:
                    x = 0, y = 6;
                    break;
            }
            if(x > 0){
                npc = check_pal_char(gen_str(x));
            }
            int npi = check_pal(gen_arr(y));
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

int main(int argc, char *argv[]){
    srand(time(0));
    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int epochs = 15;
    int runs = 200;
    int n = 250;
    if(argc == 4){
        epochs = atoi(argv[1]);
        runs = atoi(argv[2]);
        n = atoi(argv[3]);
    }
    else{
        cout << "Values incomplete, using default vals " << "\n";
    }
    cout << "epochs: " << epochs << " runs: " << runs << " str length: " << n << "\n";
    // palindrome exps
    int l = license(epochs, runs);
    int s = str_exp(epochs, runs, n);
    int i = arr_exp(epochs, runs, n);
    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "\n" << setprecision(10) << (end -(double) start) /(double) 1000 << "\n";
    return 0;
}
