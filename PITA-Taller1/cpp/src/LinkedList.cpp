// Implementation of the generic linked list.
// In C++, template classes are usually defined in the header so the compiler
// can generate the correct code for each data type used.
// The definition is included here along with instantiation examples.

#include "LinkedList.h"

// Examples of types supported by the structure.
template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<std::string>;
