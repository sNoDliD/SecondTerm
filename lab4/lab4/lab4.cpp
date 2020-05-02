#include "MainHeader.h"


int main()
{
	IntTree a;
	for (int i = 0; i < 16; i++) {
		a.add(i + 1, 0.5f);
	}
	a.print();
	cout << endl;

	a.removeAll(5, 0.5f);
	a.print();
	//EnterPoint();

	return 0;
}