#include "Header.h"

namespace {
	struct Clener
	{
		template <typename T>
		Clener operator () (T*& ptr) const
		{
			if (ptr) {
				delete ptr;
				ptr = nullptr;
			}

			return *this;
		}
	} const clener;

	struct Creator
	{
		template <typename T>
		Creator operator () (T*& ptr) const
		{
			if (!ptr) {
				ptr = new T;
			}

			return *this;
		}
	} const creator;

	struct Inputer
	{
		stringstream& in;
		bool continue_input = true;

		Inputer(stringstream& in) : in(in) {}

		template <typename T>
		Inputer operator () (T*& ptr)
		{
			if (this->continue_input) {
				creator(ptr);
				if (!(this->in >> *ptr)) {
					clener(ptr);
					this->continue_input = false;
				}

			}
			else {
				clener(ptr);
			}

			return *this;
		}
	};


	void demonstration(size_t time) {
		std::ifstream demo_file("help.txt");

		if (demo_file) {
			EnterPoint(demo_file, time);
			demo_file.close();
			cout << "The end of demo mode\n";
		}
		else {
			cout << "Can't open demo file(\n";
		}
	}

	bool change (bool condition, IGraph*& graph) {
		if (!condition) return false;

		IGraph* new_graph = graph->Change();
		clener(graph);
		graph = new_graph;

		return true;
	}
	
	bool print (bool condition, IGraph*& graph) {
		if (!condition) return false;

		graph->print();

		return true;
	}
	
	bool randomize (bool condition, IGraph*& graph) {
		if (!condition) return false;

		graph->randomize();

		return true;
	}

	bool help(bool condition) {
		if (!condition) return false;

		std::ifstream help_file("help.txt");

		if (help_file) {
			string buffer;
			while (!help_file.eof()) {
				std::getline(help_file, buffer, '\n');
				cout << buffer + '\n';
			}

			help_file.close();
		}
		else {
			cout << "Can't open help file(\n";
		}

		return true;
	}

	bool test(IGraph*& graph, int* first, int* second, float* weight) { return true; }

	string InputValues(std::istream& in, int*& first, int*& second, float*& weight) {
		string line;
		std::getline(in, line);
		if (&in != &cin) cout << line + '\n';

		stringstream temp{ line };


		if (temp >> line) {
			Inputer inputer{ temp };
			inputer(first)(second)(weight);

			if (!temp.eof() || (first && *first <= 0) || (second && *second <= 0)) {
				line = "error";
			}
		}

		return line;
	}

	void Analizer(IGraph*& graph, string command, int* first, int* second, float* weight) {
		bool success = true;
		static std::map<string, bool(&)(IGraph*&, int*, int*, float*)> s;
		auto x = &test;
		
		if (command == "help") success = help(!first);

		else if (command == "change") success = change(!first, graph);

		else if (command == "print") success = print(!first, graph);

		else if (command == "rand") success = randomize(first && second, graph);

		else if (command == "add") success = help(first && second);

		else if (command == "skeletal") success = help(!second);

		else if (command == "minway ") success = help(!weight);

		else if (command == "topsort") success = help(!first);

		else if (command == "benchmark") success = help(!first);

		else if (command == "error") cout << "Error reading parameters\n";

		else cout << "Could not recognize the command\n";

		if (!success) {
			cout << "Filed to complete operation\n";
		}
	}
}


void EnterPoint(std::istream& in, size_t sleep_time) {
	if(&in == &cin) help(true);
	IGraph* graph = new GraphMatrix;
	
	int* first{};
	int* second{};
	float* weight{};

	while (true)
	{
		string command = InputValues(in, first, second, weight);
		if (command == "exit")
			break;
		else if (command == "demo") {
			if (first && !second) {
				demonstration(*first);
				continue;
			}
			else
				command = "error";
		}

		Analizer(graph, command, first, second, weight);
		cout << endl;
		sleep_for(milliseconds(sleep_time));
	}

	clener(graph)(first)(second)(weight);

}