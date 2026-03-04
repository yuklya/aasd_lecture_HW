#include "BiList.h"
#include <iostream>
#include <string>

int main() {
    BiList<int> list1;
    list1.push_front(30);
    list1.push_front(20);
    list1.push_front(10);
    list1.push_back(40);
    list1.push_back(50);
    list1.pop_front();
    list1.pop_back();
    BiList<int> list2 = {1, 2, 3, 4, 5};
    BiList<int> list3 = list2;
    list3.clear();
    BiList<std::string> strList;
    strList.push_back("Hello");
    strList.push_back("World");
    strList.push_front("C++");
    BiList<int> emptyList;
    try {
        int value = emptyList.front();
    } catch (const std::out_of_range& e) {
    }
    return 0;
}

