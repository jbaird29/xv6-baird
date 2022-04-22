#include "types.h"
#include "user.h"
#include "pstat.h"
#include "param.h"

// Given a pid, prints pstat info for the process
void printpinfo(int pid) {
  struct pstat stat;
  int i;
  if(getpinfo(&stat) < 0) {
    printf(1, "Error with getpinfo");
    return;
  }
  for(i = 0; i < NPROC; i++) {
    if(stat.pid[i] == pid) {
      printf(1, "PID: %d | High Ticks: %d | Low Ticks: %d | Tickets: %d\n", stat.pid[i], stat.hticks[i], stat.lticks[i], stat.tickets[i]);
    }
  }
}

// Given a pid, gets total number of CPU ticks
int getpticks(int pid) {
  struct pstat stat;
  int i;
  int ticks = 0;
  if(getpinfo(&stat) < 0) {
    printf(1, "Error with getpinfo");
    return -1;
  }
  for(i = 0; i < NPROC; i++) {
    if(stat.pid[i] == pid) 
      ticks += (stat.hticks[i] + stat.lticks[i]);
  }
  return ticks;
}


// Testing that a new process starts on priority queue 1
// then moves to queue 2 for the remainder of its liftime
void testQueues(void) {
  printf(1, "Test #1: Ensure process runs once on priority 1 queue, subsequently on priority 2\n");
  volatile int i;
  int childpid = fork();
  if(childpid == 0) {
    for(i = 0; i < 1000000000; i++) {}
    printpinfo(getpid());
    exit();
  }
  wait();
  printf(1, "Validate: is high ticks == 1 and low ticks > 1?\n");
}

void testTickets1(void) {
  printf(1, "Test #2: Ensure multiple processes finish in relative order of ticket counts.\n");
  volatile int i;
  int j;
  printf(1, "Starting uptime: %d\n", uptime());
  // fork children and run in a loop with varying ticket counts
  for(j = 100; j > 0; j = j - 20) {
    if(fork() == 0) {
      settickets(j);
      for(i = 0; i < 2000000000; i++) {}
      for(i = 0; i < 2000000000; i++) {}
      printf(1, "Child | tickets: %d | uptime: %d\n", j, uptime());
      exit();
    }
  }
  // run the parent in the same loop
  for(i = 0; i < 2000000000; i++) {}
  for(i = 0; i < 2000000000; i++) {}
  printf(1, "Parent | tickets: 1 | uptime: %d\n", uptime());
  while(wait() != -1);
  printf(1, "Validate: did processes finish in order of high to low tickets?\n");
}

void testTickets2(void) {
  printf(1, "Test #3: Ensure single process runs in proportion to ticket count.\n");
  volatile int i;
  int tickets = 5;
  settickets(tickets);
  int childPID;
  int parentPID = getpid();
  int childticks = 0;
  int parentticks = getpticks(parentPID);
  // fork child and run in a loop with default ticket counts of 1
  if((childPID = fork()) == 0) {
    for(i = 0; i < 2000000000; i++) {}
    for(i = 0; i < 2000000000; i++) {}
    exit();
  }
  // run the parent in the same loop; should finish first bc of ticket count
  for(i = 0; i < 2000000000; i++) {}
  for(i = 0; i < 2000000000; i++) {}
  childticks = getpticks(childPID);
  parentticks = getpticks(parentPID) - parentticks;
  while(wait() != -1);
  printf(1, "Parent tickets: %d | parent ticks: %d\n", tickets, parentticks);
  printf(1, "Child tickets:  %d | child ticks:  %d\n", 1, childticks);
  printf(1, "Validate: did parent function have ~%d times as many CPU ticks as child?\n", tickets);
}

/*
Test: processes on Q1 run for one cycle, then two on Q2
Test: processes run in proportion to # of tickets
*/
int main(int argc, char *argv[])
{
  testQueues();
  printf(1, "\n");
  testTickets1();
  printf(1, "\n");
  testTickets2();
  exit();
}

