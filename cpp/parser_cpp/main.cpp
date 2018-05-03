#include <iostream>
#include <iterator>
#include <vector>

enum token_type
: char
{
  NUMBER,
  PLUS = '+',  SUB = '-', MUL = '*', DIV = '/',
  OP = '(', CL = ')',

  INV
};

struct Token
{
  token_type type;
  std::string str;
};

struct Node
{
  int nodetype;
  Node* r;
  Node* l;
};

// number
struct NNode
  : Node
{
  int value;
};

class AST
{
public:
  AST(const std::string& exp)
    : m_Tokens(Tokenize(exp))

private:
  std::vector<Token> Tokenize(const std::string& exp)
  {
    
  }
private:
  std::vector<Token> m_Tokens;
  Node* m_First;
  int m_Result;
};

int main(void)
{

}
