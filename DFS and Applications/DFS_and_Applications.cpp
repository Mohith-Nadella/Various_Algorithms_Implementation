#include <bits/stdc++.h>
using namespace std;
class event
{
private:
    int hype;
    int index;
    vector<event *> adj_list;
    char color;
    int f;
    int d;
    int in_degree;
    int scc_index;

public:
    event(int h, int i)
    {
        hype = h;
        index = i;
    }
    friend class GraphAlgorithm;
    friend class isCycle;
    friend class indepComponent;
    friend class validOrder;
    friend class maxHype;
    friend class comparator_event;
};
class hype_event
{
private:
    int total_hype;
    int scc_index;
    char color;
    int hype_total_child;
    set<hype_event *> adj_list;

public:
    hype_event(int th, int si)
    {
        total_hype = th;
        scc_index = si;
    }
    friend class maxHype;
};
class GraphAlgorithm
{
protected:
    int n;
    vector<event *> events;
    vector<vector<event *>> scc;

public:
    GraphAlgorithm(vector<int> hype, vector<pair<int, int>> &edg_vec)
    {
        n = hype.size() + 1;
        events.resize(n);
        for (int i = 1; i < n; i++)
        {
            event *e = new event(hype[i - 1], i);
            e->in_degree = 0;
            events[i] = e;
        }
        for (int i = 0; i < edg_vec.size(); i++)
        {
            events[edg_vec[i].first]->adj_list.push_back(events[edg_vec[i].second]);
            events[edg_vec[i].second]->in_degree++;
        }
    }
    virtual void query()
    {
    }
};
class isCycle : public GraphAlgorithm
{
private:
    bool a;

public:
    isCycle(vector<int> hype, vector<pair<int, int>> &edges) : GraphAlgorithm(hype, edges)
    {
        a = false;
        // here it creates the graph
    }
    void query()
    {
        dfs();
        if (a)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    void dfs()
    {
        for (int i = 1; i < n; i++)
        {
            events[i]->color = 'w';
        }
        for (int i = 1; i < n; i++)
        {
            if (events[i]->color == 'w')
            {
                events[i]->color = 'g';
                dfs_search(events[i]);
            }
        }
    }
    void dfs_search(event *e)
    {
        for (auto itr : e->adj_list)
        {
            if (itr->color == 'w')
            {
                itr->color = 'g';
                dfs_search(itr);
            }
            else if (itr->color == 'g')
            {
                a = true;
                return;
            }
        }
        e->color = 'b';
    }
};
class indepComponent : public GraphAlgorithm
{
private:
    int time = 0;
    vector<event *> rev_vertices;
    vector<event *> f_sorted;
    int nv = 0;
    int nic = 0;
    int max_nv = 0;

public:
    indepComponent(vector<int> hype, vector<pair<int, int>> &edges) : GraphAlgorithm(hype, edges)
    {
        // here it creates the graph
        rev_vertices.resize(n);
        for (int i = 1; i < n; i++)
        {
            event *e = new event(hype[i - 1], i);
            rev_vertices[i] = e;
        }
        for (int i = 0; i < edges.size(); i++)
        {
            rev_vertices[edges[i].second]->adj_list.push_back(rev_vertices[edges[i].first]);
        }
    }
    void indepcomp_calc()
    {
        dfs();
        for (int i = 1; i < n; i++)
        {
            rev_vertices[i]->color = 'w';
        }
        for (int i = f_sorted.size() - 1; i >= 0; i--)
        {
            if (rev_vertices[f_sorted[i]->index]->color == 'w')
            {
                rev_vertices[f_sorted[i]->index]->scc_index = nic;
                events[f_sorted[i]->index]->scc_index = nic;
                vector<event *> temp;
                temp.push_back(events[f_sorted[i]->index]);
                scc.push_back(temp);
                nv = 1;
                rev_vertices[f_sorted[i]->index]->color = 'g';
                dfs_search1(rev_vertices[f_sorted[i]->index]);
                max_nv = max(max_nv, nv);
                nic++;
            }
        }
    }
    void query()
    {
        indepcomp_calc();
        cout << nic << " " << max_nv << endl;
    }
    void dfs_search1(event *e)
    {
        for (auto itr : e->adj_list)
        {
            if (itr->color == 'w')
            {
                itr->scc_index = e->scc_index;
                events[itr->index]->scc_index = e->scc_index;
                scc[scc.size() - 1].push_back(events[itr->index]);
                nv++;
                itr->color = 'g';
                dfs_search1(itr);
            }
        }
        e->color = 'b';
    }
    void dfs()
    {
        for (int i = 1; i < n; i++)
        {
            events[i]->color = 'w';
            events[i]->f = 0;
            events[i]->d = 0;
        }
        for (int i = 1; i < n; i++)
        {
            if (events[i]->color == 'w')
            {
                time++;
                events[i]->d = time;
                events[i]->color = 'g';
                dfs_search(events[i]);
            }
        }
    }
    void dfs_search(event *e)
    {
        for (auto itr : e->adj_list)
        {
            if (itr->color == 'w')
            {
                time++;
                itr->d = time;
                itr->color = 'g';
                dfs_search(itr);
            }
        }
        time++;
        e->f = time;
        f_sorted.push_back(e);
        e->color = 'b';
    }
    friend class maxHype;
};
class comparator_event
{
public:
    bool operator()(event *e1, event *e2)
    {
        return e1->index > e2->index;
    }
};
class validOrder : public GraphAlgorithm
{
private:
    priority_queue<event *, vector<event *>, comparator_event> q;

public:
    validOrder(vector<int> hype, vector<pair<int, int>> &edges) : GraphAlgorithm(hype, edges)
    {
        // here it creates the graph
    }
    void query()
    {
        for (int i = 1; i < n; i++)
        {
            if (events[i]->in_degree == 0)
            {
                q.push(events[i]);
            }
        }
        vector<int> top_order;
        while (!q.empty())
        {
            event *e = q.top();
            top_order.push_back(e->index);
            q.pop();
            for (auto itr : e->adj_list)
            {
                itr->in_degree--;
                if (itr->in_degree == 0)
                {
                    q.push(itr);
                }
            }
        }
        if (top_order.size() != n - 1)
        {
            cout << "NO" << endl;
        }
        else
        {
            for (int i = 0; i < top_order.size(); i++)
            {
                cout << top_order[i] << " ";
            }
            cout << endl;
        }
    }
};
class maxHype : public GraphAlgorithm
{
private:
    vector<hype_event *> hype_vertices;

public:
    maxHype(vector<int> hype, vector<pair<int, int>> &edges) : GraphAlgorithm(hype, edges)
    {
        // here it creates the graph
        indepComponent *ic = new indepComponent(hype, edges);
        ic->indepcomp_calc();
        for (auto itr : ic->scc)
        {
            int total_hype = 0;
            for (auto itr_in : itr)
            {
                total_hype += itr_in->hype;
            }
            hype_event *e = new hype_event(total_hype, itr[0]->scc_index);
            hype_vertices.push_back(e);
        }
        for (int i = 0; i < ic->scc.size(); i++)
        {
            for (auto itr : ic->scc[i])
            {
                events[itr->index]->scc_index = i;
            }
        }
        for (int i = 0; i < edges.size(); i++)
        {
            if (events[edges[i].first]->scc_index != events[edges[i].second]->scc_index)
            {
                hype_vertices[events[edges[i].first]->scc_index]->adj_list.insert(hype_vertices[events[edges[i].second]->scc_index]);
            }
        }
    }
    void query()
    {
        for (int i = 0; i < hype_vertices.size(); i++)
        {
            hype_vertices[i]->color = 'w';
        }
        for (int i = 0; i < hype_vertices.size(); i++)
        {
            if (hype_vertices[i]->color == 'w')
            {
                hype_vertices[i]->color = 'g';
                hype_vertices[i]->hype_total_child = dfs_search(hype_vertices[i]);
            }
        }
        int max_hype = 0;
        for (int i = 0; i < hype_vertices.size(); i++)
        {
            max_hype = max(max_hype, hype_vertices[i]->hype_total_child);
        }
        cout << max_hype << endl;
    }
    int dfs_search(hype_event *he)
    {
        he->color = 'g';
        int max_child_hype = 0;
        for (auto itr : he->adj_list)
        {
            if (itr->color == 'w')
                max_child_hype = max(max_child_hype, dfs_search(itr));
            else
                max_child_hype = max(max_child_hype, itr->hype_total_child);
        }
        he->color = 'b';
        he->hype_total_child = he->total_hype + max_child_hype;
        return he->hype_total_child;
    }
};
int main()
{
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<int> hype(n);
    for (int i = 0; i < n; i++)
    {
        cin >> hype[i];
    }
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].first >> edges[i].second;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            GraphAlgorithm *ga = new isCycle(hype, edges);
            ga->query();
        }
        else if (type == 2)
        {
            GraphAlgorithm *ga = new indepComponent(hype, edges);
            ga->query();
        }
        else if (type == 3)
        {
            GraphAlgorithm *ga = new validOrder(hype, edges);
            ga->query();
        }
        else
        {
            GraphAlgorithm *ga = new maxHype(hype, edges);
            ga->query();
        }
    }
}
