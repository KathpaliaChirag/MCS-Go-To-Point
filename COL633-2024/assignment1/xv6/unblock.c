#include "types.h"
#include "user.h"

int 
main(int argc, char *argv[])
{
  if(argc != 2) {
    printf(2, "Usage: unblock syscall_id\n");
    exit();
  }
  int id = atoi(argv[1]);
  if(unblock(id) == 0)
    printf(1, "Syscall %d is now unblocked\n", id);
  else
    printf(2, "Failed to unblock syscall %d\n", id);
  exit();
}
