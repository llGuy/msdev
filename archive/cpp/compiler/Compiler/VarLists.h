#pragma once
#include "LinkedList.h"
#include "Variable.h"
namespace VList {
	llst::LinkedList<int, 8> listInt;
	llst::LinkedList<char, 8> listChar;
	llst::LinkedList<bool, 8> listBool;
	llst::LinkedList<std::string, 8> listStr;
}