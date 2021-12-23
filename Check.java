import java.util.Random;

public class Check {
    public static void main(String[] args) {
        int epochs = 15;
        int runs = 200;
        int n = 250;
        GenRandom gen = new GenRandom(n);
        Exp experiment = new Exp(epochs, runs, n);
        long start = System.nanoTime();
        experiment.arr_exp(gen);
        experiment.str_exp(gen);
        System.out.println((double) (System.nanoTime() - start) / 10e9);
    }
}

class GenRandom {
    private int n;
    private Random random = new Random();

    public GenRandom(int num) {
        this.n = num;
    }

    public String gen_str() {
        String ans = "";
        for (int i = 0; i < this.n; i++) {
            ans += (char) (this.random.nextInt(26) + 'a');
        }
        return ans;
    }

    public int[] gen_arr() {
        int[] ans = new int[this.n];
        for (int i = 0; i < this.n; i++) {
            ans[i] = this.random.nextInt(10);
        }
        return ans;
    }
}

class Exp {
    private int epochs;
    private int runs;
    private int n;

    public Exp(int e, int r, int num) {
        this.epochs = e;
        this.runs = r;
        this.n = num;
    }

    public void arr_exp(GenRandom gen) {
        System.out.println("-------Int Palindromes--------");
        double[] res = new double[this.epochs];
        for (int e = 0; e < this.epochs; e++) {
            int run_sum = 0;
            for (int r = 0; r < this.runs; r++) {
                run_sum += count_pal_arr(gen.gen_arr());
            }
            res[e] = (double) run_sum / this.runs;
        }
        for (double i : res) {
            System.out.print(i + " ");
        }
        System.out.println("\n");
    }

    public void str_exp(GenRandom gen) {
        System.out.println("-------Str Palindromes--------");
        double[] res = new double[this.epochs];
        for (int e = 0; e < this.epochs; e++) {
            int run_sum = 0;
            for (int r = 0; r < this.runs; r++) {
                run_sum += count_pal_str(gen.gen_str());
            }
            res[e] = (double) run_sum / this.runs;
        }
        for (double i : res) {
            System.out.print(i + " ");
        }

        System.out.println("\n");
    }

    public int count_pal_arr(int[] a) {
        int n = a.length;
        int[][] dp = new int[n][n];
        boolean[][] p = new boolean[n][n];
        int i = 0;
        int j = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                dp[i][j] = 0;
            }
        }
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                p[i][j] = false;
            }
        }
        for (i = 0; i < n; i++) {
            p[i][i] = true;
        }
        for (i = 0; i < n - 1; i++) {
            if (a[i] == a[i + 1]) {
                p[i][i + 1] = true;
                dp[i][i + 1] = 1;
            }
        }

        for (int gap = 2; gap < n; gap++) {
            for (i = 0; i < n - gap; i++) {
                j = gap + i;
                if (a[i] == a[j] && p[i + 1][j - 1]) {
                    p[i][j] = true;
                }
                if (p[i][j]) {
                    dp[i][j] = (dp[i][j-1] + dp[i+1][j] + 1 - dp[i+1][j-1]);
                } else {
                    dp[i][j] = (dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1]);
                }
            }        
        }
        return dp[0][n - 1];
    }

    public int count_pal_str(String a) {
        int n = a.length();
        int[][] dp = new int[n][n];
        boolean[][] p = new boolean[n][n];
        int i = 0;
        int j = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                dp[i][j] = 0;
            }
        }
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                p[i][j] = false;
            }
        }
        for (i = 0; i < n; i++) {
            p[i][i] = true;
        }
        for (i = 0; i < n - 1; i++) {
            if (a.charAt(i) == a.charAt(i + 1)) {
                p[i][i + 1] = true;
                dp[i][i + 1] = 1;
            }
        }

        for (int gap = 2; gap < n; gap++) {
            for (i = 0; i < n - gap; i++) {
                j = gap + i;
                if (a.charAt(i) == a.charAt(j) && p[i + 1][j - 1]) {
                    p[i][j] = true;
                }
                if (p[i][j]) {
                    dp[i][j] = (dp[i][j - 1] + dp[i + 1][j] + 1 - dp[i + 1][j - 1]);
                } else {
                    dp[i][j] = (dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
}
