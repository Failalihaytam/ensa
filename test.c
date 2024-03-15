#include <stdio.h>
#include<stdlib.h>
#include<sys/queue.h>

typedef struct {
    Queue<process> q;
    int value;
}Semaphore;

void P(Semaphore s)
{
    if (s.value == 1) {
        s.value = 0;
    }
    else {
        s.q.push(P);
        sleep();
    }
}

void V(Semaphore s)
{
    if (s.q is empty) {
        s.value = 1;
    }
    else {

        // Get a process from the Waiting Queue
        Process p = q.front();
        // Remove the process from waiting
        q.pop();
        wakeup(p);
    }
}
int main() {

    return 0;
}
