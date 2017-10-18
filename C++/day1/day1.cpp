#include <iostream>
#include "day1.h"

namespace kali {

    void list::add(int i, int j, int v) {
        node *mynode = new node(i, j, v);
        if (!head) {
            head = mynode;
        } else {
            node *current;
            for (current = head; current->next; current = current->next);
            current->next = mynode;
        }
        count++;
    }

    list::~list() {
        node *current, *mynode;
        current = mynode = head;
        while (mynode) {
            current = current->next;
            delete mynode;
            mynode = current;
        }
    }

    void list::sort() {
        for (node* i = head; i->next; i = i->next)
            for (node* j = i->next; j; j = j->next)
                if (j->i < i->i) {
                    std::swap(j->i, i->i);
                    std::swap(j->j, i->j);
                    std::swap(j->v, i->v);
                }
    }

    void list::print() {
        for (node* i = head; i; i = i->next)
            std::cout << i->i << " " << i->j << " " << i->v << std::endl;
    }

    bigmatrix* bigmatrix::map(int(*f)(int)) {
        bigmatrix *mymatrix = nullptr;
        try {
            mymatrix = new bigmatrix(n, m);
        } catch(std::bad_alloc &ba) {
            std::cout << "Something goes wrong... " << ba.what() << std::endl;
            return nullptr;
        }
        for (node *current = p->head; current; current = current->next)
            mymatrix->push(current->i, current->j, f(current->v));
        mymatrix->p->sort();
        return mymatrix;
    }

    void bigmatrix::print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                bool bl = false;
                for (node *current = p->head; current; current = current->next)
                    if (current->i == i && current->j == j) {
                        std::cout << current->v << " ";
                        bl = true;
                        break;
                    }
                if (!bl)
                    std::cout << "0 ";
            }
            std::cout << std::endl;
        }
    }

    bigmatrix* inputmatrix() {
        bigmatrix *mymatrix = nullptr;
        int n, m, v;
        const char *pr = "";
        do {
            std::cout << pr << std::endl;   
            std::cout << "Enter number of rows: ";
            pr = "You are wrong, repeat please!";
            if (!get_num(n))
                return nullptr;
        } while (n < 1 || n > 1000);
        pr = "";
        do {
            std::cout << pr << std::endl;   
            std::cout << "Enter number of columns: ";
            pr = "You are wrong, repeat please!";
            if (!get_num(m))
                return nullptr;
        } while (m < 1 || m > 1000);
        try {
            mymatrix = new bigmatrix(n, m);
        } catch (std::bad_alloc &ba) {
            std::cout << "Something goes wrong... " << ba.what() << std::endl;
            return nullptr;
        }
        std::cout << "\nEnter items of matrix:\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (!get_num(v)) {
                    mymatrix->~bigmatrix();
                    return nullptr;
                }
                //std::cout << "push " << i << " " << j << " " << v << std::endl; 
                if (v)
                    mymatrix->push(i, j, v);
            }
        return mymatrix;
    }

    bigmatrix* input() {
        bigmatrix *mymatrix = nullptr;
        int n, m;
        const char *pr = "";
        do {
            std::cout << pr << std::endl;   
            std::cout << "Enter number of rows please: ";
            pr = "You are wrong, repeat please!";
            if (!get_num(n))
                return nullptr;
        } while (n < 1);
        pr = "";
        do {
            std::cout << pr << std::endl;   
            std::cout << "Enter number of columns please: ";
            pr = "You are wrong, repeat please!";
            if (!get_num(m))
                return nullptr;
        } while (m < 1);
        try {
            mymatrix = new bigmatrix(n, m);
        } catch (std::bad_alloc &ba) {
            std::cout << "Error! " << ba.what() << std::endl;
            return nullptr;
        }
        bool bl = false, in;
        int i, j, v;
        do {
            std::cout << "\n1 - Enter item.\n0 - Bye!\n";
            if (!get_num(in))
                return nullptr;
            if (in) {
                pr = "";
                do {
                    std::cout << pr << std::endl;
                    std::cout << "Enter i j v: ";
                    if (!get_num(i))
                        return nullptr;
                    if (!get_num(j))
                        return nullptr;
                    if (!get_num(v))
                        return nullptr;
                    pr = "You are wrong, repeat please!";
                    if (v)
                        bl = true;
                } while (i < 0 || j < 0 || !v || i > n - 1 || j > m - 1);
                mymatrix->push(i, j, v);
            }
            if (!in && !bl)
                std::cout << "Enter at least one item!\n";
        } while (in || !bl);
        return mymatrix;
    }
}
