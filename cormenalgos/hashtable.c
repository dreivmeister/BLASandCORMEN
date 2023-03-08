#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 50


// Structs
typedef struct Ht_item {
	int key;
	int value;
}Ht_item;

// Defines the LinkedList.
typedef struct LinkedList {
    Ht_item* item;
    struct LinkedList* next;
} LinkedList;

typedef struct HashTable {
	Ht_item** items;
	LinkedList** overflow_buckets;
	int size;
	int count;
}HashTable;


LinkedList* allocate_list()
{
    // Allocates memory for a LinkedList pointer.
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    return list;
}

LinkedList* linkedlist_insert(LinkedList* list, Ht_item* item)
{
    // first item
    if (list == NULL)
    {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }
	// second item
    else if (list->next == NULL)
    {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }
	// other items
    LinkedList* temp = list;

    while (temp->next->next) {
        temp = temp->next;
    }

    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    return list;
}

Ht_item* linkedlist_remove(LinkedList* list)
{
    // Removes the head from the LinkedList.
    // Returns the item of the popped element.
    if (list == NULL)
        return NULL;
    if (list->next == NULL)
        return NULL;

    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    Ht_item* it = NULL;
    memcpy(temp->item, it, sizeof(Ht_item));
    // free(temp->item->key);
    // free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}

void free_linkedlist(LinkedList* list)
{
    LinkedList* temp = list;

    while (list)
    {
        temp = list;
        list = list->next;
        // free(temp->item->key);
        // free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}



unsigned int first_prime(unsigned int min,unsigned int max){

	int flag;
	unsigned int div,n;
	for(n=min;n<max;n++){
		if(n%2==0) continue;
		if(n%3!=0){													 
			flag=1;
			div=5;														
			while(flag==1 && div*div<=n){									
				if(n%div==0 || n%(div+2)==0)	flag=0;			
				else	div=div+6;								  												
			}	
			if(flag)	break;									
		}	
	}
	return n;	
}

unsigned int hash_function(int key) {
	return key % CAPACITY;
}


Ht_item* create_item(int key, int value) {
	Ht_item* item = (Ht_item*) malloc(sizeof(Ht_item));
	// item->key = malloc(sizeof(int));
	// item->value = malloc(sizeof(int));
	item->key = key;
	item->value = value;

	return item;
}

void free_item(Ht_item* item) {
	// free(item->key);
	// free(item->value);
	free(item);
}

LinkedList** create_overflow_buckets(HashTable* table) {
	LinkedList** buckets = (LinkedList**) calloc(table->size, sizeof(LinkedList*));

	for(int i = 0; i < table->size; i++) {
		buckets[i] = NULL;
	}

	return buckets;
}

void free_overflow_buckets(HashTable* table)
{
    // Free all the overflow bucket lists.
    LinkedList** buckets = table->overflow_buckets;

    for (int i = 0; i < table->size; i++)
        free_linkedlist(buckets[i]);

    free(buckets);
}



HashTable* create_table(int size) {
	HashTable* table = (HashTable*) malloc(sizeof(HashTable));
	table->size = size;
	table->count = 0;
	table->items = calloc(table->size, sizeof(Ht_item*));
	for(int i = 0; i < table->size; i++) {
		table->items[i] = NULL;
	}
	table->overflow_buckets = create_overflow_buckets(table);


	return table;
}

void free_table(HashTable* table) {
	for(int i = 0; i < table->size; i++) {
		Ht_item* item = table->items[i];

		if(item != NULL) {
			free_item(item);
		}
	}
	free_overflow_buckets(table);
	free(table->items);
	free(table);
}


void print_table(HashTable* table) {
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            printf("Index:%d, Key:%d, Value:%d\n", i, table->items[i] -> key, table->items[i]->value);
        }
    }
    printf("-------------------\n\n");
}

void handle_collision(HashTable* table, int index, Ht_item* item) {
	// item is to be inserted
	LinkedList* head = table->overflow_buckets[index];

	if(head == NULL) {
		head = allocate_list();
		head->item = item;
		table->overflow_buckets[index] = head;
		return;
	}
	else {
		table->overflow_buckets[index] = linkedlist_insert(head, item);
		return;
	}
}



void insert(HashTable* table, int key, int value) {
	Ht_item* item = create_item(key, value);
	int index = hash_function(key);

	// first item (no collision)
	if(table->items[index] == NULL) {
		if(table->count == table->size) {
			printf("hashtable is full\n");
			free_item(item);
			return;
		}
		table->items[index] = item;
		table->count++;
	}
	else {
		// same item already inserted
		if(table->items[index]->key == key) {
			// copy value
			table->items[index]->value = value;
			return;
		}
		// collision
		else {
			handle_collision(table, index, item);
			return;
		}
	}
}


int search(HashTable* table, int key) {
	int index = hash_function(key);
	Ht_item* item = table->items[index];
	LinkedList* head = table->overflow_buckets[index];

	if(item != NULL) {
		if(item->key == key) {
			return item->value;
		}
		if(head == NULL) {
			return -1;
		}
		item = head->item;
		head = head->next;
	}
	return -1;
}

void print_search(HashTable* table, int key) {
    int val = search(table, key);
    if (val == -1)
    {
        printf("Key:%d does not exist\n", key);
        return;
    }
    else {
        printf("Key:%d, Value:%d\n", key, val);
    }
}

void delete(HashTable* table, int key) {
	int index = hash_function(key);
	Ht_item* item = table->items[index];
	LinkedList* head = table->overflow_buckets[index];

	if(item == NULL) {
		return;
	}
	else {
		if(head == NULL && item->key == key) {
			// no collision chain
			table->items[index] = NULL;
			free_item(item);
			table->count--;
			return;
		}
		else if(head != NULL){
			// collision chain
			if(item->key == key) {
				// remove item
				free_item(item);
				LinkedList* node = head;
				head = head->next;
				node->next = NULL;
				table->items[index] = create_item(node->item->key, node->item->value);
				free_linkedlist(node);
				table->overflow_buckets[index] = head;
				return;
			}

			LinkedList* curr = head;
			LinkedList* prev = NULL;

			while(curr) {
				if(curr->item->key == key) {
					if(prev == NULL) {
						free_linkedlist(head);
						table->overflow_buckets[index] = NULL;
						return;
					}
					else {
						prev->next = curr->next;
						curr->next = NULL;
						free_linkedlist(curr);
						table->overflow_buckets[index] = head;
						return;
					}
				}
				curr = curr->next;
				prev = curr;
			}
		}
	}
}




int main()
{
	//Hash collision by separate chaining with head records in the bucket array.
    HashTable *ht = create_table(CAPACITY);
    insert(ht, 10,10);
    insert(ht, 4,5);
    // // insert(ht, 23,3);
    // // insert(ht, 70,1);
    print_search(ht, 10);
    // //print_search(ht, 23);
    print_search(ht, 42);
    print_table(ht);
    delete(ht, 4);
	print_table(ht);
    free_table(ht);
    return 0;
}











