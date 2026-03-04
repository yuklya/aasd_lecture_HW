//var Loop + FAke
template<class T>
struct BiListNode {
    T value;
    BiListNode<T>* next;
    BiListNode<T>* prev;
    explicit BiListNode(const T& val = T(), BiListNode<T>* n = nullptr, BiListNode<T>* p = nullptr)
        : value(val), next(n), prev(p) {}
    explicit BiListNode(bool isFake)
        : value(T()), next(this), prev(this) {}
};

