#ifndef _HINTS_HEADER
#define _HINTS_HEADER

#include <fstream>
#include <iostream>

/*

	"huurh";
	"aguhwwgggghhh";
	"huuguughghg";
	"uughghhhgh";
	"aarrragghuuhwuuh";

*/

//function gives the user an idea of how to 
//write the arithmetic functions in wookiespeak

void G_GiveHints(const std::string& p_dir) noexcept {
	std::ofstream l_oStream;
	l_oStream.open(p_dir);
	l_oStream << "# WELCOME TO THE STAR WARS ESOTERIC PROGRAMMING LANGUAGE\n";
	l_oStream << "# USING THIS LANGUAGE YOU CAN PRINT,PERFORM ARITHMETIC INSTRUCTIONS AND FILL\n";
	l_oStream << "# AND FILL THE PLANET (REGISTERS) WITH INTEGERS! THE PLANETS\n";
	l_oStream << "# THE PLANETS AT YOUR DISPOSITION ARE : HOTH,ENDOR,TATOOINE AND NABOO\n";
	l_oStream << "# ALL ARITHMETIC INSTRUCTIONS MUST BE IN WOOKIESPEAK OTHERWISE CODE WON'T COMPILE!!!\n";
	l_oStream << "# ADD : huurh\n";
	l_oStream << "# SUB : aguhwwgggghhh\n";
	l_oStream << "# MUL : huuguughghg\n";
	l_oStream << "# DIV : uughghhhgh\n";
	l_oStream << "# MOD : aarrragghuuhwuuh\n";
	l_oStream << "# SW_LANG MUST BE INFORMED THAT THIS HAPPENED A LONG TIME AGO IN A GALAXY FAR FAR AWAY\n";
	l_oStream << "# OTHERWISE CODE WON'T COMPILE!!!\n";
	l_oStream << "# PRINTING TO THE SCREEN MUST BE WRITTEN IN THE WAY YODAY WOULD SPEAK\n";
	l_oStream << "# LIKE THIS : show earthman \"foobar\" you must\n";
	l_oStream << "# CONSEQUENTLY FILLING THE PLANETS WITH VALUES MUST ALSO BE DONE IN YODA GRAMMAR\n";
	l_oStream << "# LIKE THIS : fill hoth with 42 you must\n";
	l_oStream << "# FINALLY ALL PROGRAMS MUST END WITH : may the force be with you\n";
	l_oStream << "# GOOD LUCK! MAY THE FORCE BE WITH YOU\n";

	l_oStream.close();
}

#endif