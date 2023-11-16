#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TABLES 4
#define MAX_ITEMS 6

struct MenuItem {
    char name[50];
    double price;
};

struct OrderItem {
    struct MenuItem item;
    int quantity;
};

struct Order {
    struct OrderItem items[MAX_ITEMS];
    int itemCount;
};

struct Table {
    int number;
    struct Order order;
};

// Function to initialize table numbers
void initializeTables(struct Table tables[], int numTables) {
    for (int i = 0; i < numTables; i++) {
        tables[i].number = i + 1;
        tables[i].order.itemCount = 0;
    }
}

// Function to display the menu
void displayMenu(struct MenuItem menu[], int numItems) {
    printf("Menu:\n");
    for (int i = 0; i < numItems; i++) {
        printf("%d. %s - Rs. %.2f\n", i + 1, menu[i].name, menu[i].price);
    }
}

int main() {
    struct Table tables[MAX_TABLES];
    struct MenuItem *menu = malloc(MAX_ITEMS * sizeof(struct MenuItem));

    if (menu == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return 1;
    }

    // Initialize table numbers
    initializeTables(tables, MAX_TABLES);

    // Initialize menu items
    strcpy(menu[0].name, "Pizza");
    menu[0].price = 799;
    strcpy(menu[1].name, "Burger");
    menu[1].price = 499;
    strcpy(menu[2].name, "Salad");
    menu[2].price = 299;
    strcpy(menu[3].name, "Beverage");
    menu[3].price = 199;
    strcpy(menu[4].name, "Garlic Bread");
    menu[4].price = 299;
    strcpy(menu[5].name, "Lasagna"); // Add a new menu item
    menu[5].price = 499;

    // Display the menu
    displayMenu(menu, MAX_ITEMS);

    int tableNum, itemQty, itemChoice;

    printf("Enter table number: ");
    if (scanf("%d", &tableNum) != 1 || tableNum < 1 || tableNum > MAX_TABLES) {
        printf("Invalid table number. Please enter a valid table number between 1 and %d.\n", MAX_TABLES);
        free(menu); // Free allocated memory before exiting
        return 1;  // Exit with an error code
    }

    struct Table *table = &tables[tableNum - 1];

    // Order items for the selected table
    while (1) {
        printf("Enter the item number to order (1-%d, 0 to finish): ", MAX_ITEMS);
        if (scanf("%d", &itemChoice) != 1 || itemChoice < 0 || itemChoice > MAX_ITEMS) {
            printf("Invalid item number. Please enter a valid item number.\n");
            continue;
        }

        if (itemChoice == 0) {
            break;  // Finish ordering
        }

        printf("Enter the quantity: ");
        if (scanf("%d", &itemQty) != 1 || itemQty < 1) {
            printf("Invalid quantity. Please enter a valid quantity.\n");
            continue;
        }

        struct OrderItem orderItem;
        orderItem.item = menu[itemChoice - 1];
        orderItem.quantity = itemQty;

        table->order.items[table->order.itemCount] = orderItem;
        table->order.itemCount++;
    }

    // Calculate the total for the selected table
    double total = 0;
    for (int i = 0; i < table->order.itemCount; i++) {
        total += table->order.items[i].item.price * table->order.items[i].quantity;
    }

    // Print the total for the selected table
    printf("Total for table %d: Rs. %.2f\n", table->number, total);

    free(menu); // Free allocated memory before exiting
    return 0;
}
