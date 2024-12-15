pikabot_core;
int checkRemoteDebugPresent(void)
{
  int debug_present [3];

  debug_present[0] = 0;
  /*
    BOOL CheckRemoteDebuggerPresent(
    [in]      HANDLE hProcess,
    [in, out] PBOOL  pbDebuggerPresent
    );
    hProcess = 0xffffffff => current process
    pbDebuggerPresent = debug_present[] => will fill 0 position to True if debugger is present or False otherwise 
  */
  (**(code **)(pikabot_core + 0x24))(0xffffffff,debug_present);
  return debug_present[0]; 
}