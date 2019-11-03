#include <iostream>
#include "SharedPtr.h"

using std::cout;
using std::cin;

int main() {
    int x = 2;
    int y = 4;
    int z = 8;

    SharedPtr<int> ptr1(&x);
    SharedPtr<int> ptr2(&y);
    SharedPtr<int> ptr3(ptr2);
    SharedPtr<int> ptr4;
    try {
        cout << "\nPtr1 cnt = " << *ptr1.use_count();
        cout << "\nPtr2 cnt = " << *ptr2.use_count();
        cout << "\nPtr3 cnt = " << *ptr3.use_count();

        ptr1.swap(ptr2);

        cout << "\n\nptr1 and ptr2 swap:\n";
        cout << "\nPtr1 = " << *ptr1.get();
        cout << "\nPtr2 = " << *ptr2.get();
        cout << "\nPtr3 = " << *ptr3.get();

        cout << "\n\nptr3 reset for z:\n";
        ptr3.reset(&z);
        cout << "\nPtr3 = " << *ptr3.get();

        cout << "\n\nDefine of ptr4:\n";
        ptr4 = ptr3;
        cout << "\nPtr4 = " << *ptr4.get();
        cout << "\nPtr3 = " << *ptr3.get();
    }
    catch (std::exception e) {
        cout << "\n" << e.what();
    }
}