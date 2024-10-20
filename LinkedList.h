#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Sequence.h"
#include <memory>
#include <stdexcept>

#define EMPTY "LinkedList is empty"
#define OUT_OF_RANGE "Index out of range"
#define SUBSEQ_ERR "Invalid subsequence indices"

template <typename T>
class LinkedList : public Sequence<T> {
private:
    struct Node {
        std::shared_ptr<T> data;
        std::shared_ptr<Node> next;

        explicit Node(const T& item) : data(std::make_shared<T>(item)), next(nullptr) {}
    };

    std::shared_ptr<Node> head;
    size_t length;

public:

    LinkedList() : head(nullptr), length(0) {}


    ~LinkedList() override {
    }


    T GetFirst() const override {
        if (!head)
            throw std::out_of_range(EMPTY);
        return *(head->data);
    }

    T GetLast() const override {
        if (!head)
            throw std::out_of_range(EMPTY);
        std::shared_ptr<Node> current = head;
        while (current->next) {
            current = current->next;
        }
        return *(current->data);
    }

    T Get(int index) const override {
        if (index < 0 || index >= length)
            throw std::out_of_range(OUT_OF_RANGE);
        std::shared_ptr<Node> current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return *(current->data);
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
            throw std::out_of_range(SUBSEQ_ERR);

        auto* subseq = new LinkedList<T>();
        std::shared_ptr<Node> current = head;
        for (int i = 0; i <= endIndex; ++i) {
            if (i >= startIndex) {
                subseq->Append(*(current->data));
            }
            current = current->next;
        }
        return subseq;
    }

    int GetLength() const override {
        return length;
    }

    void Append(const T& item) override {
        auto newNode = std::make_shared<Node>(item);
        if (!head) {
            head = std::move(newNode);
        } else {
            std::shared_ptr<Node> current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = std::move(newNode);
        }
        ++length;
    }

    void Prepend(const T& item) override {
        auto newNode = std::make_shared<Node>(item);
        newNode->next = std::move(head);
        head = std::move(newNode);
        ++length;
    }

    void InsertAt(const T& item, int index) override {
        if (index < 0 || index > length)
            throw std::out_of_range(OUT_OF_RANGE);
        if (index == 0) {
            Prepend(item);
        } else {
            std::shared_ptr<Node> current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            auto newNode = std::make_shared<Node>(item);
            newNode->next = std::move(current->next);
            current->next = std::move(newNode);
            ++length;
        }
    }

    Sequence<T>* Concat(Sequence<T>* list) const override {
        auto* newList = new LinkedList<T>();
        std::shared_ptr<Node> current = head;
        while (current) {
            newList->Append(*(current->data));
            current = current->next;
        }
        for (int i = 0; i < list->GetLength(); ++i) {
            newList->Append(list->Get(i));
        }
        return newList;
    }
};

#endif // LINKEDLIST_H
