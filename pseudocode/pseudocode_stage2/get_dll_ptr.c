pikabot_core;

undefined4 __cdecl get_dll_ptr(int hash)
{

  uint a;
  undefined4 *InLoadOrderModuleList;
  int iVar5;
  int *nose;
  int i;
  void *ptr;
  int *ptr_2_int_list_1;
  int j;
  int TEB;
  undefined8 b;
  int int_list_1 [4];
  int int_list [4];
  byte byte_array [272];
  int pikabot_core_var;
  
  pikabot_core_var = 2;
  do {
    // aqui hará algo antes
    if (pikabot_core_var == 1) {
      
      pikabot_core_var = pikabot_core;
      
      if (*(int *)(pikabot_core + 0x54) == 0) {
        *(undefined4 *)(pikabot_core + 0x54) = *(undefined4 *)(TEB + 0x18);
      }

      peb_ldr_data = *(int *)(*(int *)(*(int *)(pikabot_core_var + 0x54) + 0x30) + 0xc);
      InLoadOrderModuleList = *(undefined4 **)(peb_ldr_data + 0xc);

      do {
        if (InLoadOrderModuleList == (undefined4 *)(peb_ldr_data + 0xc)) {
          return 0;
        }

        a = aaa((char *)T, (undefined2 *)InLoadOrderModuleList[0xc], 0x104);
        b = bbb(ptr, byte_array, a, (int)ptr);

        if (((int)b == hash) || (j == hash)) {
          return InLoadOrderModuleList + 0x18; // DllBase
        }

        InLoadOrderModuleList = (undefined4 *)*InLoadOrderModuleList;
      } while( true );
    }
    pikabot_core_var = 1;
  } while( true );
}
