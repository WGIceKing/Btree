#pragma once
#include <iostream>

struct val {
	int value;
	bool found = false;//if found - true
};

struct node {
	val val;
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
	bool check_value(int givenValue);
	void print();
	node* getHead();
	node* getTail();
};
