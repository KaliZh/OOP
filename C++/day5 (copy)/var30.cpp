#include "var30.h"

namespace kali {

    // ----------------------------_FILE---------------------------- //

    void _FILE::set_Permissions(string permissions[], const int user) {
        if (_FILE::user != user)
            throw exception();
        for (int i = 0; i < 100; i++)
            _FILE::permissions[i] = permissions[i];
    }

    void _FILE::set_name(string &name, const int user) {
        if (permissions[user].find('w') == string::npos)
            throw exception();
        _FILE::name = name;
        size = sizeof(this);
    }

    void table_FLOW::add(const std::streamsize address) {
        if (n + 1 >= 100)
            throw exception();
        arr[n++] = address;
    }
    void table_FLOW::del(const int n) {
        for (int i = n; i < --table_FLOW::n; i++)
            arr[i] = arr[i + 1];
    }

    // ----------------------------SIMPLE_FILE---------------------------- //
    
    void SIMPLE_FILE::read(const int user) const {
        if (permissions[user].find('r') == string::npos)
            throw exception();
        cout << info << endl;
    }
    
    void SIMPLE_FILE::write(const int user, const string& info) {
        if (permissions[user].find('w') == string::npos)
            throw exception();
        SIMPLE_FILE::info = info;
        time_t now = time(0);
        datetime1 = ctime(&now);
        size = sizeof(this);
    }

    void SIMPLE_FILE::execute(const int user) const {
        if (permissions[user].find('x') == string::npos)
            throw exception();
        cout << "successfully executed" << endl;
    }

    // ----------------------------CRYPTO_FILE---------------------------- //
    
    void CRYPTO_FILE::set_users(bool users[]) {
        for (int i = 0; i < n; i++)
            CRYPTO_FILE::users[i] = users[i];
        size = sizeof(this);
    }

    // ----------------------------DIR_FILE---------------------------- //

    void DIR_FILE::read(const int user) const {
        if (permissions[user].find('r') == string::npos)
            throw exception();
        for (int i = 0; i < n; i++)
            cout << arr[i]->get_name() << endl;
    }

    void DIR_FILE::add(const int user, const _FILE &file) {
        if (permissions[user].find('w') == string::npos)
            throw exception();
        if (n + 1 >= 100)
            return;
        arr[n++] = file.clone();
        size = sizeof(this);
    }
    
    void DIR_FILE::del(const int user, const string& name) {
        if (permissions[user].find('w') == string::npos)
            throw exception();
        int i;
        for (i = 0; i < n; i++)
            if (arr[i]->get_name() == name)
                break;
        if (i == n)
            return;
        delete arr[i];
        for (; i < n - 1; i++)
            arr[i] = arr[i + 1];
        --n;
        size = sizeof(this);
    }

    _FILE* DIR_FILE::get_DIR_FILE(const int user, const string &name) {
        if (permissions[user].find('r') == string::npos)
            throw exception();
        for (int i = 0; i < n; i++)
            if (arr[i]->get_w() == 3 && arr[i]->get_name() == name)
                return arr[i];
        return nullptr;
    }

    _FILE* DIR_FILE::get_FILE(const int user, const string &name) {
        if (permissions[user].find('r') == string::npos)
            throw exception();
        for (int i = 0; i < n; i++)
            if (arr[i]->get_name() == name)
                return arr[i];
        return nullptr;
    }

    // ----------------------------FILE_SYSTEM---------------------------- //

    void table_USER::add(const string &name) {
        if (n + 1 >= 100)
            throw exception();
        arr[n++].name = name;
    }

    void table_USER::del(const int n) {
        for (int i = n; i < --table_USER::n; i++)
            arr[i] = arr[i + 1];
    }

    int table_USER::get_id(const string &name) const {
        for (int i = 0; i < n; i++)
            if (arr[i].name == name)
                return i;
        return -1;
    }

    void FILE_SYSTEM::start(string &name) {
        int user_id;
        if ((user_id = user.get_id(name)) < 0) {
            try {
                user.add(name);
                user_id = user.get_n() - 1;
            } catch (exception &ex) {
                cout << "File system is overloaded!\n";
                return;
            }
        }
        help();
        go(user_id, &root);
    }

    void FILE_SYSTEM::go(int user_id, DIR_FILE *dir) {
        string cmd, arg;
        while (true) {
            cin >> cmd;
            if (cmd == "cd") {
                cin >> arg;
                if (arg == "..")
                    return;
                cd(user_id, arg, dir);
            } else if (cmd == "cp") { 
                cin >> arg;
                cp(user_id, arg, dir);
            } else if (cmd == "mv") { 
                cin >> arg;
                mv(user_id, arg, dir);
            } else if (cmd == "pe") {
                pe(user_id, dir);
            } else if (cmd == "mk") { 
                cin >> arg;
                mk(user_id, arg, dir);
            } else if (cmd == "rm") { 
                cin >> arg;
                rm(user_id, arg, dir);
            } else if (cmd == "ls") { 
                ls(user_id, dir);
            } else if (cmd == "pwd") { 
                cout << dir->path << endl;
            } else if (cmd == "rd") { 
                cin >> arg;
                rd(user_id, arg, dir);
            } else if (cmd == "wt") { 
                string arg1;
                cin >> arg >> arg1;
                wt(user_id, arg, arg1, dir);
            } else if (cmd == "io") { 
                cin >> arg;
                io(user_id, arg, dir);
            } else if (cmd == "cb") { 
                if (buf) {
                    delete buf;
                    buf = nullptr;
                }
            } else if (cmd == "encrypt") { 
            } else if (cmd == "decrypt") { 
            } else if (cmd == "help") { 
                help();
            } else {
                cout << "Wrong command!\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max());
            }
        }
    }

    void FILE_SYSTEM::help() {
        cout << "cd dir - change directory to dir (cd .. - go back);\ncp file - copy file to buf;\nmv file - move file to buf;\n"
            "pe - paste file from buf;\nls - directory listing;\npwd - show current directory\nrm name - remove file/dir by name;\n"
            "mk name - make file/dir with name, if name has one dot - file, else - dir (name can has ONLY ONE dot and eng letters);\n"
            "rd file - read file;\nwt info file - write info to file;\nencrypt/decrpyt file - to encrypt/decrypt file;\nhelp - help;\n"
            "io file - info about file\ncb - clear buf.\n";
    }

    void FILE_SYSTEM::cd(const int user_id, string &name, DIR_FILE *dir) {
        _FILE *cddir = nullptr;
        try {
             cddir = dir->get_DIR_FILE(user_id, name);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
        if (!cddir)
            return;
        if (!cddir->openr(user_id)) {
            cout << "You dont have enough permissions!\n";
            return;
        }
        go(user_id, (DIR_FILE*)cddir);
    }

    void FILE_SYSTEM::ls(const int user_id, DIR_FILE *dir) {
        try {
            dir->read(user_id);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
        }
    }

    void FILE_SYSTEM::mk(const int user_id, string &name, DIR_FILE *dir) {
        bool bl = false;
        for (int i = 0; i < name.size(); i++) {
            if (name[i] == '.' && !bl) {
                bl = true;
            } else if (name[i] == '.' && bl) {
                cout << "Illegal name of file/dir!\n";
                return;
            } else if (name[i] < '0' || (name[i] > '9' && name[i] < 'A') || (name[i] > 'Z' && name[i] < 'a') || name[i] > 'z') {
                cout << "Illegal name of file/dir!\n";
                return;
            }
        }
        try {
            if (bl)
                dir->add(user_id, SIMPLE_FILE(name, dir->path + '/' + name, user_id));
            else dir->add(user_id, DIR_FILE(name, dir->path + '/' + name, user_id));
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
    }

    void FILE_SYSTEM::rm(const int user_id, string &name, DIR_FILE *dir) {
        try {
            dir->del(user_id, name);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
    }

    void FILE_SYSTEM::cp(const int user_id, string &name, DIR_FILE *dir) {
        if (buf) {
            cout << "Buffer can has only one file!\n";
            return;
        }
        try {
            buf = dir->get_FILE(user_id, name);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            buf = nullptr;
            return;
        }
        if (!buf)
            return;
        if (!buf->openw(user_id)) {
            cout << "You dont have enough permissions!\n";
            delete buf;
            buf = nullptr;
            return;
        }
        buf = buf->clone();
    }

    void FILE_SYSTEM::mv(const int user_id, string &name, DIR_FILE *dir) {
        if (buf) {
            cout << "Buffer can has only one file!\n";
            return;
        }
        try {
            buf = dir->get_FILE(user_id, name);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            buf = nullptr;
            return;
        }
        if (!buf)
            return;
        if (!buf->openw(user_id)) {
            cout << "You dont have enough permissions!\n";
            delete buf;
            buf = nullptr;
            return;
        }
        buf = buf->clone();
        try {
            dir->del(user_id, name);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            delete buf;
            buf = nullptr;
        }
    }

    void FILE_SYSTEM::pe(const int user_id, DIR_FILE *dir) {
        try {
            dir->add(user_id, *buf);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
        delete buf;
        buf = nullptr;
    }

    void FILE_SYSTEM::rd(const int user_id, string &name, DIR_FILE *dir) {
        _FILE *rdfile = nullptr;
        try {
            rdfile = dir->get_FILE(user_id, name);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
        if (!rdfile)
            return;
        try {
            rdfile->read(user_id);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
    }

    void FILE_SYSTEM::wt(const int user_id, string &name, string &info, DIR_FILE *dir) {
        _FILE *wtfile = nullptr;
        try {
            wtfile = dir->get_FILE(user_id, name);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
        if (!wtfile)
            return;
        else if (wtfile->get_w() == 3)
            return;
        try {
            SIMPLE_FILE *file = (SIMPLE_FILE*)wtfile;
            file->write(user_id, info);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
    }

    void FILE_SYSTEM::io(const int user_id, string &name, DIR_FILE *dir) {
        _FILE *iofile = nullptr;
        try {
            iofile = dir->get_FILE(user_id, name);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
        if (!iofile)
            return;
        try {
            iofile->properties(user_id);
        } catch(exception &ex) {
            cout << "You dont have enough permissions!\n";
            return;
        }
    }

}
