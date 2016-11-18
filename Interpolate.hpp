#include <iostream>
#include <boost/lexical_cast.hpp>
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
	void operator+(helper rhs){
		data.append(rhs.data);
	}
	friend ostream &operator<<( ostream &out, const helper hp){
		out<<hp.data;
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
			try{
				data = boost::lexical_cast<string>(value);
			}
			catch ( const boost::bad_lexical_cast &exc ){ // conversion failed, exception thrown by lexical_cast and caught
				data = '\0'; // give 'Number' an arbitrary value ( in this case zero )
			}
//			if(typeid(value) == typeid(double))
//				data.erase(hp.data.find_last_not_of('0') +1, std::string::npos);
			hp.data.append(data);
//			hp.data.erase( hp.data.find_last_not_of('0') +1, std::string::npos);
			hp+(Interpolate(format+1, Fargs...));
			return hp;
		}
		s=*format;
		hp.data.append(s);
	}
	return hp;
}

//Interpolate("i=%, d=%", 10, 20);
//Interpolate("i=%", 10)
