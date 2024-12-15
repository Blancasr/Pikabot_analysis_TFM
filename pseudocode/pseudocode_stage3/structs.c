struct pikabot_stage3_struct {
    0x00    &Victim_infoStruct
    0x04    HTTPsessionID
    0x08    Failure <bool> = 0 === False
    0x0c    <ntdll.LdrLoadDll>
    0x10    <ntdll.LdrGetProcedureAddress>
    0x14    <ntdll.RtlAllocateHeap>
    0x18    <ntdll.RtlReAllocateHeap>
    0x1c    <ntdll.RtlFreeHeap>
    0x20    <ntdll.RtlDecompressBuffer>
    0x24    <ntdll.RtlGetVersion>
    0x28    <ntdll.RtlRandomEx>
    0x2c    <ntdll.RtlCreateProcessParametersEx>
    0x30    <ntdll.RtlExitUserProcess>
    0x34    <kernel32.ExitProcess>
    0x38    <kernel32.WaitForSingleObjectEx>
    0x3c    <kernel32.CheckRemoteDebuggerPresent>
    0x40    <kernel32.VirtualAlloc>
    0x44    <kernel32.GetThreadContext>
    0x48    <kernel32.VirtualFree>
    0x4c    <kernel32.GetVolumeInformationW>
    0x50    <kernel32.LocalAlloc>
    0x54    <kernel32.LocalReAlloc>
    0x58    <kernel32.LocalFree>
    0x5c    <kernel32.CreateFileW>
    0x60    <kernel32.WriteFile>
    0x64    <kernel32.GetStdHandle>
    0x68    <kernel32.FormatMessageW>
    0x6c    <kernel32.CreateMutexW>
    0x70    <kernel32.GetLastError>
    0x74    <kernel32.OpenProcess>
    0x78    <kernel32.WriteProcessMemory>
    0x7c    <kernelbase.InitializeProcThreadAttributeList>
    0x80    <kernelbase.DeleteProcThreadAttributeList>
    0x84    <kernelbase.UpdateProcThreadAttribute>
    0x88    <kernel32.ExpandEnvironmentStringsW>
    0x8c    <kernel32.CreateProcessW>
    0x90    <kernel32.CreatePipe>
    0x94    <kernel32.ReadFile>
    0x98    <kernel32.CloseHandle>
    0x9c    <kernel32.CreateToolhelp32Snapshot>
    0xa0    <kernel32.Process32FirstW>
    0xa4    <kernel32.Process32NextW>
    0xa8
    0xac    <kernel32.IsWow64Process>
    0xb0    <kernel32.GetProductInfo>
    0xb4    <kernel32.GetComputerNameW>
    0xb8    <kernel32.GetComputerNameExW>
    0xbc    <kernel32.GlobalMemoryStatusEx>
    0xc0    <kernel32.GetUserDefaultLangID>
    0xc4    <user32.wsprintfW>
    0xc8    <user32.EnumDisplayDevicesW>
    0xcc    <user32.GetDesktopWindow>
    0xd0    <user32.GetWindowRect>
    0xd4    <user32.wsprintfA>
    0xd8    <user32.wvsprintfW>
    0xdc
    0xe0    <logoncli.DsGetDcNameW>
    0xe4    <advapi32.OpenProcessToken>
    0xe8    <advapi32.GetTokenInformation>
    0xec    <advapi32.GetUserNameW>
    0xf0    <advapi32.RegCreateKeyExW>
    0xf4    <advapi32.RegSetValueExW>
    0xf8    <advapi32.RegCloseKey>
    0xfc    <winhttp.WinHttpQueryHeaders>
    0x100   <winhttp.WinHttpOpen>
    0x104   <winhttp.WinHttpConnect>
    0x108   <winhttp.WinHttpOpenRequest>
    0x10c   <winhttp.WinHttpSetOption>
    0x110   <winhttp.WinHttpAddRequestHeaders>
    0x114   <winhttp.WinHttpSendRequest>
    0x118   <winhttp.WinHttpReceiveResponse>
    0x11c   <winhttp.WinHttpReadData>
    0x120   <winhttp.WinHttpCloseHandle>
    0x124   ptr_2_ntdll
    0x128   ptr_2_kernel32
    0x12c   ptr_2_user32
    0x130   ptr_2_advapi32
    0x134   ptr_2_netapi32
    0x138   ptr_2_winhttp
    0x13c   bot_ID = &L"96C407F500000ADC72268059519"
    0x140   registeredFlag <bool>
    0x144   process_ID
    0x148   thread_ID
    0x14c   
    0x150   ? = 9
    0x154
    0x158   *RC4_key -> RandomNumbers
    0x15c   shiftSize -> RandomVal % 0x19
    0x160   beacon_time = 74
    0x164   delay_time = 29
    0x168   seed = 2e
    0x16c   version_Pikabot = L"1.8.32-beta"
    0x170   tag_Pikabot = L"GG21_T_DLL@T@f0adda360d2b4ccda11468e026526576"
    0x174   data_start = L"M3cpu"
    0x178   *Next_concatC2Data
    0x17c   *First_concatC2Data
    0x180   IPcount = 9
    0x184   empty_response <bool>
    0x188   unknown_purspose_flag1 => 2 when empty_response = 1
    0x18c
    0x190   max_connection_attemps = 20
    0x194   user_agent = "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; Trident/7.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; .NET4.0C; .NET4.0E; InfoPath.3; Zoom 3.6.0)"
    0x198   *URIs
    0x19c   *HTTPheaders_ptr
    0x1a0   *TEB
}

struct mem_iterator_struct {
  0x00 ptr2AllocatedMem
  0x04 memIterator
  0x08 mem_size
  0x0c mem_size_left
};

HTTPheaders_ptr {
    0x00    L"Accept: */*" -> media type : tipo de medios que el cliente acepta (texto, imagenes,audio...) -> '*/*' = Cualquier cosa
    0x04    L"Accept-Language: en-US,en;q=0.8" -> idiomas preferidos: ingles estadounidense y en menor medida inglés
    0x08    L"Accept-Encoding: gzip, deflate, br" -> esquemas de codificacion que puede manejar.
    0x0c    L"Connection: keep-alive" -> el cliente mantiene la conexion abierta tras completar la solicitud/respuesta
    0x10    0
}

URIs {
0x00  L"api/apps.permissions.resources.list"
0x04  L"api/admin.apps.approve"
0x08  L"api/auth.test"
0x0c  L"api/admin.apps.restricted.list"
0x10  L"api/admin.conversations.setConversationPrefs"
0x14  L"api/admin.conversations.ekm.listOriginalConnectedChannelInfo"
0x18  L"api/admin.usergroups.addChannels"
0x1c  L"api/admin.users.session.invalidate"
0x20  L"api/admin.emoji.addAlias"
0x24  L"api/admin.conversations.archive"
0x28  L"api/admin.users.setExpiration"
0x2c  L"api/api.test"
0x30  L"api/admin.conversations.delete"
0x34  L"api/admin.teams.settings.setDiscoverability"
0x38  L"api/admin.conversations.unarchive"
0x3c  L"api/admin.users.setRegular"
0x40  L"api/admin.teams.settings.setDescription"
0x44  L"api/admin.users.invite"
0x48  L"api/admin.teams.admins.list"
0x4c  0
}

concatC2Data0 {
  0x00  L"104.129.55.105"
  0x04  port = 8AF = 2223
  0x08  enableFeatures = 1 = True
  0x0c  connection_attemps = 0
  0x10  is_unavailable = 0
  0x14  0 -> ptr to 0
}

concatC2Data1 {
  0x00  L"103.82.243.5"
  0x04  port = 35D9
  0x08  enableFeatures = 1 = True
  0x0c  connection_attemps = 0
  0x10  is_unavailable = 0
  0x14  &concatC2Data0
}

concatC2Data2 {
  0x00  L"154.201.81.8"
  0x04  port = B97
  0x08  enableFeatures = 1 = True
  0x0c  connection_attemps = 0
  0x10  is_unavailable = 0
  0x14  &concatC2Data1
}

concatC2Data3 {
  0x00  L"45.76.251.190"
  0x04  port = 15FF
  0x08  enableFeatures = 1 = True
  0x0c  connection_attemps = 0
  0x10  is_unavailable = 0
  0x14  &concatC2Data2
}

concatC2Data4 {
  0x00  L"45.32.248.100"
  0x04  port = 8B2
  0x08  enableFeatures = 1 = True
  0x0c  connection_attemps = 0
  0x10  is_unavailable = 0
  0x14  &concatC2Data3
}

concatC2Data5 {
  0x00  L"23.226.138.161"
  0x04  port = 147A
  0x08  enableFeatures = 1 = True
  0x0c  connection_attemps = 0
  0x10  is_unavailable = 0
  0x14  &concatC2Data4
}

concatC2Data6 {
  0x00  L"104.129.55.106"
  0x04  port = 35D7
  0x08  enableFeatures = 1 = True
  0x0c  connection_attemps = 0
  0x10  is_unavailable = 0
  0x14  &concatC2Data5
}

concatC2Data7 {
  0x00 L"86.38.225.106"
  0x04  port = 8AD
  0x08  enableFeatures = 1 = True
  0x0c  connection_attemps = 0
  0x10  is_unavailable = 0
  0x14  &concatC2Data6
}

First_concatC2Data {
  0x00 L"37.60.242.86"
  0x04  port = B97
  0x08  enableFeatures = 1 = True
  0x0c  connection_attemps = 0
  0x10  is_unavailable = 0
  0x14  &concatC2Data7
}

RC4_key {
  030602F0  02 02 50 22 3C 8A D6 10 2E B2 BC DC 78 E0 9C 2C  ..P"<.Ö..²¼Üxà.,             "
  03060300  80 B6 14 40 44 86 5A 9A 38 B0 F2 CA E2 60 44 DA  .¶.@D.Z.8°òÊâ`DÚ
}

Victim_infoStruct {
  0x00 0x1291
  0x04 Victim_info (LMEM_MOVEABLE)
  0x08 sizeOf_Victim_info = 12D3 -> cantidad de bytes ya copiado en Victim_info: se utiliza para encontrar la direccion a la que 'appendear' las siguientes datos
  0x0c 0
  0x10 DataIsPlainText <bool> -> marcado a 1 si aun no se han encriptado los datos
  0x14 1
  0x18 0
  0x1c 0
}

Victim_info {
  0x00 sizeOf_Victim_info - 4 = 0x12CF ->  Al principiob es 0, cuando ya se ha rellenado todo el contenido se iguala a la 
                                            longitud de Victiminfo -4 , que es lo mismo que la longitud de la info sin este mismo 
                                            byte que indica su longitud
  
  0x04 0x1291 -> command

  0x08 0x1687 {
    0x8  0
    0x9  0
    0xa 16
    0xb 87
  }

  0x0c RandomVal (structPika + 0x15c) {
    0xc 0
    0xd 0
    0xe 0
    0xf 02
  }

  0x10 RC4_key (structPika + 0x158){
    0x10  02 02 50 22 3C 8A D6 10 2E B2 BC DC 78 E0 9C 2C  ..P"<.Ö..²¼Üxà.,     "
    0x20  80 B6 14 40 44 86 5A 9A 38 B0 F2 CA E2 60 44 DA  .¶.@D.Z.8°òÊâ`DÚ
  }  

  0x30 0x0036 <sizeof(bot_ID (structPika + 0x13c))> 
  0x34 *bot_ID{
    L"9.6.C.4.0.7.F.5.0.0.0.0.0.A.D.C.7.2.2.6.8.0.5.9.5.1.9."
  }

  0x6A 0x000A <sizeof(L"M.3.c.p.u.")>
  0x6E L"M.3.c.p.u."

  0x78 0x18 <sizeof(UserNameW)>
  0x7c L"I.M.F.R.e.v.e.r.s.i.n.g."

  0x94 0x1e <sizeof(ComputerNameW)>
  0x98 L"D.E.S.K.T.O.P.-.Q.7.V.Q.0.2.0."

  0xB8 CPU_FullName {
    0x00  41 4D 44 20 52 79 7A 65 6E 20 37 20 33 37 30 30  AMD Ryzen 7 3700  
    0x10  55 20 77 69 74 68 20 52 61 64 65 6F 6E 20 56 65  U with Radeon Ve  
    0x20  67 61 20 4D 6F 62 69 6C 65 20 47 66 78 20 20 00  ga Mobile Gfx  .
  }

  0xE8 0x44 <sizeof(DisplayDevice)>
  0xec L"V.i.r.t.u.a.l.B.o.x. .G.r.a.p.h.i.c.s. .A.d.a.p.t.e.r. .(.W.D.D.M.)."

  0x31 0x1cc4 ->  Active Directory Data : Si El ordenador no tiene nombre en un dominio 
  0x35 0x1cc4         (no forma parte de un Active Directory) se rellenan 12B con 0x1cc4 en cada 4B
  0x39 0x1cc4

  0x3d 0x7ff -> datos de memoria combinados: 
                - Los bits altos contienen una representación de ullTotalPhys en MiB.
		            - Los bits bajos contienen una representación ampliada de ullAvailPhys.
  
  0x41 0x780 -> coordenada X de la esquina inferior derecha de la ventana actual
  0x45 0x3b1 -> coordenada Y de la esquina inferior derecha de la ventana actual --> con estas dos podriamos asumir el tamaño de la pantalla del PC

       <VersionInfo>
  0x49 dwMajorVersion = 0xA0
  0x4d dwMinorVersion = 0x00
  0x51 nose = 0x1
  0x55 nose = 0x0
  0x59 dwBuildNumber = 0x4a65

  0x5d 9
  0x61 retrun value of NtQueryInformationToken = 0x0
  0x65 74
  0x69 2e

  0xE8 0x16 <sizeof(*L"1.8.32-beta")>
  0xec L"1...8...3.2.-.b.e.t.a."

  0xE8 0x5a <sizeof(*L"GG21_T_DLL@T@f0adda360d2b4ccda11468e026526576")>
  0xec L"G.G.2.1._.T._.D.L.L.@.T.@.f.0.a.d.d.a.3.6.0.d.2.b.4.c.c.d.a.1.1.4.6.8.e.0.2.6.5.2.6.5.7.6."

  0x1e5 procInfo
  0x... procInfo
  0x... procInfo
  0x... procInfo
  ...
}

procInfo {
  0x00 ProcessID
  0x04 th32ParentProcessID
  0x08 Wow64Process
  0x0c bool_isThisProc
  0x10 proc_could_be_opened
  0x14 pcPriClassBase
  0x18 cntThreads
  0x1c sizeOf(szExeFile)
  0x20 szExeFile -> string containing name of process 
}

command_info_struct {
  0x00 command
  0x04 content
  0x08 content_size
  0x0c sizeof(bot_ID)
  0x10 bot_ID
  0x14 1
  0x18 0
  0x1c 0
}

action_callback_struct {
  0x00 action0 = 0x2672
  0x04 &execute_action_2672
  0x08 action1 = 0x246f
  0x0c &execute_action_246f
  0x10 action2 = 0xacb
  0x14 &execute_action_acb
  0x18 action3 = 0x36c
  0x1c &execute_action_36c
  0x20 action4 = 0x792
  0x24 &execute_action_792
  0x28 action5 = 0x359
  0x2c &execute_action_359
  0x30 action6 = 0x3a6
  0x34 &execute_action_359
  0x38 action7= 0x240
  0x3c &execute_action_359
  0x40 action8 = 0x985
  0x44 &execute_action_985
  0x48 action9 = 0x982
  0x4c &execute_action_982
  0x50 0
}