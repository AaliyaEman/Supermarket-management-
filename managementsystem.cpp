#include <iostream>
#include <string>
using namespace std;

// Node representing a product in the supermarket
struct Product {
    int productcode;
    string productname;
    float price;
    float discount;
    int quantity;  // New attribute to store quantity of each product
    Product* next;

    Product(int code, const string& name, float pr, float disc, int qty)
        : productcode(code), productname(name), price(pr), discount(disc), quantity(qty), next(nullptr) {}
};

// Supermarket class using linked list to manage products
class mysupermarket {
private:
    Product* head;

public:
    mysupermarket() : head(nullptr) {
        // Initialize with some initial products (dummy data)
        head = new Product(11, "Biscuits", 30, 5, 100);  // Product code 11, Price 30, Discount 5%, Quantity 100
        head->next = new Product(22, "Bananas", 10, 0, 200);  // Product code 22, Price 10, Discount 0%, Quantity 200
    }

    // Display menu and handle user selection
    void menu() {
        while (true) {
            int selection;
            cout << "\n            |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|       " << endl;
            cout << "            ||     WELCOME TO  MY SUPER MARKET   ||       " << endl;
            cout << "            |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|       " << endl;
            cout << "Please select one of them" << endl;
            cout << " 1) Administration" << endl;
            cout << " 2) Customer " << endl;
            cout << " 3) Exit " << endl;
            cin >> selection;

            switch (selection) {
                case 1:
                    administeration();
                    break;
                case 2:
                    costumer();
                    break;
                case 3:
                    cout << "Exiting program..." << endl;
                    return;
                default:
                    cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                    break;
            }
        }
    }

    // Handle administration tasks
    void administeration() {
        while (true) {
            int choice;
            cout << "\n              ~~~~~~~~~                        " << endl;
            cout << "       WELCOME MYSM ADMINISTRATION            " << endl;
            cout << "              ~~~~~~~~~                        " << endl;
            cout << "What do you want to do :" << endl;
            cout << "1) Add new product :" << endl;
            cout << "2) Delete a product:" << endl;
            cout << "3) Go back to main menu:" << endl;
            cin >> choice;

            switch (choice) {
                case 1:
                    add();
                    list();  // Display updated list after addition
                    break;
                case 2:
                    rem();
                    list();  // Display updated list after deletion
                    break;
                case 3:
                    return;
                default:
                    cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                    break;
            }
        }
    }

    // Handle customer tasks
    void costumer() {
        while (true) {
            int select;
            cout << "\nWhat do you want:" << endl;
            cout << "1) Buy product :" << endl;
            cout << "2) Go back :" << endl;
            cin >> select;

            switch (select) {
                case 1:
                    receipt();
                    break;
                case 2:
                    return;
                default:
                    cout << "Invalid selection. Please enter 1 or 2." << endl;
                    break;
            }
        }
    }

    // Add a new product to the supermarket
    void add() {
        int code, qty;
        string name;
        float price, discount;

        cout << "\n~~~~~~~~ Add New Product ~~~~~~~~" << endl;
        cout << "Enter code of new product: ";
        cin >> code;
        cout << "Enter name of product: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter price of product: ";
        cin >> price;
        cout << "Enter discount on product: ";
        cin >> discount;
        cout << "Enter quantity of product: ";
        cin >> qty;

        Product* newProduct = new Product(code, name, price, discount, qty);
        newProduct->next = head;
        head = newProduct;

        cout << "New product added successfully." << endl;
    }

    // Remove a product from the supermarket
    void rem() {
        if (!head) {
            cout << "No products to delete." << endl;
            return;
        }

        int productkey;
        cout << "\n          ~~~~~~~~ DELETE PRODUCT ~~~~~~~~        " << endl;
        cout << "Enter code of product to delete: ";
        cin >> productkey;

        Product* current = head;
        Product* prev = nullptr;
        bool found = false;

        while (current) {
            if (current->productcode == productkey) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                cout << "Product deleted successfully." << endl;
                found = true;
                break;
            }
            prev = current;
            current = current->next;
        }

        if (!found) {
            cout << "Product with code " << productkey << " not found." << endl;
        }
    }

    // Display all products in the supermarket
    void list() {
        cout << "\n              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~            " << endl;
        cout << "               PRODUCT#        pNAME        PRICE        QUANTITY   " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~             " << endl;

        Product* current = head;
        while (current) {
            cout << current->productcode << "  " << current->productname << "  " << current->price << "  "
                 << current->quantity << endl;
            current = current->next;
        }
    }

    // Generate a receipt for customer
    void receipt() {
        if (!head) {
            cout << "No products available for sale." << endl;
            return;
        }

        int arrc[2];
        int arrq[2];
        char choice;
        int c = 0;
        float total = 0;

        cout << "\n            ~~~~~~~~~ RECEIPT ~~~~~~~~         " << endl;
        list();  // Display list of products for customer to choose from
        cout << "\n           ~~~~~~~```````````````~~~~~~~        " << endl;
        cout << "                PLACE YOUR ORDER               " << endl;
        cout << "           ~~~~~~~```````````````~~~~~~~       " << endl;

        do {
            cout << "Enter product code: ";
            cin >> arrc[c];
            cout << "Enter product quantity: ";
            cin >> arrq[c];

            cout << "Do you want to buy another product? (y/n): ";
            cin >> choice;
            c++;
        } while (choice == 'y');

        cout << "\n   `````````` RECEIPT ``````````     " << endl;
        cout << " PRODUCT#   PRODUCT NAME   QUANTITY   PRICE   AMOUNT" << endl;

        for (int i = 0; i < c; i++) {
            Product* current = head;
            while (current) {
                if (current->productcode == arrc[i]) {
                    if (current->quantity < arrq[i]) {
                        cout << "Insufficient quantity of " << current->productname << " available." << endl;
                        break;
                    }
                    float amount = current->price * arrq[i] * (1 - current->discount / 100);
                    total += amount;
                    cout << "   " << current->productcode << "        " << current->productname << "        "
                         << arrq[i] << "         " << current->price << "       " << amount << endl;
                    // Update quantity after purchase
                    current->quantity -= arrq[i];
                }
                current = current->next;
            }
        }

        cout << "\nTotal amount: " << total << endl;
    }

    // Destructor to clean up memory
    ~mysupermarket() {
        while (head) {
            Product* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    mysupermarket a;
    a.menu();
    return 0;
}
