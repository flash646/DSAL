#include <iostream>
#include <string>
using namespace std;

struct Node {
    string label;
    int childCount;
    Node* children[10];
};

Node* root = nullptr;

class BookTree {
public:
    void create();
    void display(Node* node);

    BookTree() {
        root = nullptr;
    }
};

void BookTree::create() {
    int numChapters, numSections;

    root = new Node();
    cout << "Enter book name: ";
    cin >> root->label;

    cout << "Enter number of chapters: ";
    cin >> numChapters;
    root->childCount = numChapters;

    for (int i = 0; i < numChapters; i++) {
        root->children[i] = new Node();
        cout << "Enter chapter name: ";
        cin >> root->children[i]->label;

        cout << "Enter number of sections in chapter \"" << root->children[i]->label << "\": ";
        cin >> numSections;
        root->children[i]->childCount = numSections;

        for (int j = 0; j < numSections; j++) {
            root->children[i]->children[j] = new Node();
            cout << "Enter section " << j + 1 << " name: ";
            cin >> root->children[i]->children[j]->label;
        }
    }
}

void BookTree::display(Node* node) {
    if (node == nullptr) {
        cout << "No book found. Please create the tree first.\n";
        return;
    }

    cout << "\n--- Book Hierarchy ---";
    cout << "\nBook: " << node->label;

    for (int i = 0; i < node->childCount; i++) {
        cout << "\n  Chapter " << i + 1 << ": " << node->children[i]->label;
        cout << "\n    Sections:";
        for (int j = 0; j < node->children[i]->childCount; j++) {
            cout << "\n      " << node->children[i]->children[j]->label;
        }
    }
    cout << endl;
}

int main() {
    BookTree tree;
    int choice;

    while (true) {
        cout << "\n------------------\n";
        cout << "1. Create Book Tree\n";
        cout << "2. Display Book Tree\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tree.create();
                break;
            case 2:
                tree.display(root);
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
// Concept of General tree is used
