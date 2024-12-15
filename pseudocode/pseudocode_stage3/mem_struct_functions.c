
// -------------------------------- READ memory struct & functions --------------------------- // 

struct mem_struct {
  0x00 mem_ptr
  0x04 mem_iterator
  0x08 mem_size
  0x0c mem_size_left
};

undefined4 __cdecl getNextVal(int mem_struct)
{
  retVal = 0;
  if (mem_struct == 0) {
    return retVal;
  } else if (3 < *(uint *)(mem_struct + 0xc)) {
    // mover la direccion del dato actual a la variable de retorno
    move_mem((undefined *)retVal,*(undefined **)(mem_struct + 4),4);
    // incrementar el iterador y decrementar la memoria restante a leer en 4
    *(int *)(mem_struct + 4) = *(int *)(mem_struct + 4) + 4;
    *(int *)(mem_struct + 0xc) = *(int *)(mem_struct + 0xc) - 4; 
  }
  return retVal;
}

undefined8 __cdecl getNextVal8(int struct_mem)
{  
  var_a = 0;
  var_b = 0;
  if (struct_mem != 0 && 7 < *(uint *)(struct_mem + 0xc)) {
    move_Mem((undefined *)&var_a,*(undefined **)(struct_mem + 4),8);
    *(int *)(struct_mem + 4) = *(int *)(struct_mem + 4) + 8;
    *(int *)(struct_mem + 0xc) = *(int *)(struct_mem + 0xc) + -8;
    ret = CONCAT44(var_b,var_a);
  } else {
    ret = CONCAT44(var_b,var_a);
  }
  return ret;
}

int __cdecl getNextString(int mem_struct,int *sizeOfNextString)
{
  sizeOfStr = 0;
  str_ptr = mem_struct;
  if (mem_struct != 0) {
    str_ptr = 0;
    if (*(uint *)(mem_struct + 0xc) < 4) {;
    } else {
      // el siguiente valor es le tamaño del string
      move_Mem((undefined *)&sizeOfStr, *(mem_struct + 4),4);
      str_ptr = *(int *)(mem_struct + 4) + 4;
      // le resta al tamaño total el tamaño del string y el valor del tamaño
      *(int *)(mem_struct + 0xc) = *(int *)(mem_struct + 0xc) - 4 - sizeOfStr;
      // actualiza el iterador hacia el siguiente valor despues del string
      *(int *)(mem_struct + 4) = str_ptr + sizeOfStr;
      if (sizeOfNextString != 0x0) {
        *sizeOfNextString = sizeOfStr;
      }
    }
  }
  return str_ptr;
}


// -------------------------------- WRITE memory struct & functions --------------------------- //

struct struct_command {
  0x00 command
  0x04 data
  0x08 sizeOfData
  0x0c reserved
  0x10 reserved
  0x14 reserved
  0x18 reserved
  0x1c reserved
};

struct struct_command {
  0x00 command
  0x04 data
  0x08 sizeOfData
  0x0c reserved
  0x10 reserved
  0x14 reserved
  0x18 reserved
  0x1c reserved
};


undefined4 * __cdecl allocate_mem_struct(undefined4 command)
{
  mem_struct = (undefined4 *)(**(code **)(_pikabot_struct + 0x50))(0x40,0x20); // LocalAlloc
  data_ptr = (**(code **)(_pikabot_struct + 0x50))(0x40,1); // LocalAlloc
  mem_struct + 0x04 = data_ptr;
  mem_struct + 0x08 = 0;
  mem_struct + 0x10 = 1;
  mem_struct + 0x14 = 1;
  mem_struct + 0x18 = 0;
  mem_struct + 0x1c = 0;
  *mem_struct = command;
  return ptr1;
}


void __cdecl fillNext4B(int mem_struct, undefined4 val)
{
  if (mem_struct != 0) {
    /*
    DECLSPEC_ALLOCATOR HLOCAL LocalReAlloc(
        [in] _Frees_ptr_opt_ HLOCAL hMem,
        [in] SIZE_T                 uBytes,
        [in] UINT                   uFlags
        );
        hMem: Identificador del objeto de memoria local que se va a reasignar.
        uBytes: Nuevo tamaño del bloque de memoria, en bytes
        uFlags: Opciones de reasignación -> 2 == LMEM_MOVEABLE: Asigna memoria fija o extraíble. Si la memoria es un bloque de memoria bloqueado LMEM_MOVEABLE o un bloque de memoria LMEM_FIXED y no se especifica esta marca, la memoria solo se puede reasignar en su lugar.
        ret -> Si la función se ejecuta correctamente, el valor devuelto es un identificador para el objeto de memoria reasignado
    */
    reallocated = **(code **)(_pikabot_struct + 0x54)     // LocalReAlloc()
                        (*(undefined4 *)(mem_struct + 4), // data
                        *(int *)(mem_struct + 8) + 4,     // sizeOf(data) + 4
                        2);                               // LMEM_MOVEABLE
    *(int *)(mem_struct + 4) = reallocated; // data reallocated
 
    fill_4Bptr((undefined *)(reallocated + *(int *)(mem_struct + 8)), val); // fill last 4B
    *(int *)(mem_struct + 8) = *(int *)(mem_struct + 8) + 4; // resize sizeOf(data)
  }
  return;
}

void __cdecl fillNext8B(int mem_struct,uint unused, undefined4 val)
{
  if (mem_struct != 0) {
    reallocated = (**(code **)(_pikabot_struct + 0x54)) // kernel32.LocalReAlloc
                      (*(undefined4 *)(mem_struct + 4),    // data
                      *(int *)(mem_struct + 8) + 8,        // sizeOf(data) + 8
                      2);
    *(int *)(mem_struct + 4) = reallocated;
    fill_4Bptr((undefined *)(reallocated + *(int *)(mem_struct + 8)),unused,val);
    *(int *)(mem_struct + 8) = *(int *)(mem_struct + 8) + 8;
  }
  return;
}

void __cdecl fill_4Bptr2(undefined *mem_struct,uint unused,undefined4 val)
{
  mem_struct[3] = (char)val;
  mem_struct[2] = (char)((uint)val >> 8);
  mem_struct[1] = (char)((uint)val >> 0x10);
  *mem_struct = (char)((uint)val >> 0x18);
  return;
}

undefined4 __fastcall fill_4Bptr(undefined *buffer, undefined4 val)
{
  buffer + 0x2 = (char)((uint)val >> 8);
  buffer + 0x0 = (char)((uint)val >> 0x18);
  buffer + 0x1 = (char)((uint)val >> 0x10);
  buffer + 0x3 = (char)val;
  return;
}

void __cdecl fillRC4key(int mem_struct, undefined *key,int size)
{
  if (mem_struct != 0) {
    reallocated = (**(code **)(_pikabot_struct + 0x54))   // LocalReAlloc()
                      (*(undefined4 *)(mem_struct + 4),   // data
                      *(int *)(mem_struct + 8) + size,    // sizeOf(data) + size
                      0x42);                              // LMEM_MOVEABLE && LMEM_ZEROINIT
    *(int *)(mem_struct + 4) = reallocated; // data reallocated

    move_Mem((undefined *)(reallocated + *(int *)(mem_struct + 8)),key,size); // fill last size B
    *(int *)(mem_struct + 8) = *(int *)(mem_struct + 8) + size; // resize sizeOf(data)
  }
  return;
}

int __cdecl sizeOfString(short *val)
{ // calcula la (cantidad de bytes en string) / 2; 
  // [los strings se codifican con un punto en tras cada caracter, por eso se divide por 2]
  for (i = val; *i != 0; i = i + 1) {}
  return (int)i - (int)val >> 1;
}

void __cdecl fill_String(int mem_struct,short *strVal)
{
  size = sizeOfString(strVal);
  fill_size_string(mem_struct,(undefined *) strVal, size * 2);
  return;
}

void __cdecl fill_size_string(int mem_struct,undefined *strVal,int size)
{
  if (mem_struct != 0) {
    fillNext4B(mem_struct, size); // fill first 4 B with string size
    if (size != 0) {
      reallocated_mem = (**(code **)(_pikabot_struct + 0x54)) // LocalReAlloc()
                        (*(undefined4 *)(mem_struct + 4),     // data
                        *(int *)(mem_struct + 8) + size,      // sizeOf(data)  
                        0x42);                                // LMEM_MOVEABLE && LMEM_ZEROINIT
      *(int *)(mem_struct + 4) = reallocated_mem; // data reallocated

      move_Mem((reallocated_mem + *(int *)(mem_struct + 8)), strVal, size); // fill string at data end
      *(int *)(mem_struct + 8) = *(int *)(mem_struct + 8) + size; // resize sizeOf(data)
    }
  }
  return;
}

// -------------------------------- aux functions --------------------------- //

void __cdecl call_getNextString(int struct_mem,int *sizeOfContent)
{
  getNextString(struct_mem, sizeOfContent);
  return;
}
