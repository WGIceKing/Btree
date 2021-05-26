#pragma once
#include <iostream>

struct node {
	int value;
	node* next;
	node* prev;
};

class LinkedList {
private:
	node* head;
	node* tail;
public:
	LinkedList();
	void push_front(int givenValue);
	void push_back(int givenValue);
	void pop_back();
	bool check_value(int givenValue) const;
	void print() const;
	node* getHead();
	void deallocate() const;
};
