template<class T>
class BiList {
private:
    BiListNode<T>* fake;
    size_t size;
    BiListNode<T>* createNode(const T& value);
    void insertBetween(BiListNode<T>* node, BiListNode<T>* prev, BiListNode<T>* next);
    void removeNode(BiListNode<T>* node);
public:
    class Iterator {
    private:
        BiListNode<T>* current;
        BiListNode<T>* fake;
    public:
        Iterator(BiListNode<T>* node, BiListNode<T>* fakeNode);
        T& operator*();
        T* operator->();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };
    BiList();
    BiList(const BiList& other);
    BiList(BiList&& other) noexcept;
    BiList(std::initializer_list<T> init);
    ~BiList();
    BiList& operator=(const BiList& other);
    BiList& operator=(BiList&& other) noexcept;
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    Iterator insert(Iterator position, const T& value);
    Iterator erase(Iterator position);
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    size_t size() const;
    bool empty() const;
    void clear();
    Iterator find(const T& value) const;
    Iterator begin();
    Iterator end();
    Iterator rbegin();
    Iterator rend();
    void reverse();
    void unique();
    void sort();
    bool isValid() const;
};

