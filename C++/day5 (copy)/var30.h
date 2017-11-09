#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <limits>
#include <exception>
#include <ctime>

namespace kali {

    using std::string;
    using std::exception;
    using std::cin;
    using std::cout;
    using std::endl;
    //using std::fstream;
    //using std::ifstream;
    //using std::ofstream;

    class _FILE {
        friend class FILE_SYSTEM;
        protected:
            string name, path, permissions[100];
            int user;
            std::size_t size;
            int w;
        public:
            _FILE() {}
            _FILE(string name, string path, int user, int w) : name(name), path(path), user(user), w(w) {
                for (int i = 0; i < 100; i++)
                    permissions[i] = "r";
                permissions[0] = permissions[user] = "rwx";
            }
            virtual ~_FILE() {}
            /*virtual _FILE* clone() const {
                return new _FILE(*this);
            }*/
            virtual _FILE* clone() const = 0;
            virtual void read(const int) const = 0;
            virtual void properties(const int user) const {
                if (permissions[user].find('r') == string::npos)
                    throw exception();
                cout << "name: " << name << endl << "path: " << path << endl << "size: " << size << endl;                               
            }
            bool openr(const int user) const {
                if (permissions[user].find('r') == string::npos)
                    return false;
                else return true;
            }
            bool openw(const int user) const {
                if (permissions[user].find('w') == string::npos)
                    return false;
                else return true;
            }
            const string* get_permissions() const {
                return permissions;
            }
            void set_Permissions(string[], const int);
            const string& get_name() const {
                return name;
            }
            void set_name(string&, const int);
            int get_w() {
                return w;
            }
    };

    class table_FLOW {
        private:
            string name;
            int n;
            std::streamsize arr[100];
        public:
            table_FLOW() : n(0) {}
            table_FLOW(string name) : name(name), n(0) {}
            //~table_FLOW();
            void add(const std::streamsize);
            void del(const int n);
    };// MAIN_FLOW("MAIN"), SYMKEY_FLOW("SYMKEY");

    class SIMPLE_FILE : public _FILE {
        friend class FILE_SYSTEM;
        protected:
            //table_FLOW *ptr;
            string datetime, datetime1, info;
        public:
            SIMPLE_FILE() : _FILE()/*, ptr(&MAIN_FLOW)*/ {}
            SIMPLE_FILE(string name, string path, int user, int w = 1/*, table_FLOW *flow = &MAIN_FLOW*/) 
                : _FILE(name, path, user, w), /*ptr(flow),*/ info("empty") {
                time_t now = time(0);
                datetime = datetime1 = ctime(&now);
                size = sizeof(this);
            }
            //~SIMPLE_FILE();
            SIMPLE_FILE* clone() const {
                return new SIMPLE_FILE(*this);
            }
            void properties(const int user) const {
                _FILE::properties(user);
                cout << "created: " << datetime << "last changed: " << datetime1 << "type: ";
                type();
            }
            void type() const {
                std::size_t temp = name.find_last_of("."); 
                cout << name.substr(temp + 1) << endl;
            }
            void read(const int) const;
            void write(const int, const string&);
            void execute(const int) const;
    };

    class CRYPTO_FILE : public SIMPLE_FILE {
        friend class FILE_SYSTEM;
        private:
            int n;
            bool users[100];
        public:
            CRYPTO_FILE() : SIMPLE_FILE(), n(0) {}
            CRYPTO_FILE(string name, string path, int user, int w = 2/*, table_FLOW *flow = &MAIN_FLOW*/, int n = 0, bool *users = nullptr)
                : SIMPLE_FILE(name, path, user, w/*, flow*/), n(n) {
                for (int i = 0; i < n; i++)
                    CRYPTO_FILE::users[i] = users[i];
                size = sizeof(this);
            }
            //~CRYPTO_FILE();
            const bool* get_users() const {
                return users;
            }
            void set_users(bool[]);
    };

    class DIR_FILE : public _FILE {
        friend class FILE_SYSTEM;
        private:
            int n;
            _FILE *arr[100];
            std::streamsize address;
        public:
            DIR_FILE() : _FILE(), n(0) {}
            DIR_FILE(string name, string path, int user, int w = 3) : _FILE(name, path, user, w), n(0) {
                size = sizeof(this);
            }
            DIR_FILE(const DIR_FILE &dir) : _FILE(dir.name, dir.path, dir.user, dir.w), n(dir.n) {
                for (int i = 0; i < n; i++)
                    arr[i] = dir.arr[i]->clone();
            }
            ~DIR_FILE() {
                for (int i = 0; i < n; i++)
                    delete arr[i];
            }
            DIR_FILE* clone() const {
                return new DIR_FILE(*this);
            }
            void read(const int) const;
            void add(const int, const _FILE&);
            void del(const int, const string&);
            _FILE* get_DIR_FILE(const int, const string&);
            _FILE* get_FILE(const int, const string&);
    };

    struct USER {
        string name;
        int key;
        USER() {}
    };

    class table_USER {
        private:    
            int n;
            USER arr[100];
        public:
            table_USER() : n(0) {}
            table_USER(string name) : n(1) {
                arr[0].name = name;
            }
            //~table_USER();
            void add(const string&);
            void del(const int);
            int get_id(const string&) const;
            int get_n() {
                return n;
            }
            void set_n(const int n) {
                table_USER::n = n;
            }
            const USER* get_arr() const {
                return arr;
            }
            void set_arr(const USER arr[]) {
                for (int i = 0; i < n; i++)
                    table_USER::arr[i] = arr[i];
            }
            void show() {
                for (int i = 0; i < n; i++)
                    cout << arr[i].name << endl;
            }
    };

    class FILE_SYSTEM {
        private:
            //fstream file;
            table_USER user;
            DIR_FILE root;
            _FILE *buf;
        public:
            FILE_SYSTEM() : user("ADMIN"), root("root", "/root", 0), buf(nullptr) {
                string permissions[100];
                for (int i = 0; i < 100; i++)
                    permissions[i] = "rw";
                root.set_Permissions(permissions, 0);
            }
            ~FILE_SYSTEM() {
                if (buf)
                    delete buf;
            }
            void start(string&);
            void edit(string&);
            void go(const int, DIR_FILE*);
            void ls(const int, DIR_FILE*);
            void help();
            void mk(const int, string&, DIR_FILE*);
            void rm(const int, string&, DIR_FILE*);
            void cd(const int, string&, DIR_FILE*);
            void cp(const int, string&, DIR_FILE*);
            void mv(const int, string&, DIR_FILE*);
            void pe(const int, DIR_FILE*);
            void rd(const int, string&, DIR_FILE*);
            void wt(const int, string&, string&, DIR_FILE*);
            void io(const int, string&, DIR_FILE*);
    };

}
