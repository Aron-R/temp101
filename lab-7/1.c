#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define WAREHOUSE_CAPACITY 10

sem_t warehouse_mutex;
sem_t items_in_warehouse;
sem_t items_to_distribute;

int warehouse_count = 0;
int warehouse[WAREHOUSE_CAPACITY];
int unique_item_id = 1;

void* manufacturer(void* arg) {
    while (1) {
        // Produce goods
        int item_id = unique_item_id++;

        // Check if the warehouse is full
        if (warehouse_count == WAREHOUSE_CAPACITY) {
            printf("Warehouse is full. Manufacturer waiting...\n");
            sem_wait(&items_to_distribute);
        }

        // Acquire warehouse mutex
        sem_wait(&warehouse_mutex);

        // Add goods to the warehouse
        warehouse[warehouse_count] = item_id;
        warehouse_count++;
        printf("Manufacturer produced item %d. Items in warehouse: %d\n", item_id, warehouse_count);

        // Release warehouse mutex
        sem_post(&warehouse_mutex);

        // Notify the distributor if the warehouse was empty
        if (warehouse_count == 1) {
            sem_post(&items_in_warehouse);
        }

        // Sleep for some time before producing the next item
        // ...
    }

    pthread_exit(NULL);
}

void* distributor(void* arg) {
    while (1) {
        // Check if the warehouse is empty
        if (warehouse_count == 0) {
            printf("Warehouse is empty. Distributor waiting...\n");
            sem_wait(&items_in_warehouse);
        }

        // Acquire warehouse mutex
        sem_wait(&warehouse_mutex);

        // Remove goods from the warehouse
        int item_id = warehouse[warehouse_count - 1];
        warehouse_count--;
        printf("Distributor distributed item %d. Items in warehouse: %d\n", item_id, warehouse_count);

        // Release warehouse mutex
        sem_post(&warehouse_mutex);

        // Notify the manufacturer if the warehouse was full
        if (warehouse_count == WAREHOUSE_CAPACITY - 1) {
            sem_post(&items_to_distribute);
        }

        // Sleep for some time before distributing the next item
        // ...
    }

    pthread_exit(NULL);
}

void displayWarehouse() {
    printf("Warehouse: [");
    for (int i = 0; i < warehouse_count; i++) {
        printf("%d ", warehouse[i]);
    }
    printf("]\n");
}

int main() {
    // Initialize semaphores
    sem_init(&warehouse_mutex, 0, 1);
    sem_init(&items_in_warehouse, 0, 0);
    sem_init(&items_to_distribute, 0, 0);

    // Create manufacturer and distributor threads
    pthread_t manufacturer_thread, distributor_thread;
    pthread_create(&manufacturer_thread, NULL, manufacturer, NULL);
    pthread_create(&distributor_thread, NULL, distributor, NULL);

    while (1) {
        // Display warehouse
        displayWarehouse();

        // Sleep for some time before displaying the warehouse again
        // ...
    }

    // Wait for threads to finish (which is never in this case)
    pthread_join(manufacturer_thread, NULL);
    pthread_join(distributor_thread, NULL);

    // Cleanup semaphores
    sem_destroy(&warehouse_mutex);
    sem_destroy(&items_in_warehouse);
    sem_destroy(&items_to_distribute);

    return 0;
}

