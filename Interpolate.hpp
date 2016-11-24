#include <iostream>
#include <typeinfo>
#include <string>
namespace cs540{
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
		out<<"OOPSY"<<endl;
		return out;
	}
};

helper Interpolate(const char *format){
	ostream os(cout.rdbuf());
	if(*format == '\\'){
		os<<*(++format);
	}else
		os<<*format;
	return helper();
}
class WrongNumberOfArgs:public exception{
	const char *what() const throw(){
		return "Wrong_Number_of_Args";
	}
};
template<typename T1, typename... Targs>
helper Interpolate(const char *format, T1 value, Targs... Fargs){
	int count=0;
	const char *check = format;
	helper hp;
	ostream os(cout.rdbuf());
	for(; *check !='\0'; check++){
		if(*check == '\\'){//check if next character is %
			count = (*(check+1) == '%')? count-1:count;
		}
		if(*check == '%')
			count++;
	}
	if(count == (sizeof...(Targs)+1)){
		bool isString;
		string s, data;
		for(; *format != '\0'; format++){
			if(*format == '\\'){//Print the next %
				os<<*(++format);
			}
			else if(*format == '%'){
				os<<value;
				Interpolate(format+1, Fargs...);
				return hp;
			}else{
				os<<*format;
			}
		}
	}else{//Throw exception
		throw WrongNumberOfArgs();
	}
	return hp;
}
}//End of namespace
//Interpolate("i=%, d=%", 10, 20);
//Interpolate("i=%", 10)
