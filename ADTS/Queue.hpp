#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

// TODO: INVESTIGAR COMO HACER QUE UN NODO PUEDA APUNTAR A 2 SIGUIENTES

template<typename T>
class Queue
{
    public:
        virtual void enqueue(T val) = 0;
        virtual T dequeue() = 0;
        
        virtual T front() const = 0;
        virtual bool is_empty() const = 0;
        virtual size_t size() const = 0;
};

#endif
