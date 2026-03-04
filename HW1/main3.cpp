#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

template<class T>
class BiList {
private:
    struct BiListNode {
        T value;
        BiListNode* next;
        BiListNode* prev;
        BiListNode(const T& val = T(), BiListNode* n = nullptr, BiListNode* p = nullptr)
            : value(val), next(n), prev(p) {}
        explicit BiListNode(bool isFake)
            : value(T()), next(this), prev(this) {}
    };
    BiListNode* fake;
    size_t size;
    BiListNode* createNode(const T& value) {
        return new BiListNode(value);
    }
    void insertBetween(BiListNode* node, BiListNode* prev, BiListNode* next) {
        node->prev = prev;
        node->next = next;
        prev->next = node;
        next->prev = node;
        size++;
    }
    void removeNode(BiListNode* node) {
        if (node == fake) return;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size_--;
    }
public:
    class Iterator {
    private:
        BiListNode* current;
        BiListNode* fake;
    public:
        Iterator(BiListNode* node = nullptr, BiListNode* fakeNode = nullptr)
            : current(node), fake(fakeNode) {}
        T& operator*() {
            if (!current || current == fake) {
                throw std::runtime_error("Dereferencing invalid iterator");
            }
            return current->value;
        }
        T* operator->() {
            if (!current || current == fake) {
                throw std::runtime_error("Accessing invalid iterator");
            }
            return &(current->value);
        }
        Iterator& operator++() {
            if (current) {
                current = current->next;
                if (current == fake) {
                    current = nullptr;
                }
            }
            return *this;
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        Iterator& operator--() {
            if (!current) {
                current = fake->prev;
            } else {
                current = current->prev;
                if (current == fake) {
                    current = nullptr;
                }
            }
            return *this;
        }
        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
        friend class BiList<T>;
    };
    BiList() : size_(0) {
        fake = new BiListNode(true);
    }
    BiList(const BiList& other) : size_(0) {
        fake = new BiListNode(true);
        for (const T& val : other) {
            push_back(val);
        }
    }
    BiList(BiList&& other) noexcept
        : fake(other.fake), size_(other.size_) {
        other.fake = nullptr;
        other.size_ = 0;
    }
    BiList(std::initializer_list<T> init) : size_(0) {
        fake = new BiListNode(true);
        for (const T& val : init) {
            push_back(val);
        }
    }
    ~BiList() {
        clear();
        delete fake;
    }
    BiList& operator=(const BiList& other) {
        if (this != &other) {
            clear();
            for (const T& val : other) {
                push_back(val);
            }
        }
        return *this;
    }
    BiList& operator=(BiList&& other) noexcept {
        if (this != &other) {
            clear();
            delete fake;
            fake = other.fake;
            size = other.size;
            other.fake = new BiListNode(true);
            other.size_ = 0;
        }
        return *this;
    }
    void push_front(const T& value) {
        BiListNode* node = createNode(value);
        insertBetween(node, fake, fake->next);
    }
    void push_back(const T& value) {
        BiListNode* node = createNode(value);
        insertBetween(node, fake->prev, fake);
    }
    void pop_front() {
        if (!empty()) {
            removeNode(fake->next);
        }
    }
    void pop_back() {
        if (!empty()) {
            removeNode(fake->prev);
        }
    }
    Iterator insert(Iterator position, const T& value) {
        if (position == end()) {
            push_back(value);
            return Iterator(fake->prev, fake);
        }
        BiListNode* node = createNode(value);
        BiListNode* posNode = position.current;
        insertBetween(node, posNode->prev, posNode);
        return Iterator(node, fake);
    }
    Iterator erase(Iterator position) {
        if (position == end() || empty()) {
            return end();
        }
        BiListNode* nextNode = position.current->next;
        if (nextNode == fake) {
            nextNode = nullptr;
        }
        removeNode(position.current);
        return Iterator(nextNode, fake);
    }
    T& front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return fake->next->value;
    }
    const T& front() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return fake->next->value;
    }
    T& back() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return fake->prev->value;
    }
    const T& back() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return fake->prev->value;
    }
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    Iterator find(const T& value) const {
        BiListNode* current = fake->next;
        while (current != fake) {
            if (current->value == value) {
                return Iterator(current, fake);
            }
            current = current->next;
        }
        return end();
    }
    Iterator begin() {
        return empty() ? end() : Iterator(fake->next, fake); 
    }
    Iterator end() {
        return Iterator(nullptr, fake);
    }
    Iterator rbegin() {
        return empty() ? rend() : Iterator(fake->prev, fake); 
    }
    Iterator rend() {
        return Iterator(nullptr, fake);
    }
    void reverse() {
        if (size_ < 2) return;
        BiListNode* current = fake->next;
        BiListNode* temp = nullptr;
        while (current != fake) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        temp = fake->next;
        fake->next = fake->prev;
        fake->prev = temp;
    }
    void unique() {
        if (size_ < 2) return;
        BiListNode* current = fake->next;
        while (current != fake && current->next != fake) {
            if (current->value == current->next->value) {
                BiListNode* toDelete = current->next;
                removeNode(toDelete);
            } else {
                current = current->next;
            }
        }
    }
    void sort() {
        if (size_ < 2) return;
        T* tempArray = new T[size_];
        size_t i = 0;
        for (Iterator it = begin(); it != end(); ++it) {
            tempArray[i++] = *it;
        }
        std::sort(tempArray, tempArray + size_);
        clear();
        for (size_t i = 0; i < size_; ++i) {
            push_back(tempArray[i]);
        }
        delete[] tempArray;
    }
    bool isValid() const {
        if (fake->next->prev != fake || fake->prev->next != fake) {
            return false;
        }
        size_t count = 0;
        BiListNode* current = fake->next;
        while (current != fake && count <= size_) {
            if (current->next->prev != current) {
                return false;
            }
            if (current->prev->next != current) {
                return false;
            }
            current = current->next;
            count++;
        }
        return count == size_;
    }
};

