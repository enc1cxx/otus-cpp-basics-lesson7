#pragma once
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <new>
#include <utility>

namespace vector {
template <typename T> class RawMemory {
public:
  RawMemory() = default;

  explicit RawMemory(size_t capacity)
      : buffer_(allocate(capacity)), capacity_(capacity) {}

  ~RawMemory() { deallocate(buffer_); }

  RawMemory(const RawMemory &) = delete;
  RawMemory &operator=(const RawMemory &rhs) = delete;

  RawMemory(RawMemory &&other) noexcept
      : buffer_(std::exchange(other.buffer_, nullptr)),
        capacity_(std::exchange(other.capacity_, 0)) {}

  RawMemory &operator=(RawMemory &&rhs) noexcept {
    if (this != &rhs) {
      buffer_ = std::move(rhs.buffer_);
      capacity_ = std::move(rhs.capacity_);
      rhs.buffer_ = nullptr;
      rhs.capacity_ = 0;
    }

    return *this;
  }

  T *operator+(size_t offset) noexcept {
    if (offset <= capacity_) {
      return buffer_ + offset;
    }
  }

  const T *operator+(size_t offset) const noexcept {
    return const_cast<RawMemory &>(*this) + offset;
  }

  const T &operator[](size_t index) const noexcept {
    return const_cast<RawMemory &>(*this)[index];
  }

  T &operator[](size_t index) {
    if (index < capacity_) {
      return buffer_[index];
    } else {
      throw std::out_of_range("Incorrect Index");
    }
  }

  void swap(RawMemory &other) noexcept {
    std::swap(buffer_, other.buffer_);
    std::swap(capacity_, other.capacity_);
  }

  const T *get_address() const noexcept { return buffer_; }
  T *get_address() noexcept { return buffer_; }
  size_t capacity() const { return capacity_; }

private:
  T *buffer_ = nullptr;
  size_t capacity_ = 0;

  static T *allocate(size_t n) {
    return n != 0 ? static_cast<T *>(operator new(n * sizeof(T))) : nullptr;
  }
  static void deallocate(T *buf) noexcept { operator delete(buf); }
};

template <typename T> class Vector {
public:
  using iterator = T *;
  using const_iterator = const T *;

  Vector() = default;

  explicit Vector(size_t size) : data_(size), size_(size) {
    std::uninitialized_value_construct_n(data_.get_address(), size);
  }

  Vector(const Vector &other) : data_(other.size_), size_(other.size_) {
    std::uninitialized_copy_n(other.data_.get_address(), size_,
                              data_.get_address());
  }

  Vector(Vector &&other) noexcept
      : data_(std::move(other.data_)), size_(std::exchange(other.size_, 0)) {}

  ~Vector() { std::destroy_n(data_.get_address(), size_); }

  iterator begin() noexcept { return data_.get_address(); }
  iterator end() noexcept { return size_ + data_.get_address(); }
  const_iterator cbegin() const noexcept { return data_.get_address(); }
  const_iterator cend() const noexcept { return size_ + data_.get_address(); }
  const_iterator begin() const noexcept { return cbegin(); }
  const_iterator end() const noexcept { return cend(); }

  size_t size() const noexcept { return size_; }
  size_t capacity() const noexcept { return data_.capacity(); }
  void swap(Vector &other) noexcept {
    data_.swap(other.data_), std::swap(size_, other.size_);
  }

  void reserve(size_t new_capacity) {
    if (new_capacity <= data_.capacity()) {
      return;
    }

    RawMemory<T> new_data(new_capacity);
    if constexpr (std::is_nothrow_move_constructible_v<T> ||
                  !std::is_copy_constructible_v<T>) {
      std::uninitialized_move_n(data_.getAddress(), size_,
                                new_data.getAddress());
    } else {
      std::uninitialized_copy_n(data_.getAddress(), size_,
                                new_data.getAddress());
    }
    std::destroy_n(data_.getAddress(), size_);
    data_.swap(new_data);
  }

  void resize(size_t new_size) {
    if (new_size < size_) {
      std::destroy_n(data_.getAddress() + new_size, size_ - new_size);
    } else {
      if (new_size > data_.capacity()) {
        const size_t new_capacity = std::max(data_.capacity() * 2, new_size);
        reserve(new_capacity);
      }
      std::uninitialized_value_construct_n(data_.getAddress() + size_,
                                           new_size - size_);
    }

    size_ = new_size;
  }

  void print() {
    if (size_ == 0) {
      std::cout << "Vector is empty" << std::endl;
      return;
    }
    for (auto it = this->begin(); it != this->end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }

  template <typename... Args> T &emplace_back(Args &&...args);

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  iterator insert(const_iterator pos, const T &item) {
    return emplace(pos, item);
  }
  iterator insert(const_iterator pos, T &&item) {
    return emplace(pos, std::move(item));
  }

  iterator erase(const_iterator pos) {
    if (pos >= begin() && pos < end()) {
      size_t position = pos - begin();

      std::move(begin() + position + 1, end(), begin() + position);
      std::destroy_at(end() - 1);
      size_ -= 1;

      return (begin() + position);
    } else {
      throw std::out_of_range("Incorrect Index");
    }
  }

  template <typename Type> void push_back(Type &&value);

  void pop_back() {
    if (size_) {
      std::destroy_at(data_.get_address() + size_ - 1);
      --size_;
    }
  }

  Vector &operator=(const Vector &other) {
    if (this != &other) {
      if (other.size_ <= data_.capacity()) {
        if (size_ <= other.size_) {
          std::copy(other.data_.getAddress(), other.data_.getAddress() + size_,
                    data_.getAddress());

          std::uninitialized_copy_n(other.data_.getAddress() + size_,
                                    other.size_ - size_,
                                    data_.getAddress() + size_);
        } else {
          std::copy(other.data_.getAddress(),
                    other.data_.getAddress() + other.size_, data_.getAddress());

          std::destroy_n(data_.getAddress() + other.size_, size_ - other.size_);
        }

        size_ = other.size_;

      } else {
        Vector other_copy(other);
        swap(other_copy);
      }
    }

    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    swap(other);
    return *this;
  }

  const T &operator[](size_t index) const noexcept {
    return const_cast<Vector &>(*this)[index];
  }
  T &operator[](size_t index) noexcept { return data_[index]; }

private:
  RawMemory<T> data_;
  size_t size_ = 0;
};

template <typename T>
template <typename Type>
void Vector<T>::push_back(Type &&value) {
  if (data_.capacity() <= size_) {
    RawMemory<T> new_data(size_ == 0 ? 1 : size_ * 2);

    new (new_data.get_address() + size_) T(std::forward<Type>(value));

    if constexpr (std::is_nothrow_move_constructible_v<T> ||
                  !std::is_copy_constructible_v<T>) {
      std::uninitialized_move_n(data_.get_address(), size_,
                                new_data.get_address());
    } else {
      std::uninitialized_copy_n(data_.get_address(), size_,
                                new_data.get_address());
    }

    std::destroy_n(data_.get_address(), size_);
    data_.swap(new_data);

  } else {
    new (data_.get_address() + size_) T(std::forward<Type>(value));
  }

  size_++;
}

template <typename T>
template <typename... Args>
T &Vector<T>::emplace_back(Args &&...args) {
  if (data_.capacity() <= size_) {
    RawMemory<T> new_data(size_ == 0 ? 1 : size_ * 2);

    new (new_data.getAddress() + size_) T(std::forward<Args>(args)...);

    if constexpr (std::is_nothrow_move_constructible_v<T> ||
                  !std::is_copy_constructible_v<T>) {
      std::uninitialized_move_n(data_.get_address(), size_,
                                new_data.get_address());
    } else {
      std::uninitialized_copy_n(data_.get_address(), size_,
                                new_data.get_address());
    }

    std::destroy_n(data_.get_address(), size_);
    data_.swap(new_data);

  } else {
    new (data_.get_address() + size_) T(std::forward<Args>(args)...);
  }

  return data_[size_++];
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos,
                                                Args &&...args) {
  if (pos >= begin() && pos <= end()) {
    size_t position = pos - begin();

    if (data_.capacity() <= size_) {
      RawMemory<T> new_data(size_ == 0 ? 1 : size_ * 2);

      new (new_data.get_address() + position) T(std::forward<Args>(args)...);

      if constexpr (std::is_nothrow_move_constructible_v<T> ||
                    !std::is_copy_constructible_v<T>) {
        std::uninitialized_move_n(data_.get_address(), position,
                                  new_data.get_address());
        std::uninitialized_move_n(data_.get_address() + position,
                                  size_ - position,
                                  new_data.get_address() + position + 1);

      } else {
        std::uninitialized_copy_n(data_.get_address(), position,
                                  new_data.get_address());
        std::uninitialized_copy_n(data_.get_address() + position,
                                  size_ - position,
                                  new_data.get_address() + position + 1);
      }

      std::destroy_n(data_.get_address(), size_);
      data_.swap(new_data);

    } else {
      try {
        if (pos != end()) {
          T new_s(std::forward<Args>(args)...);
          new (end()) T(std::forward<T>(data_[size_ - 1]));

          std::move_backward(begin() + position, end() - 1, end());
          *(begin() + position) = std::forward<T>(new_s);

        } else {
          new (end()) T(std::forward<Args>(args)...);
        }

      } catch (...) {
        operator delete(end());
        throw;
      }
    }

    size_++;
    return begin() + position;
  } else {
    throw std::out_of_range("Incorrect Index");
  }
}

template <typename T>
bool operator==(const Vector<T> &lhs, const Vector<T> &rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

} // end namespace vector