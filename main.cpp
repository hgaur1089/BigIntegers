#include<iostream>
#include "Large.h"

using namespace std;

int main(){
    Large a("10");
    cout<<"The number of digits in \"a\" = "<<Length(a)<<endl;

    Large b(2);
    cout<<"The number of digits in \"b\" = "<<Length(b)<<endl;

    if (a == b) {
		cout << "a and b are equal!\n";
	}
	else
		cout << "Not equal!\n";

    Large c("1090334567"), d("1234567898765432");

    cout<<"a "<<a<<endl;
    cout<<"b "<<b<<endl;
    cout<<"c "<<c<<endl;
    cout<<"d "<<d<<endl;

    cout<<"Sum of c("<<c<<") and d("<<d<<") = "<<(c+d)<<endl;

}
