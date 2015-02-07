const int sensorPin = 0;
const int switchReaderPin = 5;
const int in_chair_indicator_pin = 3;
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const int buzzerPin = 5;

//https://github.com/hparra/ruby-serialport/
// CONSTANTS FOR TESTING
const int work_length = 4;
const int limbo_length = 6;
const int break_length = 4;
const int long_break_length = 8;
const int long_break_every_x_breaks = 3;

// CONSTANTS FOR REAL LIFE
// const int work_length = 24*60;
// const int limbo_length = 3*60;
// const int break_length = 5*60;
// const int long_break_length = 30*60;
// const int long_break_every_x_breaks = 4;

enum modes_t {WORK_MODE, LIMBO_MODE, BREAK_MODE, LONG_BREAK_MODE};
modes_t mode = WORK_MODE;


int proximity, high = 0, low = 1023;
int work_time_elapsed = 0, limbo_time_elapsed = 0, break_time_elapsed = 0;
int work_time_completed_since_last_long_break = 0;
boolean in_chair, switch_is_on, in_chair_at_last_check = false, one_third_limbo_buzzer_played = false, two_thirds_limbo_buzzer_played = false;


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
  switch_check();

  if(switch_is_on){
    active_loop();
  }else{
    inactive_loop();
  }
}

    void switch_check(){
      switch_is_on = analogRead(switchReaderPin) > 500;
    }

    void inactive_loop(){
      turn_off_lights();
      reset_all_timers_and_values();
      delay(100);
    }

        void reset_all_timers_and_values(){
          one_third_limbo_buzzer_played = false;
          two_thirds_limbo_buzzer_played = false;
          work_time_elapsed = 0;
          limbo_time_elapsed = 0;
          break_time_elapsed = 0;
          work_time_completed_since_last_long_break = 0;
          mode = WORK_MODE;
        }

        void turn_off_lights(){
          analogWrite(in_chair_indicator_pin, high);
          analogWrite(RED_PIN, high);
          analogWrite(GREEN_PIN, high);
          analogWrite(BLUE_PIN, high);
        }

    void active_loop(){
      monitor_chair_for_one_second();
      print_status();

      execute_ticklist();

      advance_appropriate_timer();
    }

        void monitor_chair_for_one_second()
        {
          for (int i = 0; i < 10; i++)
          {
            delay(100);
            proximity = analogRead(sensorPin);
            in_chair = proximity > 550;
            set_chair_indicator_led();
          }
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
          Serial.print("   prox1: ");
          Serial.print(proximity);
          Serial.print("   work: ");
          Serial.print(work_time_elapsed);
          Serial.print("   break: ");
          Serial.print(break_time_elapsed);
          Serial.print("   long: ");
          Serial.println(work_time_completed_since_last_long_break);
          Serial.print("   switch analog read: ");
          Serial.println(analogRead(switchReaderPin));
          // Serial.print("   switch on: ");
          // Serial.println(switch_is_on);
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

        void advance_appropriate_timer()
        {
          if(in_chair)
          {
            if(in_chair && in_chair_at_last_check)
            {
              break_time_elapsed = 0;

              if(mode == LIMBO_MODE){
                limbo_time_elapsed = limbo_time_elapsed + 1;
              }
              else
              {
                work_time_elapsed = work_time_elapsed + 1;
              }
            }

            in_chair_at_last_check = true;
          }
          else
          {
            break_time_elapsed = break_time_elapsed + 1;
            perform_break_time_checks();

            in_chair_at_last_check = false;
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
