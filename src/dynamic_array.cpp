#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

using namespace std;

namespace assignment {

    DynamicArray::DynamicArray(int capacity) {
        if (capacity <= 0) {
            throw std::invalid_argument("capacity is not positive");
        }
        data_ = new int[capacity];
        fill(data_, data_ + capacity, 0);
        capacity_ = capacity;
    }

    DynamicArray::~DynamicArray() {
        size_ = capacity_ = 0;
        data_ = nullptr;
    }

    void DynamicArray::Add(int value) {
        if(data_ == nullptr) {
            data_ = new int[kInitCapacity];
            fill(data_, data_ + kInitCapacity, 0);
        }
        if(size_ == capacity_) {
            capacity_ += kCapacityGrowthCoefficient;
            int *lol = new int[capacity_];
            fill(lol, lol + capacity_, 0);
            for(int i = 0; i < size_; i++) lol[i] = data_[i];
            data_ = lol;
        }
        data_[size_++] = value;
    }

    bool DynamicArray::Insert(int index, int value) {
        if(index < 0 || size_ < index) return false;
        if(data_ == nullptr) {
            data_ = new int[kInitCapacity];
            fill(data_, data_ + kInitCapacity, 0);
        }
        if(size_ == capacity_) {
            capacity_ += kCapacityGrowthCoefficient;
            int *lol = new int[capacity_];
            fill(lol, lol + capacity_, 0);
            for(int i = 0; i < size_; i++) lol[i] = data_[i];
            data_ = lol;
        }
        int *lol = new int[capacity_];
        for(int i = 0; i < index; i++) lol[i] = data_[i];
        lol[index] = value;
        for(int i = index; i < size_; i++) lol[i + 1] = data_[i];
        size_++;
        data_ = lol;
        return true;
    }

    bool DynamicArray::Set(int index, int new_value) {
        if(index < 0 || size_ <= index) return false;
        data_[index] = new_value;
        return true;
    }

    std::optional<int> DynamicArray::Remove(int index) {
        if(index < 0 || size_ <= index) return nullopt;
        int res = data_[index];
        data_[index] = 0;
        for(int i = index + 1; i < size_; i++) data_[i - 1] = data_[i];
        size_--;
        return res;
    }

    void DynamicArray::Clear() {
        size_ = 0;
        fill(data_, data_ + capacity_, 0);
    }

    std::optional<int> DynamicArray::Get(int index) const {
        if(index < 0 || size_ <= index) return nullopt;
        return data_[index];
    }

    std::optional<int> DynamicArray::IndexOf(int value) const {
        for(int i = 0; i < size_; i++) {
            if(data_[i] == value) return i;
        }
        return nullopt;
    }

    bool DynamicArray::Contains(int value) const {
        for(int i = 0; i < size_; i++) if(data_[i] == value) return true;
        return false;
    }

    bool DynamicArray::IsEmpty() const {
        return (size_ == 0);
    }

    int DynamicArray::size() const {
        return size_;
    }

    int DynamicArray::capacity() const {
        return capacity_;
    }

    bool DynamicArray::Resize(int new_capacity) {
        if(new_capacity <= capacity_) return false;
        int *lol = new int[new_capacity];
        fill(lol, lol + new_capacity, 0);
        copy(data_, data_ + capacity_, lol);
        capacity_ = new_capacity;
        data_ = lol;
        return true;
    }

    // ДЛЯ ТЕСТИРОВАНИЯ
    DynamicArray::DynamicArray(const std::vector<int> &values, int capacity) {

        size_ = static_cast<int>(values.size());
        capacity_ = capacity;

        data_ = new int[capacity]{};

        std::copy(values.data(), values.data() + size_, data_);
    }

    std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

        if (capacity_ == 0 || data_ == nullptr) {
            return {};
        }

        if (size.has_value()) {
            return {data_, data_ + size.value()};
        }

        return {data_, data_ + capacity_};
    }

}  // namespace assignment