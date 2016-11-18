#include <iostream>
#include <stdarg.h>

void print(const char *, ...);
char* convert(unsigned int, int);
int main(){
	print("%c %d %d", 'a', 20, 30);
}

void print(const char *format, ...){
	const char *traverse;
	unsigned int i;
	char *s;
	va_list arg;
	va_start(arg, format);

	for(traverse=format; *traverse != '\0'; traverse++){

		while(*traverse != '%'){
			putchar(*traverse);
			traverse++;
		}
		traverse++;

		switch(*traverse){
			case 'c': i = va_arg(arg, int);
				putchar(i);
				break;

			case 'd': i = va_arg(arg, int);
				if(i<0){
					putchar('-');
					i = -i;
				}
				puts(convert(i, 10));
				break;
		}
	}
	va_end(arg);

}

char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}
