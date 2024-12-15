
uint __cdecl resolver(int ptr2dllBaseaddress,int func_hash)
{
  int return_value = 0;
  if (ptr2dllBaseaddress == 0) {
    return 0;
  }

  if (func_hash == 0) {
    return var; // return random val
  }

  PE_Header = *(int *)(ptr2dllBaseaddress + 0x3c) + ptr2dllBaseaddress;
  sizeOfExportTable = *(int *)(PE_Header + 0x7c);
  ExportTable = *(int *)(PE_Header + 0x78) + ptr2dllBaseaddress;
  AddressOfNames = *(int *)(ExportTable + 0x20);
  AddressOfFunctions = *(int *)(ExportTable + 0x1c);
  AddressOfNameOrdinals = *(int *)(ExportTable + 0x24);

  iterator = (void *)0x0;
  do {
    if (*(void **)(ExportTable + 0x18) <= iterator) { // EAT + 0x18 = NumberOfNames
      return 0;
    }

    AddresSsOfFunction_i = (byte *)(*(int *)(AddressOfNames + ptr2dllBaseaddress + (int)iterator * 4) + ptr2dllBaseaddress);
    calculated_func_hash = calc_func_hash(iterator, AddresSsOfFunction_i, 0, 1);

    if ((int)calculated_func_hash == func_hash) {
      function_ptr = *(int *)(ptr2dllBaseaddress +
                                (iterator * 2 + ptr2dllBaseaddress + AddressOfNameOrdinals) * 4  + AddressOfNames) 
                                + ptr2dllBaseaddress;
      if (function_ptr < ExportTable) {
        return function_ptr; // function before ExportTable
      }
      if (ExportTable + ptr2dllBaseaddress + sizeOfExportTable <= function_ptr) {
        return function_ptr; // function inside ExportTable
      }
      break;
    }
    iterator = (void *)((int)iterator + 1);
  } while( true );

  if (*(int *)(pikabot_core + 8) == 0) {
      return 0;
  } else {
    /* LdrpGetProcedureAddressForCaller( 
          PVOID BaseAddress, 
          PANSI_STRING ProcedureName, 
          ULONG Ordinal, 
          PVOID *AddressOf
      )
    */
    j = (**(code **)(pikabot_core + 8))(ptr2dllBaseaddress, &some_name, 0, &function_ptr);
    if (-1 < j) {
      return function_ptr;
    }
  }

}
