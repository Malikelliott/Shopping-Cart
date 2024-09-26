/*
Assignment 2
Filename: main.c
Author: Malik Elliott 991610598
Menu Options for Shopping Cart List
Date: February 16 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 15

typedef struct item{
    int id;
    char name[10];
    float price;
    int quantity;
} Item;

typedef struct node{
    Item data;
    struct node *next;
    struct node *prev;
} Node, *NodePtr;

NodePtr makeNode (Item x);
void display(NodePtr ptr);
NodePtr insert (NodePtr ptr, Item x);
NodePtr delete (NodePtr ptr, Item x);
int countList (NodePtr p);
NodePtr search (NodePtr top, int key);
void saveToFile (NodePtr ptr, Item x, float f);
void updateList (NodePtr ptr, Item x);

int main(void){
    
    char name[MAXLEN][MAXLEN] = {"", "Carrot", "Banana",  "Orange", "Parsnip", "Avocado", "Blueberry", "Cherry", "Asparagus", "Cabbage", "Celery"};
    float price[MAXLEN] = {0, 1.49, 2.25, 2.75, 1.25, .99, 1.25, 2.25, 2.00, 3.5, 1.25};
    Item it;
    NodePtr cartList;
    float totalPrice = 0;
    
    for(int i = 1; i < 11; i++){ 
        it.id = i;
        strcpy(it.name, name[i]);
        it.price = price[i];
        it.quantity = rand() % 10;
        cartList = insert (cartList, it);
        totalPrice += (it.quantity * it.price);
    }
    int option = 0;
    printf("Welcome to Assignment 2!\n\n");
    display(cartList);
    printf("No of Items: %d\n", countList(cartList));
    printf("Total Price: %.2f\n", totalPrice);
    while (option <= 6) {
        printf(
        "What would you like to do next?\n"
        "1 Edit Cart Item\n"
        "2 Add Item to Cart\n"
        "3 Display list of Items\n"
        "4 Display total Price\n"
        "5 Remove an Item\n"
        "6 Save list to a file\n"
        "Press any other Key 7-9 to Exit\n");
        scanf("%d", &option);
       
        if (option == 1){
            updateList(cartList, it);
            totalPrice += (it.quantity * it.price);
        } else if (option == 2){
            char na[MAXLEN]; float pr; int qu;
            printf("Enter a name, price and quantity\n");
            scanf("%s%f%d", na, &pr, &qu);
            it.id = countList(cartList) + 1;
            strcpy(it.name, na);
            it.price = pr;
            it.quantity = qu;
            cartList = insert(cartList, it);
            totalPrice += (it.quantity * it.price);
            printf("%s has been added to the list!\n", na);
        } else if (option == 3){
            display(cartList);
            printf("No of Items: %d\n", countList(cartList));
            printf("Total Price: %.2f\n", totalPrice);
        } else if (option == 4){
            printf("No of Items: %d\n", countList(cartList));
            printf("Total Price: %.2f\n", totalPrice);
        } else if (option == 5){
            cartList = delete(cartList, it);
            totalPrice -= (it.quantity * it.price);
        } else if (option == 6){
            saveToFile(cartList, it, totalPrice);
        } else {
            printf("Goodbye\n");
        }
    }
}

NodePtr makeNode (Item x){
    NodePtr iList = (NodePtr) malloc(sizeof(Node));
    iList->data = x;
    iList->next = NULL;
    iList->prev = NULL;
    return (iList);
}

void display (NodePtr ptr){
    printf("ID\t| Item Name\t| Price\t| Quantity\n");
    printf("---------------------------------------\n");
    while (ptr !=NULL){
        printf("%02d:\t| %s\t| %.2f\t| %d\n",
        ptr->data.id, ptr->data.name,
        ptr->data.price, ptr->data.quantity);
        ptr = ptr->next;
    }
};

NodePtr insert (NodePtr ptr, Item x) {
    NodePtr cur = makeNode(x);
    cur->next = ptr;
    ptr = cur;
    return(ptr);
};

NodePtr delete (NodePtr ptr, Item x){
    int id;
    printf("Enter ID of item you would like to delete:\n");
    scanf("%d",&id);
    NodePtr ptr2 = search(ptr, id);
    if (ptr2 != NULL){
        NodePtr prev;
        prev = ptr2;
        ptr2 = ptr->next;
        free(prev);
        prev=NULL;
        printf("Deleting item %d\n",id);
    } else if (ptr2->next == NULL){
        free(ptr2);
        printf("Deleting item %d\n",id);
        ptr2 = NULL;
    } else {
        printf("No item by that id\n");
    }
    return(ptr);
}

int countList(NodePtr p){
    int count = 0;
	NodePtr cur = p;
	while (cur !=NULL) {
		count++;
		cur = cur->next;
	}
	return (count);
}

void updateList(NodePtr ptr, Item x){
    int id;
    printf("Edit which item? (Enter ID)\n");
    scanf("%d",&id);
    NodePtr ptr2 = search(ptr, id);
    int opt;
    if (ptr2 != NULL){
        printf("What would you like to change the quantity to?\n");
        scanf("%d", &opt);
        ptr2->data.quantity = opt;
        printf("Item no. %d edited!\n",id);
    } else
        printf("No item by that id\n");
}

void saveToFile(NodePtr ptr, Item x, float totalPrice){
    FILE *fp;
    fp=fopen("reciept.txt", "w");
    if (fp == NULL)
        printf("File not exist");
    else {
        fprintf(fp, "Thank you for checking out!!\n\n");
        fprintf(fp, "ID\t| Item Name\t| Price\t| Quantity\n");
        fprintf(fp, "---------------------------------------\n");
        int no = countList(ptr);
        do {
            fprintf(fp, "%02d:\t| %s\t| %.2f\t| %d\n", 
            ptr->data.id, ptr->data.name, ptr->data.price, ptr->data.quantity);
            ptr = ptr->next;
        } while (ptr != NULL);
        fprintf(fp, "No of Items: %d\n", no);
        fprintf(fp, "Total Price: %.2f\n", totalPrice);
        printf("Saved to file 'reciept.txt'!\n");
    }
}

NodePtr search(NodePtr ptr, int key){
    NodePtr cur = ptr;
    while (cur!= NULL && cur->data.id!=key)
    cur = cur->next;
    return (cur);
}
