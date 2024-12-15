void start_stage2()
{
  // initialize pikabot_core to 0
  for (i = 0x15; i != 0; i = i + -1) {
    *array_copy = 0;
    array_copy = array_copy + 1;
  }
  pikabot_core = &zero;
  
  thisway1();
  if (*pikabot_core != 1) {
    thisway2();
  }
  return;
}