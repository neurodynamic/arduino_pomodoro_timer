const int sensorPin = 0;
const int in_chair_indicator_pin = 3;
const int work_length = 4;
const int break_length = 4;
const int limbo_length = 6;
const int long_break_every_x_breaks = 4;
const int long_break_length = 8;
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const int buzzerPin = 5;

enum modes_t {WORK_MODE, LIMBO_MODE, BREAK_MODE};
modes_t mode = WORK_MODE;


int lightLevel, high = 0, low = 1023;//, intervals_since_last_full_second = 0;
int greenIntensity, blueIntensity, redIntensity;
double work_time_elapsed = 0, limbo_time_elapsed = 0, break_time_elapsed = 0, interval_in_ms = 1000.0;
boolean in_chair, first_limbo_alarm_on = true, second_limbo_alarm_on = true;

void setup()
{
  pinMode(in_chair_indicator_pin, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  // test();

  change_mode_if_necessary();
  
  lightLevel = analogRead(sensorPin);
  in_chair = lightLevel < 670;
  
  set_chair_indicator_led();
  
  set_time_indicator_led();
  
  tick();
}

void test(){
  while(true){
    play_boss_battle(buzzerPin);
    delay(3000);
  }
}

void change_mode_if_necessary()
{
  if(mode == WORK_MODE && work_time_elapsed >= work_length)
  {
    // reset_timers();
    mode = LIMBO_MODE;
    set_time_indicator_led();
    first_limbo_alarm_on = true;
    second_limbo_alarm_on = true;
    play_limbo_level_one(buzzerPin);
    play_limbo_level_one(buzzerPin);
  }

  if(mode == LIMBO_MODE && limbo_time_elapsed >= limbo_length/3 && first_limbo_alarm_on)
  {
    play_limbo_level_two(buzzerPin);
    play_limbo_level_two(buzzerPin);
    first_limbo_alarm_on = false;
  }

  if(mode == LIMBO_MODE && limbo_time_elapsed >= limbo_length*2/3 && second_limbo_alarm_on)
  {
    play_limbo_level_three(buzzerPin);
    play_limbo_level_three(buzzerPin);
    second_limbo_alarm_on = false;
  }

  if(mode == LIMBO_MODE && (limbo_time_elapsed >= limbo_length || in_chair == false))
  {
    reset_timers();
    mode = BREAK_MODE;
    set_time_indicator_led();
    play_monster_battle(buzzerPin);
  }

  if(mode == BREAK_MODE && break_time_elapsed >= break_length)
  {
    reset_timers();
    mode = WORK_MODE;
    set_time_indicator_led();
    play_victory(buzzerPin);
  }
}


    void reset_timers()
    {
      work_time_elapsed = 0;
      limbo_time_elapsed = 0;
      break_time_elapsed = 0;
    }

void set_time_indicator_led()
{
  if(mode == WORK_MODE)
  {
    shade_green_to_red_fade();
  }
  else if(mode == LIMBO_MODE)
  {
    shade_green_to_red_fade();
  }
  else
  {
    shade_red_to_blue_fade();
  }

  write_to_color_led(redIntensity, greenIntensity, blueIntensity);
}

    void shade_green_to_red_fade()
    {
      blueIntensity = 0;
      int pomodoro_completion = map(work_time_elapsed + limbo_time_elapsed, 0, work_length + (limbo_length/2), 0, 255);
      pomodoro_completion = constrain(pomodoro_completion, 0, 255);
    
      redIntensity = pomodoro_completion;
      greenIntensity = 255 - pomodoro_completion;
    }

    void shade_red_to_blue_fade()
    {
      greenIntensity = 0;
      int break_completion = map(break_time_elapsed, 0, break_length, 0, 255);
      break_completion = constrain(break_completion, 0, 255);
    
      blueIntensity = break_completion;
      redIntensity = 255 - break_completion;
    }

    void write_to_color_led(int redIntensity, int greenIntensity, int blueIntensity)
    {
      analogWrite(RED_PIN, redIntensity);
      analogWrite(BLUE_PIN, blueIntensity);
      analogWrite(GREEN_PIN, greenIntensity);
    }

void set_chair_indicator_led()
{
  if(in_chair)
  {
    analogWrite(in_chair_indicator_pin, low);
  }
  else
  {
    analogWrite(in_chair_indicator_pin, high);
  }
}

void tick()
{
  delay(interval_in_ms);
  // intervals_since_last_full_second = intervals_since_last_full_second + 1;
  
  // if(clock_is_on_an_exact_second())
  // {
  //   intervals_since_last_full_second = 0;
  //   print_status();
  // }
  
  advance_appropriate_timer();
}

    // boolean clock_is_on_an_exact_second()
    // {
    //   if(intervals_since_last_full_second == 1000.0/interval_in_ms)
    //   {
    //     return true;
    //   }
    //   else
    //   {
    //     return false;
    //   }
    // }

    // void print_status()
    // {
    //   Serial.print("light level: ");
    //   Serial.print(lightLevel);
    //   Serial.print("       work time: ");
    //   Serial.print(work_time_elapsed);
    //   Serial.print("       break time: ");
    //   Serial.println(break_time_elapsed); 
    // }

    void advance_appropriate_timer()
    {
      if(in_chair)
      {
        if(mode == LIMBO_MODE){
          limbo_time_elapsed = limbo_time_elapsed + interval_in_ms/1000.0;
        }
        else
        {
          work_time_elapsed = work_time_elapsed + interval_in_ms/1000.0;
        }
      }
      else
      {
        break_time_elapsed = break_time_elapsed + interval_in_ms/1000.0;
      } 
    }