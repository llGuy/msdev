#include <iostream>p
#include <stdio.h>

using namespace std;

class Vector{
public:
  Vector(int size);
  ~Vector();
  int capacity_ = 0;
  int size_ = 8;
  int *array_;
  void AddNumber(int number);
};

Vector::Vector(int size = 8){
  printf("Vector has been created with %i numbers and size %i\n",capacity_,size_);
  size_=size;
  array_ = new int[size_];
}

Vector::~Vector(){
  delete[] array_;
}

void Vector::AddNumber(int number){
  if(capacity_<size_){
    array_[capacity_] = number;
    capacity_++;  
  }
  else{
      int temp_size_ = size_ * 2;
      int *temp_=new int [temp_size_];
    for(int _number=0; _number<size_; _number++){
      temp_[_number]=array_[_number];
    }
    array_=temp_;
    delete[] temp_;
    array_[capacity_] = number;
    capacity_++;
  }
}

int main()
{
  Vector vector;
  bool loopIsReal = true;
  while(loopIsReal == true){
    for(int i = 0; i < vector.size_ ; i++){
      printf("%i ", vector.array_[i]);
    }
    printf("\n");
    printf("Add a number:\n ");
      int temp;
    cin>>temp;
    vector.AddNumber(temp);
  };
}

