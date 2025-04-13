#ifndef QUEUELINKED_H
#define QUEUELINKED_H

#include <iostream>

#include "Queue.hpp"
#include "../LinkedList.hpp"

template<typename T>
class QueueLinkedList : public Queue<T>
{
    private:
        LinkedList<T>* linked_list;
        size_t count;

    public:
        QueueLinkedList();
        ~QueueLinkedList();
        
        void enqueue(T object);
        T dequeue();

        T front() const;
        T back() const;
        bool is_empty() const;
        size_t size() const;
    
        void print_elements() const;


};

//--------------------IMPLEMENTACION-------------------

template<typename T>
QueueLinkedList<T>::QueueLinkedList()
{
    linked_list = new LinkedList<T>;
    count = 0;
}

template<typename T>
QueueLinkedList<T>::~QueueLinkedList()
{
    delete linked_list;
}

template<typename T>
void QueueLinkedList<T>::enqueue(T object)
{
    linked_list->push_front(object);
    count++;
}

template<typename T>
T QueueLinkedList<T>::dequeue()
{
    if(linked_list->is_empty())
    {
        std::cerr << "Error quitando elemento de la cola: Cola vacía" << std::endl;
        return T();
    }
    
    count--;
    return linked_list->pop_back();
}

template<typename T>
T QueueLinkedList<T>::front() const
{
    // -> para el caso de linked_list, deberia devolver el elemento de mas a la derecha (el trasero)

    return linked_list->get_rear();

}

template<typename T>
T QueueLinkedList<T>::back() const
{
    // -> para el caso de linked_list, deberia devolver el elemento de mas a la izquierda (el frontal)
    
    return linked_list->get_head();
}

template<typename T>
bool QueueLinkedList<T>::is_empty() const
{
    return count == 0;
}

template<typename T>
size_t QueueLinkedList<T>::size() const
{
    return count;
}

template<typename T>
void QueueLinkedList<T>::print_elements() const
{
    linked_list->traverse();
}

#endif
