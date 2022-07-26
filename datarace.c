#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t foo_mutex = PTHREAD_MUTEX_INITIALIZER;

int shared = 0;

void *add(void *unused) {
  for(int i=0; i < 1000000; i++) { 
    pthread_mutex_lock(&foo_mutex);
    shared++;
    pthread_mutex_unlock(&foo_mutex);
  }
  return NULL;
}

int main() {
  pthread_t t;
  // Child thread starts running add
  pthread_create(&t, NULL, add, NULL);
  // Main thread starts running add
  add(NULL);
  // Wait until child thread t terminates
  pthread_join(t, NULL);
  printf("shared=%d\n", shared);
  return 0;
}
