enum {
    MaxGThreads = 5,		// Maximum number of threads, used as array size for gttbl
    StackSize = 0x400000,	// Size of stack of each thread
};

struct gt {
  // Saved context, switched by gtswtch.S (see for detail)
  // Hodnoty registru procesoru
  struct gtctx {
    uint64_t rsp;
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t rbx;
    uint64_t rbp;
  }
  ctx;
  enum {
    Unused,
    Running,
    Ready,
  } 
  st; // Thread state

  struct timeval t_start; // time of last start
  struct timeval t_stop; // time of last stop

  struct {
      long sum;
      long min;
      long max;
      long count;
  } 
  wait_time; // struct for computing wait time

  struct {
      long sum;
      long min;
      long max;
      long count;
  } 
  run_time; // struct for computing run time

  int priority; // priority used only in PRI and LS mode
  int starvingCount; // starvingCount only used in PRI mode

  enum {
    RR,
    PRI,
    LS,
    UNDEFINED,
  } 
  mode; // mode is only set to main thread

  int lottery_bound; 
};

void gtinit(char* mode);				// initialize gttbl
void gtret(int ret);			// terminate thread
void gtswtch(struct gtctx * old, struct gtctx * new);	// declaration from gtswtch.S
bool gtyield(void);				// yield and switch to another thread
void gtstop(void);				// terminate current thread
int gtgo(void( * f)(void), int priority);		// create new thread and set f as new "run" function
void resetsig(int sig);			// reset signal
void gthandle(int sig);			// periodically triggered by alarm
int uninterruptibleNanoSleep(time_t sec, long nanosec);	// uninterruptible sleep
void handle_sigint(int sig); // print info 
double time_diff(struct timeval x, struct timeval y); // helper func