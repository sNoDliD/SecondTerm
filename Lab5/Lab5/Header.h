#ifndef MY_HEADER_ALL_DATA
#define MY_HEADER_ALL_DATA

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout; using std::cin; using std::endl;

using std::vector;
using std::string; using std::stringstream;
using std::size_t;
using vertices = vector<size_t>;

void EnterPoint();

class IGraph {
public:
	virtual bool is_acyclic() = 0;
	virtual void DFS() = 0;
	virtual void DFS_weigth() = 0;

	virtual vertices Sort_kana() = 0;
	virtual vector<vertices> Dijkstree() = 0;
	virtual vertices Dijkstree(size_t vertex) = 0;
	virtual vertices Dijkstree(size_t vertex_start, size_t vertex_end) = 0;

	virtual size_t Total_weight() = 0;
	virtual IGraph* Skeletal() = 0;
	virtual IGraph* Skeletal_weigth() = 0;
	virtual IGraph* Kruskal() = 0;
	virtual ~IGraph() {};
};

class GraphMatrix : public IGraph {
	GraphMatrix();
};

class GraphList : public IGraph {
	GraphList();
};


#endif // !MY_HEADER_ALL_DATA
