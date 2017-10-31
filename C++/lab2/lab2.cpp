#include "lab2.h"

namespace adt {

    template <typename T>
        ArraySequence<T>& ArraySequence<T>::operator=(const ArraySequence &a) {
            if (this != &a) {
                n = a.n;
                delete[] items;
                items = new T[n];
                for (int i = 0; i < n; i++)
                    items[i] = a.items[i];
            }
            return *this;
        }

    template <typename T>
        ArraySequence<T>& ArraySequence<T>::operator=(ArraySequence &&a) {
            n = a.n;
            T *temp = items;
            items = a.items;
            a.items = temp;
            return *this;
        }

    template <typename T>
        ArraySequence<T> ArraySequence<T>::get_Subsequence(const int startind, const int endind) const {
            if (!n)
                throw std::runtime_error("empty sequence");
            else if (endind > startind || startind >= n || endind >= n)
                throw std::runtime_error("incorrect index");
            ArraySequence temp;
            for (int i = startind; i <= endind; i++)
                temp.append(items[i]);
            return temp;
        }

    template <typename T>
        void ArraySequence<T>::append(const T item) {
            T *temp = items;
            items = new T[n + 1];
            for (int i = 0; i < n; i++)
                items[i] = temp[i];
            items[n++] = item;
            delete[] temp;
        }

    template <typename T>
        void ArraySequence<T>::prepend(const T item) {
            T *temp = items;
            items = new T[n + 1];
            for (int i = 0; i < n; i++)
                items[i + 1] = temp[i];
            items[0] = item;
            n++;
            delete[] temp;
        }

    template <typename T>
        void ArraySequence<T>::insert(const int ind, const T item) {
            if (ind < 0 || ind > n)
                throw std::runtime_error("incorrect index");
            T *temp = items;
            items = new T[++n];
            for (int i = 0; i < ind; i++)
                items[i] = temp[i];
            items[ind] = item;
            for (int i = ind + 1; i < n; i++)
                items[i] = temp[i];
            delete[] temp;
        }

    template <typename T>
        void ArraySequence<T>::remove(const T item) {
            int nn = n;
            for (int i = 0; i < n; i++)
                if (items[i] == item)
                    --nn;
            if (nn == n)
                return;
            T *temp = items;
            items = new T[nn];
            nn = 0;
            for (int i = 0; i < n; i++)
                if (temp[i] != item)
                    items[n++] = temp[i];
            n = nn;
            delete[] temp;
        }

    template <typename T>
        const T* ArraySequence<T>::sort_Insertion() {
            for (int i = 1; i < n; i++) {
                T temp = items[i]; 
                int j = i - 1;
                while (j >= 0 && items[j] > temp)
                    items[j + 1] = items[j--];
                items[j + 1] = temp;
            }
            return items;
        }

    template <typename T>
        void merge(int left, int middle, int middle1, int right) {
            int leftind = left;
            int rightind = middle1;
            ArraySequence<T> temp;
            while (leftind <= middle && rightind <= right) {
                if (ArraySequence<T>::items[leftind] <= ArraySequence<T>::items[rightind])
                    temp.append(ArraySequence<T>::items[leftind++]);
                else temp.append(ArraySequence<T>::items[rightind++]);
            }
            if (leftind == middle1) {
                while (rightind <= right)
                    temp.append(ArraySequence<T>::items[rightind++]);
            } else {
                while (leftind <= middle)
                    temp.append(ArraySequence<T>::items[leftind++]);
            }
            for (int i = left; i <= right; i++)
                ArraySequence<T>::items[i] = temp.items[i];
        }

    template <typename T>
        void sort_Subsequence(int low, int high) {
            if ((high - low) < 1)
                return;
            int middle = (low + high) / 2;
            int middle1 = middle + 1;
            sort_Subsequence<T>(low, middle);
            sort_Subsequence<T>(middle1, high);
            merge<T>(low, middle, middle1, high);
        }

    template <typename T>
        const T* ArraySequence<T>::sort_Merge() {
            sort_Subsequence<T>(0, ArraySequence<T>::n - 1);
            return ArraySequence<T>::items;
        }

    template <typename T>
        ListSequence<T>& ListSequence<T>::operator=(const ListSequence<T> &a) {
            if (this != &a) {
                n = a.n;
                node<T> *current, *temp;
                current = temp = head;
                while (temp) {
                    current = current->next;
                    delete temp;
                    temp = current;
                }
                head = nullptr;
                for (current = a.head; current; current = current->next)
                    append(current->item);
            }
            return *this;
        }

    template <typename T>
        ListSequence<T>& ListSequence<T>::operator=(ListSequence<T> &&a) {
            n = a.n;
            node<T> temp = head;
            head = a.head;
            a.head = head;
            return *this;
        }
    
    template <typename T>
        ListSequence<T>::~ListSequence<T>() {
            node<T> *current, *temp;
            current = temp = head;
            while (temp) {
                current = current->next;
                delete temp;
                temp = current;
            }
        }

    template <typename T>
        ListSequence<T> ListSequence<T>::get_Subsequence(const int startind, const int endind) const {
            if (!n)
                throw std::runtime_error("empty sequence");
            else if (endind > startind || startind >= n || endind >= n)
                throw std::runtime_error("incorrect index");
            ListSequence<T> temp;
            for (node<T> *current = head; current->ind <= endind; current = current->next) 
                if (current->ind >= startind)
                    temp.append(current->item);
            return temp;
        }

    template <typename T>
        void ListSequence<T>::append(const T item) {
            if (!head) {
                head = new node<T>(item);
            } else {
                node<T> *temp = head;
                for (; temp->next; temp = temp->next);
                temp->next = new node<T>(item, temp->ind + 1, temp);
            }
            n++;
        }

    template <typename T>
        void ListSequence<T>::prepend(const T item) {
            if (!head) {
                head = new node<T>(item);
            } else {
                node<T> *temp = new node<T>(item);
                temp->next = head;
                head->prev = temp;
                for (node<T> *current = head; current; current = current->next)
                    current->ind++;
                head = temp;
            }
            n++;
        }

    template <typename T>
        void ListSequence<T>::insert(const int ind, const T item) {
            if (ind < 0 || ind > n)
                throw std::runtime_error("incorrect index");
            if (!head) {
                head = new node<T>(item);
            } else {
                node<T> *current = head;
                for (; current->ind != ind; current = current->next);
                node<T> *temp = new node<T>(item, ind, current->prev, current);
                current->prev->next = temp;
                current->prev = temp;
                for (; current; current = current->next)
                    current->ind++;
            }
            n++;
        }

    template <typename T>
        void ListSequence<T>::remove(const T item) {
            node<T> *temp;
            for (temp = head; temp->item != item || temp; temp = temp->next);
            if (!temp)
                return;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            --n;
        }

    template <typename T>
        void ListSequence<T>::sort_Insertion() {
            for (node<T> *i = head->next; i; i = i->next) {
                T temp = i->item;
                node<T> *j = i->prev, *prev = j;
                while (j && j->item > temp) {
                    j->next->item = j->item;
                    prev = j;
                    j = j->prev;
                } 
                prev->item = temp;
            }
        }

    template <typename T>
        node<T>* merge(node<T> *a, node<T> *b) {
            node<T> *res = nullptr;
            if (!a) 
                return b;
            else if (!b)
                return a;
            if (a->item <= b->item) {
                res = a;
                res->next = merge(a->next, b);
            } else {
                res = b;
                res->next = merge(a, b->next);
            }
            return res;
        }

    template <typename T>
        void split(node<T> *p, node<T> **pfront, node<T> **pback) {
            node<T> *fast, *slow;
            if (!p || !p->next) {
                *pfront = p;
                *pback = nullptr;
            } else {
                slow = p;
                fast = p->next;
                while (fast) {
                    fast = fast->next;
                    if (fast) {
                        slow = slow->next;
                        fast = fast->next;
                    }
                }
                *pfront = p;
                *pback = slow->next;
                slow->next = nullptr;
            }
        }

    template <typename T>
        void MergeSort(node<T> **phead) {
            node<T> *head = *phead, *a, *b;
            if (!head || !head->next)
                return;
            split(head, &a, &b);
            MergeSort(&a);
            MergeSort(&b);
            *phead = merge(a, b);
        }

}
