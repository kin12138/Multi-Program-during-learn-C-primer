//
// Created by libin on 2025/6/9.
//

#include "SharedPointer.h"


template<typename T>
void SharedPointer<T>::decrement_and_destroy() {
    if (!ref_count) return;
    if (ptr && 0 == --*ref_count){
        delete ref_count;
        deleter(ptr);
    } else if( !ptr ) {
        delete ref_count;
    }
    ptr = ref_count = nullptr;
}