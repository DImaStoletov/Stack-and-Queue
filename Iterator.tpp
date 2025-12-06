#include "Iterator.h"
template<typename T>
fwd_container<T>::iterator::iterator(const const_iterator& other)
    : base(other.base ? static_cast<iterator_base*>(other.base->clone()) : nullptr) {}

template<typename T>
typename fwd_container<T>::iterator& fwd_container<T>::iterator::operator=(const const_iterator& other) {
    delete base;
    base = other.base ? static_cast<iterator_base*>(other.base->clone()) : nullptr;
    return *this;
}

template<typename T>
bool fwd_container<T>::iterator::operator==(const const_iterator& other) const {
    return *this->base == *other.base;
}

template<typename T>
bool fwd_container<T>::iterator::operator!=(const const_iterator& other) const {
    return !(*this == other);
}

template<typename T>
fwd_container<T>::const_iterator::const_iterator(const iterator& other)
    : base(other.base ? static_cast<const_iterator_base*>(other.base->clone()) : nullptr){}

template<typename T>
typename fwd_container<T>::const_iterator& fwd_container<T>::const_iterator::operator=(const iterator& other) {
    delete base;
    base = other.base ? static_cast<const_iterator_base*>(other.base->clone()) : nullptr;
    return *this;
}

template<typename T>
bool fwd_container<T>::const_iterator::operator==(const iterator& other) const {
    return *this->base == *other.base;
}

template<typename T>
bool fwd_container<T>::const_iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const fwd_container<T>& x) {
    auto it = x.begin();
    auto end_it = x.end();

    if (it != end_it) {
        os << *it;
        ++it;
    }

    for (; it != end_it; ++it) {
        os << " " << *it;
    }

    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, fwd_container<T>& x) {
    T value;
    while (is >> value) {
        x.Push(value);
        if (is.peek() == '\n' || is.eof()) {
            break;
        }
    }
    return is;
}
