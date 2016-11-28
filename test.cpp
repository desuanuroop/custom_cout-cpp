#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include "Interpolate1.hpp"

using namespace std;
using namespace cs540;

class A {
	public:

    friend int main(int argc, char **argv);
    friend std::ostream & operator<<(std::ostream &os, const A &a) {
        return os << a.i;
    }
    A(){}
    A(int i_) : i(i_) {}
    int i;
};

class B {
	public:
    friend int main(int argc, char **argv);
    friend std::ostream & operator<<(std::ostream &os, const B &a) {
        return os << a.str;
    }
    B(){}
    B(std::string s) : str(std::move(s)) {}
    std::string str;
};


template <typename... Ts>
void test(const char *func, int line_no, const std::string &cmp, const std::string &fmt, Ts &&...params) {
    std::stringstream s;
    s << cs540::Interpolate(fmt.c_str(), std::forward<Ts>(params)...);
    if (s.str() != cmp) {
        std::cerr << "Comparison failed at " << func << ":" << line_no << ":\n";
        std::cerr << "    Correct result: \"" << cmp << "\"\n";
        std::cerr << "    Actual result: \"" << s.str() << "\"\n";
    }
}
#define CS540_TEST(...) test(__FUNCTION__, __LINE__, __VA_ARGS__)


int main(int argc, char **argv){
//Sample Test cases
	{
		int i = 1234;
		double x = 3.14;
		std::string str("foo");
		std::cout << Interpolate(R"(i=%, x1=%, x2=%\%, str1=%, str2=%)", i, x, 1.001, str, "hello") << std::endl;
	}

//Handling of escapre characters
	{
		CS540_TEST("", "");
		CS540_TEST(R"(\)", R"(\)");
		CS540_TEST(R"(%)", R"(\%)");
		CS540_TEST(R"(\\)", R"(\\)");
		CS540_TEST(R"(foo)", R"(foo)");
		CS540_TEST("\n", "\n");
	}
// Test if it returns ostream.
    	{
        	std::stringstream s;
		s << Interpolate("i=%", 1234) << ", foo" << std::endl;
        	assert(s.str() == "i=1234, foo\n");
    	}

//handling of space after %
	{
		CS540_TEST("1234", "%", 1234);
		CS540_TEST(" 1234", " %", 1234);
		CS540_TEST("1234 ", "% ", 1234);
		CS540_TEST(" 1234 ", " % ", 1234);
	}
// Test objects
        {
                CS540_TEST("i=1, x=3.49887, s=foo, a=768, b=hello, c=x", "i=%, x=%, s=%, a=%, b=%, c=%", 1, 3.4988678671, "foo", A(768), B("hello"), 'x');
        }

// Test rvalue/lvalue.
	{
        	int i1 = 12376;
	        const int i2 = 778;
        	CS540_TEST("i=8798, j=12376, k=778", "i=%, j=%, k=%", 8798, i1, i2);
    	}
// Many args.
	{
    CS540_TEST(
        "56789 3.14 1234 Z hello 313 goodbye -31 1.99 0xffff7777 "
        "56789 3.14 1234 Z hello 313 goodbye -31 1.99 0xffff7777 "
        "56789 3.14 1234 Z hello 313 goodbye -31 1.99 0xffff7777 "
        "56789 3.14 1234 Z hello 313 goodbye -31 1.99 0xffff7777 "
        "56789 3.14 1234 Z hello 313 goodbye -31 1.99 0xffff7777",
        "% % % % % % % % % % "
        "% % % % % % % % % % "
        "% % % % % % % % % % "
        "% % % % % % % % % % "
        "% % % % % % % % % %",
        56789, 3.14, short(1234), 'Z', "hello", A(313), B("goodbye"), -31, 1.99F, (void *)0xffff7777,
        56789, 3.14, short(1234), 'Z', "hello", A(313), B("goodbye"), -31, 1.99F, (void *)0xffff7777,
        56789, 3.14, short(1234), 'Z', "hello", A(313), B("goodbye"), -31, 1.99F, (void *)0xffff7777,
        56789, 3.14, short(1234), 'Z', "hello", A(313), B("goodbye"), -31, 1.99F, (void *)0xffff7777,
        56789, 3.14, short(1234), 'Z', "hello", A(313), B("goodbye"), -31, 1.99F, (void *)0xffff7777);
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

	{
		stringstream ss;
		ss<<Interpolate("% %", 10,20);
		assert(ss.str() == "10 20");
		cout<<ss.str()<<endl;
	}
}
