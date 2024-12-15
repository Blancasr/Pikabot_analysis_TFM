
int syscall(void)

{
  int retval =  syscall();
  if (-1 < retval) {
    return 0;
  }
  return 1;
}
