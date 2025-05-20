#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define float long double
class complex_num
{
private:
    int real;
    int imag;

public:
    complex_num()
    {
        real = 0;
        imag = 0;
    }
    complex_num(int a, int b)
    {
        real = a;
        imag = b;
    }
    void set_complex(int a, int b)
    {
        real = a;
        imag = b;
    }
    complex_num operator+(complex_num b)
    {
        return complex_num(real + b.real, imag + b.imag);
    }
    complex_num operator*(complex_num b)
    {
        int R = (real * b.real) - (imag * b.imag);
        int I = (real * b.imag) + (imag * b.real);
        return complex_num(R, I);
    }
    complex_num operator*(int x)
    {
        return complex_num(real * x, imag * x);
    }
    void print_complex()
    {
        cout << real << " " << imag;
    }
};
istream &operator>>(istream &s, complex_num &c)
{
    int a, b;
    s >> a >> b;
    c.set_complex(a, b);
    return s;
}
template <typename type>
istream &operator>>(istream &s, vector<type> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        s >> v[i];
    }
    return s;
}
ostream &operator<<(ostream &s, complex_num &comp)
{
    comp.print_complex();
    return s;
}
template <typename q1>
class poly_mul
{
private:
    vector<q1> coeff;

public:
    poly_mul(vector<q1> vec)
    {
        coeff = vec;
    }
    void operator*(vector<q1> b)
    {
        int degb = b.size() - 1;
        while (b.size() < coeff.size())
        {
            b.push_back(q1());
        }
        vector<q1> res = mul_two_poly(coeff, 0, coeff.size() - 1, b, 0, b.size() - 1);
        for (int i = 0; i < coeff.size() + degb; i++)
        {
            cout << fixed << setprecision(6) << res[i] << " ";
        }
        cout << endl;
    }
    vector<q1> mul_two_poly(vector<q1> a, int la, int ra, vector<q1> b, int lb, int rb)
    {
        if (la == ra)
        {
            vector<q1> res;
            res.push_back(a[la] * b[lb]);
            return res;
        }
        int n = ra - la + 1;
        int ma = (la + ra) / 2;
        vector<q1> A = mul_two_poly(a, la, ma, b, lb, ma);
        vector<q1> B = mul_two_poly(a, ma + 1, ra, b, ma + 1, rb);
        vector<q1> C = add_two_poly(a, la, ma, a, ma + 1, ra, 1);
        vector<q1> D = add_two_poly(b, lb, ma, b, ma + 1, rb, 1);
        vector<q1> E = mul_two_poly(C, 0, C.size() - 1, D, 0, D.size() - 1);
        vector<q1> F = add_two_poly(E, 0, E.size() - 1, A, 0, A.size() - 1, -1);
        vector<q1> G = add_two_poly(F, 0, F.size() - 1, B, 0, B.size() - 1, -1);
        vector<q1> res(2 * n - 1, q1());
        int offset;
        if (n % 2 == 0)
            offset = (n / 2);
        else
            offset = (n + 1) / 2;
        int i = 0;
        while (i < A.size())
        {
            res[i] = res[i] + A[i];
            i++;
        }
        i = 0;
        while (i < G.size())
        {
            res[i + offset] = res[i + offset] + G[i];
            i++;
        }
        i = 0;
        while (i < B.size())
        {
            res[i + 2 * offset] = res[i + 2 * offset] + B[i];
            i++;
        }
        return res;
    }
    vector<q1> add_two_poly(vector<q1> a, int la, int ra, vector<q1> b, int lb, int rb, int op)
    {
        vector<q1> res(max(ra - la + 1, rb - lb + 1), q1());
        for (int i = 0; i < max(ra - la + 1, rb - lb + 1); i++)
        {
            if (i <= ra - la)
                res[i] = res[i] + a[i + la];
            if (i <= rb - lb)
                res[i] = res[i] + (b[i + lb] * op);
        }
        return res;
    }
};
string operator*(string s, int x)
{
    string s1 = "";
    for (int i = 0; i < x; i++)
    {
        s1 += s;
    }
    return s1;
}
template <typename q2>
class evaluate_poly
{
private:
    vector<q2> coeff;
    int deg;

public:
    evaluate_poly(vector<q2> vec)
    {
        coeff = vec;
        deg = vec.size() - 1;
    }
    void evaluate(int x)
    {
        vector<q2> evaluated(deg + 1);
        int i = 0;
        int X = 1;
        while (i <= deg)
        {
            evaluated[i] = coeff[i] * X;
            X *= x;
            i++;
        }
        q2 sum = evaluated[deg];
        for (int i = deg - 1; i >= 0; i--)
        {
            sum += evaluated[i];
        }
        cout << fixed << setprecision(6) << sum << endl;
    }
};
template <typename q3>
class diff_poly
{
private:
    vector<q3> coeff;
    int deg;

public:
    diff_poly(vector<q3> vec)
    {
        coeff = vec;
        deg = vec.size() - 1;
    }
    void diff_poly_vec()
    {
        for (int i = 1; i < deg + 1; i++)
        {
            cout << fixed << setprecision(6) << (coeff[i] * i) << " ";
        }
        cout << endl;
    }
};
int32_t main()
{
    int no_of_queries;
    cin >> no_of_queries;
    for (int i = 0; i < no_of_queries; i++)
    {
        int q;
        cin >> q;
        if (q == 1)
        {
            int d1, d2;
            string type;
            cin >> type;
            if (type == "integer")
            {
                cin >> d1;
                vector<int> v1(d1);
                cin >> v1;
                cin >> d2;
                vector<int> v2(d2);
                cin >> v2;
                if (d1 >= d2)
                {
                    poly_mul<int> pm(v1);
                    pm *v2;
                }
                else
                {
                    poly_mul<int> pm(v2);
                    pm *v1;
                }
            }
            else if (type == "float")
            {
                cin >> d1;
                vector<float> v1(d1);
                cin >> v1;
                cin >> d2;
                vector<float> v2(d2);
                cin >> v2;
                if (d1 >= d2)
                {
                    poly_mul<float> pm(v1);
                    pm *v2;
                }
                else
                {
                    poly_mul<float> pm(v2);
                    pm *v1;
                }
            }
            else
            {
                cin >> d1;
                vector<complex_num> v1(d1);
                cin >> v1;
                cin >> d2;
                vector<complex_num> v2(d2);
                cin >> v2;
                if (d1 >= d2)
                {
                    poly_mul<complex_num> pm(v1);
                    pm *v2;
                }
                else
                {
                    poly_mul<complex_num> pm(v2);
                    pm *v1;
                }
            }
        }
        else if (q == 2)
        {
            string type;
            cin >> type;
            int d, x;
            if (type == "integer")
            {
                cin >> d;
                vector<int> v(d);
                cin >> v;
                cin >> x;
                evaluate_poly<int> ep(v);
                ep.evaluate(x);
            }
            else if (type == "float")
            {
                cin >> d;
                vector<float> v(d);
                cin >> v;
                cin >> x;
                evaluate_poly<float> ep(v);
                ep.evaluate(x);
            }
            else
            {
                cin >> d;
                vector<string> v(d);
                cin >> v;
                cin >> x;
                evaluate_poly<string> ep(v);
                ep.evaluate(x);
            }
        }
        else
        {
            string type;
            cin >> type;
            int d;
            if (type == "integer")
            {
                cin >> d;
                vector<int> v(d);
                cin >> v;
                diff_poly<int> dp(v);
                dp.diff_poly_vec();
            }
            else
            {
                cin >> d;
                vector<float> v(d);
                cin >> v;
                diff_poly<float> dp(v);
                dp.diff_poly_vec();
            }
        }
    }
}