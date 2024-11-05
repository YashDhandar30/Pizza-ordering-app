#include <iostream>
#include <string>
using namespace std;
// Struct to represent a pizza
struct Pizza {
    string name;
    int price;  // Price in rupees
};
// Class to implement a simple circular queue
class PizzaQueue {
private:
    int front, rear, capacity;
    Pizza* queue;

public:
    PizzaQueue(int size) {
        capacity = size;
        queue = new Pizza[capacity];
        front = rear = -1;
    }

    ~PizzaQueue() {
        delete[] queue;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % capacity == front;
    }
    void enqueue(Pizza pizza) {
        if (isFull()) {
            cout << "Order queue is full. Cannot place more orders.\n";
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        queue[rear] = pizza;
        cout << "Order placed: " << pizza.name << "\n";
    }
    void dequeue() {
        if (isEmpty()) {
            cout << "No pending orders.\n";
            return;
        }
        cout << "Processing order for: " << queue[front].name << "\n";
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
    }
};
// Function to display the pizza menu
void displayMenu(Pizza menu[], int size) {
    cout << "\n--- Pizza Menu ---\n";
    for (int i = 0; i < size; ++i) {
        cout << i + 1 << ". " << menu[i].name << " ₹" << menu[i].price << "\n";
    }
    cout << "------------------\n";
}
// Function to place an order
void placeOrder(PizzaQueue& orderQueue, Pizza menu[], int size) {
    int choice;
    cout << "Enter the number of the pizza you want to order: ";
    cin >> choice;

    if (choice < 1 || choice > size) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }

    orderQueue.enqueue(menu[choice - 1]);
}

int main() {
    // Array to hold menu items
    Pizza menu[] = {
        {"Margherita", 650},
        {"Pepperoni", 800},
        {"BBQ Chicken", 950},
        {"Veggie Delight", 700},
        {"Hawaiian", 850}
    };
    int menuSize = sizeof(menu) / sizeof(menu[0]);
    PizzaQueue orderQueue(5);  // max 5 orders in queue
    int choice;
    while (true) {
        cout << "\n--- Pizza Ordering System ---\n";
        cout << "1. View Menu\n";
        cout << "2. Place Order\n";
        cout << "3. Process Next Order\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        switch (choice) {
            case 1:
                displayMenu(menu, menuSize);
                break;
            case 2:
                placeOrder(orderQueue, menu, menuSize);
                break;
            case 3:
                orderQueue.dequeue();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
