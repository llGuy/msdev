#pragma once
#include <iostream>
#include "Variable.h"
namespace llst {
	template<class Type,unsigned int size>
	class LinkedList {
	private:
		//size of the linked list (how many items there are)
		unsigned int _size;
		//makes it so that all the variables / nodes
		//know where the next one is
		void LinkNodes(int endSize,int startSize,Variable<Type>* inputNode) {
			if(startSize == endSize) {
				inputNode->isEndOfList = true;
				return;
			}
			else if(startSize == 0) {
				//if the index is 0, the program is at the head (the beginning) 
				_head->_pointerNextVar = new Variable<Type>;
				startSize++;
				LinkNodes(endSize,startSize,_head->_pointerNextVar);
			}
			else if(startSize > 0 && startSize < endSize) {
				inputNode->_pointerNextVar = new Variable<Type>;
				startSize++;
				LinkNodes(endSize,startSize,inputNode->_pointerNextVar);
			}
			else return;
		}
	public:
		//number of variables that are initialized in the list
		unsigned int _numOfInitializedVar = 0;
		Variable<Type>* _head = new Variable<Type>;
		explicit LinkedList(void) 
			: _size(0), _capacity(size){
			//calls the function to link the current nodes together
			InitializeList();
		}
		~LinkedList(void) {};
		//number of nodes the llist can store
		unsigned int _capacity;
		void InitializeList(void) {LinkNodes(_capacity,_size,_head);}
		//returns the node at a certain index
		Variable<Type>* FindNode(unsigned index,unsigned start,Variable<Type>* inputNode) {
			if(start == index) return inputNode;
			else {
				start++;
				return FindNode(index,start,inputNode->_pointerNextVar);
			}
		}
		Variable<Type>* FindNodeAndGetPosition(unsigned index,unsigned &start,Variable<Type>* inputNode) {
			if(start == index) return inputNode;
			else {
				start++;
				return FindNodeAndGetPosition(index,start,inputNode->_pointerNextVar);
			}
		}
		//returns a node that has a certain name
		Variable<Type>* FindNodeStr(const std::string &inputName,Variable<Type>* inputNode) {
			if(inputNode->_name == inputName) 
				return inputNode;
			else if(inputNode->_name == "NULL") 
				return inputNode;
			else 
				return FindNodeStr(inputName,inputNode->_pointerNextVar);
		}
		//adds a node to the list
		void Append(void) {
			FindNode(_capacity - 1,0,_head)->_pointerNextVar = new Variable<Type>;
			_capacity++;
		}
		//initializes a variable in the list
		void AppendInitializedVariable(const Type &inputData,const std::string &name) {
			//debug purposes
			if(name == "r") std::cout << "appended variable r\n";

			if(_numOfInitializedVar < _capacity) {
				FindNode(_numOfInitializedVar,0,_head)->_value = inputData;
				FindNode(_numOfInitializedVar,0,_head)->_name = name;
				_numOfInitializedVar++;
			}
			else {
				Append();
				FindNode(_numOfInitializedVar,0,_head)->_value = inputData;
				FindNode(_numOfInitializedVar,0,_head)->_name = name;
				_numOfInitializedVar++;
			}
		}
		signed int GetPositionOfVar(const std::string &name,Variable<Type>* var, signed int position) {
			if(var->_name == name) return position;
			else if(var->_name == "NULL") return -1;
			else {
				position++;
				return GetPositionOfVar(name,var->_pointerNextVar,position);
			}
		}
		void DeleteNode(const std::string &name,Variable<Type>* ptrToVar) {
			signed int _positionSInt = GetPositionOfVar(name,_head,0);
			if(_positionSInt < 0) return;
			size_t _positionOfVar = (size_t)_positionSInt;
			size_t _positionPre = 0;
			size_t _positionPost = _positionOfVar + 1;
			if(_positionOfVar != 0) 
				_positionPre = _positionOfVar - 1;

			if(_positionOfVar + 1 == _capacity) FindNode(_positionPre,0,_head)->_pointerNextVar = new Variable<Type>;
			else if(_positionOfVar == 0) {
				Variable<Type>* _temp = _head->_pointerNextVar;
				_head = _temp;
			}
			else FindNode(_positionPre,0,_head)->_pointerNextVar = FindNode(_positionPost,0,_head);
			_numOfInitializedVar--;
			_capacity--;
		}
	};
}