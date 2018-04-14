#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CodeLine {
public:
    CodeLine(){};
    ~CodeLine(){};
    
    virtual void TranslateCPP()=0;
    virtual bool isMultiline() const { return false; } ;
    virtual string multilineEndString() const { return ""; }
    
    virtual void setSubBlock(vector<CodeLine*> sub){};
};

class CodeLinePrint : public CodeLine {
public:
    CodeLinePrint(){};
    ~CodeLinePrint(void) {};
    void TranslateCPP(){
    }
};

class CodeLineIf : public CodeLine {
private:
    vector<CodeLine*> _subIf;
public:
    CodeLineIf() {};
    ~CodeLineIf() {};
    
     void TranslateCPP() {};
     bool isMultiline() const { return true; };
     string multilineEndString() const { return "endif"; };
     void setSubBlock(vector<CodeLine*> sub){
        _subIf = sub;
    };
};

class Program {
private:
    vector<string> _lines;
    size_t _current;
public:
    Program(vector<string> test):_lines(test) {};
    ~Program() {};
    
    string currentLine() const{ return _lines[_current]; };
    bool nextLine() { _current++; return _current < _lines.size(); };
    
    string currentFirstWord() const {
        string l = currentLine();
        string rv;
        for(size_t i=0;i<l.length();i++){
            if( l[i] == ' '){
                break;
            }
            rv += l[i];
        }
        return rv;
    }
    vector<CodeLine*> parse(string endString=""){
        vector<CodeLine*> rv;
        
        while(nextLine()){
            string firstWord = currentFirstWord();
            if( endString.length() != 0 && endString == firstWord){
                break;
            }
            CodeLine * cl = NULL;
            if( firstWord == "if"){
                cl = new CodeLineIf();
            }else if( firstWord == "print"){
                cl = new CodeLinePrint();
            }
            if( cl->isMultiline() ){
                vector<CodeLine*> args = parse( cl->multilineEndString() );
                cl->setSubBlock(args);
            }
            if( cl ){
                rv.push_back(cl);
            }else{
                cout << "PARSE ERROR" << endl;
            }
        }
        return rv;
    }
};

void fizzbuzz(){
    
    
    for(int i=0;i<30;i++){
        // multiple 3 : fizz, 5 buzz, fizzbuzz other number
        size_t mult3 = (i % 3) == 0;
        size_t mult5 = (i % 5) == 0;
        
        string val[5];
        for(size_t i=0;i<5;i++){
            val[i] = "";
        }
        val[i%3] += "fizz";
        val[i%5] += "buzz";
        
        char num[12];
        snprintf(num, 12, "%d", i);
        // if 3 : 0, if 5 : 0, if 3&5: 0 else 1
        
        val[1] = string(num);
        
        std::cout << i << ": " << val[!(mult3||mult5)] << endl;
    }

}

void parserExample(){
    vector<string> test;
    test.push_back("print a");
    test.push_back("if a");
    test.push_back("print a");
    test.push_back("endif");
    Program pgm(test);
    vector<CodeLine*> parsed = pgm.parse("");

}
void endianness(){
    int a = 1;
    char * c = (char*)&a;
    
    cout << "val: " << (int)*(c) << endl;
    
    union {
        uint32_t word;
        uint8_t bytes[4];
    } test_struct;
    test_struct.word = 0x1;
    if (test_struct.bytes[0] != 0)
        cout << "little-endian" << endl;
    else
        cout << "big-endian" << endl;
}
void limits(){
    cout << hex;
    cout << "    Number of bits in a char object (byte)                     = " << CHAR_BIT << endl;
    cout << "    Minimum value for an object of type signed char            = " << SCHAR_MIN << endl;
    cout << "    Maximum value for an object of type signed char            = " << SCHAR_MAX << endl;
    cout << "    Maximum value for an object of type unsigned char          = " << UCHAR_MAX << endl;
    cout << "    Minimum value for an object of type char                   = " << CHAR_MIN << endl;
    cout << "    Maximum value for an object of type char                   = " << CHAR_MAX << endl;
    cout << "    Minimum value for an object of type short int              = " << SHRT_MIN << endl;
    cout << "    Maximum value for an object of type short int              = " << SHRT_MAX << endl;
    cout << "    Maximum value for an object of type unsigned short int     = " << USHRT_MAX << endl;
    cout << "    Minimum value for an object of type int                    = " << INT_MIN << endl;
    cout << "    Maximum value for an object of type int                    = " << INT_MAX << endl;
    cout << "    Maximum value for an object of type unsigned int           = " << UINT_MAX << endl;
    cout << "    Minimum value for an object of type long int               = " << LONG_MIN << endl;
    cout << "    Maximum value for an object of type long int               = " << LONG_MAX << endl;
    cout << "    Maximum value for an object of type unsigned long int      = " << ULONG_MAX << endl;
    cout << "    Minimum value for an object of type long long int          = " << LLONG_MIN << endl;
    cout << "    Maximum value for an object of type long long int          = " << LLONG_MAX << endl;
    cout << "    Maximum value for an object of type unsigned long long int = " << ULLONG_MAX << endl;

}

void pointerLoop(){
    void * a = 0x0;
    void * b = &a;
    void * c = &b;
    void * d = &c;
    a=&d;
    
    cout << hex;
    cout << "a  = " << (size_t)a << ", *a=d:" << *(size_t*)a << endl;
    cout << "b  = " << (size_t)b << ", *b=a:" << *(size_t*)b << endl;
    cout << "c  = " << (size_t)c << ", *c=b:" << *(size_t*)c << endl;
    cout << "d  = " << (size_t)d << ", *d=c:" << *(size_t*)d << endl;

}
int main(){
    
    pointerLoop();
    return 0;

}
