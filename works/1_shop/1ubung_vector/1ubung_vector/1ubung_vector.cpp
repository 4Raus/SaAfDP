#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

struct Item {
    string name;
    int part_number;
    int quantity;
    double price_per_unit;
};

struct Order {
    int order_number;
    string order_date;
    string customer_name;
    string phone_number;
    vector<Item> items;
};

class SupermarketOrderList {

public:
    vector<Order> orders;
    double get_order_purchase_price(int order_number);
    void add_item_to_order(int order_number, const Item& item);
    void add_order(const Order& order);
    void remove_order(int order_number);
    void print_table(const Order& order);
    bool order_exists(int order_number) const;
};

double SupermarketOrderList::get_order_purchase_price(int order_number) {
    double total_purchase_price = 0.0;
    for (const auto& item : orders[order_number].items) {
        total_purchase_price += item.price_per_unit * item.quantity;
    }
    return total_purchase_price;
}

void SupermarketOrderList::add_item_to_order(int order_number, const Item& item) {
    for (int i = 0; i < orders.size(); i++) {
        if (orders[i].order_number == order_number) {
            orders[i].items.push_back(item);
        }
    }
}

void SupermarketOrderList::add_order(const Order& order) {
    orders.push_back(order);
}

void SupermarketOrderList::remove_order(int order_number) {
    for (int i = 0; i < orders.size(); i++) {
        if (orders[i].order_number == order_number) {
            orders.erase(orders.begin() + i);
        }
    }

}

void SupermarketOrderList::print_table(const Order& order) {
    cout << "Order Number: " << order.order_number << endl;
    cout << "Order Date: " << order.order_date << endl;
    cout << "Customer Name: " << order.customer_name << endl;
    cout << "Phone Number: " << order.phone_number << endl;
    cout << "Items:" << endl;
    cout << setw(20) << left << "Name";
    cout << setw(15) << left << "Part Number";
    cout << setw(10) << left << "Quantity";
    cout << setw(10) << left << "Price/Unit";
    cout << setw(10) << left << "Total Price" << endl;
    cout << setfill('-') << setw(65) << "" << setfill(' ') << endl;
    double total_price = 0;
    for (int i = 0; i < order.items.size(); i++) {
        const Item& item = order.items[i];
        double item_price = item.price_per_unit * item.quantity;
        cout << setw(20) << left << item.name;
        cout << setw(15) << left << item.part_number;
        cout << setw(10) << left << item.quantity;
        cout << setw(10) << left << item.price_per_unit;
        cout << setw(10) << left << item_price << endl;
        total_price += item_price;
    }
    cout << setfill('-') << setw(65) << "" << setfill(' ') << endl;
    cout << setw(55) << left << "Total Purchase Price:" << total_price << endl;
}


bool SupermarketOrderList::order_exists(int order_number) const {
    for (int i = 0; i < orders.size(); i++) {
        if (orders[i].order_number == order_number) {
            return true;
        }
    }
    return false;
}

int main() {
    SupermarketOrderList order_list;
    char choice;
    system("CLS");

    do {
        cout << "Select an option:" << endl;
        cout << "1. Add new order" << endl;
        cout << "2. Add item to order" << endl;
        cout << "3. Remove order" << endl;
        cout << "4. Total price" << endl;
        cout << "5. Print table" << endl;
        cout << "6. Exit" << endl;

        cin >> choice;

        switch (choice) {
        case '1': {
            Order order;
            cout << "Enter order number: ";
            cin >> order.order_number;
            cout << "Enter order date: ";
            cin >> order.order_date;
            cout << "Enter customer name: ";
            cin >> order.customer_name;
            cout << "Enter phone number: ";
            cin >> order.phone_number;

            char add_item_choice;
            do {
                Item item;
                cout << "Enter item name: ";
                cin >> item.name;
                cout << "Enter part number: ";
                cin >> item.part_number;
                cout << "Enter quantity: ";
                cin >> item.quantity;
                cout << "Enter price per unit: ";
                cin >> item.price_per_unit;

                order.items.push_back(item);

                cout << "Add another item? (Y/N): ";
                cin >> add_item_choice;
            } while (add_item_choice == 'Y' || add_item_choice == 'y');

            order_list.add_order(order);
            cout << "Order added successfully!\n" << endl;
            system("CLS");
            break;
        }
        case '2': {
            int order_number;
            cout << "Enter order number: ";
            cin >> order_number;

            if (order_list.order_exists(order_number)) {
                Item item;
                cout << "Enter item name: ";
                cin >> item.name;
                cout << "Enter part number: ";
                cin >> item.part_number;
                cout << "Enter quantity: ";
                cin >> item.quantity;
                cout << "Enter price per unit: ";
                cin >> item.price_per_unit;

                order_list.add_item_to_order(order_number, item);
                cout << "Item added to order successfully!" << endl;
            }
            else {
                cout << "Order not found!" << endl;
            }
            system("CLS");
            break;
        }
        case '3': {
            int order_number;
            cout << "Enter order number: ";
            cin >> order_number;

            if (order_list.order_exists(order_number)) {
                order_list.remove_order(order_number);
                cout << "Order removed successfully!" << endl;
            }
            else {
                cout << "Order not found!" << endl;
            }
            system("CLS");
            break;
        }
        case '4': {
            int order_number;
            cout << "Enter order number: ";
            cin >> order_number;
            for (int i = 0; i < order_list.orders.size(); i++) {
                if (order_list.orders[i].order_number == order_number) {
                    cout << "$" << order_list.get_order_purchase_price(i) << endl;
                }
            }
            break;
        }
        case '5': {
            int order_number;
            cout << "Enter order number: ";
            cin >> order_number;
            for (int i = 0; i < order_list.orders.size(); i++) {
                if (order_list.orders[i].order_number == order_number) {
                    order_list.print_table(order_list.orders[i]);
                }
            }
            break;
        }
        case '6': {
            cout << "Exiting program..." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
        }
    } while (true);

    return 0;
}