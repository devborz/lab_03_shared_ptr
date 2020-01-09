#pragma once

#include <atomic>
#include <iostream>

template <typename T>
class shared_ptr {
 public:
  shared_ptr() = default;
  shared_ptr(T* ptr);
  shared_ptr(const shared_ptr& r);
  shared_ptr(shared_ptr&& r);
  ~shared_ptr();
  shared_ptr<T>& operator=(const shared_ptr& r);
  shared_ptr<T>& operator=(shared_ptr&& r);
  operator bool() const;
  T& operator*();
  T* operator->();
  T* release();
  T* get();
  void reset(T* ptr = nullptr);
  void swap(shared_ptr& r);
  std::atomic_uint* use_count();

 private:
  T* pointer_;
  std::atomic_uint* use_count_;
};

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) {
  this->pointer_ = ptr;
  this->use_count_ = new std::atomic_uint(1);
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& r) {  // констурктор копирования
  this->pointer_ = r.pointer_;
  this->use_count_ = r.use_count_;
  ++*this->use_count_;
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& r) {  // констурктор перемещения
  this->swap(r);
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
  this->reset();
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& r) {
  shared_ptr(r).swap(*this);  // создает временный указатель shared,
  // который копирует r, меняет значение this с ним
  return *this;  // возвращает полученное значение
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& r) {
  shared_ptr(std::move(r)).swap(*this);  // создает временный указатель shared,
  // который копирует r, меняет значение this с ним
  return *this;  // возвращает полученное значение
}

template <typename T>
shared_ptr<T>::operator bool() const {
  return (this->pointer_ != nullptr);
  // проверяет, указывает ли указатель на объект
}

template <typename T>
T& shared_ptr<T>::operator*() {
  return *this->pointer_;  // возвращает значение по ссылке
}

template <typename T>
T* shared_ptr<T>::operator->() {
  return this->pointer_;  // возвращает указатель
}

template <typename T>
T* shared_ptr<T>::release() {
  auto temp = shared_ptr(*this);  // сохраняет указатель
  this->reset();                  // сбрасывает shared_ptr
  return temp.get();              // возвращает указатель
}

template <typename T>
T* shared_ptr<T>::get() {
  return this->pointer_;  // возвращает указатель на объект
}

template <typename T>
void shared_ptr<T>::reset(T* ptr) {
  // если this указывает на объект, уменьшает значение счетчика
  if (this->use_count_ != nullptr)
    if (*this->use_count_ == 1) {
      delete this->use_count_;
      delete this->pointer_;
    } else {
      --*this->use_count_;
    }

  this->pointer_ = ptr;

  if (ptr != nullptr) this->use_count_ = new std::atomic_uint{1};
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr& r) {
  std::swap(this->pointer_, r.pointer_);
  std::swap(this->use_count_, r.use_count_);
}

template <typename T>
std::atomic_uint* shared_ptr<T>::use_count() {
  return this->use_count_;  // возвращает значение счетчика
}
