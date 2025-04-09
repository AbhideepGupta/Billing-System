#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdio>  
      

using namespace std;

class Product {
private:
    int productNumber;
    string productName;
    float productRate;
public:
    Product() : productNumber(0), productName(""), productRate(0.0) {}

    Product(int pNum, string pNam, float rate) : productNumber(pNum), productName(pNam), productRate(rate) {
        ofstream outProduct("Products.txt", ios::app);
        if (outProduct.is_open()) {
            outProduct << productNumber << ' ' << productName << ' ' << productRate << endl;
            outProduct.close();
            cout << "\n\n\n\tPRODUCT CREATED SUCCESSFULLY";
        } else {
            cout << "\n\n\tError opening file to create product!";
        }
        getch();
    }

    int getNumber() { return productNumber; }
    string getName() { return productName; }
    float getRate() { return productRate; }

    void setNumber(int x) { productNumber = x; }
    void setName(string x) { productName = x; }
    void setRate(float x) { productRate = x; }
};

class Bill {
public:
    string date;
    float totalAmount;

    Bill() {
        time_t now = time(0);
        date = ctime(&now);
        totalAmount = 0.0;
    }
};

class BillItems {
private:
    Product product;
    int quantity;
public:
    void getItem(int code) {
        ifstream prod("Products.txt");
        if (!prod.is_open()) {
            cout << "\n\tError opening product file.";
            return;
        }

        int pn;
        string pp;
        float pr;
        bool found = false;

        while (prod >> pn >> pp >> pr) {
            if (pn == code) {
                product.setNumber(pn);
                product.setName(pp);
                product.setRate(pr);
                found = true;
                break;
            }
        }
        prod.close();

        if (!found) {
            cout << "\n\tProduct code not found.";
        }
    }

    void setQuantity(int x) { quantity = x; }

    float getAmount() {
        return product.getRate() * quantity;
    }

    void printItemDet() {
        cout << "\t" << setw(14) << product.getNumber()
            << "\t" << setw(12) << product.getName()
            << "\t" << setw(12) << product.getRate()
            << "\t" << setw(8) << quantity << "\t";
    }
};

class Invoice : public Bill {
private:
    int numOfItems;
    BillItems item[50];
};

class NavPages {
public:
    static void intro() {
        cout << "\n\n\n\tBILLING SYSTEM";
        cout << "\n\t================================================================\n";
        cout << "\n\n\tMADE BY:";
        cout << "\n\n\tAbhideep Gupta";
        cout << "\n\n\tRashi Jain";
        cout << "\n\n\tManan";
        cout << "\n\n\tPrincess Dhawan";
    }

    static void user() {
        int ch;
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t1. CUSTOMER";
        cout << "\n\n\t2. ADMINISTRATOR";
        cout << "\n\n\t3. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        cin >> ch;
        switch (ch) {
        case 1: customer(); break;
        case 2: admin(); break;
        case 3: exit(0);
        default: cout << "\n\tInvalid Choice!"; getch(); break;
        }
    }

    static void customer() {
        int n;
        BillItems item[20];
        system("cls");
        cout << "\n\n\tENTER THE NUMBER OF ITEMS: ";
        cin >> n;
        displayProduct(); // show available products
        int code, qty;

        for (int i = 0; i < n; i++) {
            cout << "\n\tENTER ITEM CODE: ";
            cin >> code;
            item[i].getItem(code);
            cout << "\tENTER ITEM QUANTITY: ";
            cin >> qty;
            item[i].setQuantity(qty);
        }

        Bill fBill;
        for (int i = 0; i < n; i++) {
            fBill.totalAmount += item[i].getAmount();
        }

        // Print the bill
        system("cls");
        cout << "\n\n\tINVOICE\t\t\tDate/Time: " << fBill.date;
        cout << "\n\t======================================================================================================";
        cout << "\n\tProduct Number\tProduct Name\tProduct Rate\tQuantity\tAmount\n";
        for (int i = 0; i < n; i++) {
            item[i].printItemDet();
            cout << setw(6) << item[i].getAmount() << endl;
        }
        cout << "\n\n\t\t\t\tTOTAL AMOUNT: " << fBill.totalAmount;
        cout << "\n\tThank You for Shopping";
        cout << "\n\tPress any key to continue...";
        getch();
    }

    static void admin() {
        while (1) {
            system("cls");
            int ch;
            cout << "\n\n\n\tADMIN MENU";
            cout << "\n\n\t1. CREATE PRODUCT";
            cout << "\n\n\t2. DISPLAY ALL PRODUCTS";
            cout << "\n\n\t3. MODIFY PRODUCT";
            cout << "\n\n\t4. DELETE PRODUCT";
            cout << "\n\n\t5. BACK TO MAIN MENU";
            cout << "\n\n\tPlease Enter Your Choice (1-5): ";
            cin >> ch;
            switch (ch) {
            case 1: createProduct(); break;
            case 2: displayProduct(); break;
            case 3: modifyProduct(); break;
            case 4: deleteProduct(); break;
            case 5: return;
            default: cout << "\n\tInvalid Choice!"; getch(); break;
            }
        }
    }

    static void createProduct() {
        system("cls");
        int n;
        string p;
        float r;
        cout << "\n\n\tENTER THE DETAILS OF THE PRODUCT";
        cout << "\n\tENTER THE PRODUCT NUMBER: ";
        cin >> n;
        cout << "\n\tENTER THE PRODUCT NAME: ";
        cin.ignore();
        getline(cin, p);
        cout << "\n\tENTER THE PRODUCT RATE: ";
        cin >> r;
        Product prod(n, p, r);
    }

    static void displayProduct() {
        system("cls");
        ifstream displayProducts("Products.txt");
        if (!displayProducts) {
            cout << "\n\n\tUnable to open product file!";
            getch();
            return;
        }

        int n;
        string p;
        float r;
        cout << "\n\n\tDISPLAY ALL PRODUCTS";
        cout << "\n\t=================================================================";

        while (displayProducts >> n >> p >> r) {
            cout << "\n\tPRODUCT NUMBER : " << n;
            cout << "\n\tPRODUCT NAME   : " << p;
            cout << "\n\tRATE OF PRODUCT: " << r;
            cout << "\n\t=================================================================";
        }

        displayProducts.close();
        cout << "\n\tPress any key to continue...";
        getch();
    }

    static void modifyProduct() {
        system("cls");
        displayProduct();
        ifstream prodIn("Products.txt");
        ofstream prodTmp("temp.txt");

        if (!prodIn || !prodTmp) {
            cout << "\n\tFile operation failed!";
            return;
        }

        int modNum;
        cout << "\n\tEnter the Product Number to Modify: ";
        cin >> modNum;

        int n;
        string p;
        float r;

        while (prodIn >> n >> p >> r) {
            if (n == modNum) {
                cout << "\n\tEnter new rate: ";
                cin >> r;
            }
            prodTmp << n << ' ' << p << ' ' << r << endl;
        }

        prodIn.close();
        prodTmp.close();
        remove("Products.txt");
        rename("temp.txt", "Products.txt");

        cout << "\n\n\n\tPRODUCT RATE UPDATED SUCCESSFULLY";
        getch();
    }

    static void deleteProduct() {
        system("cls");
        displayProduct();
        ifstream prodIn("Products.txt");
        ofstream prodTmp("temp.txt");

        if (!prodIn || !prodTmp) {
            cout << "\n\tFile operation failed!";
            return;
        }

        int modNum;
        cout << "\n\tEnter the Product Number to Delete: ";
        cin >> modNum;

        int n;
        string p;
        float r;

        while (prodIn >> n >> p >> r) {
            if (n != modNum) {
                prodTmp << n << ' ' << p << ' ' << r << endl;
            }
        }

        prodIn.close();
        prodTmp.close();
        remove("Products.txt");
        rename("temp.txt", "Products.txt");

        cout << "\n\n\n\tPRODUCT DELETED SUCCESSFULLY";
        getch();
    }
};

int main() {
    NavPages::intro();
    getch();
    system("cls");

    while (1) {
        NavPages::user();
    }

    return 0;
}
