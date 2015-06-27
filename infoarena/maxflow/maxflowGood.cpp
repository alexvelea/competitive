#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
   
#include <cassert>
#include <ctime>
#include <cstdlib>
using namespace std;
   
ifstream fin("maxflow.in");
ofstream fout("maxflow.out");
 
#define int64 long long
   
const int inf = 0x3f3f3f3f, kMaxN = 0;
const double eps = 1e-6;
 
//########### EDGE CLASS
struct Edge {
    int a, b, flow, cap;
    Edge();
    Edge(int _a, int _b, int _cap);
 
    int other(int _nod);
    int getMaxFlow(int _nod);
    int getReverseMaxFlow(int _nod);
    void pumpFlow(int _nod, int _f);
    void pumpReverseFlow(int _nod, int _f);
};

//########### FLOW CLASS
struct Flow {
    static int inf;
    int source, sink, flow, maxNod;
    int64 mxPossibleFlow;
    vector<vector<int> > edgeId;
    vector<Edge> edges;
    vector<int> father, potentialFinish, que;
   
    Flow();
    Flow(int _source, int _sink, int _maxNod);
   
    void addEdge(int a, int b, int cap);
    int pumpFlow();
    int getFlow();
} flow;

//############ EDGE DEFINITION
Edge::Edge() {
    a = b = flow = cap = 0;
}
 
Edge::Edge(int _a, int _b, int _cap) {
    a = _a;
    b = _b;
    cap = _cap;
    flow = 0;
}
 
int Edge::other(int _nod) {
    return a + b - _nod;
}
 
int Edge::getMaxFlow(int _nod) {
    if (_nod == a) {
        return cap - flow;
    } else {
        return flow;
    }
}
 
int Edge::getReverseMaxFlow(int _nod) {
    return getMaxFlow(other(_nod));
}
 
void Edge::pumpFlow(int _nod, int _f) {
    if (_nod == a) {
        flow += _f;
    } else {
        flow -= _f;
    }
}
 
void Edge::pumpReverseFlow(int _nod, int _f) {
    pumpFlow(other(_nod), _f);
} 
//################# END EDGE

//################# FLOW
int Flow::inf = 0x3f3f3f3f;
   
Flow::Flow() {
    source = sinkw = maxNod = 0;  
    flow = mxPossibleFlow = 0;
    edgeId.resize(1);
}  
Flow::Flow(int _source, int _sink, int _maxNod) {
    source = _source;
    sink = _sink;
    maxNod = _maxNod;
    edgeId.resize(maxNod + 1);
    flow = mxPossibleFlow = 0;
     
    father.reserve(maxNod + 1);
    que.reserve(maxNod + 1);
    potentialFinish.reserve(maxNod + 1);
}
 
void Flow::addEdge(int a, int b, int cap) {
    if (a == source or b == source) {
        mxPossibleFlow += cap;
    }

    assert(a <= maxNod and b <= maxNod);
    edgeId[a].push_back(edges.size());
    edgeId[b].push_back(edges.size());
    edges.push_back(Edge(a, b, cap));
}
 
int Flow::pumpFlow() {
    const int notVisited = -1;
 
    potentialFinish.clear();
    for (int i = 0; i <= maxNod; ++i) {
        father[i] = notVisited;
    }
       
    father[source] = source;
    int st = 0, dr = 0;
    que[dr++] = source;
 
    srand(time(NULL));
    while (st < dr) {
        int nod = que[st++];
         
        for (auto itr : edgeId[nod]) {
            if (father[edges[itr].other(nod)] == notVisited and edges[itr].getMaxFlow(nod)) {
                father[edges[itr].other(nod)] = itr;
                if (edges[itr].other(nod) == sink) {
                    potentialFinish.push_back(itr);
                } else {
                    que[dr++] = edges[itr].other(nod);
                }
            }
        }
    }
     
    int totalFlow = 0;
    for (auto finishItr : potentialFinish) {
        int mxFlow = edges[finishItr].getReverseMaxFlow(sink);
        for (int nod = edges[finishItr].other(sink); mxFlow != 0 and nod != source; nod = edges[father[nod]].other(nod)) {
            mxFlow = min(mxFlow, edges[father[nod]].getReverseMaxFlow(nod));
        }
         
        if (mxFlow == 0) {
            continue;
        }
         
        edges[finishItr].pumpReverseFlow(sink, mxFlow);
        for (int nod = edges[finishItr].other(sink); nod != source; nod = edges[father[nod]].other(nod)) {
            edges[father[nod]].pumpReverseFlow(nod, mxFlow);
        }
        totalFlow += mxFlow;
    }
    return totalFlow;   
}
     
int Flow::getFlow() {
    int actFlow = 0;
    do {
        actFlow = pumpFlow();
        flow += actFlow;
    } while (actFlow != 0);
    return flow;
}
//############ END FLOW
 
   
int main() {
    int n, m; fin >> n >> m;
    flow = Flow(1, n, n);
    while (m--) {
        int a, b, f; fin >> a >> b >> f;
        flow.addEdge(a, b, f);
    }
    fout << flow.getFlow() << '\n';
    return 0;
}
