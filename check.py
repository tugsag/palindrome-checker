import string
import random
import matplotlib.pyplot as plt
import time

def check_palindrome(arr):
    n = len(arr)
    dp = [[0 for x in range(n)] for y in range(n)]
    p = [[False for x in range(n)] for y in range(n)]
    for i in range(n):
        p[i][i] = True
    for i in range(n-1):
        if(arr[i] == arr[i+1]):
            p[i][i+1] = True
            dp[i][i+1] = 1
    
    for gap in range(2, n):
        for i in range(n-gap):
            j = gap + i
            if(arr[i] == arr[j] and p[i+1][j-1]):
                p[i][j] = True
            if(p[i][j]):
                dp[i][j] = (dp[i][j-1] + dp[i+1][j] + 1 - dp[i+1][j-1])
            else:
                dp[i][j] = (dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1])
    return dp[0][n-1]

def gen_arr(n):
    rands = [random.randint(0, 9) for i in range(n)]
    return rands

def gen_str(n):
    ans = ''
    for i in range(n):
        ans += random.choice(string.ascii_letters).lower()
    return ans


def run_arr_exp(epochs, runs, n):
    res = []
    for j in range(epochs):
        ep = []
        for i in range(runs):
            ep.append(check_palindrome(gen_arr(n)))
        res.append(ep)
    return [sum(x)/len(x) for x in res], [sorted(x)[runs//2] for x in res]

def run_str_exp(epochs, runs, n):
    res = []
    for j in range(epochs):
        ep = []
        for i in range(runs):
            ep.append(check_palindrome(gen_str(n)))
        res.append(ep)
    return [sum(x)/len(x) for x in res], [sorted(x)[runs//2] for x in res]

def show(mean, med):
    plt.plot(mean)
    plt.plot(med, color='r')
    plt.show()

if __name__ == '__main__':
    start = time.perf_counter()
    mean, med = run_str_exp(15, 200, 250)
    print(mean)
    mean, med = run_arr_exp(15, 200, 250)
    print(mean)
    print(time.perf_counter() - start)
