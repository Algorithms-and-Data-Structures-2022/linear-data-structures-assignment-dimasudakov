#include "assignment/linked_list.hpp"

using namespace std;

namespace assignment {

    LinkedList::~LinkedList() {

        // эквивалентно очистке списка
        LinkedList::Clear();
    }

    void LinkedList::Add(int value) {
        if(size_ == 0) {
            front_ = new Node(value, nullptr);
            back_ = front_;
            size_++;
            return;
        }
        Node *p = new Node(value);
        back_ -> next = p;
        back_ = p;
        size_++;
    }

    bool LinkedList::Insert(int index, int value) {
        if(index < 0 || size_ < index) return false;
        if(index == size_) {
            Add(value);
            return true;
        }
        if(index == 0) {
            Node *p = new Node(value);
            p -> next = front_;
            front_ = p;
            size_++;
            return true;
        }
        Node *p = front_;
        for(int i = 0; i < index - 1; i++) {
            p = p -> next;
        }
        Node *lol = new Node(value);
        lol -> next = p -> next;
        p -> next = lol;
        size_++;
        return true;
    }

    bool LinkedList::Set(int index, int new_value) {
        if(index < 0 || size_ <= index) return false;
        Node *cur = front_;
        for(int i = 0; i < index; i++) {
            cur = cur -> next;
        }
        cur -> value = new_value;
        return true;
    }

    std::optional<int> LinkedList::Remove(int index) {
        if(index < 0 || size_ <= index) return nullopt;
        if(size_ == 1) {
            int res = front_ -> value;
            Clear();
            return res;
        }
        if(index == 0) {
            size_--;
            int res = front_ -> value;
            Node *p = front_;
            front_ = front_ -> next;
            delete p;
            return res;
        }

        Node *p = front_;
        for(int i = 0; i < index - 1; i++) p = p -> next;

        int res = (p -> next) -> value;
        if(index == size_ - 1) {
            p -> next = nullptr;
            back_ = p;
            size_--;
            return res;
        }
        p -> next = (p -> next) -> next;
        size_--;
        return res;
    }

    void LinkedList::Clear() {
        Node *cur = front_;
        for(int i = 0; i < size_; i++) {
            if(i == size_ - 1) {
                delete cur;
                break;
            }
            Node* mem = cur -> next;
            delete cur;
            cur = mem;
        }
        back_ = front_ = nullptr;
        size_ = 0;
    }

    std::optional<int> LinkedList::Get(int index) const {
        if(index < 0 || size_ <= index) return nullopt;
        Node cur = *front_;
        for(int i = 0; i < index; i++) cur = *cur.next;
        return cur.value;
    }

    std::optional<int> LinkedList::IndexOf(int value) const {
        Node *cur = front_;
        for(int i = 0; i < size_; i++) {
            if(cur -> value == value) return i;
            cur = cur -> next;
        }
        return nullopt;
    }

    bool LinkedList::Contains(int value) const {
        Node *cur = front_;
        for(int i = 0; i < size_; i++) {
            if(cur -> value == value) return true;
            cur = cur -> next;
        }
        return false;
    }

    bool LinkedList::IsEmpty() const {
        return (size_ == 0);
    }

    int LinkedList::size() const {
        return size_;
    }

    std::optional<int> LinkedList::front() const {
        if(size_ == 0) return nullopt;
        return front_ -> value;
    }

    std::optional<int> LinkedList::back() const {
        if(size_ == 0) return nullopt;
        return back_ -> value;
    }

    Node *LinkedList::FindNode(int index) const {
        if(index < 0 || size_ <= index) return nullptr;
        Node* cur = front_;
        for(int i = 0; i < index; i++) {
            cur = (*cur).next;
        }
        return cur;
    }

    // ДЛЯ ТЕСТИРОВАНИЯ
    LinkedList::LinkedList(const std::vector<int> &values) {

        if (values.empty()) {
            return;
        }

        auto *curr_node = new Node(values.front());
        front_ = curr_node;

        for (int index = 1; index < values.size() - 1; ++index) {
            curr_node->next = new Node(values[index]);
            curr_node = curr_node->next;
        }

        if (values.size() == 1) {
            back_ = front_;
        } else {
            curr_node->next = new Node(values.back());
            back_ = curr_node->next;
        }

        size_ = static_cast<int>(values.size());
    }

    std::vector<int> LinkedList::toVector() const {

        if (front_ == nullptr || size_ == 0) {
            return {};
        }

        std::vector<int> array;
        array.reserve(size_);

        for (auto *node = front_; node != nullptr; node = node->next) {
            array.push_back(node->value);
        }

        return array;
    }

}  // namespace assignment