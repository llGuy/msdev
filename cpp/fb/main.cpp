#include <iostream>
#include <array>

// function that will print the sequence of fizz buzz
// for any given limit
void FB(uint32_t total)
{
    // array of 3 containing "fizz" for the first element
    std::array<std::string, 3> fizz { "fizz" };
    // array of 5 containing "buzz" for the first element
    std::array<std::string, 5> buzz { "buzz" };

    for(uint32_t i = 0; i < total; ++i)
    {
	// if i is either a multiple of 3 or 5,
	// this line will fill the string out1 with some string
	// "fizz", "buzz" or "fizzbuzz"
	// if i is not divisible by either 3 or 5
	// out1 will contain nothing
	std::string out1 = fizz[i % 3] + buzz[i % 5];
	// array containing the number and the string in out1
	std::array<std::string, 2> outs { std::to_string(i), out1 };
	// the choice simulates the if statement
	// the string in out1 will either contain "fizz", "buzz", both or nothing
	// the choice variable will be set to 1 if out1 contains any thing
	// if out1 contains nothing (length 0), then choice will be 0 (false)
	uint32_t choice = out1.length() % 7 % 3;
	// print out the correct string depending on the choice
	std::cout << outs[choice] << " ; ";
    }
    std::cout << '\n';
}

int main(void)
{
    std::cout << "max number : ";
    uint32_t max;
    std::cin >> max;

    FB(max);
    
    return 0;
}
