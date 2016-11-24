#include <iostream>
#include <typeinfo>
#include <tuple>
#include <sstream>
#include <assert.h>
using namespace std;

template<typename T>
void print(std::ostream &os, const char *, const T& tuple);

template<typename T1, typename... Targs>
class helper{
	public:
	int x;
	//template members
	const char *format;
	T1 value;
	std::tuple<T1, Targs...> Fargs;

	//constructor
	helper(const char *form, T1 value, std::tuple<T1, Targs ...> &Fargs):x(100){
		this->format = form;
		this->value = value;
		this->Fargs = Fargs;
	}
	friend std::ostream& operator<<(std::ostream &os, const helper *hp){
		/*os<<"2: "<< hp->format<<" "<< hp->value<<endl;
		os<<"printing tupel index 0"<<endl;
		os<<get<0>(hp->Fargs)<<" "<<sizeof...(Targs)<<endl;
		return os;*/
		print(os, hp->format, hp->Fargs);
		//Print when you encounter %
/*		const char *format = hp->format;
		bool first=true;
		int k=0;
		for(;*format != '\0'; format++){
			if(*format == '%'){
				os<<get<0>(hp->Fargs);
			}else
				os<<*format;
		}*/
	}//End of Friend
};
template<typename T>
void print3(std::ostream &os, const char *format, const T &tuple){

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
	}
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
const helper<T1, Targs... > *Int(const char *frm, T1 value, Targs... Fargs){
	cout<<"1"<<endl;
	std::tuple<T1,Targs ...> F = std::make_tuple(value, Fargs...);
	helper<T1, Targs ...> *hp = new helper<T1, Targs ...>(frm, value, F);
//	return hp;
	return hp;
}
int main(){
	stringstream ss;
	cout<<Int("% % % %", 10, 20, "Hello", 7.989);
	cout<<endl;
//	string s = ss.str();
//	assert(ss.str() == "2: 100\n");
}
