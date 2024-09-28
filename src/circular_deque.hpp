#ifndef CIRCULAR_DEQUE_H
#define CIRCULAR_DEQUE_H

#include <array>
#include <cstddef>
#include <new>
#include <stdexcept>
#include <type_traits>


namespace hsc_snippets {
    template<class T, size_t N>
    class CircularDeque {
    private:
        static_assert(N > 0, "CircularDeque capacity N must be greater than 0");

        using StorageType = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
        std::array<StorageType, N> arr;

        size_t front_index = 0;
        size_t rear_index = 0;
        size_t count = 0;

        // Helper to get a pointer to the element at index i
        T *element_ptr(size_t i) {
            return reinterpret_cast<T *>(&arr[i]);
        }

        const T *element_ptr(size_t i) const {
            return reinterpret_cast<const T *>(&arr[i]);
        }

    public:
        CircularDeque() = default;

        ~CircularDeque() {
            clear();
        }

        // Rest of the implementation remains similar, but with placement new and explicit destructor calls

        void push_back(const T &value) {
            if (full()) {
                throw std::overflow_error("CircularDeque is full");
            }
            new(&arr[rear_index]) T(value);
            rear_index = (rear_index + 1) % N;
            count++;
        }

        void push_back(T &&value) {
            if (full()) {
                throw std::overflow_error("CircularDeque is full");
            }
            new(&arr[rear_index]) T(std::move(value));
            rear_index = (rear_index + 1) % N;
            count++;
        }

        void push_front(const T &value) {
            if (full()) {
                throw std::overflow_error("CircularDeque is full");
            }
            front_index = (front_index + N - 1) % N;
            new(&arr[front_index]) T(value);
            count++;
        }

        void push_front(T &&value) {
            if (full()) {
                throw std::overflow_error("CircularDeque is full");
            }
            front_index = (front_index + N - 1) % N;
            new(&arr[front_index]) T(std::move(value));
            count++;
        }

        void pop_front() {
            if (empty()) {
                throw std::underflow_error("CircularDeque is empty");
            }
            element_ptr(front_index)->~T();
            front_index = (front_index + 1) % N;
            count--;
        }

        void pop_back() {
            if (empty()) {
                throw std::underflow_error("CircularDeque is empty");
            }
            rear_index = (rear_index + N - 1) % N;
            element_ptr(rear_index)->~T();
            count--;
        }

        T &front() {
            if (empty()) {
                throw std::underflow_error("CircularDeque is empty");
            }
            return *element_ptr(front_index);
        }

        const T &front() const {
            if (empty()) {
                throw std::underflow_error("CircularDeque is empty");
            }
            return *element_ptr(front_index);
        }

        T &back() {
            if (empty()) {
                throw std::underflow_error("CircularDeque is empty");
            }
            size_t index = (rear_index + N - 1) % N;
            return *element_ptr(index);
        }

        const T &back() const {
            if (empty()) {
                throw std::underflow_error("CircularDeque is empty");
            }
            size_t index = (rear_index + N - 1) % N;
            return *element_ptr(index);
        }

        void clear() {
            while (!empty()) {
                pop_back();
            }
            front_index = 0;
            rear_index = 0;
        }

        bool empty() const {
            return count == 0;
        }

        bool full() const {
            return count == N;
        }

        size_t size() const {
            return count;
        }
    };
}

#endif // CIRCULAR_DEQUE_H
