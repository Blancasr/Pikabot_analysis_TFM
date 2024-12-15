pikabot_core;
int getActiveDebugRegisters(void)
{
  /*
    LPVOID VirtualAlloc(
    [in, optional] LPVOID lpAddress,
    [in]           SIZE_T dwSize,
    [in]           DWORD  flAllocationType,
    [in]           DWORD  flProtect
    );
    - lpAddress = start_ptr => initial position of reserved memory region
    - dwsize = 0x2cc = 716 B => memory region size
    - flAllocationType => 
    - flprotect = 4 => read and write permissions
  */
  base_ptr = (undefined4 *)(**(code **)(pikabot_core + 0x28))(start_ptr,0x2cc,iVar13,4);

  if (base_ptr != 0) {
    *context = 0x10010;

    /*
    BOOL GetThreadContext(
        [in]      HANDLE    hThread,
        [in, out] LPCONTEXT lpContext
        );
    - return = Zero if failure
    */
    ret = (**(code **)(pikabot_core + 0x2c))(0xfffffffe,context);
    if (ret != 0) {
      if ((((debug_registers.dr0 != 0) || (debug_registers.dr1 != 0)) || (debug_registers.dr2 != 0)) || (debug_registers.dr3 != 0) )
      {
        ret_val = 1;
      }
    }
    /*
    BOOL VirtualFree(
        [in] LPVOID lpAddress,
        [in] SIZE_T dwSize,
        [in] DWORD  dwFreeType
        );
    - dwFree = 0x800 => Libera la región especificada de páginas o marcador de posición,
                            dwSize tiene que ser 0 y lpAddress la direccion que devolvión VirtualAlloc
    */
    (**(code **)(pikabot_core + 0x30))(base_ptr,0,0x8000);
  }
  return ret_val;
}
