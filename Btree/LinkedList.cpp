#include "LinkedList.h"

LinkedList::LinkedList() {
	this->head = NULL;
	this->tail = NULL;
}

void LinkedList::push_front(int givenValue) {
	node* new_node = new node;
	new_node->next = head;
	new_node->prev = NULL;
	new_node->value = givenValue;

	if (head == NULL) {
		head = new_node;
		tail = new_node;
	}
	else {
		head->prev = new_node;
		head = new_node;
	}
}

void LinkedList::push_back(int givenValue) {
	node* new_node = new node;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->value = givenValue;

	if (head == NULL) {
		head = new_node;
		tail = new_node;
	}
	else {
		node* tmp = head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new_node;
		new_node->prev = tmp;
		tail = new_node;
	}
}

void LinkedList::pop_back() {
	if (head == NULL) {
		std::cout << "NULL" << std::endl;
	}
	else {
		node* tmp = tail;
		if (head == tail) {
			head = NULL;
			tail = NULL;
			delete tmp;
		}
		else {
			tail->prev->next = NULL;
			tail = tail->prev;
			delete tmp;
		}
	}
}

bool LinkedList::check_value(int givenValue) const {
	if (head == NULL) {
		return false;
	}
	else {
		node* tmp = head;
		while (tmp != NULL) {
			if (tmp->value == givenValue) {
				return true;
			}
			tmp = tmp->next;
		}
		return false;
	}
}

void LinkedList::print() const {
	if (head == NULL) {
		std::cout << "NULL" << std::endl;
	}
	else {
		node* tmp = head;
		while (tmp != NULL) {
			std::cout << tmp->value << " ";
			tmp = tmp->next;
		}
	}
	std::cout << std::endl;
}

node* LinkedList::getHead() {
	return this->head;
}

void LinkedList::deallocate() const {
	node* cur = head;
	if (head != NULL) {
		while (cur != NULL) {
			node* next = cur->next;
			delete cur;
			cur = next;
		}
	}
}