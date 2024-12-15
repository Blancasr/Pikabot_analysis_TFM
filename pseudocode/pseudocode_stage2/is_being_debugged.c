
bool is_being_debugged(void)
{
  int TEB;
  int PEB;
  
  PEB = *(int *)(TEB + 0x30);
  return *(char *)(PEB + 2) == '\x01';
}