#pragma once
#include <iostream>
#include <string>

class Stack
{
	struct Node
	{
		Node* prev;
		std::string s;

		Node(Node* prev, std::string s) : prev(prev), s(s){}
	};

	Node* current;
	Node start;

public:

	Stack();
	void push(std::string s);
	std::string pop();
	std::string peek();

	bool is_empty();

	~Stack();

};

class NumStack
{
	struct Node
	{
		Node* prev;
		double s;

		Node(Node* prev, double s) : prev(prev), s(s) {}
	};

	Node* current;
	Node start;

public:

	NumStack();
	void push(double s);
	double pop();
	double peek();

	bool is_empty();

	~NumStack();

};

