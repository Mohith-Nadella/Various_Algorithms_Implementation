#include <bits/stdc++.h>
using namespace std;
class node
{
private:
    string id;
    vector<pair<node *, int>> adj_list;
    int parity;
    int sh_dist;

public:
    node(string str, int p)
    {
        id = str;
        parity = p;
        sh_dist = INT_MAX;
    }
    void add_neighbour(node *n, int w)
    {
        adj_list.push_back({n, w});
    }
    vector<pair<node *, int>> &get_adj_list()
    {
        return adj_list;
    }
    int get_parity()
    {
        return parity;
    }
    void set_sh_dist(int sd)
    {
        sh_dist = sd;
    }
    int get_sh_dist()
    {
        return sh_dist;
    }
    bool operator<(node n)
    {
        return sh_dist < n.get_sh_dist();
    }
    bool operator>(node n)
    {
        return sh_dist > n.get_sh_dist();
    }
};
template <typename T>
class min_priority_queue
{
private:
    vector<T> vec;
    int cur_size;

public:
    min_priority_queue()
    {
        vec.resize(1000000);
        cur_size = 0;
    }
    void move_up(int h)
    {
        if (empty())
        {
            return;
        }
        T X = vec[h];
        while (h > 1 && *vec[h / 2] > *X)
        {
            vec[h] = vec[h / 2];
            h = h / 2;
        }
        vec[h] = X;
        return;
    }
    void move_down(int h)
    {
        if (empty())
        {
            return;
        }
        T X = vec[h];
        while (2 * h <= cur_size)
        {
            int c_min;
            if (2 * h + 1 <= cur_size && *vec[2 * h + 1] < *vec[2 * h])
            {
                c_min = 2 * h + 1;
            }
            else
            {
                c_min = 2 * h;
            }
            if (*vec[c_min] > *X)
            {
                break;
            }
            vec[h] = vec[c_min];
            h = c_min;
        }
        vec[h] = X;
        return;
    }
    const size_t size()
    {
        return cur_size;
    }
    void push(const T &n)
    {
        cur_size++;
        vec[cur_size] = n;
        move_up(cur_size);
        return;
    }
    void pop()
    {
        if (empty())
        {
            return;
        }
        vec[1] = vec[cur_size];
        cur_size--;
        move_down(1);
        return;
    }
    const T &top()
    {
        return vec[1];
    }
    bool empty()
    {
        return cur_size == 0;
    }
};
class marauder_map
{
private:
    map<pair<string, int>, node *> id_room;

public:
    marauder_map(int n, int m)
    {
        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            node *n1 = new node(s, 0);
            node *n2 = new node(s, 1);
            id_room[{s, 0}] = n1;
            id_room[{s, 1}] = n2;
        }
        for (int i = 0; i < m; i++)
        {
            string s1, s2;
            int w;
            cin >> s1 >> s2 >> w;
            id_room[{s1, 0}]->add_neighbour(id_room[{s2, 1}], w);
            id_room[{s1, 1}]->add_neighbour(id_room[{s2, 0}], w);
            id_room[{s2, 0}]->add_neighbour(id_room[{s1, 1}], w);
            id_room[{s2, 1}]->add_neighbour(id_room[{s1, 0}], w);
        }
    }
    void find_shortest_even_path(string s1, string s2)
    {
        node *source = id_room[{s1, 0}];
        node *sink = id_room[{s2, 0}];
        min_priority_queue<node *> pq;
        source->set_sh_dist(0);
        pq.push(source);
        while (!pq.empty())
        {
            node *parent = pq.top();
            int d = parent->get_sh_dist();
            pq.pop();
            if (parent == sink)
            {
                cout << d << endl;
                return;
            }
            for (auto child : parent->get_adj_list())
            {
                node *c = child.first;
                int c_w = child.second;
                if (c->get_sh_dist() > d + c_w)
                {
                    c->set_sh_dist(d + c_w);
                    pq.push(c);
                }
            }
        }
        cout << -1 << endl;
    }
};
int main()
{
    int n;
    cin >> n;
    int m;
    cin >> m;
    marauder_map mm(n, m);
    string s1, s2;
    cin >> s1 >> s2;
    mm.find_shortest_even_path(s1, s2);
}