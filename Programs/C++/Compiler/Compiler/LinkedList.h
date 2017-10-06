#pragma once
#include <iostream>
#include "Variable.h"
namespace llst {
	template<class Type, unsigned int size>
	class LinkedList {
	private:
		unsigned int _size;
		void LinkNodes(int endSize, int startSize, Variable<Type> * inputNode) {
			if (startSize == endSize) {
				inputNode->isEndOfList = true;
				return;
			}
			else if (startSize == 0) {
				_head->_pointerNextVar = new Variable<Type>;
				startSize++;
				LinkNodes(endSize, startSize, _head->_pointerNextVar);
			}
			else if (startSize > 0 && startSize < endSize) {
				inputNode->_pointerNextVar = new Variable<Type>;
				startSize++;
				LinkNodes(endSize, startSize, inputNode->_pointerNextVar);
			}
			else return;
		}
	public:
		unsigned int _numOfInitializedVar = 0;
		Variable<Type> * _head = new Variable<Type>;
		LinkedList() {
			_size = 0;
			_capacity = size;
			InitializeList();
		}
		~LinkedList() {
		}
		unsigned int _capacity;
		void InitializeList() {
			LinkNodes(_capacity, _size, _head);
		}
		Variable<Type> * FindNode(unsigned index, unsigned start, Variable<Type> *inputNode) {
			if (start == index) return inputNode;
			else {
				start++;
				return FindNode(index, start, inputNode->_pointerNextVar);
			}
		}
		Variable<Type> * FindNodeStr(std::string inputName,Variable<Type> *inputNode) {
			if(inputNode->_name == inputName) return inputNode;
			else if(inputNode->_name == "NULL") return inputNode;
			else return FindNodeStr(inputName,inputNode->_pointerNextVar);
		}
		void Append() {
			FindNode(_capacity, 0, _head)->_pointerNextVar = new Variable<Type>;
			_capacity++;
		}
		void AppendInitializedVariable(Type inputData, std::string name) {
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
	};
}