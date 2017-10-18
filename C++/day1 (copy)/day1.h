
namespace kali {

    struct node {
        int i, j, v;
        node *next;
        //node(int i, int j, int v) : i(i), j(j), v(v), next(nullptr) {};
    };
    node* alloc_node(int ii, int jj, int vv) {
        node* mynode = new node;
        mynode->i = ii;
        mynode->j = jj;
        mynode->v = vv;
        mynode->next = nullptr;
        return mynode;
    }

    struct list {
        node *head;
        int count;
        //list() : head(nullptr), count(0) {};
        //virtual ~list();
        //void add(int, int, int);
    };
    list* alloc_list() {
        list* mylist = new list;
        mylist->head = nullptr;
        mylist->count = 0;
        return mylist;
    }

    struct bigmatrix {
        /*bigmatrix(int n, int m) : n(n), m(m) {
            p = new list();
        };
        ~bigmatrix() {
            //std::cout << "del bigmatrix\n";
            n = m = 0;
            if (p)
                delete p;
        }*/
        //bigmatrix* map(int(*f)(int));
        //void print();
        private:
        int n, m;
        list *p;
    };

    template <class T>
    bool get_num(T &a) {
        std::cin >> a;
        if (!std::cin.good())
            return false;
        return true;
    }

    bigmatrix* inputmatrix();
    
    inline int triplenumber(int x) {
        return x * 3;
    }

    inline int reversenumber(int x) {
        int res = 0;
        for (int i = x; i; i /= 10)
            res = (res * 10) + (i % 10);
        return res;
    }

}
