#include "Header.h"

namespace{
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




	void help() {

	}

	string InputValues(std::istream& in, int*& first, int*& second, float*& weight) {
		string line;
		std::getline(in, line);
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

	void Analizer(IGraph* graph, int* first, int* second, float* weight) {

	}
}


void EnterPoint(std::istream& in) {
	IGraph* graph{ nullptr };

	int* first{};
	int* second{};
	float* weight{};

	while (true)
	{
		string command = InputValues(in, first, second, weight);
		if (command == "exit")
			break;

		Analizer(graph, first, second, weight);

	}

}