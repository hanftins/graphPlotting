#pragma once
#include <iostream>

template <class T>
struct Node {
	T data;
	Node<T>* next;
};

template <class T>
void pushStack(Node<T>*& head, T value) {
	Node<T>* newNode = new Node<T>;
	newNode->data = value;
	newNode->next = NULL;
	if (!head)
		head = newNode;
	else {
		newNode->next = head;
		head = newNode;
	}
}

template <class T>
void popStack(Node<T>*& head) {
	if (head) {
		if (!(head->next)) {
			delete head;
			head = NULL;
		}
		else {
			Node<T>* p = head;
			head = head->next;
			delete p;
		}
	}
}

template <class T>
bool emptyStack(Node<T>* head) {
	return (!head);
}

template <class T>
T topStack(Node<T>* head) {
	if (head) 
		return head->data;
	else
		throw 1;
}

template <class T>
int sizeStack(Node<T>* head) {
	Node<T>* p = head;
	int count = 0;
	while (p) {
		p = p->next;
		count++;
	}
	return count;
}