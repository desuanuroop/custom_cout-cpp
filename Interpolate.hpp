#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;
class helper{
	public:
	string data;
	//constructor
	helper(){}
	helper(const char *value):data(value){
	}
	//overload + operator
	friend ostream &operator<<( ostream &out, const helper hp){
		return out;
	}
};

helper Interpolate(const char *format){
	return helper(format);
}

template<typename T1, typename... Targs>
helper Interpolate(const char *format, T1 value, Targs... Fargs){
	helper hp;
	bool isString;
	string s, data;
	for(; *format != '\0'; format++){
		if(*format == '%'){
			cout<<value;
			Interpolate(format+1, Fargs...);
			return hp;
		}
		cout<<*format;
	}
	return hp;
}

//Interpolate("i=%, d=%", 10, 20);
//Interpolate("i=%", 10)
