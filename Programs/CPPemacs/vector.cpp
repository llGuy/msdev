#include <iostream>
#include <string>
#include <stdio.h>

#define NULL 0

using namespace std;

class Vector {
public:
  Vector(int size_input = 8);
  ~Vector();
  int *array_;
  int size_;
  int capacity_;
  void AddNumber(int num_input);
}

  Vector::Vector(int size_input = 8{
      size_ = size_input;
      array_ = new int[size_];
      for (int num_in_array = 0; num_in_array < size_; num_in_array++){
	array_[num_in_array] = NULL;
      }
    }
    Vector::~Vector(){
      delete[] array_;
    }
    Vector::AddNumber(int num_input){
      if(capacity_ < size_){
	array_[capacity_] = num_input;
      }
    }

int main(){
  
}
