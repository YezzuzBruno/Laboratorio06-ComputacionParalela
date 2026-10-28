#include <cstdio>
#include <cstdlib>
#include <omp.h>

struct Node {
    int   value;
    Node *next;
};

static Node *head = nullptr;

static void insert(int v) {
    Node *n = new Node{v, head};
    head    = n;
}

static int search(int v) {
    for (Node *p = head; p; p = p->next)
        if (p->value == v) return 1;
    return 0;
}

static long count() {
    long c = 0;
    for (Node *p = head; p; p = p->next) c++;
    return c;
}

int main() {
    const int N = 1000;
    const int T = 4;  

    double t0 = omp_get_wtime();
    for (int i = 0; i < N; i++) insert(i);
    double t1 = omp_get_wtime();

    std::printf("nodos insertados: %d\n", N);
    std::printf("nodos contados  : %ld\n", count());

    long found = 0;
    double t2 = omp_get_wtime();
    #pragma omp parallel for num_threads(T) reduction(+:found)
    for (int i = 0; i < N; i++)
        found += search(i);
    double t3 = omp_get_wtime();

    std::printf("busquedas exitosas: %ld de %d\n", found, N);

    std::printf("\n--- tiempos (T=%d hilos) ---\n", T);
    std::printf("inserciones : %.9f s\n", t1 - t0);
    std::printf("busquedas   : %.9f s\n", t3 - t2);
    std::printf("total       : %.9f s\n", t3 - t0);

    return 0;
}