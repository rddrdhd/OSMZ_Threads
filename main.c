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

    printf("F Thread id = %d, val = %02d BEGINNING\n", id, ++i);
    uninterruptibleNanoSleep(0, 50000000);
    printf("F Thread id = %d, val = %02d END\n", id, ++i);
    uninterruptibleNanoSleep(0, 50000000);
  }
}

// Dummy function to simulate some thread work
void g(void) {
  static int x;
  int i, id;

  id = ++x;
  while (true) {
    printf("G Thread id = %d, val = %02d BEGINNING\n", id, ++i);
    uninterruptibleNanoSleep(0, 50000000);
    printf("G Thread id = %d, val = %02d END\n", id, ++i);
    uninterruptibleNanoSleep(0, 50000000);
  }
}

void clean_exit_on_sig(int sig_num) {
    printf("\n Signal %d received", sig_num);
}

int main(int argc, char* argv[]) {

    srand(time(0)); //to generate different lottery numbers every run
    if (argc == 2) {
        char* mode = argv[1];
        signal(SIGINT, handle_sigint);
        gtinit(mode);	// initialize threads, see gthr.c
        gtgo(f, 5);		// set f() as first thread
        gtgo(f, 10);	// set f() as second thread
        gtgo(g, 2);		// set g() as third thread
        gtgo(g, 0);		// set g() as fourth thread
        gtret(1);		// wait until all threads terminate
    } else {
        printf(" Use one of those args: \n\t'RR' for round robin,\n\t'PRI' for prioritized round robin,\n\t'LS' for lottery scheduling\n\n");
        return 0;
    }
}
