#ifndef Student_h
#define Student_h
#include<iostream>
#include<string>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <stdlib.h>
using namespace std;


class Student {
	public:
		Student();	
		int num_ssn() const{return int_ssn;}
		string string_ssn() const{return ssn;}
	private:
		int int_ssn;
		string ssn;
		int conv_to_int();
}
;
int Student::conv_to_int() {
/*this function is to convert the string ssn to int for easy comparision 
 * OUTPUT IS 4 NUMBERS SINCE THE POSSIBILITY OF REPLICATING THE SAME 4 NUMBERS ARE 9^4
 * ABCD
 * */
	int social,buffer,decimal;
	social=0;
	decimal=1;
	char c;
	for(int a=4;a>=0;--a){
       		c=ssn[a];
        	if(c=='-') a--;         
        	c=ssn[a];
        	buffer=c-'0';
        	buffer*=decimal;
        	social=social+buffer;
        	decimal*=10;
}
	int_ssn = social;
}


Student::Student(){
	
	//constructer will auto construct ssn first
	int rndnum;
	for(int a=0;a<11;++a){
		rndnum= rand() % 10;	
		switch(a){
			case 3: ssn += "-";
				break;
			case 6: ssn += "-";
				break;
			default: ssn += to_string(rndnum);
				break;
		}
	}
	conv_to_int();
}	
#endif
