#include <iostream>
#include <exception>

namespace adt {

    template <typename T> 
        class Sequence {
            virtual int get_Length() const = 0;
            virtual bool is_Empty() const = 0;
            virtual T get(const int ind) const = 0;
            virtual T get_First() const = 0;
            virtual T get_Last() const = 0;
            virtual void append(const T item) = 0;
            virtual void prepend(const T item) = 0;
            virtual void insert(const int ind, const T item) = 0;
            virtual void remove(const T item) = 0;
        };

    template <typename T>
        class ArraySequence : public Sequence<T> {
            private:
                int n;
                T *items;
            public:
                ArraySequence<T>() : n(0), items(nullptr) {};
                ArraySequence<T>(const T item) : n(1), items(new T[1]) {
                    items[0] = item;
                }
                ArraySequence<T>(const ArraySequence<T> &a) : n(a.n), items(new T[a.n]) {
                    for (int i = 0; i < n; i++)
                        items[i] = a.items[i];
                }
                ArraySequence<T>(ArraySequence<T> &&a) : n(a.n), items(a.items) {
                    a.items = nullptr;
                }
                ArraySequence<T>& operator=(const ArraySequence<T>&);
                ArraySequence<T>& operator=(ArraySequence<T>&&);
                ~ArraySequence<T>() {
                    delete[] items;
                }
                int get_Length() const {
                    return n;
                }
                bool is_Empty() const {
                    if (!n)
                        return true;
                    else return false;
                }
                T get(const int ind) const {
                    if (ind < 0 || ind >= n)
                        throw std::runtime_error("incorrect index");
                    else return items[ind];
                }
                T get_First() const {
                    if (!n)
                        throw std::runtime_error("empty sequence");
                    else return items[0];
                }
                T get_Last() const {
                    if (!n)
                        throw std::runtime_error("empty sequence");
                    else return items[n - 1];
                }
                ArraySequence<T> get_Subsequence(const int, const int) const;
                void append(const T);
                void prepend(const T);
                void insert(const int, const T);
                void remove(const T);
        };


    template <typename T>
        struct node {
            T item;
            int ind;
            node *prev, *next;
            node<T>(T item, int ind = 0, node<T> *prev = nullptr, node<T> *next = nullptr) : item(item), ind(ind), prev(prev), next(next) {};
        };

    template <typename T>
        class ListSequence : public Sequence<T> {
            private:
                int n;
                node<T> *head;
            public:
                ListSequence<T>() : n(0), head(nullptr) {};
                ListSequence<T>(const T item) : n(1), head(new node<T>(item)) {};
                ListSequence<T>(const ListSequence<T> &a) : n(0), head(nullptr) {
                    for (node<T> *temp = a.head; temp; temp = temp->next)
                        append(temp->item);
                }
                ListSequence<T>(ListSequence<T> &&a) : n(a.n), head(a.head) {
                    a.head = nullptr;
                }
                ListSequence<T>& operator=(const ListSequence<T>&);
                ListSequence<T>& operator=(ListSequence<T>&&);
                ~ListSequence<T>();
                int get_Length() const {
                    return n;
                }
                bool is_Empty() const {
                    if (!n)
                        return true;
                    else return false;
                }
                T get(const int ind) const {
                    if (ind < 0 || ind >= n)
                        throw std::runtime_error("incorrect index");
                    node<T> *temp = head;
                    for (; temp->ind != ind; temp = temp->next);
                    return temp->item;
                }
                T get_First() const {
                    if (!n)
                        throw std::runtime_error("empty sequence");
                    else return head->item;
                }
                T get_Last() const {
                    if (!n)
                        throw std::runtime_error("empty sequence");
                    node<T> *temp = head;
                    for (; temp->next; temp = temp->next);
                    return temp->item;
                }
                ListSequence<T> get_Subsequence(const int, const int) const;
                void append(const T);
                void prepend(const T);
                void insert(const int, const T);
                void remove(const T);
        };

}
