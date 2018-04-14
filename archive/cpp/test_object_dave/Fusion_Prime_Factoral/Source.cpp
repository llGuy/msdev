#include "MyClass.h"

using namespace std;

int main()
{
	MyClass::enable_debug = true;
	cout << "start of program - debug: " << (MyClass::enable_debug ? "true" : "false" ) << endl;

	MyClass s;
	MyClass *y = new MyClass(5);
	MyClass *z;

	s.Prime(751);
	y->Factoral(12);

	z = y;
	y->DebugInfo("this is y");
	z->DebugInfo("this is z");

	z->Prime(456);

	delete y;
	
	cout << "end of program" << endl;
}