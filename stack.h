#include <iostream>
using namespace std;

bool autoresize_ = true;

template <typename T> class Stack {
  T *array;
  int capacity;
  int elements;

public:
  Stack(int ca = 10) : capacity(ca) {
    elements = 0;
    array = new T[capacity];
  }
  bool is_empty() { return elements == 0; }
  void resize() {
    capacity *= 2;
    T *newarray = new T[capacity];
    for (int i = 0; i < elements; i++) {
      newarray[i] = array[i];
    }
    delete[] array;
    array = newarray;
  }
  void push(T x) {
    if (elements == capacity) {
      cout << "Stack is full" << endl;
      if (autoresize_){
        cout << "Resize" << endl;
        resize();
        push(x);
      }
      return;
    }
    array[elements++] = x;
  }
  T pop() {
    if (elements == 0) {
      throw "Stack is empty";
    }
    T elemnt = array[--elements];
    return elemnt;
  }
  void display() {
    for (int i = 0; i < elements; i++) {
      cout << this->array[i] << " ";
    }
    cout << endl;
  }

  int size() { return elements; }
  ~Stack() { delete[] array; }
};
