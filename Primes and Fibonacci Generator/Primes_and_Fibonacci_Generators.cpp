#include <bits/stdc++.h>
using namespace std;
class CurrencySorter
{
    void quick_sort(vector<long long int> &v, long long int l, long long int r)
    {
        if (l >= r)
        {
            return;
        }
        // pivot will be randomly selected from rand function and partition the array such that left of pivot contains elements < pivot and right contains elements > pivot
        long long int pivot = l + rand() % (r - l + 1);
        long long int val = v[pivot];
        swap(v[r], v[pivot]);
        long long int l1 = l - 1;
        long long int r1 = l;
        while (r1 <= r)
        {
            if (v[r1] <= val)
            {
                l1++;
                swap(v[l1], v[r1]);
            }
            r1++;
        }
        pivot = l1;
        quick_sort(v, l, pivot - 1);
        quick_sort(v, pivot + 1, r);
    }

public:
    void operator()(vector<long long int> &v)
    {
        quick_sort(v, 0, v.size() - 1);
    }
};
class FibonacciGenerator
{
    void mulmat(vector<vector<long long int>> &m1, vector<vector<long long int>> &m2)
    {
        long long int nums[2][2];
        nums[0][0] = ((m1[0][0] * m2[0][0]) + (m1[0][1] * m2[1][0])) % (1000000007);
        nums[0][1] = ((m1[0][0] * m2[0][1]) + (m1[0][1] * m2[1][1])) % (1000000007);
        nums[1][0] = ((m1[1][0] * m2[0][0]) + (m1[1][1] * m2[1][0])) % (1000000007);
        nums[1][1] = ((m1[1][0] * m2[0][1]) + (m1[1][1] * m2[1][1])) % (1000000007);
        m1[0][0] = nums[0][0];
        m1[0][1] = nums[0][1];
        m1[1][0] = nums[1][0];
        m1[1][1] = nums[1][1];
    }
    vector<vector<long long int>> matpow(long long int n)
    {
        vector<vector<long long int>> mat = {{1, 1}, {1, 0}};
        vector<vector<long long int>> mat1 = {{1, 0}, {0, 1}};
        while (n)
        {
            if (n % 2 == 1)
            {
                mulmat(mat1, mat);
            }
            mulmat(mat, mat);
            n /= 2;
        }
        return mat1;
    }

public:
    long long int operator()(long long int x)
    {
        if (x == 1)
            return 1;
        if (x == 0)
            return 0;
        vector<vector<long long int>> M = matpow(x - 2);
        return (M[0][0] + M[1][0]) % (1000000007);
    }
};
class PrimeCalculator
{
public:
    // do seive's algo
    vector<bool> is_primes;
    PrimeCalculator()
    {
        is_primes.resize(1000001, true);
        is_primes[0] = false;
        is_primes[1] = false;
        for (long long int i = 2; i <= 1000; i++)
        {
            if (is_primes[i])
            {
                long long int j = i * i;
                while (j <= 1000000)
                {
                    is_primes[j] = false;
                    j += i;
                }
            }
        }
    }
    vector<bool> create_primes_l_r(long long l, long long int r)
    {
        vector<bool> is_primes_l_r(r - l + 1, true);
        if (l == 1)
            is_primes_l_r[0] = false;
        for (long long int i = 2; i <= 1000000; i++)
        {
            if (i * i > r)
            {
                break;
            }
            else if (is_primes[i])
            {
                long long int j;
                if (i * i < l)
                {
                    j = ceil((double)l / i) * i;
                }
                else if (i * i >= l)
                {
                    j = i * i;
                }
                while (j <= r)
                {
                    is_primes_l_r[j - l] = false;
                    j += i;
                }
            }
        }
        return is_primes_l_r;
    }
    void printPrimes_L_R(long long int l, long long int r)
    {
        vector<bool> is_primes_l_r(create_primes_l_r(l, r));
        long long int index = l;
        for_each(is_primes_l_r.begin(), is_primes_l_r.end(), [&](bool val)
                 {
                if(val){
                    cout<<index<<" ";
                }
                index++; });
        cout << endl;
    }
    void printPrimeSum_L_R(long long int l, long long int r)
    {
        vector<bool> is_primes_l_r(create_primes_l_r(l, r));
        long long int sum = 0;
        long long int index = l;
        for_each(is_primes_l_r.begin(), is_primes_l_r.end(), [&](bool val)
                 {
                if(val){
                    sum+=index;
                }
                index++; });
        cout << sum << endl;
    }
};
class NumberAnalyzer
{
public:
    vector<bool> is_primes;
    NumberAnalyzer()
    {
        is_primes.resize(10001, true);
        is_primes[0] = false;
        is_primes[1] = false;
        for (long long int i = 2; i <= 100; i++)
        {
            if (is_primes[i])
            {
                long long int j = i * i;
                while (j <= 10000)
                {
                    is_primes[j] = false;
                    j += i;
                }
            }
        }
    }
    void prime_factorization(map<long long int, long long int> &divisors, long long int x)
    {
        for (long long int i = 2; i <= (int)(sqrt(x)); i++)
        {
            if (is_primes[i])
            {
                if (x % i == 0)
                {
                    while (x % i == 0)
                    {
                        divisors[i]++;
                        x /= i;
                    }
                }
            }
        }
        if (x != 1)
            divisors[x]++;
    }
    bool isSquareFree(long long int x)
    {
        map<long long int, long long int> divisors;
        prime_factorization(divisors, x);
        for (auto itr : divisors)
        {
            if (itr.second >= 2)
            {
                return false;
            }
        }
        return true;
    }
    long long int countDivisors(long long int x)
    {
        map<long long int, long long int> divisors;
        prime_factorization(divisors, x);
        long long int count = 1;
        for_each(divisors.begin(), divisors.end(), [&](pair<long long int, long long int> p)
                 { count *= (p.second + 1); });
        return count;
    }
    long long int sumOfDivisors(long long int x)
    {
        map<long long int, long long int> divisors;
        prime_factorization(divisors, x);
        long long int sum = 1;
        for_each(divisors.begin(), divisors.end(), [&](pair<long long int, long long int> p)
                 {
            long long int numerator=pow(p.first,p.second+1)-1;
            long long int denominator=p.first-1;
            sum*=(numerator/denominator); });
        return sum;
    }
};
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long int type;
    cin >> type;
    if (type == 1)
    {
        // take all inputs
        // for each input sort the array by {
        // CurrencySorter cs();
        // cs(given vector);
        // prlong long int the array;
        // }
        long long int t;
        cin >> t;
        while (t--)
        {
            long long int n;
            cin >> n;
            vector<long long int> nums(n);
            for (long long int i = 0; i < n; i++)
            {
                cin >> nums[i];
            }
            CurrencySorter cs;
            cs(nums);
            for_each(nums.begin(), nums.end(), [](long long int x)
                     { cout << x << " "; });
            cout << endl;
        }
    }
    else if (type == 2)
    {
        // take all inputs
        // for each input find fibonacci value by {
        //  FibonacciGenerator f();
        // f(given value);
        // prlong long int the returned value;
        // }
        long long int t;
        cin >> t;
        while (t--)
        {
            long long int n;
            cin >> n;
            FibonacciGenerator f;
            cout << f(n) << endl;
        }
    }
    else if (type == 3)
    {
        // for each input take l and r and call the req function by creating a object with type name as PrimeCalculator;
        long long int t;
        cin >> t;
        PrimeCalculator pc;
        while (t--)
        {
            string s;
            cin >> s;
            long long int l, r;
            cin >> l >> r;
            if (s == "printPrimes")
            {
                pc.printPrimes_L_R(l, r);
            }
            else if (s == "printPrimeSum")
            {
                pc.printPrimeSum_L_R(l, r);
            }
        }
    }
    else if (type == 4)
    {
        // check which function need to be executed and call the function by creating a object with type name NumberAnalyzer and prlong long int the result;
        long long int t;
        cin >> t;
        NumberAnalyzer na;
        while (t--)
        {
            string s;
            cin >> s;
            long long int num;
            cin >> num;
            if (s == "isSquareFree")
            {
                if (na.isSquareFree(num))
                {
                    cout << "yes" << endl;
                }
                else
                    cout << "no" << endl;
            }
            else if (s == "countDivisors")
            {
                cout << na.countDivisors(num) << endl;
            }
            else if (s == "sumOfDivisors")
            {
                cout << na.sumOfDivisors(num) << endl;
            }
        }
    }
}