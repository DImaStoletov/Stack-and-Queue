#include "Queue.h"
using std::cerr;
using std::bad_alloc;
using std::runtime_error;
using std::endl;
using std::exception;
using std::bad_cast;
using std::move;
template <typename T>
Queue<T>::Queue(Queue &&other) noexcept : Front(other.Front), Back(other.Back), n(other.n){
    other.Front = nullptr;
    other.Back = nullptr;
    other.n = 0;
}

template <typename T>
Queue<T>::Queue(const Queue &other) : Front(nullptr), Back(nullptr), n(0){
    if (!other.IsEmpty())
    {
        Node* node = other.Front;
        while (node != nullptr)
        {
            Push(node->data);
            node = node->next;
        }
        n = other.n;
    }
}


template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &other){
    if (!other.IsEmpty() && this != &other)
    {
        Clear();
        Node* node = other.Front;
        while (node != nullptr)
        {
            Push(node->data);
            node = node->next;
        }
        n = other.n;
    }
    return *this;
}

template <typename T>
Queue<T> &Queue<T>::operator=(Queue<T> &&other) noexcept{
    if (this != &other)
    {
        Clear();

        Front = other.Front;
        Back = other.Back;
        n = other.n;
        other.Front = nullptr;
        other.Back = nullptr;
        other.n = 0;
    }
    return *this;
}

template <typename T>
void Queue<T>::Push(const T &x){
    try
    {
        Node* new_node = new Node(x);
        if (IsEmpty())
        {
            Front = new_node;
            Back = new_node;
        }
        else
        {
            Back->next = new_node;
            Back = new_node;
        }
        n++;
    }
    catch (const bad_alloc &e)
    {
        cerr << "Memory error: " << e.what() << endl;
        throw runtime_error("Memory error");
    }
    catch (const exception &e)
    {
        cerr << "Unxcepted error: " << e.what() << endl;
        throw;
    }
}

template <typename T>
void Queue<T>::Push(T &&x){
    try
    {
        Node* new_node = new Node(move(x));
        if (IsEmpty())
        {
            Front = new_node;
            Back = new_node;
        }
        else
        {
            Back->next = new_node;
            Back = new_node;
        }
        n++;
    }
    catch (const bad_alloc &e)
    {
        cerr << "Memory error: " << e.what() << endl;
        throw runtime_error("Memory error");
    }
    catch (const exception &e)
    {
        cerr << "Unxcepted error: " << e.what() << endl;
        throw;
    }
}

template <typename T>
T Queue<T>::Pop(){
    if (IsEmpty())
    {
        throw runtime_error("Queue is empty");
    }

    try
    {
        T x = Front->data;
        Node* temp = Front;
        Front = Front->next;

        if (Front == nullptr)
        {
            Back = nullptr;
        }

        delete temp;
        n--;
        return x;
    }
    catch (const exception &e)
    {
        cerr << "Unexpected error: " << e.what() << endl;
        throw;
    }
}

template <typename T>
T &Queue<T>::GetFront() const{
    if (IsEmpty())
    {
        throw runtime_error("Empty error");
    }
    return Front->data;
}

template <typename T>
T &Queue<T>::GetBack() const{
    if (IsEmpty())
    {
        throw runtime_error("Empty error");
    }
    return Back->data;
}

template <typename T>
bool Queue<T>::IsEmpty() const{
    return Front == nullptr;
}

template <typename T>
size_t Queue<T>::Size() const{
    return n;
}

template <typename T>
void Queue<T>::Clear(){
    while (!IsEmpty())
    {
        Node* node = Front;
        Front = Front->next;
        delete node;
    }
    n = 0;
}

template <typename T>
typename Queue<T>::iterator Queue<T>::begin() {
    return iterator(new typename Queue<T>::QueueIterator(Front));
}

template <typename T>
typename Queue<T>::iterator Queue<T>::end() {
    return iterator(new typename Queue<T>::QueueIterator(nullptr));
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::begin() const {
    return const_iterator(new typename Queue<T>::ConstQueueIterator(Front));
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::end() const {
    return const_iterator(new typename Queue<T>::ConstQueueIterator(nullptr));
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::cbegin() const {
    return const_iterator(new typename Queue<T>::ConstQueueIterator(Front));
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::cend() const {
    return const_iterator(new typename Queue<T>::ConstQueueIterator(nullptr));
}

