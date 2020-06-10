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
#include <random>

using std::cout; using std::cin; using std::endl;


using std::vector; using std::size_t;
using std::string; using std::stringstream;
using std::this_thread::sleep_for; using std::chrono::milliseconds;

using vertices = vector<size_t>;

void EnterPoint(std::istream& in = cin, size_t sleep_time = 0);


class Randomazer {
private:
	std::mt19937 rng;
public:
	Randomazer() {
		std::random_device dev;
		this->rng = std::mt19937(dev());
	}

	int operator()(int start = 0, int end = INT16_MAX) {
		size_t delta = 0;
		if (start < 0) {
			delta = -start;
			start = 0;
			end += delta;
		}
		std::uniform_int_distribution<std::mt19937::result_type> dist(start, end);

		return dist(this->rng) - delta;
	}
};

class IGraph {
public:
	virtual void randomize(size_t n, size_t m, bool w) = 0;
	virtual void add(size_t n, size_t m, int weight) = 0;
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
	size_t n;
	int** weights;
	bool** arr;

	GraphMatrix() : n(0), weights(nullptr), arr(nullptr) {}

	void randomize(size_t n, size_t m, bool w) override {
		if (this->weights || this->arr)
			this->~GraphMatrix();
		this->n = n;
		this->weights = new int* [n];
		this->arr = new bool* [n];

		for (size_t i = 0; i < n; i++) {
			weights[i] = new int[n] {0};
			arr[i] = new bool[n] {0};
		}

		Randomazer r;

		size_t edge_max = (n - 1) * n / 2;
		if (m > edge_max) {
			m = edge_max;
		}

		for (size_t i_edge = 0; i_edge < m; i_edge++){
			while (true){
				size_t first = r(0, n), second = r(0, n);
				if (arr[first][second] == 0) {
					add(first, second, w ? 1 : r(-99, 99));
					break;
				}
			}
		}



	}
	void add(size_t v1, size_t v2, int weight) override {
		if (v1 < n && v2 < n) {
			arr[v1][v2] = arr[v2][v1] = 1;
			weights[v1][v2] = weights[v2][v1] = weight;
		}
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

	~GraphMatrix() override {
		if (this->weights) {
			for (size_t i = 0; i < this->n; i++)
				delete[] this->weights[i];

			delete[] this->weights;
		}
		if (this->arr) {
			for (size_t i = 0; i < this->n; i++)
				delete[] this->arr[i];

			delete[] this->arr;
		}
	}
};

class GraphList : public IGraph {
public:
	GraphList() {}

	void randomize(size_t n, size_t m, bool w) override {

	}
	void add(size_t n, size_t m, int weight) override {

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
