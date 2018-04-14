#pragma once
#include <iostream>
//class node stores a value - char, int...
//it composes the linked list
template<class Type>
class Node
{
public:
	Node() {
		isEndOfList = false;
	}
	~Node() {
		//deletes the pointer to the next node
		delete _pointerNextNode;
	}
	//boolean on whether the node is the last of the list
	bool isEndOfList;
	//pointer points to the next node
	Node<Type> * _pointerNextNode;
	//the data that is being stored inside the node
	Type _data;
	//operator function sets data to a value
	void operator=(Type other) {
		//sets the data to the other value of type "Type"
		_data = other;
	}
	friend std::ostream &operator<<(std::ostream &stream,Node<Type> &inputNode) {
		stream << inputNode._data;
		return stream;
	}
};
//class LinkedList takes in a template and the size of the list
template<class Type, unsigned int size> 
class LinkedList {
private:
	//creates a pointer to the first node of the linked list
	Node<Type> * _head = new Node<Type>;
	//size of the list at the beginning which is 0
	unsigned int _size;
	//this function links the nodes together
	void LinkNodes(int endSize, int startSize, Node<Type> * inputNode) {
		//if the start size is equal to the finishing size
		if (startSize == endSize) {
			//the process is finished
			inputNode->isEndOfList = true;
			return;
		}
		//if we are at the beginning
		else if (startSize == 0){
			//set the head's pointer to the next pointer in the list
			_head->_pointerNextNode = new Node<Type>;
			//add to the current size
			startSize++;
			//recursion of this function
			//the code in this "else if" statement will never be called again
			LinkNodes(endSize, startSize, _head->_pointerNextNode);
		}
		//if the node is not the beginning nor the end
		else if (startSize > 0 && startSize < endSize) {
			//links the current node to the next
			inputNode->_pointerNextNode = new Node<Type>;
			//increase the current size by 1
			startSize++;
			//recursion of the function
			LinkNodes(endSize, startSize, inputNode->_pointerNextNode);
		}
		else {
			//if some how none of the above happen, the computer exits this function
			return;
		}
	}
public:
	LinkedList() {
		//initializes the size at the beginning
		//eventually is will equal SIZE_OF_LIST_END
		_size = 0;
	}
	~LinkedList() {
		//nothing to delete because the node class has
		//built-in delete functions
	}
	//size of the list when the nodes are created and linked
	unsigned int _capacity = size;
	//function to find a node in the linked list
	//takes in the index of the requested node and the starting index
	Node<Type> * FindNode(int index, int start, Node<Type> *inputNode) {
		//if the starting index isn't equal to the requested index
		if (start != index) {
			//increase the current index (start) 
			start++;
			//recursion of the function
			FindNode(index, start, inputNode->_pointerNextNode);
		}
		//if the starting position is equal to the requested index 
		else {
			//returns the pointer of the current node
			return inputNode;
		}
	}
	//function initializes the list and all the nodes inside it
	void InitializeList() {
		//calls the function LinkNodes()
		LinkNodes(_capacity, _size, _head);
	}
	//operator function is used to treat the list as an array to 
	//easily access the node that is requested, takes in an index
	Node<Type> &operator[](unsigned index) {
		//returns the node(not pointer) of the requested index
		if(index < _capacity - 1) return *FindNode(index, 0, _head);
		//print an error saying the index entered is too big
		else return *FindNode(_capacity - 1,0,_head);
	}
	//function will add a node to the beginning of the list
	void Append() {
		//makes the last node point to a new node, which will be part of the list
		FindNode(_capacity, 0, _head)->_pointerNextNode = new Node<Type>;
		_capacity++;
	}
	//function inserts a node between 2 nodes
	void Insert(Node<Type> & n1, Node<Type> & n2) {
		//creates a temporary node
		Node<Type> * _temp = new Node<Type>;
		//temp is equal to the next node of n1
		_temp = n1._pointerNextNode;
		//n1 points to a new Node
		n1._pointerNextNode = new Node<Type>;
		//links the new node with n2
		n1._pointerNextNode->_pointerNextNode = _temp;
		//increases capacity by 1
		_capacity++;
	}
	//function deletes a node in the list
	void Delete(Node<Type> &nodePrev, Node<Type> &nodePost) {
		//temporary node that will store the pointer to the node after nodePost
		Node<Type> * _temp = new Node<Type>;
		_temp = nodePost._pointerNextNode;
		//pointer of nodePrev is equal to _temp
		nodePrev._pointerNextNode = _temp;
		//decrease _capacity of the list by 1
		_capacity--;
	}
};

