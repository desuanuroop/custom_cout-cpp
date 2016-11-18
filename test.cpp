#include <iostream>
#include "Interpolate.hpp"

template<typename T1>
void func(int v, T1 name){
	cout<<is_same<T1, const char *>::value<<endl;
}
int main(){
//	helper hp = Interpolate("i=%, d=%", 12, 3.5656);
//	cout<<Interpolate("Name=%, age=%, gpa=%", true, 12,12)<<endl;
//	cout<<Interpolate("i=%, d=%", 12, 3.5656)<<endl;
	cout<<Interpolate("N=%", 0.1)<<endl;
	cout<<(typeid(0.1) == typeid(double))<<endl;
	cout<<0.1<<endl;
}
