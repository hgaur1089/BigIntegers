#include<bits/stdc++.h>
using namespace std;
class Large {
    string digits;

    public:

    //constructors
    Large(string &);
    Large(unsigned long long num = 0);
    Large(const char*);
    Large(Large &);

    //Helper Functions
    friend void divide_by_2(Large &);
    friend bool Null(const Large &);
    friend int Length(const Large &);
    int operator[](const int)const;

    //--------OPERATOR OVERLOADING--------------//

    //Direct Assignment
    Large &operator=(const Large &);

    //Comparision operators
    friend bool operator==(const Large&, const Large&);
    friend bool operator!=(const Large&, const Large&);
    
    friend bool operator<(const Large&, const Large&);
    friend bool operator<=(const Large&, const Large&);
    friend bool operator>(const Large&, const Large&);
    friend bool operator>=(const Large&, const Large&);

    //Post/Pre Increment
    Large &operator++();
    Large operator++(int temp);
    Large &operator--();
    Large operator--(int temp);

    //Addition and Substraction
    friend Large &operator+=(Large&, const Large&);
    friend Large operator+(const Large&, const Large&);
    friend Large &operator-=(Large&, const Large&);
    friend Large operator-(const Large&, const Large&);

    //Multiplication and Division
    friend Large &operator*=(Large&, const Large&);
    friend Large operator*(const Large&, const Large&);
    friend Large &operator/=(Large&, const Large&);
    friend Large operator/(const Large&, const Large&);

    //Modulo
    friend Large operator%(const Large&, const Large&);
    friend Large &operator%=(Large&, const Large&);

    //Power Function
    friend Large &operator^=(Large&, const Large&);
    friend Large operator^(const Large&, const Large&);

    //Square Root Function
    friend Large sqrt(Large&);

    //Read and Write
    friend ostream &operator<<(ostream&, const Large&);
    friend istream &operator>>(istream&, Large&); 


};

Large::Large(string &s){
    digits = "";
    int n = s.size();

    for(int i=n-1; i>=0; i--){
        if(!isdigit(s[i]))
            throw("ERROR");
            digits.push_back(s[i] - '0');
    }
}

Large::Large(unsigned long long num){
    do{
        digits.push_back(num%10);
        num = num/10;
    } while(num);
}

Large::Large(const char* s){
    digits = "";

    for(int i = strlen(s) - 1; i>=0; i--){
        digits.push_back(s[i] - '0');
    }
}

Large::Large(Large& num){
    digits = num.digits;
}

bool Null(const Large& num){
    if(num.digits.size() == 1 && num.digits[0] == 0){
        return true;
    }
    return false;
}

int Length(const Large& num){
    return num.digits.size();
}

int Large::operator[](const int index)const {
    if(digits.size() <= index || index < 0){
        throw("ERROR");
    }
    return digits[index];
}

bool operator==(const Large& num1, const Large& num2){
    return num1.digits == num2.digits;
}

bool operator!=(const Large& num1, const Large& num2){
    return !(num1 == num2);
}

bool operator<(const Large& a, const Large& b){
    int n = Length(a);
    int m = Length(b);

    if(n != m){
        return n < m;
    }

    while (n--){
        if(a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    }
    return false;
}

bool operator>(const Large& a, const Large& b){
    return b < a;
}

bool operator<=(const Large& a, const Large& b){
    return !(a > b);
}

bool operator>=(const Large& a, const Large& b){
    return !(a < b);
}

Large &Large::operator=(const Large & a){
    int n = Length(a);
    digits = "";
    for(int i = 1; i < n; i++){    
        digits += a.digits[i];
    }

    return *this;
}

Large &Large::operator++(){
    int i;
    int n = digits.size();
    for(i = 0; i<n && digits[i] == 9; i++){
        digits[i] = 0;
    }

    if(i==n){
        digits.push_back(1);
    } else {
        digits[i]++;
    }

    return *this;
}

Large Large::operator++(int temp){
    Large prev;
    prev = (*this);
    ++(*this);
    return prev;
}

Large &Large::operator--(){
    if(digits[0] == 0 && digits.size() == 1){
        throw("UNDERFLOW");
    }

    int i;
    int n = digits.size();
    for(i=0; digits[i] == 0 && i<n; i++){
        digits[i] = 9;
    }
    digits[i]--;

    if(n>1 && digits[n-1] == 0){
        digits.pop_back();
    }

    return *this;
}

Large Large::operator--(int temp){
    Large prev;
    prev = *this;
    --(*this);

    return prev;
}

Large &operator+=(Large& a, const Large& b){
    int t = 0;
    int s;
    int i;

    int n = Length(a);
    int m = Length(b);

    if(m > n)
        a.digits.append(m - n, 0);

     n = Length(a);

     for(i=0; i<n; i++){
         if(i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else    
            s = a.digits[i] + t;
        t = s/10;
        a.digits[i] = (s % 10);
     }
     if(t)
        a.digits.push_back(t);

    return a;
}

Large operator+(const Large& a, const Large& b){
    Large temp;
    temp = a;
    temp += b;
    return temp;
}

Large &operator-=(Large& a, const Large& b){
    if(a < b)
        throw("UNDERFLOW");
    
    int n = Length(a);
    int m = Length(b);
    int i;
    int t = 0;
    int s;

    for(i=0; i<n; i++){
        if(i<m)
            s = a.digits[i] - b.digits[i] + t;
        else   
            s = a.digits[i] + t;
        
        if(s < 0){
            s += 10;
            t = -1;
        } else {
            t = 0;
        }
        a.digits[i] = s;
    }

    while(n > 1 && a.digits[n - 1] == 0){
        a.digits.pop_back();
        n--;
    }

    return a;
}

Large operator-(const Large& a, const Large& b){
    Large temp;
    temp = a;
    temp -= b;
    return temp;
}

Large &operator*=(Large& a, const Large& b){
    if(Null(a) || Null(b)){
        a = Large();
        return a;
    }

    int n = Length(a);
    int m = Length(b);

    vector<int> v(n+m, 0);

    // multiply every digit of one number with the other complete number and at last add all the numbers
    //for eg: 66*11 the array will contain v[0, 1, 2, 3] = [6, 12, 6, 0]
    //    66
    //  x 11
    //---------
    //    66
    //  +66x
    //---------
    // 6 12 6
    //now we have to move the carry and add it from left to right since the numbers are sstored in reverse order  
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            v[i+j] +=  (a.digits[i]) * (b.digits[j]);
        }
    }

    n += m;
    a.digits.resize(v.size());

    //here we calculate the multiflied number from the vector by moving the carry
    for(int s, i=0, t=0; i<n; i++){
        s = t + v[i];
        v[i] = s%10;
        t = s/10;
        a.digits[i] = v[i];
    }

    //to remove zeros from front of number if there are any
    for(int i = n-1; i >= 1 && !v[i]; i--){
        a.digits.pop_back();
    }

    return a;
}

Large operator*(const Large& a, const Large& b){
    Large temp;
    temp = a;
    temp *= b;

    return temp;
}

Large &operator/=(Large& a, const Large& b){
    if(Null(b))
        throw("Arithmatic Error: Division by 0!!!");
    if(a < b){
        a = Large();
        return a;
    }

    if(a == b){
        a = Large(1);
        return a;
    }
    int i;
    int lgcat, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    Large t;

    for(i = n-1; t*10 + a.digits[i] < b; i--){
        t *= 10;
        t += a.digits[i];
    }

    for(; i >= 0; i--){
        t = t*10 + a.digits[i];
        for(cc=9; cc*b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());
    for(i =0 ;i<lgcat; i++)
        a.digits[i] = cat[lgcat - i - 1];
        a.digits.resize(lgcat);

    return a;
}

Large operator/(const Large& a, const Large& b){
    Large temp;
    temp = a;
    temp /= b;
    return temp;
}

Large &operator%=(Large& a, const Large& b){
    if(Null(b))
        throw("Arithmetic Error: Division By 0");
	if(a < b){
        a = Large();
        return a;
    }
    if(a == b){
        a = Large(1);
        return a;
    }

    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    Large t;
    for(i = n-1; t*10 + a.digits[i] < b; i--){
        t *= 10;
        t += a.digits[i];
    }

    for(; i>=0; i--){
        t = t*10 + a.digits[i];
        for(cc = 9; cc*b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }

    a = t;
    return a;
}

Large operator%(const Large &a,Large &b){
	Large temp;
	temp = a;
	temp %= b;
	return temp;
}

void divide_by_2(Large& a){
    int add = 0;
    for(int i = Length(a) - 1; i>=0; i--){
        int digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = digit;
    }

    //if there are any 0s at start then remove them
    while(a.digits.size() > 1 && !a.digits.back()){
        a.digits.pop_back();
    }
}

Large &operator^=(Large& a, const Large& b){
    Large Exponent, Base(a);
    Exponent = b;
    a = 1;

    while(!Null(Exponent)){
        if(Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }

    return a;
}

Large operator^(Large & a,Large & b){
	Large temp(a);
	temp ^= b;
	return temp;
}

Large srqt(Large& a){
    Large left(1);
    Large right(a);
    Large v(1), mid, prod;
    divide_by_2(right);

    while (left <= right)
    {
        mid += left;
        mid += right;
        divide_by_2(mid);

        prod = (mid*mid);

        if(prod <= a){
            v = mid;
            ++mid;
            left = mid;
        } else {
            --mid;
            right = mid;
        }

        mid = Large();
    }
    
    return v;
}

istream &operator>>(istream& in, Large& a){
    string s;
    in>>s;
    int n = s.size();
    for(int i = n-1; i >= 0; i--){
        if(!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digits[n - i - 1] = s[i];
    }

    return in;
}

ostream &operator<<(ostream& out, const Large& a){
    for(int i = a.digits.size() - 1; i >= 0; i--){
        cout<<(short)a.digits[i];
    }

    return cout;
}
