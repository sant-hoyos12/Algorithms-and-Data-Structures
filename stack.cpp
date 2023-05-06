#ifdef stack_hpp

template <typename T>
Stack<T>::Stack() {
	count = 0;
	stack = nullptr;
}

template<typename T>
Stack<T>::~Stack(){
	clear();
	stack = nullptr;
}

template <typename T>
unsigned Stack<T>::size() {
	return count;
}

template <typename T>
bool Stack<T>::empty() {
	return count == 0;
}

template <typename T>
void Stack<T>::clear(){
	while (count > 0) {
		pop();
	}
}

template <typename T>
void Stack<T>::display(){
	Cell *curr = stack;
	std::cout << "stack -> ";
	while (curr != nullptr){
		std::cout << curr->data << " -> ";
		curr = curr->next;
	}
	std::cout << "nullptr" << std::endl;
}

// template <typename T>
// void Stack<T>::multi_push(const std::vector<T> &src){
// 	typename std::vector<T>::const_reverse_iterator it = src.crbegin() ;
// 	for (; it != src.crend(); it++){
// 		push(*it);
// 	}
// }
//
// template <typename T>
// void Stack<T>::cmulti_push(const std::vector<T> &src){
// 	T aux = pop();
// 	multi_push(src);
// 	push(aux);
// }
//
// template <typename T>
// void Stack<T>::multi_pop(unsigned& q){
// 	for (unsigned i = 0; i < q; i++){
// 		pop();
// 	}
// }

template <typename T>
void Stack<T>::push(T item){
	Cell *cell = new Cell;
	cell->data=item;
	if (stack == nullptr) cell->next = nullptr;
	else cell->next = stack;
	stack = cell;
	count++;
}

template <typename T>
T Stack<T>::pop(){
	if (stack == nullptr){
		std:: cout<< "Error" << std::endl;
		exit(1);
	}
	T rc = stack->data;
	Cell *tmp = stack;
	stack = stack->next;
	count--;

	delete tmp;
	return rc;
}

template <typename T>
T Stack<T>::peek(){
	if (stack == nullptr){
		std:: cout<< "Error" << std::endl;
		exit(1);
	}
	return stack->data;
}

template <typename T>
void Stack<T>::deepCopy(const Stack<T> &src){
	if (src.stack == nullptr){
		stack = nullptr;
		count = 0;
	} else {
		Cell *iter = src.stack;
		Cell *dummy_stack = new Cell;
		Cell *curr = dummy_stack;
		while (iter != nullptr){
			curr->data = iter->data;
			curr->next = new Cell;
			curr->next->next = nullptr;
			curr = curr->next;
			iter = iter->next;
		}
		stack = dummy_stack;
	}
}

template <typename T>
T Stack<T>::pook(){
	if (stack == nullptr){
		std:: cout<< "Error" << std::endl;
		exit(1);
	}
	Cell *aux = stack;
	while (aux->next != nullptr) aux = aux->next;
	return aux->data;
}

#endif
