/*
This is the programming part of your exam. When finished, name your file as hLastNameFirstNamei.cpp.
Upload that cpp code to blackboard by the deadline.
Design, implement and demonstrate your own implementation of a String class. Call it String5103.
Support the usual features of a traditional String class from STL: different constructors (e.g., init a
String5103 object from C-String), copy constructor, destructor, overloaded operators including =, ==,
<, >, +, <<, >>, [ ].
*/
#include <iostream>

using namespace std;

class String5103
{
    private:
        char* str;
        unsigned int len;
    public:
        // default constructor
        String5103(); 
        String5103(const char* s);
        // Copy constructor
        String5103(const String5103&); 
        // destructor
        ~String5103();
        // overloaded operations
        String5103& operator=(const String5103&);
        bool operator==(const String5103&) const;
        bool operator<(const String5103&) const;
        bool operator>(const String5103&) const;
        String5103 operator+(String5103&);
        friend ostream& operator<<(ostream&, const String5103&);
        friend istream& operator>>(istream&, String5103&);
        const char& operator[] (unsigned int) const;
        // operations
        unsigned int size() const;
};

String5103::String5103()
{
	str = new char[1];
	str[0] = '\0';
    len = 0;
}

String5103::String5103(const char* s)
{
	if(s) 
    {
        int cnt = 0;
        while (s[cnt] != '\0') 
        	cnt++;
        len = cnt;
        str = new char[cnt + 1];
        for (int i=0; i<cnt; i++)
            str[i] = s[i];
        str[cnt] = '\0';
    } 
    else 
    {
        str = new char[1];
		str[0] = '\0';
    	len = 0;
    }
}

String5103::String5103(const String5103 &s)
{
    str = new char[s.size() + 1];
    for (int i=0; i < s.size(); i++)
        str[i] = s[i];
    str[s.size()] = '\0';
    len = s.size();
}

String5103::~String5103()
{
    delete[] str;
}

String5103& String5103::operator=(const String5103 &s)
{
    //this = s?
	if (this == &s)
		return *this;
	//else this = s
	delete str;
    str = new char[s.size()];
    for (int i=0; i<s.size(); i++)
        str[i] = s[i];
    len = s.size();
    return *this;
}

bool String5103::operator==(const String5103 &s) const
{
	if (s.size() != len)
		return false;
	for (int i=0; i<len; i++)
	{
		if (str[i] != s[i])
			return false;
	}
    return true;
}

bool String5103::operator<(const String5103 &s) const
{
	for (int i=0; i<len; i++)
	{
		if (s.str[i] == '\0' )
			return false;
		else if (str[i] < s.str[i])
			return true;
		else if (str[i] > s.str[i])
			return false;
	}
	if (s.size() == len)
		return false;
	else
		return true;
}

bool String5103::operator>(const String5103 &s) const
{
	for (int i=0; i<len; i++)
	{
		if (s.str[i] == '\0' )
			return true;
		else if (str[i] > s.str[i])
			return true;
		else if (str[i] < s.str[i])
			return false;
	}
	return false;
}

String5103 String5103::operator+(String5103 &s)
{
    char* new_str = new char[len + s.size()];

    for (int i=0; i<len; i++)
    {
        new_str[i] = str[i];
    }
    for (unsigned i=0; i<s.size(); i++)
        new_str[len+i] = s[i];
    new_str[len + s.size()] = '\0';
    String5103 temp(new_str);

    return temp;
}

ostream& operator<<(ostream &os, const String5103 &s)
{
    if (s.size() > 0) 
    {
        for (int i=0; i < s.size(); i++)
            os << s[i];
    } 
    else 
    	os << "";
	return os;
}

istream& operator>>(istream &is, String5103 &s)
{
	char* temp = new char[1000];
	cout << "Please enter a string: ";
    is >> temp;
    s = String5103(temp);
    delete[] temp;
    
    return is;
}

const char& String5103::operator[] (unsigned int index) const
{
    return str[index];
}

unsigned int String5103::size() const
{
    return len;
}

int main()
{
	
    // test default constructor
    String5103 def;
    cout << "Tesing default constructor" << endl
    	 << "Input: String5103 def" << endl
         << "Output: def = " << def << endl << endl;

    // test parameterized constructor
    String5103 param1("parameter");
    String5103 param2("p");
    cout << "Tesing parameterized constructor" << endl
    	 << "Input: String5103 param1(\"parameter\")" << endl
         << "Output: param1 = " << param1 << endl
         << "Input: String5103 param2(\"p\")" << endl
         << "Output: param2 = " << param2 << endl << endl;

    // test copy contructor
    String5103 copy1("copy contructor");
    String5103 copy2(copy1);
    cout << "Tesing copy constructor" << endl
         << "Input: String5103 copy1(\"copy contructor\")" << endl
         << "Input: String5103 copy2(\"copy1\")" << endl
         << "Output: copy2 = " << copy2 << endl << endl;
    
    // test =
    String5103 equal1("equal 1");
    String5103 equal2("equal 2");
    equal1 = equal2;
    cout << "Testing =" << endl
    	 << "Input: String5103 equal1(\"equal 1\")" << endl
    	 << "Input: String5103 equal2(\"equal 2\")" << endl
    	 << "Input: equal1 = equal2" << endl
         << "Output: equal1 = " << equal1 << endl << endl; 

    // test ==
    String5103 ee("test");
    bool ee_currect = ee == "test";
    bool ee_wrong = ee == "dsfg";
    cout << "Testing ==" << endl
         << "Input: test == test" << endl
         << "Output: " << ee_currect << endl
         << "Input: test == dsfg" <<endl
         << "Output: " << ee_wrong << endl << endl;
    
    // test <
    String5103 less("bcd");
    bool less_currect = less < "bcde";
    bool less_wrong = less < "acd";
    cout << "Testing <" << endl
         << "Input: bcd < bcde" << endl 
         << "Output: " << less_currect << endl
         << "Input: bcd < acd" << endl
         << "Output: " << less_wrong << endl << endl;

    // test >
    String5103 greater("2");
    bool greater_currect = greater > "1";
    bool greater_wrong = greater > "3";
    cout << "Testing >" << endl
         << "Input: 2 > 1" << endl
         << "Output: " << greater_currect << endl
         << "Input 2 > 3:" << endl
         << "Output: " << greater_wrong << endl;
    cout << endl;

    // test +
    String5103 add1("abcasd");
    String5103 add2("efgs");
    String5103 res;
    res = add1 + add2;
    cout << "Testing +" << endl
    	 << "Input: abcasd + efgs" << endl
    	 << "Output: " << res << endl << endl;

    // test <<
    String5103 out("testing ostream");
    cout << "Testing <<" << endl
    	 << "Input: String5103 out(\"testing ostream\")" << endl
    	 << "Output: cout << out = " << out << endl << endl;

    // test >>
    String5103 in;
    cin >> in;
    cout << "Testing >>" << endl
    	 << "Output: " << in << endl << endl;
	
    // test []
    String5103 braket("012345");
    cout << "Testing []" << endl
    	 << "Input: 012345" << endl
         << "Output: s[3] = " << braket[3] << endl;
    cout << endl;
    
    return 0;
}
