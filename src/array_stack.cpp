#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

using namespace std;

namespace assignment {

    ArrayStack::ArrayStack(int capacity) {
        if (capacity <= 0) {
            throw invalid_argument("capacity is not positive");
        }
        data_ = new int[capacity];
        fill(data_, data_ + capacity, 0);
        capacity_ = capacity;
    }

    ArrayStack::~ArrayStack() {
        size_ = capacity_ = 0;
        data_ = nullptr;
    }

    void ArrayStack::Push(int value) {
        if(size_ == capacity_) {
            capacity_ += kCapacityGrowthCoefficient;
            int *lol = new int[capacity_];
            fill(lol, lol + capacity_, 0);
            for(int i = 0; i < size_; i++) lol[i] = data_[i];
            data_ = lol;
        }
        data_[size_++] = value;
    }

    bool ArrayStack::Pop() {
        if(size_ == 0) return false;
        size_--;
        data_[size_] = 0;
        return true;
    }

    void ArrayStack::Clear() {
        size_ = 0;
        fill(data_, data_ + capacity_, 0);
    }

    std::optional<int> ArrayStack::Peek() const {
        if(size_ == 0) return std::nullopt;
        return data_[size_ - 1];
    }

    bool ArrayStack::IsEmpty() const {
        return (size_ == 0);
    }

    int ArrayStack::size() const {
        return size_;
    }

    int ArrayStack::capacity() const {
        return capacity_;
    }

    bool ArrayStack::Resize(int new_capacity) {
        if(new_capacity <= capacity_) return false;
        int *lol = new int[new_capacity];
        copy(data_, data_ + capacity_, lol);
        capacity_ = new_capacity;
        data_ = lol;
        return true;
    }

    // ДЛЯ ТЕСТИРОВАНИЯ
    ArrayStack::ArrayStack(const std::vector<int> &values, int capacity) {

        size_ = static_cast<int>(values.size());
        capacity_ = capacity;

        data_ = new int[capacity]{};

        std::copy(values.data(), values.data() + size_, data_);
    }

    std::vector<int> ArrayStack::toVector(std::optional<int> size) const {

        if (capacity_ == 0 || data_ == nullptr) {
            return {};
        }

        if (size.has_value()) {
            return {data_, data_ + size.value()};
        }

        return {data_, data_ + capacity_};
    }

}  // namespace assignment
