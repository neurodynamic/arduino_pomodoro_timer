const int sensorPin = 0;
const int ambientSensorPin = 1;
const int in_chair_indicator_pin = 3;
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const int buzzerPin = 5;

// const int work_length = 4;
// const int limbo_length = 6;
// const int break_length = 4;
// const int long_break_length = 8;
// const int long_break_every_x_breaks = 3;

const int work_length = 24*60;
const int limbo_length = 2*60;
const int break_length = 5*60;
const int long_break_length = 30*60;
const int long_break_every_x_breaks = 4;

enum modes_t {WORK_MODE, LIMBO_MODE, BREAK_MODE, LONG_BREAK_MODE};
modes_t mode = WORK_MODE;


int lightLevel, ambientLightLevel, high = 0, low = 1023;//, intervals_since_last_full_second = 0;
int work_time_elapsed = 0, limbo_time_elapsed = 0, break_time_elapsed = 0;//, interval_in_ms = 1000.0;
int work_time_completed_since_last_long_break = 0;
boolean in_chair, one_third_limbo_buzzer_played = false, two_thirds_limbo_buzzer_played = false;


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
  // test_song();
  monitor_chair_for_one_second();
  print_status();

  execute_ticklist();

  advance_appropriate_timer();
}

    void test_song(){
      while(true){
        play_monster_battle_ascension(buzzerPin);
        delay(3000);
      }
    }

    void monitor_chair_for_one_second()
    {
      for (int i = 0; i < 10; i++)
      {
        delay(100);
        lightLevel = analogRead(sensorPin);
        ambientLightLevel = analogRead(ambientSensorPin);
        in_chair = ambientLightLevel - lightLevel >= 110;
        set_chair_indicator_led();
      }
    }

    void execute_ticklist()
    {
      switch(mode)
      {
        case WORK_MODE: execute_work_mode_ticklist(); break;
        case LIMBO_MODE: execute_limbo_mode_ticklist(); break;
        case BREAK_MODE: execute_break_mode_ticklist(); break;
        case LONG_BREAK_MODE: execute_long_break_mode_ticklist(); break;
        defaul : break;
      }
    }
        
        void execute_work_mode_ticklist()
        {
          shade_green_to_red_fade();

          if(work_time_elapsed >= work_length){
            change_to_limbo_mode();
          }
        }

            void change_to_limbo_mode()
            {
              // reset_timers();
              mode = LIMBO_MODE;
              shade_green_to_red_fade();
              one_third_limbo_buzzer_played = false;
              two_thirds_limbo_buzzer_played = false;
              trigger_limbo_alarm(1);
            } 
        
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
            if(work_time_completed_since_last_long_break >= break_length * long_break_every_x_breaks)
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

    void print_status()
    {
      Serial.print("ll: ");
      Serial.print(lightLevel);
      Serial.print("   all: ");
      Serial.print(ambientLightLevel);
      Serial.print("   diff: ");
      Serial.print(ambientLightLevel - lightLevel);
      Serial.print("   work time: ");
      Serial.print(work_time_elapsed);
      Serial.print("   break time: ");
      Serial.println(break_time_elapsed); 
    }

    void advance_appropriate_timer()
    {
      if(in_chair)
      {
        break_time_elapsed = 0;

        if(mode == LIMBO_MODE){
          limbo_time_elapsed = limbo_time_elapsed + 1;
        }
        else
        {
          work_time_elapsed = work_time_elapsed + 1;
          break_time_elapsed = 0;
        }
      }
      else
      {
        break_time_elapsed = break_time_elapsed + 1;
        perform_break_time_checks();
      } 
    }

        void perform_break_time_checks()
        {

          if(break_time_elapsed > work_time_elapsed){
            work_time_completed_since_last_long_break += work_time_elapsed;
            work_time_elapsed = 0;
          }

          if(break_time_elapsed == break_length){
            work_time_completed_since_last_long_break += work_time_elapsed;
            work_time_elapsed = 0;
          }

          if(break_time_elapsed >= long_break_length){
            work_time_completed_since_last_long_break = 0;
            work_time_elapsed = 0;
          }
        }