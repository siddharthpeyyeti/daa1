#include<bits/stdc++.h>
using namespace std;

//vector of vectors to hold final answer
vector <vector <int>> ans;

//intersection function
void intersect(vector <int> pred, vector <int> desc, vector <int> &scc) {
    sort(pred.begin(), pred.end());
    sort(desc.begin(), desc.end());
    int pp=0, dp=0;
    while (pp<pred.size() && dp<desc.size()) {
        if (pred[pp]>desc[dp])
            dp++;
        else if (pred[pp]<desc[dp])
            pp++;
        else if (pred[pp]==desc[dp])
            scc.push_back(pred[pp]);
    }
}


//transpose graph
void transposeGraph(vector<int> G[], vector<int> transpose[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < G[i].size(); j++)
            transpose[(G[i][j])].push_back(i);
}

//dfs utility function for recursion
void dfsutil(vector <int> G[], int v, bool visited[], vector <int> &desc) {
    // Mark the current node as visited and
    // print it
    visited[v] = true;
    cout << v << " ";
    desc.push_back(v);

    // Recur for all the vertices adjacent
    // to this vertex
    for (auto i = G[v].begin(); i != G[v].end(); ++i)
        if (!visited[*i])
            dfsutil(G, *i, visited, desc);
}

//dfs function to initialize visited and begin search
void dfs(vector <int> G[], int n, int pivot, vector <int> &desc) {
    bool visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;
    //call recursive dfs util function
    dfsutil(G, pivot, visited, desc);
}

//function to print graph
void printGraph(vector <int> G[], int n) {
	for (int i = 0; i < n; ++i) {
        cout << "\n Adjacency list of vertex " << i << "\n";
        for (auto x : G[i])
            cout << "-> " << x;
		printf("\n");
	}
}

void dcsc(vector <int> G[], int n, vector <int> V) {
    if (0) {
        cout << "{ ";
        for (int i=0; i<n; i++) {
            cout << V[i] << " ";
        }
        cout << "}";
    }
    else {
        //choose pivot vertex randomly
        int pivot = V[2];

        //create predecessor and descendant arrays
        vector <int> desc, pred;

        //dfs on pivot to find all the vertices it can reach
        dfs(G, n, pivot, desc);
        cout << "\n\ndesc: \n";
        for (int i=0; i<desc.size(); i++)
            cout << desc[i];

        //TRANSPOSE THE GRAPH
        //declare transpose, call transpose function on G, print
        vector<int> transpose[n];
        transposeGraph(G, transpose, n);
        printGraph(transpose, n);

        //call dfs on transpose and get predecessors
        dfs(transpose, n, pivot, pred);
        cout << "\n\npred: \n";
        for (int i=0; i<pred.size(); i++)
            cout << pred[i];

        //find intersection of desc and pred
        sort(pred.begin(), pred.end());
        sort(desc.begin(), desc.end());
        vector<int> scc(desc.size()+pred.size());
        set_intersection(pred.begin(), pred.end(), desc.begin(), desc.end(), scc.begin());
        for (int i=scc.size()-1; i>0; i--)
            if (scc[i]==0)
                scc.pop_back();
            else
                break;

        //store the component as an answer
        ans.push_back(scc);
        cout << "\nSCC:\n";
        for (int i=0; i<scc.size(); i++)
            cout << scc[i];
    }
}

int main() {
    //number of vertices n, number of edges m
    int n, m;

    //create vector of vertices v from 0 to n
    vector <int> V;
    printf("\nEnter number of vertices: ");
    scanf("%d", &n);
    for (int i=0; i<n; i++)
        V.push_back(i);

    //adjacency list G
	vector <int> G[n];
    printf("\nEnter number of edges: ");
	scanf("%d", &m);
	//scan each edge
	for (int i=0; i<m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        //add the edge to the list
        G[x].push_back(y);
	}
	printGraph(G, n);

	dcsc(G, n, V);
	return 0;
}
