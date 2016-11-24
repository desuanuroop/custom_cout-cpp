#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include "Interpolate.hpp"

using namespace std;
using namespace cs540;
template<typename T1>
void func(int v, T1 name){
	cout<<is_same<T1, const char *>::value<<endl;
}
int main(){
/*	helper hp = Interpolate("i=%, d=%", 12, 3.5656);
	cout<<Interpolate("Name=%, age=%, gpa=%", true, 12,12)<<endl;
	cout<<Interpolate("i=%, d=%", 12, 3.5656)<<endl;
	cout<<Interpolate("N=% %", 0.1, "Anuroop")<<endl;
	std::cout<<std::boolalpha;
	std::cout<< Interpolate("% %", true, false)<<endl;
*/
/*	{
		int i = 1234;
		double x = 3.14;
		std::string str("foo");
//		std::cout << Interpolate(R"(i=%, x1=%, x2=%\%, str1=%, str2=%)", i, x, 1.001, str, "hello") << std::endl;
	}
// Test if it returns ostream.
    {
        std::stringstream s;
        //cout<< Interpolate("i=% % %", 1234, 10, 10) <<std::endl;
	s << Interpolate("i=% % %", 1234, 10, 10);
	cout<<endl;
//	cout<<s.str().length()<<" and "<<string("i=1234 10 10\n").length() <<endl;
    }
// Test too many args.
    try {
        std::stringstream s;
        s << Interpolate("i=%, j=%", 1, 2, 3);
        assert(false);
    } catch (cs540::WrongNumberOfArgs) {
//        std::cout << "Caught exception due to too many args." << std::endl;
   }
// Test too few.
    try {
        std::stringstream s;
        s << Interpolate("i=%, j=%, k=%", 1, 2);
        assert(false);
    } catch (cs540::WrongNumberOfArgs) {
  //      std::cout << "Caught exception due to few args." << std::endl;
   }*/
	stringstream ss;
	ss<<Interpolate("% %", 10,20);
//	assert(ss.str() == "10 20");
	cout<<endl<<ss.str()<<endl;
}
