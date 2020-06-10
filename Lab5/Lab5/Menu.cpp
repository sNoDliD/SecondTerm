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
		string line;
		int count;

		Inputer(string line) : line(line), count(0) {}

		template <typename T>
		Inputer operator () (T& value, bool(*check)(T) = nullptr) {
			if (this->count == -1) {
				return *this;
			}

			string oneWord;
			stringstream allWords{ this->line };

			if (allWords >> oneWord) {
				stringstream oneWordStream{ oneWord };

				if (allWords.eof()) {
					this->line = "";	
				}
				std::getline(allWords, this->line);

				if (oneWordStream >> value && oneWordStream.eof() && 
					(check && check(value) || !check)) {
					
					this->count++;
					return *this;
				}
			}
				
			this->count = -1;
			return *this;
		}

		template <typename T, class lambda>
		Inputer operator () (T& value, lambda check) {
			return this->operator()(value, (bool(*)(T)) check);
		}

	};

	void demonstration(string params) {
		int time;

		Inputer inputer{ params };
		int values_count = inputer(time, [](int time) {return time > 0 && time < 5e3; }).count;


		if (values_count == 1) {
			std::ifstream demo_file("demo.txt");
			if (demo_file) {
				EnterPoint(demo_file, time);
				demo_file.close();
				cout << "The end of demo mode\n";
			}
			else {
				cout << "Can't open demo file(\n";
			}
		}
		else
			cout << "Incorrect input! Look 'help'\n";
	}

	void help() {
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
	}

	bool change(IGraph*& graph, string line) {
		IGraph* new_graph = graph->Change();
		clener(graph);
		graph = new_graph;

		return true;
	}

	bool print(IGraph*& graph, string line) {
		graph->print();

		return true;
	}

	bool randomize(IGraph*& graph, string line) {
		int n, m;

		auto positive = [](int value) { return value > 0; };
		Inputer inputer{ line };
		inputer = inputer(n, positive)(m, positive);

		if (inputer.count == 2) {
			string w;
			inputer (w);
			graph->randomize(n, m, w == "W");
			return true;
		}
		return false;
	}

	bool add(IGraph*& graph, string line) {
		int n, m;
		float weight;

		auto positive = [](int value) { return value > 0; };
		Inputer inputer{ line };
		inputer = inputer(n, positive)(m, positive);

		if (inputer.count == 2) {
			if (inputer(weight).count == -1)
				weight = 1;
			graph->add(n, m, weight);
			return true;
		}
		return false;
	}

	bool skeletal(IGraph*& graph, string line) { 
		IGraph* skelet; 
		string answer;
		
		Inputer inputer{ line };
		inputer(answer);
		if (answer == "1") {
			skelet = graph->Skeletal();
		}
		else if (answer == "2") {
			skelet = graph->Skeletal_weigth();
		}
		else {
			skelet = graph->Kruskal();
		}

		skelet->print();
		clener(skelet);

		return true; 
	}

	bool minway(IGraph*& graph, string line) {
		int v1, v2;

		auto positive = [](int value) { return value > 0; };
		Inputer inputer{ line };
		bool one = inputer(v1, positive).count == 1;
		bool two = inputer(v2, positive).count == 2;

		if (two) {
			graph->Dijkstree(v1, v2);
		}
		else if (one) {

			graph->Dijkstree(v1);
		}
		else {
			graph->Dijkstree();

		}

		return true;
	}

	bool topsort(IGraph*& graph, string line) { 
		if (graph->is_acyclic()) {
			vertices v = graph->Sort_kana();
		}
		else
			cout << "Graph is not acyclic (\n";
		return true; 
	}

	bool benchmark(IGraph*& graph, string line) { return true; }

	string InputValues(std::istream& in, string& command) {
		cout << ">> ";
		string line;
		std::getline(in, line);
		if (&in != &cin) cout << line << '\n';

		stringstream temp{ line };
		temp >> command;
		std::getline(temp, line);

		return line;
	}

	void Analizer(IGraph*& graph, string command, string params) {
		bool success = true;
		static std::map<string, bool(*)(IGraph*&, string)> menu{
			{"change", change} ,
			{"print", print} ,
			{"rand", randomize} ,
			{"add", add} ,
			{"skeletal", skeletal} ,
			{"minway", minway} ,
			{"topsort", topsort} ,
			{"benchmark", benchmark} 
		};

		if (menu.count(command)) {
			if (!menu[command](graph, params))
				cout << "Filed to complete operation\n";
		}
		else if (command == "demo") {
			demonstration(params);
		}
		else if (command == "help") {
			help();
		}
		else cout << "Could not recognize the command\n";
	}
}


void EnterPoint(std::istream& in, size_t sleep_time) {
	if (&in == &cin) {
		help();
	}

	IGraph* graph = new GraphMatrix;
	while (true)
	{
		string command;
		string params = InputValues(in, command);

		if (command == "exit")
			break;
		
		Analizer(graph, command, params);

		cout << endl;
		sleep_for(milliseconds(sleep_time));
	}
}