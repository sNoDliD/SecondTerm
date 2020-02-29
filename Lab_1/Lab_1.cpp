#include "Header.h"

void f1() {
	cout << "f1" << endl;
}
void f2() {
	cout << "f2" << endl;
}
void f3() {
	cout << "f3" << endl;
}


int main(){
	Initialization(); 
	int a = 2;

	SwitchFuncOld(2, f1, f2, f3)();
	SwitchFunc(2, { f1, f2, f3 })();

	system("pause");
	try {
		StartMenu();
	} catch (int& e) {
		system("cls");
		cout << "Program breaks: ";
		switch (e){
		case -1:
			cout << "File truoble";
			break;
		case -2:
			cout << "Enum error";
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
