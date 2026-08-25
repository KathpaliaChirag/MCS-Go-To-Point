#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "syscall.h"

// Function to get history
int
sys_gethistory(void)
{
  acquire(&history_lock);
  for(int i = 0; i < history_count; i++){
    // The format is: "pid command mem_usage"
    cprintf("%d %s %d\n", proc_history[i].pid, proc_history[i].name, proc_history[i].mem_usage);
  }
  release(&history_lock);
  return 0;
}

// sys_block: marks a syscall as blocked for the current process.
int sys_block(void) {
  int syscall_id;
  if(argint(0, &syscall_id) < 0)
    return -1;
  // Do not allow blocking of critical syscalls: fork and exit.
  if(syscall_id == SYS_fork || syscall_id == SYS_exit)
    return -1;
  // Mark the given syscall as blocked in the current process.
  myproc()->blocked[syscall_id] = 1;
  return 0;
}

// sys_unblock: removes the block on a given syscall.
int sys_unblock(void) {
  int syscall_id;
  if(argint(0, &syscall_id) < 0)
    return -1;
  // Unblock the syscall by setting its flag to 0.
  myproc()->blocked[syscall_id] = 0;
  return 0;
}


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
