#pragma once
#include <string>
using namespace std;

template <class T>
class List
{
    struct Node
    {
        T data;
        Node *next;
    };

public:
    class Iterator
    {
    public:
        Iterator(Node *begin)
        {
            current = begin;
        }
        bool hasItem() const
        {
			if (current) return true;
			else return false;
        }
        T getItem() const
        {
            return current->data;
        }
        void next()
        {
            if (hasItem()) current = current->next;
        }

    private:
        Node *current;
    };
    List()
    {
        begin = 0;
    }
    ~List()
    {
        Node *current = begin;
        while (current)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }
    void pushBack(T data)
    {
        Node* node = new Node;
        node->data = data;
        node->next = 0;

        if (!begin) begin = node;
        else
        {
            Node *current = begin;
            while (current->next) current = current->next;
            current->next = node;
        }
    }
    T findAt(int index) const
    {
        Node *current = begin;
        int i = 0;
        while (current)
        {
            if (i == index) return current->data;
            current = current->next;
            i++;
        }
        throw (std::string)"The node does not exist.";
    }
    T takeFirst()
    {
        if (!begin) throw (string)"The first element is not exist.";
        T first = begin->data;
        begin = begin->next;
        return first;
    }

    int countSize() const
    {
        int size = 0;
        Node *current = begin;
        while (current)
        {
            size++;
            current = current->next;
        }
        return size;
    }
    Iterator createIterator() const
    {
        return Iterator(begin);
    }
    bool contains(T data) const
    {
        Iterator it = createIterator();
        while (it.hasItem())
        {
            if (it.getItem() == data) return true;
			it.next();
        }
        return false;
    }
    bool isEmpty() const
    {
        if (!begin) return true;
        else return false;
    }

private:
    Node* begin;
};
