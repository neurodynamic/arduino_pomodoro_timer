void execute_break_mode_ticklist()
{
  shade_red_to_blue_fade(break_time_elapsed, break_length);

  if(break_time_elapsed >= break_length){
    change_to_work_mode();
  }
}

void execute_long_break_mode_ticklist()
{
  shade_red_to_blue_fade(break_time_elapsed, long_break_length);

  if(break_time_elapsed >= long_break_length){
    change_to_work_mode();
  }
}

    void change_to_work_mode()
    {
      reset_timers();
      mode = WORK_MODE;
      shade_green_to_red_fade();
      play_victory(buzzerPin);
    }

    void shade_green_to_red_fade()
    {
      int redIntensity, blueIntensity = 0, greenIntensity, normalized_fade_completion;

      normalized_fade_completion = map(work_time_elapsed + limbo_time_elapsed, 0, work_length + (limbo_length/2), 0, 255);
      normalized_fade_completion = constrain(normalized_fade_completion, 0, 255);

      redIntensity = normalized_fade_completion;
      greenIntensity = 255 - normalized_fade_completion;

      write_to_color_led(redIntensity, greenIntensity, blueIntensity);
    }

    void shade_red_to_blue_fade(int fade_completion, int fade_length)
    {
      int redIntensity, blueIntensity, greenIntensity = 0, normalized_fade_completion;

      normalized_fade_completion = map(fade_completion, 0, fade_length, 0, 255);
      normalized_fade_completion = constrain(normalized_fade_completion, 0, 255);

      blueIntensity = normalized_fade_completion;
      redIntensity = 255 - normalized_fade_completion;

      write_to_color_led(redIntensity, greenIntensity, blueIntensity);
    }

        void write_to_color_led(int redIntensity, int greenIntensity, int blueIntensity)
        {
          analogWrite(RED_PIN, redIntensity);
          analogWrite(BLUE_PIN, blueIntensity);
          analogWrite(GREEN_PIN, greenIntensity);
        }