#include <iostream>
using namespace std;
void tprintf(const char *format){
	cout<< format;
}

template<typename T, typename... Targs>
std::ostream& tprintf(const char *format, T value, Targs... Fargs){
	for(; *format != '\0'; format++){
		if(*format == '%'){
			cout<<value;
			tprintf(format+1, Fargs...);
			return;
		}
		cout<<*format;
	}
	return std::cout;
}

int main(){
	int i=616;
	double x = 3.14;
	std::string str("foo");
	cout<< tprintf("(i=%, x1=%, x2=%, str1=%, str2=%)\n", i, x, 1.001, str, "hello")<<std::endl<<133<<std::endl;
	tprintf("% world% %\n","Hello",'!',123);
	return 0;
}
