#ifndef ADD_THIS_IN_ALL_MY_PRODUCTS
#define ADD_THIS_IN_ALL_MY_PRODUCTS


template <typename Tfunc, typename... T>
int CallWithoutBack(Tfunc& Func,const char* message = "", T&... data) {
	try {
		Func(data...);
	}
	catch (const char* msg) {
		system("cls");
		std::cout << "Error: " << msg << std::endl;
		return -1;
	}
	system("cls");
	std::cout << message;
	return 0;
}




#endif // !ADD_THIS_IN_ALL_MY_PRODUCTS
