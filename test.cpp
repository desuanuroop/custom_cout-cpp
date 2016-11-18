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
// Test if it returns ostream.
    {
        std::stringstream s;
        cout << Interpolate("i=% % %", 1234, 10, 10) <<std::endl;
    }
// Test too many args.
    try {
        std::stringstream s;
        s << Interpolate("i=%, j=%", 1, 2, 3);
        assert(false);
    } catch (cs540::WrongNumberOfArgs) {
        std::cout << "Caught exception due to too many args." << std::endl;
   }
// Test too few.
    try {
        std::stringstream s;
        s << Interpolate("i=%, j=%, k=%", 1, 2);
        assert(false);
    } catch (cs540::WrongNumberOfArgs) {
        std::cout << "Caught exception due to few args." << std::endl;
   }
}
