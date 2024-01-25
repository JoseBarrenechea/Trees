#include <iostream>
using namespace std;

template <typename T> class Queue {
  T *array;
  int capacity;
  int elements;
  int front, back;

public:
  Queue(int ca = 10) : capacity(ca) {
    array = new T[capacity];
    elements = 0;
    front = -1;
    back = -1;
  }
 bool is_empty() {return elements == 0;}
  void enqueue(T data) {
    if (elements == capacity) {
      return;
    } else {
      back = (back + 1) % capacity;
      array[back] = data;
      if (front == -1) {
        front = 0;
      }
      elements++;
    }
  }

  T dequeue() {
    if (is_empty()) {
      throw "Queue is empty";
    } else {
      T temp = array[front];
      front = (front + 1) % capacity;
      elements--;
      if (elements == 0) {
        front = back = -1;
      }
      return temp;
    }
  }

  void display() {
    for (int i = 0; i < elements; i++) {
      int index = (front + i) % capacity;
      cout << array[index] << " ";
    }
    cout << endl;
  }
};
