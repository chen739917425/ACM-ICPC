template<class T>
struct MCMF {
    static const int N = 20, M = 200;
    const T inf = 1e9;
    struct Edge {
        int ne, to;
        T cap, w;
        Edge() {}
        Edge(int to_, T cap_, T w_, int ne_): to(to_), cap(cap_), w(w_), ne(ne_) {} 
    };
    vector<Edge> e;
    vector<int> head, cur, inq, fa;
    vector<T> f;
    T cost;
    MCMF() {
        head.resize(N, -1);
        cur.resize(N);
        inq.resize(N);
        f.resize(N);
        fa.resize(N);
        cost = 0;
    }
    void add(int u, int v, int c, int w) {
        e.emplace_back(Edge(v, c, w, head[u]));
        head[u] = e.size() - 1;
    }
    void link(int u, int v, int c, int w) {
        add(u, v, c, w);
        add(v, u, 0, -w);
    }
    bool spfa(int s, int t) {
        fill(f.begin(), f.end(), inf);
        fill(fa.begin(), fa.end(), -1);
        queue<int> q;
        q.push(s);
        f[s] = 0;
        while (q.size()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int i = head[u]; ~i; i = e[i].ne) {
                int v = e[i].to;
                T w = e[i]. w, c = e[i].cap;
                if (c && f[u] + w < f[v])
                    q.push(v), inq[v] = 1, f[v] = f[u] + w, fa[v] = u;
            }
        }
        return f[t] < inf;
    }
    T dfs(int u, int t, T flow) {
        if (u == t)
            return flow;
        int cur_f = 0;
        for (int& i = cur[u]; ~i; i = e[i].ne) {
            int v = e[i].to;
            T w = e[i].w, c = e[i].cap;
            if (c && fa[v] == u) {
                T ret = dfs(v, t, min(flow, c));
                cost += ret * w;
                cur_f += ret;
                flow -= ret;
                e[i].cap -= ret;
                e[i^1].cap += ret;
            }
            if (flow <= 0)
                return cur_f;
        }
        return cur_f;
    }
    T run(int s, int t) {
        T max_f = 0;
        while (spfa(s, t)) {
            cur.assign(head.begin(), head.end());
            max_f += dfs(s, t, inf);
        }
        return max_f;
    }
};