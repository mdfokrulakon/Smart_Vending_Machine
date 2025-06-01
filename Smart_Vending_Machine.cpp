#include <bits/stdc++.h>
#include <ctime>
using namespace std;

struct Product {
    string name;
    int price;
};

// Quick Sort by product name
int partition(vector<Product>& products, int low, int high) {
    string pivot = products[high].name;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (products[j].name < pivot) {
            i++;
            swap(products[i], products[j]);
        }
    }
    swap(products[i + 1], products[high]);
    return i + 1;
}

void quickSort(vector<Product>& products, int low, int high) {
    if (low < high) {
        int pi = partition(products, low, high);
        quickSort(products, low, pi - 1);
        quickSort(products, pi + 1, high);
    }
}

// Binary Search by product name
int binarySearch(const vector<Product>& products, const string& key) {
    int low = 0, high = (int)products.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (products[mid].name == key)
            return mid;
        else if (products[mid].name < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Greedy Coin Change
void giveChange(int change, const vector<int>& coins) {
    cout << "Returning change: " << change << endl;
    for (int coin : coins) {
        int count = change / coin;
        if (count > 0) {
            cout << "Tk " << coin << " x " << count << endl;
            change -= coin * count;
        }
    }
    if (change > 0)
        cout << "Cannot return exact change with available coins.\n";
}

int main() {
    vector<Product> beverages = {
    {"Mango Juice", 45}, {"Apple Juice", 50}, {"Mozo", 45}, {"StarShip", 30},
    {"Drinko", 10}, {"Max Cola", 20}, {"Sprite", 40}, {"Fanta", 35},
    {"Pepsi", 25}, {"7Up", 30}};

    vector<Product> chips = {
    {"Lays", 30}, {"Pringles", 60}, {"Bingo", 25}, {"Aluz", 20},
    {"Kurkure", 15}, {"Sun", 10}, {"Cheetos", 35}, {"Haldiram", 25},
    {"Ruffles", 40}, {"Uncle Chips", 20}};

    vector<Product> chocolates = {
    {"Dairy Milk", 40}, {"Perk Chocolate", 35}, {"Choco Pie", 30}, {"Kitkat", 30},
    {"Silk", 40}, {"Hershey", 30}, {"Snickers", 45}, {"Galaxy", 50},
    {"Toblerone", 60}, {"Bounty", 35}};
    vector<int> coins = {500,100, 50, 10, 5};

    vector<Product> cart;
    int totalPrice = 0;

    while (true) {
        cout << "\n=== Smart Vending Machine ===\n";
        cout << "1. Beverages\n2. Chips\n3. Chocolates\n4. Checkout/Exit\n";
        cout << "Enter choice (1-4): ";
        int choice; cin >> choice; cin.ignore();

        vector<Product> category;

        if (choice == 1)
            category = beverages;
        else if (choice == 2)
            category = chips;
        else if (choice == 3)
            category = chocolates;
        else if (choice == 4) {
            if (cart.empty()) {
                cout << "No items in cart. Exiting. Thank you!\n";
                break;
            }
            cout << "\nYour cart:\n";
            for (const auto& p : cart)
                cout << "- " << p.name << " (Tk " << p.price << ")\n";
            cout << "Total: Tk " << totalPrice << "\nInsert money (Tk): ";
            int paid; cin >> paid;

            if (paid < totalPrice) {
                cout << "Not enough money. Transaction cancelled.\n";
            } else {
                // Time coin change
                clock_t startChange = clock();
                giveChange(paid - totalPrice, coins);
                clock_t endChange = clock();

                double changeDuration = double(endChange - startChange) / CLOCKS_PER_SEC;
                cout << "Coin Change calculation took " << changeDuration << " seconds.\n";

                cout << "Thank you for your purchase!\n";
                cart.clear();
                totalPrice = 0;
            }
            continue;
        }
        else {
            cout << "Invalid choice.\n";
            continue;
        }

        // Timing Quick Sort
        clock_t startSort = clock();
        quickSort(category, 0, (int)category.size() - 1);
        clock_t endSort = clock();

        double sortDuration = double(endSort - startSort) / CLOCKS_PER_SEC;
        cout << "\nProducts sorted by name:\n";
        for (const auto& p : category)
            cout << "- " << p.name << " (Tk " << p.price << ")\n";
        cout << "Quick Sort took " << sortDuration << " seconds.\n";

        cout << "Enter exact product name to add to cart (or 'back' to return): ";
        string productName; getline(cin, productName);
        if (productName == "back")
            continue;

        // Timing Binary Search
        clock_t startSearch = clock();
        int idx = binarySearch(category, productName);
        clock_t endSearch = clock();

        double searchDuration = double(endSearch - startSearch) / CLOCKS_PER_SEC;

        if (idx == -1) {
            cout << "Product not found.\n";
        } else {
            cart.push_back(category[idx]);
            totalPrice += category[idx].price;
            cout << productName << " added to cart. Total: Tk " << totalPrice << endl;
        }
        cout << "Binary Search took " << searchDuration << " seconds.\n";
    }

    return 0;
}
