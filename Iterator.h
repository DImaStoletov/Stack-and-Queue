#ifndef ITERATOR_H_INCLUDED
#define ITERATOR_H_INCLUDED
#include <iostream>
#include <iterator>
#include <stdexcept>
template<typename T>
class fwd_container{
public:
    // обобщающий базовый итератор
    class iterator_base_com {
    public:
        virtual ~iterator_base_com() = default;
        virtual iterator_base_com* clone() const = 0;
    };

    // итератор, от которого будут наследоваться итераторы динамических классов
    class iterator_base : public iterator_base_com {
    public:
        virtual T& operator*() = 0;
        virtual T* operator->() = 0;
        virtual iterator_base& operator++() = 0;
        virtual bool operator==(const iterator_base_com& other) const = 0;
        virtual bool operator!=(const iterator_base_com& other) const = 0;
    };

    // константный интератор, от которго будут наследоваться константные итераторы динамических классов
    class const_iterator_base : public iterator_base_com {
    public:
        virtual const T& operator*() const = 0;
        virtual const T* operator->() const = 0;
        virtual const_iterator_base& operator++() = 0;
        virtual bool operator==(const iterator_base_com& other) const = 0;
        virtual bool operator!=(const iterator_base_com& other) const = 0;
    };

    class const_iterator;

    class iterator {
    private:
        iterator_base* base;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

        iterator() : base(nullptr) {}
        iterator(iterator_base* base_) : base(base_) {}

        iterator(const iterator& other) : base(other.base ? static_cast<iterator_base*>(other.base->clone()) : nullptr) {}

        iterator(iterator&& other) noexcept : base(other.base) {
            other.base = nullptr;
        }

         ~iterator() { delete base; }

        iterator& operator=(const iterator& other) {
            delete base;
            base = other.base ? static_cast<iterator_base*>(other.base->clone()) : nullptr;
            return *this;
        }

        iterator& operator=(iterator&& other) noexcept {
            delete base;
            base = other.base;
            other.base = nullptr;
            return *this;
        }

        reference operator*() {
            return **base;
        }

        pointer operator->() {
            return &(**base);
        }

        iterator& operator++() {
            ++(*base);
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*base);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return *base == *other.base;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
        friend class const_iterator;

        iterator(const const_iterator& other);

        iterator& operator=(const const_iterator& other);

        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
    };


    class const_iterator {
    private:
        const_iterator_base* base;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() : base(nullptr) {}
        const_iterator(const_iterator_base* base_) : base(base_) {}

        const_iterator(const const_iterator& other) : base(other.base ? static_cast<const_iterator_base*>(other.base->clone()) : nullptr) {}

        const_iterator(const_iterator&& other) noexcept : base(other.base) {
            other.base = nullptr;
        }

         ~const_iterator() { delete base; }

        const_iterator& operator=(const const_iterator& other) {
            delete base;
            base = other.base ? static_cast<const_iterator_base*>(other.base->clone()) : nullptr;
            return *this;
        }

        const_iterator& operator=(const_iterator&& other) noexcept {
            delete base;
            base = other.base;
            other.base = nullptr;
            return *this;
        }

        reference operator*() const {
            return **base;
        }

        pointer operator->() const {
            return &(**base);
        }

        const_iterator& operator++() {
            ++(*base);
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++(*base);
            return temp;
        }

        bool operator==(const const_iterator& other) const {
            return *base == *other.base;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
        friend class iterator;

        const_iterator(const iterator& other);

        const_iterator& operator=(const iterator& other);

        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    };

    virtual ~fwd_container() = default;

    virtual void Push(const T& x) = 0;
    virtual void Push(T&& x) = 0;
    virtual T Pop() = 0;
    virtual T& GetFront() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;
    virtual void Clear() = 0;

    virtual iterator begin() = 0;
    virtual iterator end() = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const fwd_container<U>& x);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, fwd_container<U>& x);
};
#include "Iterator.tpp"


#endif // ITERATOR_H_INCLUDED
