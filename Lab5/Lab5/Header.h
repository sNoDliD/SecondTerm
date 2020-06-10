#ifndef MY_HEADER_ALL_DATA
#define MY_HEADER_ALL_DATA

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <map>
#include <functional>

using std::cout; using std::cin; using std::endl;


using std::vector; using std::size_t;
using std::string; using std::stringstream;
using std::this_thread::sleep_for; using std::chrono::milliseconds;

using vertices = vector<size_t>;

void EnterPoint(std::istream& in = cin, size_t sleep_time = 0);


class IGraph {
public:
	virtual void randomize(size_t n, size_t m, bool oriented) = 0;
	virtual void add(size_t n, size_t m, float weight) = 0;
	virtual void print() = 0;

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

	virtual IGraph* Change() = 0;
	virtual ~IGraph() {};
};

class GraphMatrix : public IGraph {
public:
	GraphMatrix() {

	}
	void randomize(size_t n, size_t m, bool oriented) override {

	}
	void add(size_t n, size_t m, float weight) override{

	}
	void print() override {

	}
	bool is_acyclic() override {
		return true;
	}
	void DFS() override {

	}
	void DFS_weigth() override {

	}

	vertices Sort_kana() override {
		return vertices{};
	}
	vector<vertices> Dijkstree()override {
		return vector<vertices>{};
	}
	vertices Dijkstree(size_t vertex) override {
		return vertices{};
	}
	vertices Dijkstree(size_t vertex_start, size_t vertex_end) override {
		return vertices{};
	}

	size_t Total_weight() override {
		return size_t{};
	}
	IGraph* Skeletal() override {
		return this;
	}
	IGraph* Skeletal_weigth() override {
		return this;
	}
	IGraph* Kruskal() override {
		return this;
	}

	IGraph* Change() override {
		IGraph* graphList{};
		return graphList;
	}

	~GraphMatrix() override {}
};

class GraphList : public IGraph {
public:
	GraphList() {}

	void randomize(size_t n, size_t m, bool oriented) override {

	}
	void add(size_t n, size_t m, float weight) override {

	}
	void print() override {

	}
	bool is_acyclic() override {
		return true;
	}
	void DFS() override {

	}
	void DFS_weigth() override {

	}

	vertices Sort_kana() override {
		return vertices{};
	}
	vector<vertices> Dijkstree()override {
		return vector<vertices>{};
	}
	vertices Dijkstree(size_t vertex) override {
		return vertices{};
	}
	vertices Dijkstree(size_t vertex_start, size_t vertex_end) override {
		return vertices{};
	}

	size_t Total_weight() override {
		return size_t{};
	}
	IGraph* Skeletal() override {
		return this;
	}
	IGraph* Skeletal_weigth() override {
		return this;
	}
	IGraph* Kruskal() override {
		return this;
	}

	IGraph* Change() override {
		return this;
	}

	~GraphList() override {}
};


#endif // !MY_HEADER_ALL_DATA
