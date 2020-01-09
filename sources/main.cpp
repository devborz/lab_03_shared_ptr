#include <iostream>
#include "shared_ptr.h"

using std::cin;
using std::cout;

int main() {
  shared_ptr<int> ptr1(new int{1});
  shared_ptr<int> ptr2(new int{2});
  shared_ptr<int> ptr3(ptr2);
  shared_ptr<int> ptr4;
  try {
    cout << "\nPtr1 = " << *ptr1.get() << " cnt = " << *ptr1.use_count();
    cout << "\nPtr2 = " << *ptr2.get() << " cnt = " << *ptr2.use_count();
    cout << "\nPtr3 = " << *ptr3.get() << " cnt = " << *ptr3.use_count();

    cout << "\n\nPtr3 was copied from Ptr2. Now we will reset Ptr2 to check"
         << " if Ptr3's сounter points to nowhere...\nRESETTING PTR2...";
    ptr2.reset();
    cout << "\nPtr3 = " << *ptr3.get() << " cnt = " << *ptr3.use_count();

    ptr1.swap(ptr3);

    cout << "\n\nPtr1 and Ptr3 swap:";
    cout << "\nPtr1 = " << *ptr1.get();
    cout << "\nPtr3 = " << *ptr3.get();

    cout << "\n\nPtr3 reset for new:\n";
    ptr3.reset(new int{5});
    cout << "Ptr3 = " << *ptr3.get() << " cnt = " << *ptr3.use_count();

    cout << "\n\nDefine of Ptr4 (Ptr4 = Ptr3):";
    ptr4 = ptr3;
    cout << "\nPtr4 = " << *ptr4.get() << " cnt = " << *ptr4.use_count();
    cout << "\nPtr3 = " << *ptr3.get() << " cnt = " << *ptr3.use_count()
         << std::endl;
  } catch (const std::exception& e) {
    cout << "\n" << e.what();
  }
}
