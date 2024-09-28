#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Item {
    char name[50];
    int part_number;
    int quantity;
    double price_per_unit;
};

struct Order {
    int order_number;
    char order_date[20];
    char customer_name[50];
    char phone_number[20];
    Item* items;
    int item_count = 0;
};

struct SupermarketOrderList {
    Order* orders;
    int order_count = 0;

    SupermarketOrderList() {
        orders = nullptr;
        order_count = 0;
    }

    bool order_exists(int order_number) {
        for (int i = 0; i < order_count; i++) {
            if (orders[i].order_number == order_number) {
                return true;
            }
        }
        return false;
    }

    double purchase_price(Order order) {
        double total_price = 0;
        for (int i = 0; i < order.item_count; i++) {
            const Item& item = order.items[i];
            total_price += item.price_per_unit * item.quantity;
        }
        return total_price;
    }

    void add_item(Order& order) {
        Item item;
        cout << "Enter item name: ";
        cin.getline(item.name, 50);
        cout << "Enter item part number: ";
        cin >> item.part_number;
        cout << "Enter item quantity: ";
        cin >> item.quantity;
        cout << "Enter item price per unit: ";
        cin >> item.price_per_unit;
        cin.ignore();
        Item* new_items = new Item[order.item_count + 1];
        if (order.item_count > 0) {
            memcpy(new_items, order.items, order.item_count * sizeof(Item));
            delete[] order.items;
        }
        order.items = new_items;
        order.items[order.item_count++] = item;
        cout << "Item added successfully!" << endl;
    }

    void add_order() {
        Order order;
        cout << "Enter order number: ";
        cin >> order.order_number;
        cin.ignore();
        cout << "Enter order date (DD/MM/YYYY): ";
        cin.getline(order.order_date, 20);
        cout << "Enter customer name: ";
        cin.getline(order.customer_name, 50);
        cout << "Enter customer phone number: ";
        cin.getline(order.phone_number, 20);
        order.items = nullptr;
        order.item_count = 0;
        char choice;
        do {
            cout << "Do you want to add an item to the order? (Y/N): ";
            cin >> choice;
            cin.ignore();
            if (choice == 'Y' || choice == 'y') {
                add_item(order);
            }
        } while (choice == 'Y' || choice == 'y');
        Order* new_orders = new Order[order_count + 1];
        if (order_count > 0) {
            memcpy(new_orders, orders, order_count * sizeof(Order));
            delete[] orders;
        }
        orders = new_orders;
        orders[order_count++] = order;
        cout << "Order added successfully!" << endl;
    }

    void remove_order(int order_number) {
        int index = -1;
        for (int i = 0; i < order_count; i++) {
            if (orders[i].order_number == order_number) {
                index = i;
                break;
            }
        }
        if (index >= 0) {
            Order* new_orders = new Order[order_count - 1];
            if (index > 0) {
                memcpy(new_orders, orders, index * sizeof(Order));
            }
            if (index < order_count - 1) {
                memcpy(new_orders + index, orders + index + 1, (order_count - index - 1) * sizeof(Order));
            }
            delete[] orders;
            orders = new_orders;
            order_count--;
            cout << "Order removed successfully!" << endl;
        }
        else {
            cout << "Order not found!" << endl;
        }
    }

    void display_order(const Order& order) {
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
        for (int i = 0; i < order.item_count; i++) {
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

    void display_orders() {
        if (order_count == 0) {
            cout << "No orders found!" << endl;
        }
        else {
            for (int i = 0; i < order_count; i++) {
                display_order(orders[i]);
            }
        }
    }

    ~SupermarketOrderList() {
        if (orders != nullptr) {
            for (int i = 0; i < order_count; i++) {
                if (orders[i].items != nullptr) {
                    delete[] orders[i].items;
                }
            }
            delete[] orders;
        }
    }
};

int main() {
    SupermarketOrderList order_list;
    char choice;
    do {
        cout << endl;
        cout << "Supermarket Order Management System" << endl;
        cout << "===================================" << endl;
        cout << "1. Add Order" << endl;
        cout << "2. Remove Order" << endl;
        cout << "3. Add Item" << endl;
        cout << "4. Total price" << endl;
        cout << "5. Display Orders" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case '1':
            order_list.add_order();
            break;
        case '2':
            int order_number;
            cout << "Enter order number to remove: ";
            cin >> order_number;
            cin.ignore();
            order_list.remove_order(order_number);
            break;
        case '3': {
            cout << "Enter order number: ";
            int order_number;
            cin >> order_number;
            cin.ignore();
            for (int i = 0; i < order_list.order_count; i++) {
                if (order_list.orders[i].order_number == order_number) {
                    order_list.add_item(order_list.orders[i]);
                    break;
                }
            }
            break;
        }
        case '4': {
            int order_number;
            cout << "Enter order number: ";
            cin >> order_number;
            order_list.order_exists(order_number);
            cout << "$" << order_list.purchase_price(order_list.orders[order_number - 1]) << endl;
            break;
        }
        case '5':
            order_list.display_orders();
            break;
        case '6':
            cout << "BYE\n";
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    } while (choice != '6');
    return 0;
}
