#include "Stack.h"



Stack::Stack(): start(NULL, "")
{
	current = &start;
}
void Stack::push(std::string s)
{
	Node* n = new Node(current, s);
	current = n;

}
std::string Stack::pop()
{
	if (current == &start) return "";

	std::string temp = current->s;
	Node* prev = current;
	current = current->prev;
	delete prev;
	return temp;
}
std::string Stack::peek()
{
	return current->s;
}

bool Stack::is_empty()
{
	if (current == &start) return true;
	return false;
}

Stack::~Stack()
{
	while (current != &start)
	{
		Node* prev = current;
		current = current->prev;
		delete prev;
	}
}


NumStack::NumStack() : start(NULL, 0)
{
	current = &start;
}
void NumStack::push(double s)
{
	Node* n = new Node(current, s);
	current = n;

}
double NumStack::pop()
{
	if (current == &start) return 0;

	double temp = current->s;
	Node* prev = current;
	current = current->prev;
	delete prev;
	return temp;
}
double NumStack::peek()
{
	return current->s;
}

bool NumStack::is_empty()
{
	if (current == &start) return true;
	return false;
}

NumStack::~NumStack()
{
	while (current != &start)
	{
		Node* prev = current;
		current = current->prev;
		delete prev;
	}
}