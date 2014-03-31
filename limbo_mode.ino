void execute_limbo_mode_ticklist()
{
  shade_green_to_red_fade();

  if(limbo_time_elapsed >= limbo_length/3 && one_third_limbo_buzzer_played == false)
  {
    trigger_limbo_alarm(2);
  }

  else if(limbo_time_elapsed >= limbo_length*2/3 && two_thirds_limbo_buzzer_played == false)
  {
    trigger_limbo_alarm(3);
  }

  else if(limbo_time_elapsed >= limbo_length || in_chair == false)
  {
    if(work_time_completed_since_last_long_break >= work_length * long_break_every_x_breaks)
    {
      work_time_completed_since_last_long_break = 0;
      start_long_break();
    }
    else
    {
      start_regular_break();
    }
  }
}

    void trigger_limbo_alarm(int alarm_number)
    {
      switch(alarm_number)
      {
        case 1: 
          play_limbo_level_one(buzzerPin);
          play_limbo_level_one(buzzerPin);
          break;
        case 2: 
          play_limbo_level_two(buzzerPin);
          play_limbo_level_two(buzzerPin);
          one_third_limbo_buzzer_played = true;
          break;
        case 3: 
          play_limbo_level_three(buzzerPin);
          play_limbo_level_three(buzzerPin);
          two_thirds_limbo_buzzer_played = true;
          break;
        defaul : break;
      }
    }

    void start_regular_break()
    {
      work_time_completed_since_last_long_break += work_time_elapsed;
      reset_timers();
      mode = BREAK_MODE;
      shade_red_to_blue_fade(break_time_elapsed, break_length);
      play_monster_battle_ascension(buzzerPin);
    }

    void start_long_break()
    {
      reset_timers();
      mode = LONG_BREAK_MODE;
      shade_red_to_blue_fade(break_time_elapsed, long_break_length);
      play_boss_battle(buzzerPin);
    }

        void reset_timers()
        {
          work_time_elapsed = 0;
          limbo_time_elapsed = 0;
          break_time_elapsed = 0;
        }