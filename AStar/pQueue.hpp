#ifndef POOP
#define POOP
#include "Node.hpp"
// #include <algorithm>
#include <list>

inline bool Comp(const Node* lhs, const Node* rhs){
		return (lhs->dist+lhs->pos) < (rhs->dist+rhs->pos);
}

template<class T>
class pQueue {
public:
	pQueue();
	void push(T t);
	void pop();
	int size();
	T top();
	void reHeap();
private:
	std::list<T> elems;
};

template<class T>
pQueue<T>::pQueue(){
	elems = std::list<T>();
}

template<class T>
void pQueue<T>::push(T t){
	elems.push_back(t);
	reHeap();
}

template<class T>
int pQueue<T>::size(){
	return elems.size();
}

template<class T>
void pQueue<T>::pop(){
	elems.pop_front();
}

template<class T>
T pQueue<T>::top(){
	return elems.front();
}

template<class T>
void pQueue<T>::reHeap(){
 	elems.sort(Comp);
}

#endif