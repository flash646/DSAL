#include<iostream>
#include<string>
using namespace std;

class dictionary;

class avlnode {
    string keyword;
    string meaning;
    avlnode *left, *right;
    int bf;

public:
    avlnode() : keyword(""), meaning(""), left(NULL), right(NULL), bf(0) {}
    avlnode(string k, string m) : keyword(k), meaning(m), left(NULL), right(NULL), bf(0) {}
    friend class dictionary;
};

class dictionary {
    avlnode *par, *loc;

public:
    avlnode *root;
    dictionary() : root(NULL), par(NULL), loc(NULL) {}
    void accept();
    void insert(string key, string mean);
    void LLrotation(avlnode*, avlnode*);
    void RRrotation(avlnode*, avlnode*);
    void inorder(avlnode* root);
    void deletekey(string key);
    void descending(avlnode*);
    void search(string);
    void update(string, string);
    void showBalanceFactors(avlnode* root);
};

void dictionary::descending(avlnode *root) {
    if (root) {
        descending(root->right);
        cout << root->keyword << " " << root->meaning << endl;
        descending(root->left);
    }
}

void dictionary::accept() {
    string key, mean;
    cout << "Enter Keyword: ";
    cin >> key;
    cout << "Enter meaning: ";
    cin >> mean;
    insert(key, mean);
}

void dictionary::LLrotation(avlnode *a, avlnode *b) {
    a->left = b->right;
    b->right = a;
    a->bf = b->bf = 0;
}

void dictionary::RRrotation(avlnode *a, avlnode *b) {
    a->right = b->left;
    b->left = a;
    a->bf = b->bf = 0;
}

void dictionary::insert(string key, string mean) {
    if (!root) {
        root = new avlnode(key, mean);
        return;
    }

    avlnode *a, *pa, *p, *pp;
    pa = NULL;
    p = a = root;
    pp = NULL;

    while (p) {
        if (p->bf) {
            a = p;
            pa = pp;
        }
        if (key < p->keyword) {
            pp = p;
            p = p->left;
        } else if (key > p->keyword) {
            pp = p;
            p = p->right;
        } else {
            cout << "Already exists\n";
            return;
        }
    }

    avlnode *y = new avlnode(key, mean);
    if (key < pp->keyword) {
        pp->left = y;
    } else {
        pp->right = y;
    }

    int d;
    avlnode *b, *c;
    b = c = NULL;

    if (key > a->keyword) {
        b = p = a->right;
        d = -1;
    } else {
        b = p = a->left;
        d = 1;
    }

    while (p != y) {
        if (key > p->keyword) {
            p->bf = -1;
            p = p->right;
        } else {
            p->bf = 1;
            p = p->left;
        }
    }

    if (!(a->bf) || !(a->bf + d)) {
        a->bf += d;
        return;
    }

    if (d == 1) {
        if (b->bf == 1) {
            LLrotation(a, b);
        } else {
            c = b->right;
            b->right = c->left;
            a->left = c->right;
            c->left = b;
            c->right = a;

            switch (c->bf) {
                case 1:
                    a->bf = -1;
                    b->bf = 0;
                    break;
                case -1:
                    a->bf = 0;
                    b->bf = 1;
                    break;
                case 0:
                    a->bf = 0;
                    b->bf = 0;
                    break;
            }
            c->bf = 0;
            b = c;
        }
    } else {
        if (b->bf == -1) {
            RRrotation(a, b);
        } else {
            c = b->left;
            a->right = c->left;
            b->left = c->right;
            c->left = a;
            c->right = b;

            switch (c->bf) {
                case 1:
                    a->bf = 0;
                    b->bf = -1;
                    break;
                case -1:
                    a->bf = 1;
                    b->bf = 0;
                    break;
                case 0:
                    a->bf = 0;
                    b->bf = 0;
                    break;
            }
            c->bf = 0;
            b = c;
        }
    }

    if (!pa) root = b;
    else if (a == pa->left) pa->left = b;
    else pa->right = b;
}

void dictionary::search(string key) {
    loc = NULL;
    par = NULL;
    avlnode *ptr = root;
    while (ptr) {
        if (ptr->keyword == key) {
            loc = ptr;
            break;
        } else if (key < ptr->keyword) {
            par = ptr;
            ptr = ptr->left;
        } else {
            par = ptr;
            ptr = ptr->right;
        }
    }
    if (!loc) cout << "Not found\n";
}

void dictionary::update(string oldkey, string newmean) {
    search(oldkey);
    if (loc) {
        loc->meaning = newmean;
        cout << "UPDATE SUCCESSFUL\n";
    }
}

void dictionary::inorder(avlnode *root) {
    if (root) {
        inorder(root->left);
        cout << root->keyword << " " << root->meaning << endl;
        inorder(root->right);
    }
}

void dictionary::showBalanceFactors(avlnode *root) {
    if (root) {
        showBalanceFactors(root->left);
        cout << root->keyword << " has Balance Factor: " << root->bf << endl;
        showBalanceFactors(root->right);
    }
}

int main() {
    dictionary d;
    int ch;
    string key, mean;
    do {
        cout << "1.Insert\n2.Update\n3.Ascending\n4.Descending\n5.Show Balance Factors\n6.Quit\n";
        cin >> ch;
        switch (ch) {
            case 1:
                d.accept();
                break;
            case 2:
                cout << "Enter key whose meaning to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin >> mean;
                d.update(key, mean);
                break;
            case 3:
                d.inorder(d.root);
                break;
            case 4:
                d.descending(d.root);
                break;
            case 5:
                d.showBalanceFactors(d.root);
                break;
            case 6:
                return 0;
        }
    } while (ch != 6);
}