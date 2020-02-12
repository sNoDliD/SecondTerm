#include "Header.h"

int main(){
	initialization();

	try {
		startMenu();
	}
	catch (int e) {
		system("cls");
		cout << "Program breaks: ";
		switch (e)
		{
		case -1: 
			cout << "File truoble";
			break;
		default:
			cout << "Just break";
			break;
		}
		cout << endl;
	}
	
	memoryFree();
	return 0;
}
