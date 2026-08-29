/*
@title: Link-Cut Tree
@category: Trees
@complexity: O(log N) amortized per operation
@tags: dynamic trees, path queries, splay tree
*/

struct LinkCutTree {
    struct Node {
        int ch[2] = {0, 0}, par = 0;
        bool flip = false;
        long long val = 0, sum = 0;
    };
    vector<Node> t;

    LinkCutTree(int n) : t(n + 1) {}

    bool isRoot(int x) {
        int p = t[x].par;
        return p == 0 || (t[p].ch[0] != x && t[p].ch[1] != x);
    }
    void pushUp(int x) {
        t[x].sum = t[x].val + t[t[x].ch[0]].sum + t[t[x].ch[1]].sum;
    }
    void applyFlip(int x) {
        if (!x) return;
        swap(t[x].ch[0], t[x].ch[1]);
        t[x].flip ^= 1;
    }
    void pushDown(int x) {
        if (t[x].flip) {
            applyFlip(t[x].ch[0]);
            applyFlip(t[x].ch[1]);
            t[x].flip = false;
        }
    }
    void rotate(int x) {
        int p = t[x].par, g = t[p].par;
        int dir = (t[p].ch[1] == x);
        if (!isRoot(p)) t[g].ch[t[g].ch[1] == p] = x;
        t[x].par = g;
        t[p].ch[dir] = t[x].ch[dir ^ 1];
        if (t[x].ch[dir ^ 1]) t[t[x].ch[dir ^ 1]].par = p;
        t[x].ch[dir ^ 1] = p;
        t[p].par = x;
        pushUp(p);
        pushUp(x);
    }
    void splay(int x) {
        static vector<int> stk;
        stk.clear();
        int y = x;
        stk.push_back(y);
        while (!isRoot(y)) {
            y = t[y].par;
            stk.push_back(y);
        }
        while (!stk.empty()) {
            pushDown(stk.back());
            stk.pop_back();
        }
        while (!isRoot(x)) {
            int p = t[x].par, g = t[p].par;
            if (!isRoot(p)) {
                if ((t[g].ch[1] == p) == (t[p].ch[1] == x)) rotate(p);
                else rotate(x);
            }
            rotate(x);
        }
        pushUp(x);
    }
    // Makes x the deepest node on the root-to-x path, splayed to the top;
    // returns the last node touched (useful for LCA on the represented tree).
    int access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].par) {
            splay(y);
            t[y].ch[1] = last;
            pushUp(y);
            last = y;
        }
        splay(x);
        return last;
    }
    void makeRoot(int x) {
        access(x);
        applyFlip(x);
    }
    int findRoot(int x) {
        access(x);
        while (t[x].ch[0]) {
            pushDown(x);
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }
    bool connected(int x, int y) {
        if (x == y) return true;
        return findRoot(x) == findRoot(y);
    }
    // Links x to y. Precondition: x and y are in different trees.
    void link(int x, int y) {
        makeRoot(x);
        t[x].par = y;
    }
    // Cuts the edge between x and y, if it exists (safe no-op otherwise).
    void cut(int x, int y) {
        makeRoot(x);
        access(y);
        if (t[y].ch[0] == x && t[x].ch[1] == 0) {
            t[y].ch[0] = 0;
            t[x].par = 0;
            pushUp(y);
        }
    }
    void setVal(int x, long long v) {
        access(x);
        t[x].val = v;
        pushUp(x);
    }
    // Sum of vertex values on the path from x to y. Precondition: connected(x,y).
    long long pathQuery(int x, int y) {
        makeRoot(x);
        access(y);
        return t[y].sum;
    }
};