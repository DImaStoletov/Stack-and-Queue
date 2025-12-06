#include "Stack.h"
using std::cerr;
using std::bad_alloc;
using std::runtime_error;
using std::endl;
using std::exception;
using std::bad_cast;
using std::move;
template <typename T>
Stack<T>::Stack(Stack &&other) noexcept : top(other.top), n(other.n){
    other.top = nullptr;
    other.n = 0;
}

template <typename T>
Stack<T>::Stack(const Stack &other) : top(nullptr), n(0){
    try{
        if (!other.IsEmpty())
        {
            Node* cur_other = other.top;
            Node* cur_new = nullptr;

            top = new Node(cur_other->data);
            cur_new = top;
            cur_other = cur_other->next;

            while (cur_other != nullptr)
            {
                cur_new->next = new Node(cur_other->data);
                cur_new = cur_new->next;
                cur_other = cur_other->next;
            }

            n = other.n;
        }
    }
    catch (const bad_alloc &e)
    {
        cerr << "Memory error: " << e.what() << endl;
        throw runtime_error("Memory error");
    }
    catch (const exception &e)
    {
        cerr << "Unexpected error: " << e.what() << endl;
        throw;
    }
}


template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other){
    try{
        if (this != &other)
        {
            Clear();

            if (!other.IsEmpty())
            {
                Node* cur_other = other.top;
                Node* cur_new = nullptr;

                top = new Node(cur_other->data);
                cur_new = top;
                cur_other = cur_other->next;

                while (cur_other != nullptr)
                {
                    cur_new->next = new Node(cur_other->data);
                    cur_new = cur_new->next;
                    cur_other = cur_other->next;
                }

                n = other.n;
            }
        }
        return *this;
    }
    catch (const bad_alloc &e)
    {
        cerr << "Memory error: " << e.what() << endl;
        throw runtime_error("Memory error");
    }
    catch (const exception &e)
    {
        cerr << "Unexpected error: " << e.what() << endl;
        throw;
    }
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&other) noexcept{
    if (this != &other)
    {
        Clear();
        top = other.top;
        n = other.n;
        other.top = nullptr;
        other.n = 0;
    }
    return *this;
}

template <typename T>
void Stack<T>::Push(const T &x){
    try
    {
        Node *node = new Node(x);
        node->next = top;
        top = node;
        n++;
    }
    catch (const bad_alloc &e)
    {
        cerr << "Memory error: " << e.what() << endl;
        throw runtime_error("Memory error");
    }
    catch (const exception &e)
    {
        cerr << "Unexpected error: " << e.what() << endl;
        throw;
    }
}

template <typename T>
void Stack<T>::Push(T &&x){
    try
    {
        Node *node = new Node(move(x));
        node->next = top;
        top = node;
        n++;
    }
    catch (const bad_alloc &e)
    {
        cerr << "Memory error: " << e.what() << endl;
        throw runtime_error("Memory error");
    }
    catch (const exception &e)
    {
        cerr << "Unexpected error: " << e.what() << endl;
        throw;
    }
}


template <typename T>
T Stack<T>::Pop(){
    if (IsEmpty())
    {
        throw runtime_error("Stack is empty");
    }
    try
    {
        T x = top->data;
        Node *node = top;
        top = top->next;
        delete node;
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
T &Stack<T>::GetFront() const{
    if (IsEmpty())
    {
        throw runtime_error("Empty error");
    }
    return top->data;
}

template <typename T>
bool Stack<T>::IsEmpty() const{
    return top == nullptr;
}

template <typename T>
size_t Stack<T>::Size() const{
    return n;
}

template <typename T>
void Stack<T>::Clear(){
    while (!IsEmpty()){
        Node *node = top;
        top = top->next;
        delete node;
    }
    n = 0;
}

template <typename T>
typename Stack<T>::iterator Stack<T>::begin() {
    return iterator(new typename Stack<T>::StackIterator(top));
}

template <typename T>
typename Stack<T>::iterator Stack<T>::end() {
    return iterator(new typename Stack<T>::StackIterator(nullptr));
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::begin() const {
    return const_iterator(new typename Stack<T>::ConstStackIterator(top));
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::end() const {
    return const_iterator(new typename Stack<T>::ConstStackIterator(nullptr));
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::cbegin() const {
    return const_iterator(new typename Stack<T>::ConstStackIterator(top));
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::cend() const {
    return const_iterator(new typename Stack<T>::ConstStackIterator(nullptr));
}

