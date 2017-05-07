// Playlist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;

class node
{
	char artist[50];
	char song[50];
	node *next;
public:
	node(char a[], char s[]);
	friend class linkedList;
};

node::node(char a[], char s[])
{
	strcpy_s(artist, a);
	strcpy_s(song, s);
	next = NULL;
}

class linkedList
{
	node *head;
	node *tail;
public:
	linkedList();
	void addNodeToEnd(node *nptr);
	void addNodeToHead(node *nptr);
	int insertAfter(node *ptr, char b[]);
	int removeNode(char b[]);
	void showListwithoptions();
	int readfile(string filename);
};

linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}

void linkedList::showListwithoptions()
{
	char response;
	node *ptr;
	ptr = head;
	cout << "*****Music Playlist*****" << endl;
	if (ptr == NULL)
	{
		cout << "The list is empty " << endl;
		return;
	}
	while (ptr != NULL)
	{
		cout << "Next song: " << ptr->artist << "," << ptr->song << endl;

		cout << "Select [P]lay, [S]kip, [D]elete or [Q]uit." << endl;
		cin >> response;
		cin.clear();
		cin.ignore();

		if (response == 'p' || response == 'P')
		{
			cout << "Playing song:" << ptr->song << "\n" << endl;;
		}
		else if (response == 's' || response == 'S')
		{
			cout << "Song Skipped" << "\n" << endl;
		}
		else if (response == 'd' || response == 'D')
		{
			node * del = ptr;
			ptr = ptr->next;
			this->removeNode(del->song);
			cout << "Song Deleted" << endl;
		}
		else if (response == 'q' || response == 'Q')
		{
			cout << "Thanks for listening!" << "\n" << endl;
			break;
		}
		ptr = ptr->next;

	}
}
void linkedList::addNodeToEnd(node *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void linkedList::addNodeToHead(node *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		ptr->next = head;
		head = ptr;
	}
}

int linkedList::readfile(string filename)
{
	ifstream infile(filename);
	if (!infile)
	{
		return -1;
	}

	while (!infile.eof())
	{
		char artist[50];
		char song[50];

		infile.getline(artist, 50, ',');
		infile.getline(song, 50);

		node * newnode = new node(artist, song);
		this->addNodeToEnd(newnode);
	}
	infile.close();
}
int linkedList::insertAfter(node *newnode, char b[])
{
	node *ptr = head;
	while (ptr != NULL)
	{
		if (strcmp(ptr->song, b) == 0)
		{
			newnode->next = ptr->next;
			ptr->next = newnode;
			if (tail == ptr)
				tail = newnode;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

int linkedList::removeNode(char b[])
{
	node *ptr = head;
	if (ptr == NULL)
		return -1;

	if (strcmp(head->song, b) == 0)
	{
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (strcmp((ptr->next)->song, b) == 0))
		{
			if (tail == ptr->next)
				tail = ptr;
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

int main()
{
	string filename;
	cout << "Please enter full filename: ";
	getline(cin, filename);
	char answer;
	linkedList *playlist = new linkedList();


	playlist->readfile(filename);
	for (;;) {
		playlist->showListwithoptions();
	}
	return 0;
}