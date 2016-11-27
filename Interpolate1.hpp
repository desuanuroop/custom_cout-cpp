#include <iostream>
#include <typeinfo>
#include <tuple>
#include <sstream>
#include <assert.h>

namespace cs540{

using namespace std;
template<typename T>
void print(std::ostream &os, const char *, const T& tuple);

template<typename T1, typename... Targs>
class helper{
	public:
	int x;
	//template members
	const char *format;
	std::tuple<T1, Targs ...> Fargs;

	//constructor
	helper(const char *form, std::tuple<T1, Targs ...> Fargs):x(100){
		this->format = form;
		this->Fargs = Fargs;
	}
	helper(const char *form){
		this->format = form;
	}
	~helper(){
		cout<<"IN destructor"<<endl;
	}
	friend std::ostream& operator<<(std::ostream &os, const helper *hp){
		print(os, hp->format, hp->Fargs);
	}//End of Friend
};
//Exception class
class WrongNumberOfArgs:public exception{
	const char *what() const throw(){
		return "Wrong_Number_of_Args";
	}
};

template<typename T>
void print3(std::ostream &os, const char *format, const T &tuple){
	os<<format;
}
template<std::size_t index, std::size_t... indices, typename T>
void print3(std::ostream &os, const char *format, const T &tuple){
/*	os<<endl<<"format is:"<<format<<endl;
	os<<std::get<index>(tuple);
	print3<indices...>(os,format,tuple);*/

	const char *temp = format;
	int count=0;
	for(; *temp != '\0'; temp++){
		if(*temp == '\\')
			count = (*(temp+1) == '%')?count-1:count;
		else if(*temp == '%')
			count++;
	}
	if(count == sizeof...(indices)+1){
		for(;*format != '\0'; format++){
			if(*format == '\\')//print the next character
				os<<*(++format);
			else if(*format == '%'){
				os<<get<index>(tuple);
				print3<indices...>(os, format+1, tuple);
				return;
			}else
				os<<*format;
		}
	}else if(!count){
		for(;*format != '\0'; format++){
			if(*format == '\\'){
				if(!*(format+1))
					os<<*format;
				else
					if(*(format+1) == '\\')
						os<<format;
					else
						os<<*(++format);
			}
			else
				os<<format;
		return;
		}
	}
	else
		throw WrongNumberOfArgs();
}
template<std::size_t... indices, typename T>
void print2(std::ostream &os, const char *format, const T &tuple, const std::index_sequence<indices...> &){
//	os<<"printting: "<<get<0>(tuple);
	print3<indices...>(os,format, tuple);
	//os<<typeid(indices...).name()<<endl;
}
template<typename T>
void print(std::ostream &os, const char * format, const T &tuple){
	print2(os, format, tuple, std::make_index_sequence<std::tuple_size<T>::value>());
}

template<typename T1, typename... Targs>
const helper<T1, Targs... > *Interpolate(const char *frm, const T1 &value, const Targs &... Fargs){
	std::tuple<T1,const Targs ...> F = std::make_tuple(value, Fargs...);
	helper<T1, Targs ...> *hp = new helper<T1, Targs ...>(frm, F);
//	return hp;
	return hp;
}
//Just string
template<typename T>
const helper<int, int>* Interpolate(T frm){
	helper<int, int> *hp = new helper<int, int>(frm);
	return hp;
}
}//END of cs540
