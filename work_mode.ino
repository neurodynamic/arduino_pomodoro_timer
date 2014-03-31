void execute_work_mode_ticklist()
{
  shade_green_to_red_fade();

  if(work_time_elapsed >= work_length){
    change_to_limbo_mode();
  }
}

    void change_to_limbo_mode()
    {
      mode = LIMBO_MODE;
      shade_green_to_red_fade();
      one_third_limbo_buzzer_played = false;
      two_thirds_limbo_buzzer_played = false;
      trigger_limbo_alarm(1);
    } 