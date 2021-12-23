using System;
using System.Diagnostics;

class Palindrome{
    static void Main(string[] args){
        int epochs = 15;
        int runs = 200;
        int n = 250;
        Stopwatch stopwatch = new Stopwatch();
        GenRandom gen = new GenRandom(n);
        Exp experiment = new Exp(epochs, runs, n);
        stopwatch.Start();
        experiment.arr_exp(gen);
        experiment.str_exp(gen);
        stopwatch.Stop();
        TimeSpan ts = stopwatch.Elapsed;
        Console.WriteLine(ts);
    }
}

class GenRandom{
    private int n;
    Random random = new Random();
    public GenRandom(int n){
        if(n < 1){
            throw new Exception("length of str cannot be less than 1");
        }
        else{
            this.n = n;
        }
    }

    public string gen_str(){
        string ans = "";
        string chars = "abcdefghijklmnopqrstuvwxyz";
        for(int i = 0; i < this.n; i++){
            ans += chars[this.random.Next(chars.Length)];
        }
        return ans; 
    }

    public int[] gen_arr(){
        int[] ans = new int[n];
        for(int i = 0; i < this.n; i++){
            ans[i] = this.random.Next(10);
        }
        return ans;
    }
}

class Exp{
    private int epochs;
    private int runs;
    private int n;
    public Exp(int epochs, int runs, int n){
        this.epochs = epochs;
        this.runs = runs;
        this.n = n;
    }

    public void arr_exp(GenRandom gen){
        Console.WriteLine("------Int Palindromes--------");
        double[] res = new double[this.epochs];
        for(int e = 0; e < this.epochs; e++){
            int run_sum = 0;
            for(int r = 0; r < this.runs; r++){
                run_sum += count_pal_arr(gen.gen_arr());
            }
            res[e] = run_sum /(double) this.runs;
        }
        foreach(double i in res){
            Console.Write("{0} ", i);
        }
        Console.Write("\n");
    }

    public void str_exp(GenRandom gen){
        Console.WriteLine("------Str Palindromes--------");
        double[] res = new double[this.epochs];
        for(int e = 0; e < this.epochs; e++){
            int run_sum = 0;
            for(int r = 0; r < this.runs; r++){
                run_sum += count_pal_str(gen.gen_str());
            }
            res[e] = run_sum /(double) this.runs;
        }
        foreach(double i in res){
            Console.Write("{0} ", i);
        }
        Console.Write("\n");
    }

    public int count_pal_arr(int[] a){
        int n = a.Length;
        int[,] dp = new int[n,n];
        bool[,] p = new bool[n,n];
        int i = 0;
        int j = 0;
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                dp[i,j] = 0;
            }
        }
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                p[i,j] = false;
            }
        }
        for(i = 0; i < n; i++){
            p[i,i] = true;
        }
        for(i = 0; i < n-1; i++){
            if(a[i] == a[i+1]){
                p[i,i+1] = true;
                dp[i,i+1] = 1;
            }
        }

        for(int gap = 2; gap < n; gap++){
            for(i = 0; i < n-gap; i++){
                j = gap + i;
                if(a[i] == a[j] && p[i+1,j-1]){
                    p[i,j] = true;
                }
                if(p[i,j]){
                    dp[i,j] = (dp[i,j-1] + dp[i+1,j] + 1 - dp[i+1,j-1]);
                }
                else{
                    dp[i,j] = (dp[i,j-1] + dp[i+1,j] - dp[i+1,j-1]);
                }
            }
        }
        return dp[0,n-1];
    }

    public int count_pal_str(string a){
        int n = a.Length;
        int[,] dp = new int[n,n];
        bool[,] p = new bool[n,n];
        int i = 0;
        int j = 0;
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                dp[i,j] = 0;
            }
        }
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                p[i,j] = false;
            }
        }
        for(i = 0; i < n; i++){
            p[i,i] = true;
        }
        for(i = 0; i < n-1; i++){
            if(a[i] == a[i+1]){
                p[i,i+1] = true;
                dp[i,i+1] = 1;
            }
        }

        for(int gap = 2; gap < n; gap++){
            for(i = 0; i < n-gap; i++){
                j = gap + i;
                if(a[i] == a[j] && p[i+1,j-1]){
                    p[i,j] = true;
                }
                if(p[i,j]){
                    dp[i,j] = (dp[i,j-1] + dp[i+1,j] + 1 - dp[i+1,j-1]);
                }
                else{
                    dp[i,j] = (dp[i,j-1] + dp[i+1,j] - dp[i+1,j-1]);
                }
            }
        }
        return dp[0,n-1];
    }
}
