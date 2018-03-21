/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	// TODO (4 lines)
	// HINT: use the findVertex function to check if a vertex already exists

	auto v1 = findVertex(in);

	if(v1 != NULL) return false;

	vertexSet.push_back(new Vertex<T>(in));

	return false;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	// TODO (6 lines)
	// HINT: use findVertex to obtain the actual vertices
	// HINT: use the next function to actually add the edge
	auto vs = findVertex(sourc);
	auto vd = findVertex(dest);

	if(vs == NULL || vd == NULL) return false;

	vs->addEdge(vd, w);
	return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	// TODO (1 line)
	adj.push_back(Edge<T>(d,w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	// TODO (5 lines)
	// HINT: Use "findVertex" to obtain the actual vertices.
	// HINT: Use the next function to actually remove the edge.
	auto vs = findVertex(sourc);
	auto vd = findVertex(dest);

	if(vs == NULL || vd == NULL) return false;

	return vs->removeEdgeTo(vd);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	// TODO (6 lines)
	// HINT: use an iterator to scan the "adj" vector and then erase the edge.

	for(auto it = adj.begin(); it != adj.end(); it++)
		if(it->dest == d){
			adj.erase(it);
			return true;
		}

	return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	// TODO (10 lines)
	// HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
	// HINT: take advantage of "removeEdgeTo" to remove incoming edges.
	for(auto it = vertexSet.begin(); it != vertexSet.end(); it++){
		if((*it)->info == in){
			auto v = *it;
			vertexSet.erase(it);
			for(auto u : vertexSet)
				u->removeEdgeTo(v);
			delete v;
			return true;
		}
	}
	return false;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	// TODO (7 lines)
	vector<T> res;

	for(auto v : vertexSet)
		v->visited = false;
	for(auto v : vertexSet)
		if(! v->visited)
			dfsVisit(v, res);
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	// TODO (7 lines)
	v->visited = true;
	res.push_back(v->info);

	for(auto & x : v->adj){
			auto y = x.dest;
		if( ! y->visited)
			dfsVisit(y, res);
	}
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	// TODO (22 lines)
	// HINT: Use the flag "visited" to mark newly discovered vertices .
	// HINT: Use the "queue<>" class to temporarily store the vertices.
	vector<T> res;

	auto sourc = findVertex(source);
	if(sourc==NULL) return res;
	queue<Vertex<T>*> queue;

	queue.push(sourc);
	sourc->visited = true;

	while(!queue.empty()){
		auto v = queue.front();
		queue.pop();
		res.push_back(v->info);
		for(auto & edge : v->adj){
			auto w = edge.dest;
			if( ! w->visited ){
				queue.push(w);
				w->visited = true;
			}
		}
	}
	return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
	// TODO (26 lines)
	vector<T> res;
	for(auto v : vertexSet) v->indegree = 0;
	for(auto v : vertexSet)
		for(auto & edge : v->adj)
			edge.dest->indegree++;

	queue<Vertex<T>*> queue;
	for(auto v : vertexSet){
		if(v->indegree == 0)
			queue.push(v);
	}

	while(!queue.empty()){
		auto v = queue.front();
		queue.pop();
		res.push_back(v->info);
		for(auto & edge : v->adj){
			auto w = edge.dest;
			w->indegree--;
			if( w->indegree == 0){
				queue.push(w);
			}
		}
	}

	if( vertexSet.size() != res.size()){
		cout << "� imposs�vel ordenar topologicamente!" << endl;
		res.clear();
		return res;
	}
	return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	auto s = findVertex(source);
	if(s == NULL) return -1;

	int maxChild = 0;
	queue<Vertex<T>*> q;
	inf = s->info;

	for(auto v = vertexSet.begin(); v != vertexSet.end(); v++){
		(*v)->visited = false;
	}
	s->visited = true;
	q.push(s);

	while(!q.empty()){
		auto v = q.front();
		q.pop();
		int children = 0;
		for(auto &e : v->adj){
			auto d = e.dest;
			if( ! d->visited ){
				d->visited = true;
				q.push(d);
				children++;
			}
		}
		if(maxChild < children){
			maxChild = children;
			inf = v->info;
		}
	}
	return maxChild;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
	// TODO (9 lines, mostly reused)
	// HINT: use the auxiliary field "processing" to mark the vertices in the stack.
	for(auto v : vertexSet){
		v->visited = false;
		v->processing = false;
	}
	for( auto v : vertexSet ){
		if( !v->visited){
			if(! dfsIsDAG(v))
				return false;
			}
	}
	return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	// TODO (12 lines, mostly reused)
	v->visited = true;
	v->processing = true;
	for( auto &e : v->adj){
		auto d = e.dest;
		if(d->processing){
			return false;
		}
		if(!d->visited){
			if(!dfsIsDAG(d)){
				return false;
			}
		}
	}
	v->processing = false;
	return true;
}

#endif /* GRAPH_H_ */
