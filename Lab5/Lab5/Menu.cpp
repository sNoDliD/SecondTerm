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

		template <typename T, class lambda>
		Inputer operator () (T& value, lambda check) {
			if (this->count != -1) {
				string oneWord;
				stringstream allWords{ this->line };
				if (allWords >> oneWord) {
					stringstream onwWordStream{ oneWord };

					if (onwWordStream >> value && check != nullptr && check(value))
						this->count = onwWordStream.eof() ? this->count + 1 : -1;
					else
						this->count = -1;

					if (allWords.eof())
						this->line = "";
					else
						std::getline(allWords, this->line);
				}
				else {
					this->count = -1;
				}
			}

			return *this;
		}

		template <typename T>
		Inputer operator () (T& value) {
			if (this->count != -1) {
				string oneWord;
				stringstream allWords{ this->line };
				if (allWords >> oneWord) {
					stringstream onwWordStream{ oneWord };

					if (onwWordStream >> value)
						this->count = onwWordStream.eof() ? this->count + 1 : -1;
					else
						this->count = -1;

					if (allWords.eof())
						this->line = "";
					else
						std::getline(allWords, this->line);
				}
				else {
					this->count = -1;
				}
			}

			return *this;
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

	bool help() {

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

		graph->randomize();

		return true;
	}

	bool add(IGraph*& graph, string line) { return true; }

	bool skeletal(IGraph*& graph, string line) { return true; }

	bool minway(IGraph*& graph, string line) { return true; }

	bool topsort(IGraph*& graph, string line) { return true; }

	bool benchmark(IGraph*& graph, string line) { return true; }

	bool error(IGraph*& graph, string line) { return true; }

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
			{"benchmark", benchmark} ,
			{"error", error}
		};
		/*if (command == ) success = help(!first);

		else if (command == "change") success = change(!first, graph);

		else if (command == "print") success = print(!first, graph);

		else if (command == "rand") success = randomize(first && second, graph);

		else if (command == "add") success = help(first && second);

		else if (command == "skeletal") success = help(!second);

		else if (command == "minway ") success = help(!weight);

		else if (command == "topsort") success = help(!first);

		else if (command == "benchmark") success = help(!first);*/


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
	if(&in == &cin) help();
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