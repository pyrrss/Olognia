#include <iostream>

#include "Queue.hpp"

// TODO: HACERLO DINAMICO PARA CUANDO SE LLENE

template<typename T>
class QueueArray : public Queue<T>
{
    private:
        T* array; 
        size_t capacity; // -> tamaño de la queue
        size_t front_index; // -> indice de elemento de más a la izquierda
        size_t rear_index; // -> indice de elemento de más a la derecha
        size_t count; // -> contador para tamaño cola

    public:
        QueueArray(size_t capacity);
        ~QueueArray();

        void enqueue(T object);
        T dequeue();

        T front() const;
        bool is_empty() const;
        size_t size() const;

        void print_elements() const;
};

// TODO: seguir con el iterador
template<typename T>
class Iterator
{
    private:
        QueueArray<T>* queue; // -> puntero a queue
        size_t current_index; // -> indice actual
        size_t count; // -> contador de elementos iterados
    public:
        Iterator(QueueArray<T>* queue, size_t current_index, size_t count);
        
        T operator*() const; // -> operador *: devuelve elemento actual mediante desreferencia
        Iterator<T>& operator++(); // -> operador ++: avanza al siguiente elemento
        bool operator!=(const Iterator<T>& other) const; // -> operador !=: compara si dos iteradores son diferentes

};

//----------------------IMPLEMENTACION-------------------------

template<typename T>
QueueArray<T>::QueueArray(size_t capacity)
{
    this->capacity = capacity;
    front_index = -1;
    rear_index = -1;
    count = 0;
    array = new T[capacity];
}

template<typename T>
QueueArray<T>::~QueueArray()
{
    delete[] array;
}

template<typename T> 
void QueueArray<T>::enqueue(T object)
{
    
    if(count == capacity)
    {
        // HACERLO DINAMICO

        std::cerr << "Error ingresando elemento a la queue: Array interno lleno" << std::endl;
        return;
    }
        
    rear_index = (rear_index + 1) % capacity;
    array[rear_index] = object;
    count++;
}

template<typename T>
T QueueArray<T>::dequeue()
{
    if(is_empty())
    {
        std::cerr << "Error quitando elemento de la queue: Array interno vacío" << std::endl;
        return T();
    }
    
    front_index = (front_index + 1) % 5;
    count--;

    return array[front_index];
}

template<typename T>
T QueueArray<T>::front() const
{
    return array[front_index];
}

template<typename T>
bool QueueArray<T>::is_empty() const
{
    return count == 0;
}

template<typename T>
size_t QueueArray<T>::size() const
{
    return count;
}

template<typename T>
void QueueArray<T>::print_elements() const
{
    for (size_t i = 0; i < count; ++i)
    {
        size_t index = (front_index + 1 + i) % capacity;
        std::cout << array[index] << std::endl;
    }
}




