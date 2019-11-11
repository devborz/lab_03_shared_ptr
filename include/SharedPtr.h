//
// Created by devborz on 14.10.2019.
//

#pragma once

#include <iostream>
#include <atomic>

using std::atomic_uint;

template <typename T>
class SharedPtr {
private:
    T* ptr;
    atomic_uint* cnt_of_use;

public:

    SharedPtr();
    SharedPtr(T* ptr);
    SharedPtr(SharedPtr& r);
    SharedPtr(SharedPtr&& r);
    ~SharedPtr();
    auto operator=(const SharedPtr& r)->SharedPtr&;
    auto operator=(SharedPtr&& r)->SharedPtr&;

    // проверяет, указывает ли указатель на объект
    operator bool() const;
    auto operator*() const->T&;
    auto operator->() const->T*;

    auto get()->T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);
    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    atomic_uint* use_count();
};

template <typename T>
SharedPtr<T>::SharedPtr() {
    cnt_of_use = nullptr;
    ptr = nullptr;
}



template <typename T>
SharedPtr<T>::SharedPtr(T * ptr) {
    this->ptr = ptr;
    this->cnt_of_use = new atomic_uint(1);
}


template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr & r) {
    this->ptr = r.ptr;
    this->cnt_of_use = r.cnt_of_use;
    ++*this->cnt_of_use;
}


template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr && r) {
    this->ptr = std::move(r).ptr;
    this->cnt_of_use = std::move(r).cnt_of_use;
    ++*this->cnt_of_use;
}


template <typename T>
SharedPtr<T>::~SharedPtr() {
    this->reset();
};



template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr & r) -> SharedPtr& {
    if (this->cnt_of_use != nullptr) --*this->cnt_of_use;

    this->ptr = std::move(r).ptr;
    this->cnt_of_use = std::move(r).cnt_of_use;

    ++*this->cnt_of_use;
    
    return *this;
}


template <typename T>
auto SharedPtr<T>::operator=(SharedPtr && r) -> SharedPtr& {
    if (this->cnt_of_use != nullptr) --*this->cnt_of_use;

    this->ptr = std::move(r).ptr;
    this->cnt_of_use = std::move(r).cnt_of_use;

    ++*this->cnt_of_use;

    return *this;
}


// проверяет, указывает ли указатель на объект
template <typename T>
SharedPtr<T>::operator bool() const {
    return (this->ptr != nullptr);
}


template <typename T>
auto SharedPtr<T>::operator*() const -> T& {
    return *this->ptr;
}


template <typename T>
auto SharedPtr<T>::operator->() const -> T* {
    return this->ptr;
}


template <typename T>
auto SharedPtr<T>::get() -> T* {
    return this->ptr;
}


template <typename T>
void SharedPtr<T>::reset() {
    if (this->cnt_of_use != nullptr) --*this->cnt_of_use;

    this->ptr = nullptr;
    this->cnt_of_use = nullptr;
}


template <typename T>
void SharedPtr<T>::reset(T * ptr) {
    if (this->cnt_of_use != nullptr) --*this->cnt_of_use;


    this->ptr = ptr;
    this->cnt_of_use = new atomic_uint{1};
}


template <typename T>
void SharedPtr<T>::swap(SharedPtr & r) {
    T* tmp1 = r.ptr;
    atomic_uint* tmp2 = r.cnt_of_use;
    r = *this;

    this->ptr = tmp1;
    this->cnt_of_use = tmp2;
}


// возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
template <typename T>
atomic_uint* SharedPtr<T>::use_count() {
    return this->cnt_of_use;
}
