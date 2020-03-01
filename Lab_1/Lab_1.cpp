#include "Header.h"


int main(){
	Initialization(); 

	try {
		StartMenu();
	} catch (int e) {
		system("cls");
		cout << "Program breaks: ";
		switch (e){
		case -1:
			cout << "File truoble";
			break;
		case -2:
			cout << "Enum error";
			break;
		case -3:
			cout << "Switch not provided";
			break;
		default:
			cout << "Just break with code " << e;
			break;
		}
		cout << endl;
	}

	MemoryFree();
	return 0;
}
