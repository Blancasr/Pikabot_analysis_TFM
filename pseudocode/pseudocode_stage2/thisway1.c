pikabot_core;

void thisway1(void)

{
  int *pikabot_core_var;
  int int_var_aux;
  uint item;
  int TEB;
  int rdp;

  int* ptr_2_ntdll; // my var
  int* ptr_2_kernel32; // my var
  
  int ret_syscall0 = NtQuerySystemInformation();  // id = 36
  int ret_syscall1 = ZwQueryInformationProcess(); // id = 19
  int ret_syscall2 = ZwQueryInformationProcess(); // id = 19
  int BeingDebugged = is_being_debugged();

  if (ret_syscall0 == 0 && ret_syscall1 == 0 && ret_syscall2 == 0 && BeingDebugged == 0 ) {

    pikabot_core + 0x54 = *(int *)(TEB + 0x18); // *TEB

    int_var_aux = get_dll_ptr(0x7a12924e); // ptr to ntdll.dll
    pikabot_core + 0x40 = int_var_aux; 

    ptr_2_ntdll = pikabot_core + 0x40; // this is my code in order to simplify program reading
    pikabot_core_var = pikabot_core;                                                         

    if (int_var_aux != 0) {

      item = resolver(int_var_aux,0x7f7ac2b7); // item = ntdll.LdrGetProcedureAddress
      pikabot_core + 0x8 = item;

      item = resolver( ptr_2_ntdll ,0x607977c4); // item = ntdll.LdrLoadDLL
      pikabot_core + 0x4 = item;

      item = resolver(ptr_2_ntdll ,-0x1690d85); // item = ntdll.RtlAllocateHeap
      pikabot_core + 0xc = item;

      item = resolver(ptr_2_ntdll ,0x7c5fa278); // item = ntdll.RtlFreeHeap
      pikabot_core + 0x10 = item;

      item = resolver(ptr_2_ntdll ,0x2710f5e7); // item = ntdll.RtlDecompressBuffer
      pikabot_core + 0x14 = item;

      item = resolver(ptr_2_ntdll ,-0x70532664); // item = ntdll.CreateProcessParametersEx
      pikabot_core + 0x18 = item;

      item = resolver(ptr_2_ntdll ,-0x670e3b2b); // item = RtlDestroyProcessParameters
      pikabot_core + 0x1c = item;

      int_var_aux = get_dll_ptr(-0x72b6f8ea); // ptr to kernel32.dll
      pikabot_core + 0x44 = int_var_aux;
      ptr_2_kernel32 = int_var_aux; // this is my code in order to simplify program reading

      if (ptr_2_kernel32 != 0) {

        item = resolver(ptr_2_kernel32, -0x25f62be1); // item = kernel32.ExitProcess

        pikabot_core + 0x20 = item;

        item = resolver(ptr_2_kernel32 ,-0x4471972a); // item = kernel32.CheckRemoteDebuggerPresent

        pikabot_core + 0x24 = item;

        item = resolver(ptr_2_kernel32 ,0x28e93418); // item = kernel32.VirtualAlloc

        pikabot_core + 0x28 = item;

        item = resolver(ptr_2_kernel32 ,-0x7d07239d); // item = kernel32.GetThreadContext

        pikabot_core + 0x2c = item;

        item = resolver(ptr_2_kernel32 ,-0x16059c51); // item = kernel32.VirtualFree

        pikabot_core + 0x30 = item;

        item = resolver(ptr_2_kernel32 ,0x683fdb76); // item = kernel32.CreateToolHelp32Snapshot
        pikabot_core + 0x34 = item;

        item = resolver(pikabot_core[0x11],0x731d47c9); // item = kernel32.Process32First

        pikabot_core + 0x38 = item;

        item = resolver(pikabot_core_var[0x11],-0xb7832a0); // item = kernel32.Process32Next
        pikabot_core + 0x3c = item;

        // crea un snapshot del estado actual de la máquina y devuelve 0 si no coincide ningún proceso con la lista de procesos prohibidos
        int a = compare_snapshot(); 
        int b = compare_snapshot2();
        int c = compare_snapshot3();
        int d = compare_snapshot4();

        int adr = getActiveDebugRegisters(); // calls GetThreadContext and checks if debug registers are active
        Check_RemoteDebuggerPresent(rdp); // calls kernel32.CheckRemoteDebuggerPresent

        if (a == 0 && b == 0 && c == 0 && d == 0 && adr == 0 && rdp == 0 ) {
          return;
        }
      }
    }
  }

  *pikabot_core = 1;
  return;
}
