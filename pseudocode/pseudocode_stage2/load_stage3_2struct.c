void pikabot_load_stage3(undefined *random_str,uint some_size,int key,int param_4)
{
  allocated_ptr = (undefined *)pikabot_RtlAllocateHeap(0x40000);
  allocated_ptr2 = (undefined *)pikabot_RtlAllocateHeap(0x40000);

  copyContent(allocated_ptr, random_str, some_size);
  size = FUN_02f26438((int)allocated_ptr, some_size);
  copy_smthing((int)allocated_ptr,size, key, param_4,(int)allocated_ptr2);
  copyContent((undefined *)(*(int *)(pikabot_core + 0x50) + *(int *)(pikabot_core + 0x4c)),
              allocated_ptr2,size);
  *(int *)(pikabot_core + 0x50) = *(int *)(pikabot_core + 0x50) + size;
  
  RtlFreeHeap(allocated_ptr2);
  RtlFreeHeap(allocated_ptr);
  return;
}