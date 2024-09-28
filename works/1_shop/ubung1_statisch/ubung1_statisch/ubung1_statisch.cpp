#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_ITEMS = 100;
const int MAX_ORDERS = 100;

struct Item {
    char name[50];
    int part_number;
    int quantity;
    double price_per_unit;
};

struct Order {
    int order_number;
    char order_date[11];
    char customer_name[50];
    char phone_number[20];
    Item items[MAX_ITEMS];
    int item_count = 0;

    // Function to add an item to the order
    void add_item(const Item& item) {
        items[item_count] = item;
        item_count++;
    }
};

class SupermarketOrderList {
public:
    Order orders[MAX_ORDERS];
    int order_count = 0;

    // Function to determine if an order with a given order number exists in the supermarket order list
    bool order_exists(int order_number) {
        for (int i = 0; i < order_count; i++) {
            if (orders[i].order_number == order_number) {
                return true;
            }
        }
        return false;
    }

    // Function to determine the purchase price of an order
    double purchase_price(Order order) {
        double total_price = 0;
        for (int i = 0; i < order.item_count; i++) {
            total_price += order.items[i].price_per_unit * order.items[i].quantity;
        }
        return total_price;
    }

    // Constructor
    SupermarketOrderList() {
        order_count = 0;
    }

    // Function to add a new order to the supermarket order list
    void add_order(const Order& order) {
        orders[order_count] = order;
        order_count++;
    }

    // Function to add an item to an existing order
    void add_item_to_order(int order_number, const Item& item) {
        for (int i = 0; i < order_count; i++) {
            if (orders[i].order_number == order_number) {
                orders[i].add_item(item);
                return;
            }
        }
        cout << "Order not found" << endl;
    }

    // Function to remove an order with a given order number from the supermarket order list
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
            
            new_orders = orders;
            order_count--;
            cout << "Order removed successfully!" << endl;
        }
        else {
            cout << "Order not found!" << endl;
        }
    }

    // Function to print the supermarket order list
    void print_table(const Order& order) {
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
};

int main() {
    SupermarketOrderList order_list;
    char choice;
    do {
        cout << endl;
        cout << "Supermarket Order Management System" << endl;
        cout << "===================================" << endl;
        cout << "Select an option:" << endl;
        cout << "1. Add new order" << endl;
        cout << "2. Add item to order" << endl;
        cout << "3. Remove order" << endl;
        cout << "4. Print table" << endl;
        cout << "5. Purchase price" << endl;
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
            cin.ignore();
            cin >> order.customer_name;
            cout << "Enter phone number: ";
            cin >> order.phone_number;

            int item_count;
            cout << "Enter number of items: ";
            cin >> item_count;

            for (int i = 0; i < item_count; i++) {
                Item item;
                cout << "Enter item name: ";
                cin.ignore();
                cin >> item.name;
                cout << "Enter item part number: ";
                cin >> item.part_number;
                cout << "Enter item quantity: ";
                cin >> item.quantity;
                cout << "Enter item price per unit: ";
                cin >> item.price_per_unit;
                order.add_item(item);
            }
            order_list.add_order(order);
            break;
        }
        case '2': {
            int order_number;
            cout << "Enter order number: ";
            cin >> order_number;

            if (order_list.order_exists(order_number)) {
                Item item;
                cout << "Enter item name: ";
                cin.ignore();
                cin >> item.name;
                cout << "Enter item part number: ";
                cin >> item.part_number;
                cout << "Enter item quantity: ";
                cin >> item.quantity;
                cout << "Enter item price per unit: ";
                cin >> item.price_per_unit;
                order_list.add_item_to_order(order_number, item);
            }
            else {
                cout << "Order not found." << endl;
            }

            break;
        }
        case '3': {
            int order_number;
            cout << "Enter order number: ";
            cin >> order_number;
            order_list.remove_order(order_number);
            break;
        }
        case '4': {
            int order_number;
            cout << "Enter order number: ";
            cin >> order_number;
            order_list.order_exists(order_number);
            order_list.print_table(order_list.orders[order_number - 1]);
            break;
        }
        case '5': {
            int order_number;
            cout << "Enter order number: ";
            cin >> order_number;
            order_list.order_exists(order_number);
            cout << "$" << order_list.purchase_price(order_list.orders[order_number - 1]) << endl;
            break;
        }
        case '6': {
            cout << "BYE\n";
            break;
        }
        default: {
            cout << "Invalid option. Please try again." << endl;
            break;
        }
        }
    } while (choice != '6');

    return 0;
}