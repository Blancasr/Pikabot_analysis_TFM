defined4 __cdecl create_snapshot(int forbidden_exe_hash)
{
/*
  HANDLE CreateToolhelp32Snapshot(
    [in] DWORD dwFlags,
    [in] DWORD th32ProcessID
  );
  - dwFlags:
    TH32CS_SNAPPROCESS
    0x00000002 : Includes all processes in the system in the snapshot. To enumerate the processes, see Process32First.
  - th32ProcessID: 0 to indicate current process
  - returns: hSnapshot
*/
  Toolhelp32Snapshot = (**(code **)(pikabot_core + 0x34))(2,0);
  if (Toolhelp32Snapshot != -1) {
    /*
      BOOL Process32First(
        [in]      HANDLE           hSnapshot,
        [in, out] LPPROCESSENTRY32 lppe
      );
      returns: true if successfull
    */
    data[0] = 0x22c;
    process32W_i = (**(code **)(pikabot_core + 0x38))(Toolhelp32Snapshot,data);
    if (process32W_i != 0) {
      do {
        uVar3 = compare_proc_with_forbidden((int)process32W_i + 0x1c,forbidden_exe_hash);
        if (uVar3 == uVar4) {
          goto LAB_02f2132e;
        }
        /*
          BOOL Process32NextW(
            [in]  HANDLE            hSnapshot,
            [out] LPPROCESSENTRY32W lppe
          );
          returns: true if successfull
        */
        process32W_i = (**(code **)(pikabot_core + 0x3c))(Toolhelp32Snapshot,data);

      } while (process32W_i != 0);
    }
    NtAllocateVirtualMemory();
  }
  return 0;

LAB_02f2132e:
  if (*pcVar5 == '\0') {
LAB_02f2134a:
    NtAllocateVirtualMemory();
    return 1;

  if (9 < (byte)(*pcVar5 - 0x30U)) {
    goto LAB_02f2134a;
  }

  goto LAB_02f2132e;
}
