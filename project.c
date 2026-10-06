/* Stationery Items and Sales Management System

   Data structures used:
   1. Singly linked list - items
   2. Singly linked list - sales
   3. Queue (linked)     - reorder management
   4. Stack (linked)     - undo last sale
   5. Array + sorting    - sales percentage, profit and product analysis

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Structures ---------- */
struct Item {
    int id;
    char name[30];
    char category[20];
    float cost_price, selling_price;
    int quantity, reorder_level, total_sold;
    struct Item *next;
};

struct Sale {
    int sale_id, item_id, qty;
    float revenue, profit;
    struct Sale *next;
};

struct QueueNode {
    int item_id;
    struct QueueNode *next;
};

struct StackNode {
    int sale_id;
    struct StackNode *next;
};

/* ---------- Global heads ---------- */
struct Item *itemHead = NULL;
struct Sale *saleHead = NULL, *saleTail = NULL;
struct QueueNode *front = NULL, *rear = NULL;
struct StackNode *top = NULL;
int saleCounter = 0;

/* ---------- Table borders (for neat output) ---------- */
#define ITEM_LINE  "+------+----------------------+--------------+-----------+-----------+-------+---------+\n"
#define SALE_LINE  "+--------+--------+-------+------------+------------+\n"
#define QUEUE_LINE "+------+----------------------+--------+--------+\n"
#define PCT_LINE   "+----------------------+--------+-----------+\n"
#define PROF_LINE  "+----------------------+--------+--------------+\n"
#define RANK_LINE  "+------+----------------------+--------------+\n"

/* ---------- Function prototypes (functions of all members) ---------- */
/* Member 1 */
struct Item *findItem(int id);
void addItem();
void displayItems();
void updateItem();
/* Member 2 */
int isInQueue(int id);
void enqueueReorder(int id);
int dequeueReorder();
void checkReorderLevels();
void displayReorderQueue();
void processReorder();
void checkAvailability();
/* Member 3 */
void recordSale();
void displaySales();
void deleteItem();
void freeAll();
/* Member 4 */
void push(int sale_id);
int pop();
void undoLastSale();
void searchByName();
void salesPercentage();
/* Member 5 */
int copyToArray(struct Item *arr[]);
float itemProfit(struct Item *t);
void sortArray(struct Item *arr[], int n, int mode);
void profitAnalysis();
void productAnalysis();


/* =====================================================================
   MEMBER 1 : ITEM MANAGEMENT (singly linked list of items)
   ===================================================================== */

struct Item *findItem(int id) {
    struct Item *t = itemHead;
    while (t != NULL) {
        if (t->id == id) return t;
        t = t->next;
    }
    return NULL;
}

void addItem() {
    struct Item *n = (struct Item *)malloc(sizeof(struct Item));
    printf("Item ID: ");
    scanf("%d", &n->id);
    if (findItem(n->id) != NULL) {
        printf("ID already exists!\n");
        free(n);
        return;
    }
    printf("Name: ");
    scanf(" %29[^\n]", n->name);
    printf("Category: ");
    scanf(" %19[^\n]", n->category);
    printf("Cost price: ");
    scanf("%f", &n->cost_price);
    printf("Selling price: ");
    scanf("%f", &n->selling_price);
    printf("Quantity: ");
    scanf("%d", &n->quantity);
    printf("Reorder level: ");
    scanf("%d", &n->reorder_level);
    n->total_sold = 0;
    n->next = NULL;

    if (itemHead == NULL) itemHead = n;
    else {
        struct Item *t = itemHead;
        while (t->next != NULL) t = t->next;
        t->next = n;
    }
    printf("Item added.\n");
}

void displayItems() {
    struct Item *t = itemHead;
    if (t == NULL) { printf("No items.\n"); return; }
    printf("\n" ITEM_LINE);
    printf("| %-4s | %-20s | %-12s | %9s | %9s | %5s | %7s |\n",
           "ID", "Name", "Category", "Cost", "Price", "Qty", "Reorder");
    printf(ITEM_LINE);
    while (t != NULL) {
        printf("| %-4d | %-20s | %-12s | %9.2f | %9.2f | %5d | %7d |\n",
               t->id, t->name, t->category, t->cost_price,
               t->selling_price, t->quantity, t->reorder_level);
        t = t->next;
    }
    printf(ITEM_LINE);
}

void updateItem() {
    int id;
    printf("Item ID to update: ");
    scanf("%d", &id);
    struct Item *t = findItem(id);
    if (t == NULL) { printf("Item not found.\n"); return; }
    printf("New name: ");
    scanf(" %29[^\n]", t->name);
    printf("New category: ");
    scanf(" %19[^\n]", t->category);
    printf("New cost price: ");
    scanf("%f", &t->cost_price);
    printf("New selling price: ");
    scanf("%f", &t->selling_price);
    printf("New quantity: ");
    scanf("%d", &t->quantity);
    printf("New reorder level: ");
    scanf("%d", &t->reorder_level);
    printf("Item updated.\n");
}


/* =====================================================================
   MEMBER 2 : REORDER QUEUE (linked queue) + AVAILABILITY CHECK
   ===================================================================== */

int isInQueue(int id) {
    struct QueueNode *q = front;
    while (q != NULL) {
        if (q->item_id == id) return 1;
        q = q->next;
    }
    return 0;
}

void enqueueReorder(int id) {
    struct QueueNode *n = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    n->item_id = id;
    n->next = NULL;
    if (rear == NULL) front = rear = n;
    else { rear->next = n; rear = n; }
}

int dequeueReorder() {
    if (front == NULL) return -1;
    struct QueueNode *t = front;
    int id = t->item_id;
    front = front->next;
    if (front == NULL) rear = NULL;
    free(t);
    return id;
}

void checkReorderLevels() {
    struct Item *t = itemHead;
    while (t != NULL) {
        if (t->quantity <= t->reorder_level && !isInQueue(t->id))
            enqueueReorder(t->id);
        t = t->next;
    }
}

void displayReorderQueue() {
    struct QueueNode *q = front;
    if (q == NULL) { printf("Reorder queue is empty.\n"); return; }
    printf("\nReorder queue (first row is reordered first)\n");
    printf(QUEUE_LINE);
    printf("| %-4s | %-20s | %6s | %6s |\n", "ID", "Name", "Stock", "Level");
    printf(QUEUE_LINE);
    while (q != NULL) {
        struct Item *it = findItem(q->item_id);
        if (it != NULL)
            printf("| %-4d | %-20s | %6d | %6d |\n",
                   it->id, it->name, it->quantity, it->reorder_level);
        q = q->next;
    }
    printf(QUEUE_LINE);
}

void processReorder() {
    int id = dequeueReorder();
    if (id == -1) { printf("Nothing to reorder.\n"); return; }
    struct Item *t = findItem(id);
    if (t == NULL) { printf("Item no longer exists.\n"); return; }
    int add;
    printf("Reordering %s. Quantity to add: ", t->name);
    scanf("%d", &add);
    t->quantity += add;
    printf("New stock of %s = %d\n", t->name, t->quantity);
}

void checkAvailability() {
    int id;
    printf("Item ID: ");
    scanf("%d", &id);
    struct Item *t = findItem(id);
    if (t == NULL) printf("Item not found.\n");
    else if (t->quantity > 0)
        printf("%s is available. Stock = %d\n", t->name, t->quantity);
    else
        printf("%s is OUT OF STOCK.\n", t->name);
}


/* =====================================================================
   MEMBER 3 : SALES RECORDS (linked list) + NODE DELETION + CLEANUP
   ===================================================================== */

void recordSale() {
    int id, qty;
    printf("Item ID sold: ");
    scanf("%d", &id);
    struct Item *it = findItem(id);
    if (it == NULL) { printf("Item not found.\n"); return; }
    printf("Quantity: ");
    scanf("%d", &qty);
    if (qty <= 0 || qty > it->quantity) {
        printf("Invalid quantity. Available = %d\n", it->quantity);
        return;
    }

    it->quantity -= qty;
    it->total_sold += qty;

    struct Sale *s = (struct Sale *)malloc(sizeof(struct Sale));
    s->sale_id = ++saleCounter;
    s->item_id = id;
    s->qty = qty;
    s->revenue = qty * it->selling_price;
    s->profit = qty * (it->selling_price - it->cost_price);
    s->next = NULL;

    if (saleHead == NULL) saleHead = saleTail = s;
    else { saleTail->next = s; saleTail = s; }

    push(s->sale_id);
    checkReorderLevels();
    printf("Sale #%d recorded. Revenue = %.2f, Profit = %.2f\n",
           s->sale_id, s->revenue, s->profit);
}

void displaySales() {
    struct Sale *s = saleHead;
    if (s == NULL) { printf("No sales yet.\n"); return; }
    printf("\n" SALE_LINE);
    printf("| %-6s | %-6s | %5s | %10s | %10s |\n",
           "SaleID", "ItemID", "Qty", "Revenue", "Profit");
    printf(SALE_LINE);
    while (s != NULL) {
        printf("| %-6d | %-6d | %5d | %10.2f | %10.2f |\n",
               s->sale_id, s->item_id, s->qty, s->revenue, s->profit);
        s = s->next;
    }
    printf(SALE_LINE);
}

void deleteItem() {
    int id;
    printf("Item ID to delete: ");
    scanf("%d", &id);
    struct Item *t = itemHead, *prev = NULL;
    while (t != NULL && t->id != id) {
        prev = t;
        t = t->next;
    }
    if (t == NULL) { printf("Item not found.\n"); return; }
    if (prev == NULL) itemHead = t->next;
    else prev->next = t->next;
    free(t);
    printf("Item deleted.\n");
}

void freeAll() {
    while (itemHead != NULL) {
        struct Item *t = itemHead;
        itemHead = itemHead->next;
        free(t);
    }
    while (saleHead != NULL) {
        struct Sale *t = saleHead;
        saleHead = saleHead->next;
        free(t);
    }
    while (dequeueReorder() != -1) { }
    while (pop() != -1) { }
}


/* =====================================================================
   MEMBER 4 : UNDO (stack) + SEARCH BY NAME + SALES PERCENTAGE
   ===================================================================== */

void push(int sale_id) {
    struct StackNode *n = (struct StackNode *)malloc(sizeof(struct StackNode));
    n->sale_id = sale_id;
    n->next = top;
    top = n;
}

int pop() {
    if (top == NULL) return -1;
    struct StackNode *t = top;
    int id = t->sale_id;
    top = top->next;
    free(t);
    return id;
}

void undoLastSale() {
    int sid = pop();
    if (sid == -1) { printf("No sale to undo.\n"); return; }

    struct Sale *s = saleHead, *prev = NULL;
    while (s != NULL && s->sale_id != sid) {
        prev = s;
        s = s->next;
    }
    if (s == NULL) return;

    struct Item *it = findItem(s->item_id);
    if (it != NULL) {
        it->quantity += s->qty;
        it->total_sold -= s->qty;
    }

    if (prev == NULL) saleHead = s->next;
    else prev->next = s->next;
    if (s == saleTail) saleTail = prev;
    free(s);
    printf("Sale #%d undone.\n", sid);
}

void searchByName() {
    char key[30];
    int found = 0;
    printf("Enter name to search: ");
    scanf(" %29[^\n]", key);
    struct Item *t = itemHead;
    while (t != NULL) {
        if (strcmp(t->name, key) == 0) {
            printf("Found: ID %d, %s, Qty %d, Price %.2f\n",
                   t->id, t->name, t->quantity, t->selling_price);
            found = 1;
        }
        t = t->next;
    }
    if (!found) printf("No item with that name.\n");
}

void salesPercentage() {
    struct Item *arr[100];
    int n = copyToArray(arr), i, total = 0;
    if (n == 0) { printf("No items.\n"); return; }
    for (i = 0; i < n; i++) total += arr[i]->total_sold;
    if (total == 0) { printf("No sales yet.\n"); return; }

    sortArray(arr, n, 1);
    printf("\nSales percentage (highest first)\n");
    printf(PCT_LINE);
    printf("| %-20s | %6s | %9s |\n", "Item", "Sold", "Share");
    printf(PCT_LINE);
    for (i = 0; i < n; i++)
        printf("| %-20s | %6d | %8.2f%% |\n", arr[i]->name,
               arr[i]->total_sold, (arr[i]->total_sold * 100.0) / total);
    printf(PCT_LINE);
}


/* =====================================================================
   MEMBER 5 : PROFIT AND PRODUCT ANALYSIS (array + sorting)
   ===================================================================== */

int copyToArray(struct Item *arr[]) {
    int n = 0;
    struct Item *t = itemHead;
    while (t != NULL) {
        arr[n++] = t;
        t = t->next;
    }
    return n;
}

float itemProfit(struct Item *t) {
    return t->total_sold * (t->selling_price - t->cost_price);
}

/* mode 1 = sort by units sold, mode 2 = sort by profit (descending) */
void sortArray(struct Item *arr[], int n, int mode) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            int swap;
            if (mode == 1) swap = arr[j]->total_sold < arr[j + 1]->total_sold;
            else swap = itemProfit(arr[j]) < itemProfit(arr[j + 1]);
            if (swap) {
                struct Item *tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void profitAnalysis() {
    struct Item *arr[100];
    int n = copyToArray(arr), i;
    float totalRevenue = 0, totalProfit = 0;
    struct Sale *s = saleHead;
    while (s != NULL) {
        totalRevenue += s->revenue;
        totalProfit += s->profit;
        s = s->next;
    }
    printf("\n+-------------------------+------------+\n");
    printf("| Total revenue           | %10.2f |\n", totalRevenue);
    printf("| Total profit            | %10.2f |\n", totalProfit);
    printf("+-------------------------+------------+\n");

    sortArray(arr, n, 2);
    printf("\nProfit per item (highest first)\n");
    printf(PROF_LINE);
    printf("| %-20s | %6s | %12s |\n", "Item", "Units", "Profit");
    printf(PROF_LINE);
    for (i = 0; i < n; i++)
        printf("| %-20s | %6d | %12.2f |\n", arr[i]->name,
               arr[i]->total_sold, itemProfit(arr[i]));
    printf(PROF_LINE);
}

void productAnalysis() {
    struct Item *arr[100];
    int n = copyToArray(arr), i;
    if (n == 0) { printf("No items.\n"); return; }
    int limit = n < 3 ? n : 3;

    sortArray(arr, n, 1);
    printf("\nTop %d best sellers\n", limit);
    printf(RANK_LINE);
    printf("| %-4s | %-20s | %12s |\n", "Rank", "Item", "Units sold");
    printf(RANK_LINE);
    for (i = 0; i < limit; i++)
        printf("| %-4d | %-20s | %12d |\n", i + 1, arr[i]->name, arr[i]->total_sold);
    printf(RANK_LINE);

    sortArray(arr, n, 2);
    printf("\nTop %d most profitable\n", limit);
    printf(RANK_LINE);
    printf("| %-4s | %-20s | %12s |\n", "Rank", "Item", "Profit");
    printf(RANK_LINE);
    for (i = 0; i < limit; i++)
        printf("| %-4d | %-20s | %12.2f |\n", i + 1, arr[i]->name, itemProfit(arr[i]));
    printf(RANK_LINE);
}


/* =====================================================================
   EVERYONE : MENU AND MAIN (unchanged)
   ===================================================================== */

void displayMenu() {
    printf("\n+----------------------------------------+\n");
    printf("|   STATIONERY MANAGEMENT SYSTEM         |\n");
    printf("+----------------------------------------+\n");
    printf("|  1. Add item                           |\n");
    printf("|  2. Display items                      |\n");
    printf("|  3. Update item                        |\n");
    printf("|  4. Delete item                        |\n");
    printf("|  5. Check item availability            |\n");
    printf("|  6. Search item by name                |\n");
    printf("|  7. Record sale                        |\n");
    printf("|  8. Display sales                      |\n");
    printf("|  9. Undo last sale                     |\n");
    printf("| 10. Show reorder queue                 |\n");
    printf("| 11. Process reorder                    |\n");
    printf("| 12. Sales percentage                   |\n");
    printf("| 13. Profit analysis                    |\n");
    printf("| 14. Product analysis                   |\n");
    printf("|  0. Exit                               |\n");
    printf("+----------------------------------------+\n");
    printf("Enter choice: ");
}

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:  addItem(); break;
            case 2:  displayItems(); break;
            case 3:  updateItem(); break;
            case 4:  deleteItem(); break;
            case 5:  checkAvailability(); break;
            case 6:  searchByName(); break;
            case 7:  recordSale(); break;
            case 8:  displaySales(); break;
            case 9:  undoLastSale(); break;
            case 10: checkReorderLevels(); displayReorderQueue(); break;
            case 11: processReorder(); break;
            case 12: salesPercentage(); break;
            case 13: profitAnalysis(); break;
            case 14: productAnalysis(); break;
            case 0:  freeAll(); printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}