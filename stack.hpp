#ifndef stack_hpp
#define stack_hpp

#include<cstdlib>
#include<iostream>

template <typename T>
class Stack{
private:
	struct Cell{
		T data;
		Cell *next;
	};

	Cell *stack;
	unsigned count;

	void deepCopy(const Stack<T> &src);

public:
	Stack();
	~Stack();

	unsigned size();
	bool empty();
	void clear();
	void display();
//	void reverse();

	// void multi_push(const std::vector<T> &src);
	// void cmulti_push(const std::vector<T> &src);
	// void multi_pop(unsigned& q);

	void push(T item);
	T pop();
	T peek();
	T pook();
};

#include "stack.cpp"
#endif
