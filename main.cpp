#include <iostream>

using namespace std;

void addContact(string name, string num);

int getNetworkIndex(int network);

bool numberExists(string num);

void insertBST(struct BST *bst, struct BST *root);

void deletE(string num);

void displayPhoneBook();

void display(struct BST *p);

void search(string num);

struct Person {
    string name;
    int network;
    int number;
public:
    Person(string new_name, int new_network, int new_number) {
        name = new_name;
        network = new_network;
        number = new_number;
    }
};

struct BST {
    int id;
    BST *left;
    BST *right;
    Person *person;
public:
    BST(int new_id) {
        id = new_id;
        left = nullptr;
        right = nullptr;
        person = nullptr;
    }
};

BST *hash_array[100][4];

int main() {
    while (true) {
        int choise;
        cout << "\n\n\n########## M E N U\n\n";
        cout << "0. Exit\n";
        cout << "1. Display\n";
        cout << "2. Insert\n";
        cout << "3. Delete\n";
        cout << "4. Search\n";
        cout << "Enter an option : ";
        cin >> choise;

        switch (choise) {
            case 0: {
                exit(0);
            }
            case 1: {
                cout << "\n\n\n########## D I S P L A Y\n\n";
                displayPhoneBook();
                break;
            }
            case 2: {
                string name;
                string number;
                cout << "\n\n\n########## I N S E R T\n\n";
                cout << "Enter name : ";
                cin >> name;
                cout << "\nEnter number : ";
                cin >> number;

                string network_string = "";


                for (int i = 0; i < number.length(); ++i) {
                    if (i < 3) network_string += number[i];
                }


                int network = stoi(network_string);


                if (number.length() != 11) cout << "\n\nincorrect number!";
                else {

                    if (getNetworkIndex(network) == -1) cout << "\n\nincorrect number!";
                    else {

                        if (numberExists(number))cout << "\n\nNumber exists!";
                        else {
                            addContact(name, number);
                            cout << "\n\nContact successfully inserted!";
                        }
                    }
                }
                break;
            }
            case 3: {
                string number;
                cout << "\n\n\n########## D E L E T E\n\n";
                cout << "\nEnter number : ";
                cin >> number;
                deletE(number);
                break;
            }
            case 4: {
                string number;
                cout << "\n\n\n########## S E A R C H\n\n";
                cout << "\nEnter number : ";
                cin >> number;
                search(number);
                break;
                break;
            }
            default: {
                cout << "\ninvalid option!";
            }
        }
    }
}

void addContact(string name, string num) {
    string network_string = "";
    string number_string = "";

    for (int i = 0; i < num.length(); ++i) {
        if (i < 3) network_string += num[i];
        else number_string += num[i];
    }

    int network = stoi(network_string);
    int number = stoi(number_string);


    struct Person *person = new Person(name, network, number);


    struct BST *bst = new BST(number);
    bst->person = person;


    int index = number % 100;
    int network_index = getNetworkIndex(network);

    if (hash_array[index][network_index] == nullptr) {
        hash_array[index][network_index] = bst;
    }
    else {
        insertBST(bst, hash_array[index][network_index]);
    }
}

int getNetworkIndex(int network) {
    // Jazz
    if (network == 30 || network == 32) return 0;
        // Telenor
    else if (network == 34) return 1;
        // Zong
    else if (network == 31) return 2;
        // Ufone
    else if (network == 33) return 3;
    else return -1;
}

void insertBST(struct BST *current, struct BST *root) {
    struct BST *p = root;
    struct BST *k = p;

    if (p == nullptr) {
        root = current;
    } else {
        while (p != nullptr) {
            k = p;
            if (p->id > current->id) p = p->left;
            else p = p->right;
        }

        if (k->id > current->id) {
            k->left = current;
        } else {
            k->right = current;
        }
    }
}

bool numberExists(string num) {
    string network_string = "";
    string number_string = "";


    for (int i = 0; i < num.length(); ++i) {
        if (i < 3) network_string += num[i];
        else number_string += num[i];
    }

    int network = stoi(network_string);
    int number = stoi(number_string);

    int index = number % 100;
    int network_index = getNetworkIndex(network);

    struct BST *p = hash_array[index][network_index];
    while (p != nullptr) {
        if (p->id == number) return true;
        if (p->id > number) p = p->left;
        else p = p->right;
    }
    return false;
}

void displayPhoneBook() {
    for (int i = 0; i < 4; ++i) {

        if (i == 0) cout << "\n########## J A Z Z\n\n";
        else if (i == 1) cout << "\n########## T E L E N O R\n\n";
        else if (i == 2) cout << "\n########## Z O N G\n\n";
        else if (i == 3) cout << "\n########## U F O N E\n\n";

        for (int j = 0; j < 99; ++j) {
            display(hash_array[j][i]);
        }
    }
}

void display(struct BST *p) {
    if (p != nullptr) {
        display(p->left);
        printf("Name : %-15s Number : %d%d\n", p->person->name.c_str(), p->person->network, p->person->number);
        display(p->right);
    }
}

void search(string num) {
    string network_string = "";
    string number_string = "";

    for (int i = 0; i < num.length(); ++i) {
        if (i < 3) network_string += num[i];
        else number_string += num[i];
    }

    int network = stoi(network_string);
    int number = stoi(number_string);

    int index = number % 100;
    int network_index = getNetworkIndex(network);

    struct BST *p = hash_array[index][network_index];
    while (p != nullptr) {
        if (p->id == number) {
            printf("Name : %-15s Number : %d%d\n", p->person->name.c_str(), p->person->network, p->person->number);
            return;
        }
        if (p->id > number) p = p->left;
        else p = p->right;
    }
    cout << "Number not found!";
}

void deletE(string num) {

    string network_string = "";
    string number_string = "";

    for (int i = 0; i < num.length(); ++i) {
        if (i < 3) network_string += num[i];
        else number_string += num[i];
    }

    int network = stoi(network_string);
    int number = stoi(number_string);

    int index = number % 100;
    int network_index = getNetworkIndex(network);

    struct BST *root = hash_array[index][network_index];

    struct BST *p = root;
    struct BST *k = p;
    struct BST *r = nullptr;

    // if root
    if (root->id == number && root->left == nullptr && root->right == nullptr){
        hash_array[index][network_index] = nullptr;
        return;
    }

    while (p != nullptr) {
        k = p;
        if (p->id > number) p = p->left;
        else if (p->id < number) p = p->right;
        if (p->id == number) break;
    }

    // Case 1 : Delete leaf node

    if (p->left == nullptr && p->right == nullptr) {
        if (k->left == p) k->left = nullptr;
        else k->right = nullptr;
        delete p;
    }

        // Case 2 : Node have only 1 child

    else if ((p->right == nullptr && p->left != nullptr) || (p->right != nullptr && p->left == nullptr)) {
        if (k->right == p && p->right == nullptr) k->right = p->left;
        else if (k->right == p && p->left == nullptr) k->right = p->right;
        else if (k->left == p && p->right == nullptr) k->left = p->left;
        else if (k->left == p && p->left == nullptr) k->left = p->right;
    }

        // Case 3 : Delete node with 2 subtrees
    else if (p->right != nullptr && p->right != nullptr) {

        // If node is not root & its one right branch have something in left
        if (p->right->left != nullptr && p != root) {
            r = p->right;

            while (r->left != nullptr) {
                k = r;
                r = r->left;
            }

            p->id = r->id;
            k->left = r->right;

            delete r;

        }

        // If node is root
        if (p->id == root->id) {

            k = p->right;
            p->id = k->id;
            p->right = k->right;

            r = p->right;
            while (r->left != nullptr) {
                r = r->left;
            }

            r->left = k->left;
        }
    }
}