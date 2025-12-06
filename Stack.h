#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "Iterator.h"

template<typename T>
class Stack: public fwd_container<T>{
public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    Stack() : top(nullptr), n(0) {};
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack(){ Clear(); };

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    void Push(const T& x) override;
    void Push(T&& x) override;
    T Pop() override;
    T& GetFront() const override;
    bool IsEmpty() const override;
    size_t Size() const override;
    void Clear() override;

    iterator begin() override;
    iterator end() override;
    const_iterator begin() const override;
    const_iterator end() const override;
    const_iterator cbegin() const override;
    const_iterator cend() const override;


private:
    struct Node{
        T data;
        Node* next;

        Node(const T& x) : data(x), next(nullptr) {}
        Node(T&& x) : data(std::move(x)), next(nullptr) {}
    };


    Node* top; //указатель на вершину стека
    size_t n; //количество элементов

    class StackIterator : public fwd_container<T>::iterator_base {
    public:
        StackIterator(Node* node) : cur(node) {}

        T& operator*() override {
            return cur->data;
        }

        T* operator->() override {
            return &(cur->data);
        }

        StackIterator& operator++() override {
            cur = cur->next;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::iterator_base_com& other) const override {
            return cur == static_cast<const StackIterator&>(other).cur;
        }

        bool operator!=(const typename fwd_container<T>::iterator_base_com& other) const override {
            return !(*this == other);
        }

        typename fwd_container<T>::iterator_base_com* clone() const override {
            return new StackIterator(cur);
        }
    private:
        Node* cur;

        friend class Stack<T>;
    };


    class ConstStackIterator : public fwd_container<T>::const_iterator_base {
    public:
        ConstStackIterator(const Node* node) : cur(node) {}

        const T& operator*() const override {
            return cur->data;
        }

        const T* operator->() const override {
            return &(cur->data);
        }

        ConstStackIterator& operator++() override {
            cur = cur->next;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::iterator_base_com& other) const override {
            return cur == static_cast<const ConstStackIterator&>(other).cur;
        }

        bool operator!=(const typename fwd_container<T>::iterator_base_com& other) const override {
            return !(*this == other);
        }

        typename fwd_container<T>::iterator_base_com* clone() const override {
            return new ConstStackIterator(cur);
        }
    private:
        const Node* cur;
    };
};

#include "Stack.tpp"
#endif // STACK_H_INCLUDED
