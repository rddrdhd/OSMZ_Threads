// Based on https://c9x.me/articles/gthreads/code0.html
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include "gthr.h"

// Dummy function to simulate some thread work
void f(void) {
  static int x;
  int i, id;

  id = ++x;
  while (true) {

    printf("F Thread id = %d, val = %d BEGINNING\n", id, ++i);
    uninterruptibleNanoSleep(0, 50000000);
    printf("F Thread id = %d, val = %d END\n", id, ++i);
    uninterruptibleNanoSleep(0, 50000000);
  }
}

// Dummy function to simulate some thread work
void g(void) {
  static int x;
  int i, id;

  id = ++x;
  while (true) {

    printf("G Thread id = %d, val = %d BEGINNING\n", id, ++i);
    uninterruptibleNanoSleep(0, 50000000);
    printf("G Thread id = %d, val = %d END\n", id, ++i);
    uninterruptibleNanoSleep(0, 50000000);
  }
}

void handle_sigint(int sig) {
    printf("\nHere goes some interesting stuff\n");
    signal(SIGINT, SIG_DFL);
    raise(SIGINT);
}

int main(void) {
    
    signal(SIGINT, handle_sigint);
    gtinit();		// initialize threads, see gthr.c
    gtgo(f);		// set f() as first thread
    gtgo(f);		// set f() as second thread
    gtgo(g);		// set g() as third thread
    gtgo(g);		// set g() as fourth thread
    gtret(1);		// wait until all threads terminate
}
