#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "Iterator.h"
template <typename T>
class Queue: public fwd_container<T>{
public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    Queue() : Front(nullptr), Back(nullptr), n(0) {};
    Queue(const Queue &other);
    Queue(Queue &&other) noexcept;
    ~Queue() { Clear(); };

    Queue &operator=(const Queue &other);
    Queue &operator=(Queue &&other) noexcept;

    void Push(const T& x) override;
    void Push(T&& x) override;
    T Pop() override;
    T& GetFront() const override;
    T& GetBack() const;
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
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
        Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };

    Node* Front;
    Node* Back;
    size_t n;

    class QueueIterator : public fwd_container<T>::iterator_base{
    public:
        QueueIterator(Node* node) : cur(node) {}
        T& operator*() override {
            return cur->data;
        }

        T* operator->() override {
            return &(cur->data);
        }

        QueueIterator& operator++() override {
            cur = cur->next;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::iterator_base_com& other) const override {
            return cur == static_cast<const QueueIterator&>(other).cur;
        }

        bool operator!=(const typename fwd_container<T>::iterator_base_com& other) const override {
            return !(*this == other);
        }

        typename fwd_container<T>::iterator_base_com* clone() const override {
            return new QueueIterator(cur);
        }
    private:
        Node* cur;
    };

    class ConstQueueIterator : public fwd_container<T>::const_iterator_base{
    public:
        ConstQueueIterator(Node* node) : cur(node) {}

        const T& operator*() const override {
            return cur->data;
        }

        const T* operator->() const override {
            return &(cur->data);
        }

        ConstQueueIterator& operator++() override {
            cur = cur->next;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::iterator_base_com& other) const override {
            return cur == static_cast<const ConstQueueIterator&>(other).cur;
        }

        bool operator!=(const typename fwd_container<T>::iterator_base_com& other) const override {
            return !(*this == other);
        }

        typename fwd_container<T>::iterator_base_com* clone() const override {
            return new ConstQueueIterator(cur);
        }
    private:
        Node* cur;
    };
};


#include "Queue.tpp"
#endif // QUEUE_H_INCLUDED
