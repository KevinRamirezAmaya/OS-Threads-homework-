#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estructura para almacenar el contador individual de cada hilo
typedef struct {
    int counter;
    int max;
} ThreadData;

void* thread_function(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    for (int i = 0; i < data->max; i++) {
        data->counter++;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <valor de max> <número de hilos>\n", argv[0]);
        return 1;
    }

    int max = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    // Inicializar contadores individuales y valor máximo para cada hilo
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].counter = 0;
        thread_data[i].max = max;
    }

    // Crear hilos
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, thread_function, &thread_data[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sumar los contadores individuales de cada hilo
    int total_counter = 0;
    for (int i = 0; i < num_threads; i++) {
        total_counter += thread_data[i].counter;
    }

    printf("El valor total del contador es: %d\n", total_counter);
    return 0;
}
