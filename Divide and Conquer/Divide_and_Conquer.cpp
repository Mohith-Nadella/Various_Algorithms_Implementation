#include <bits/stdc++.h>
using namespace std;
// comparator for ascending or decending order
#define int long long int
class Comparator
{
    string s;

public:
    Comparator(string S)
    {
        s = S;
    }
    bool operator()(int a, int b)
    {
        if (s == "ascending")
        {
            return a < b;
        }
        else
        {
            return a > b;
        }
    }
};
// class for Galactic Chessmaster's Challenge
class GCC
{
    int n;
    vector<vector<int>> board;

public:
    GCC() {}
    void set_board()
    {
        cin >> n;
        board.resize(n, vector<int>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> board[i][j];
            }
        }
    }
    // merge sort
    void Sort_vector(vector<int> &nums, int l, int r, Comparator &c)
    {
        if (r <= l)
        {
            return;
        }
        int m = (l + r) / 2;
        Sort_vector(nums, l, m, c);
        Sort_vector(nums, m + 1, r, c);
        vector<int> nums1(r - l + 1);
        int i = l;
        int j = m + 1;
        int k = 0;
        while (i <= m && j <= r)
        {
            if (c(nums[i], nums[j]))
            {
                nums1[k] = nums[i];
                i++;
                k++;
            }
            else
            {
                nums1[k] = nums[j];
                k++;
                j++;
            }
        }
        while (i <= m)
        {
            nums1[k] = nums[i];
            i++;
            k++;
        }
        while (j <= r)
        {
            nums1[k] = nums[j];
            j++;
            k++;
        }
        for (int i = l; i <= r; i++)
        {
            nums[i] = nums1[i - l];
        }
    }
    // sorting the rows
    void sortRows(Comparator &comparator)
    {
        for (int i = 0; i < n; i++)
        {
            Sort_vector(board[i], 0, n - 1, comparator);
        }
    }
    // counting inversions using merge and count algm
    int Inversions(vector<int> &nums, int l, int r)
    {
        if (r <= l)
        {
            return 0;
        }
        int n1 = (l + r) / 2;
        int count = Inversions(nums, l, n1) + Inversions(nums, n1 + 1, r);
        vector<int> nums1(r - l + 1);
        int i = l;
        int j = n1 + 1;
        int k = 0;
        while (i <= n1 && j <= r)
        {
            if (nums[i] <= nums[j])
            {
                nums1[k] = nums[i];
                i++;
                k++;
            }
            else
            {
                nums1[k] = nums[j];
                count += (n1 - i + 1);
                j++;
                k++;
            }
        }
        while (i <= n1)
        {
            nums1[k] = nums[i];
            i++;
            k++;
        }
        while (j <= r)
        {
            nums1[k] = nums[j];
            j++;
            k++;
        }
        for (int i = l; i <= r; i++)
        {
            nums[i] = nums1[i - l];
        }
        return count;
    }
    // counts the no of inversions
    void countInversions()
    {
        vector<int> nums;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                nums.push_back(board[i][j]);
            }
        }
        cout << Inversions(nums, 0, n * n - 1) << endl;
    }
    // printing the board
    void display()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};
bool comparatorx(pair<int, int> p1, pair<int, int> p2)
{
    return p1.first < p2.first;
}
bool comparatory(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second < p2.second;
}
class Players
{
    int n;
    vector<pair<int, int>> players;
    map<pair<int, int>, int> index;

public:
    Players()
    {
        cin >> n;
        players.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin >> players[i].first;
            cin >> players[i].second;
            index[players[i]] = i;
        }
    }
    double distance(pair<pair<int, int>, pair<int, int>> p)
    {
        int a = (p.first.first - p.second.first) * (p.first.first - p.second.first);
        int b = (p.first.second - p.second.second) * (p.first.second - p.second.second);
        return sqrt(a + b);
    }
    pair<pair<int, int>, pair<int, int>> closest_points(vector<pair<int, int>> &pairsx, int l, int r, vector<pair<int, int>> &pairsy)
    {
        double d;
        pair<pair<int, int>, pair<int, int>> p;
        if (r - l == 1)
        {
            if (index[pairsx[l]] < index[pairsx[r]])
                return {pairsx[l], pairsx[r]};
            else
                return {pairsx[r], pairsx[l]};
        }
        if (r - l == 2)
        {
            double d1 = distance({pairsx[l], pairsx[l + 1]});
            double d2 = distance({pairsx[l], pairsx[l + 2]});
            double d3 = distance({pairsx[l + 1], pairsx[l + 2]});
            if (d1 <= d2 && d1 <= d3)
            {
                if (index[pairsx[l]] < index[pairsx[l + 1]])
                    return {pairsx[l], pairsx[l + 1]};
                else
                    return {pairsx[l + 1], pairsx[l]};
            }
            else if (d2 <= d1 && d2 <= d3)
            {
                if (index[pairsx[l]] < index[pairsx[l + 2]])
                    return {pairsx[l], pairsx[l + 2]};
                else
                    return {pairsx[l + 2], pairsx[l]};
            }
            else
            {
                if (index[pairsx[l + 1]] < index[pairsx[l + 2]])
                    return {pairsx[l + 1], pairsx[l + 2]};
                else
                    return {pairsx[l + 2], pairsx[l + 1]};
            }
        }
        int n1 = (l + r) / 2;
        vector<pair<int, int>> pairsyl;
        vector<pair<int, int>> pairsyr;
        for (int i = 0; i < pairsy.size(); i++)
        {
            if (pairsy[i].first <= pairsx[n1].first)
                pairsyl.push_back(pairsy[i]);
            else
                pairsyr.push_back(pairsy[i]);
        }
        pair<pair<int, int>, pair<int, int>> p1 = closest_points(pairsx, l, n1, pairsyl);
        pair<pair<int, int>, pair<int, int>> p2 = closest_points(pairsx, n1 + 1, r, pairsyr);
        // now calculate distances of both pair of pairs and take the smallest as d
        double d1 = distance(p1);
        double d2 = distance(p2);
        d = min(d1, d2);
        if (d == d1)
        {
            p = p1;
        }
        else
        {
            p = p2;
        }
        // now take the range n1-d to n1+d and take the sorted pairs w.r.t y in that range using pairsy and store in vector numsy
        vector<pair<int, int>> numsy;
        for (int i = 0; i < pairsy.size(); i++)
        {
            if (pairsy[i].first >= (double)(pairsx[n1].first - d) && pairsy[i].first <= (double)(pairsx[n1].first + d))
            {
                numsy.push_back(pairsy[i]);
            }
        }
        // now iterate in numsy and check next 15 pairs for smallest distance in that order
        // if any pair has less distance than d then update d and update p with that pair
        // after iterating return p;
        int i = 0;
        while (i < numsy.size())
        {
            int j = i + 1;
            while (j <= i + 15 && j < numsy.size())
            {
                double d3 = distance({numsy[i], numsy[j]});
                if (d3 < d)
                {
                    d = d3;
                    if (index[numsy[i]] < index[numsy[j]])
                        p = {numsy[i], numsy[j]};
                    else
                        p = {numsy[j], numsy[i]};
                }
                j++;
            }
            i++;
        }
        return p;
    }
    void closest_pair()
    {
        // sort the pairs w.r.t x and store in numx;
        // sort the pairs w.r.t y and store in numy;
        vector<pair<int, int>> numx(players);
        vector<pair<int, int>> numy(players);
        sort(numx.begin(), numx.end(), comparatorx);
        sort(numy.begin(), numy.end(), comparatory);
        pair<pair<int, int>, pair<int, int>> p = closest_points(numx, 0, n - 1, numy);
        cout << p.first.first << " " << p.first.second << " " << p.second.first << " " << p.second.second << endl;
    }
};
int32_t main()
{
    GCC gcc;
    string inp_str;
    cin >> inp_str;
    while (inp_str != "END")
    {
        if (inp_str == "CREATE_2D")
        {
            gcc.set_board();
        }
        else if (inp_str == "INVERSION_2D")
        {
            gcc.countInversions();
        }
        else if (inp_str == "SORT_2D")
        {
            string s1;
            cin >> s1;
            Comparator c(s1);
            gcc.sortRows(c);
        }
        else if (inp_str == "DISPLAY_2D")
        {
            gcc.display();
        }
        else if (inp_str == "CLOSEST_2D")
        {
            Players p;
            p.closest_pair();
        }
        cin >> inp_str;
    }
}