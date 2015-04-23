const int irSwitchReaderPin = 0,
          onOffSwitchReaderPin = 5,
          testSwitchReaderPin = 3,
          in_chair_indicator_pin = 3,
          RED_PIN = 9,
          GREEN_PIN = 10,
          BLUE_PIN = 11,
          buzzerPin = 5;

//https://github.com/hparra/ruby-serialport/
// CONSTANTS FOR TESTING
const int work_test_length = 4,
          limbo_test_length = 6,
          break_test_length = 4,
          long_break_test_length = 8,
          long_break_test_every_x_breaks = 3;

// CONSTANTS FOR REAL LIFE
const int irl_work_length = 24*60, 
          irl_limbo_length = 3*60,
          irl_break_length = 5*60,
          irl_long_break_length = 30*60,
          irl_long_break_every_x_breaks = 4;

// ACTUAL VALUES
int work_length, 
    limbo_length,
    break_length,
    long_break_length,
    long_break_every_x_breaks;

enum modes_t {WORK_MODE, LIMBO_MODE, BREAK_MODE, LONG_BREAK_MODE};
modes_t mode = WORK_MODE;


int irSwitchReading, 
    testSwitchReading,
    high = 0, 
    low = 1023,
    work_time_elapsed = 0, 
    limbo_time_elapsed = 0,
    break_time_elapsed = 0, 
    work_time_completed_since_last_long_break = 0;
    
boolean in_chair, 
        on_off_switch_is_on, 
        test_switch_mode,
        test_mode = false,
        in_chair_at_last_check = false, 
        one_third_limbo_buzzer_played = false, 
        two_thirds_limbo_buzzer_played = false;


void setup()
{
  pinMode(in_chair_indicator_pin, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  restBuzzer(buzzerPin);
    
  Serial.begin(9600);
}

void loop()
{
  on_off_switch_check();  

  if(on_off_switch_is_on){
    active_loop();
  }else{
    inactive_loop();
  }
}

    void on_off_switch_check(){
      on_off_switch_is_on = analogRead(onOffSwitchReaderPin) > 500;
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
      test_switch_check();
      monitor_chair_for_one_second();
      print_status();

      execute_ticklist();

      advance_appropriate_timer();
    }
    
        void test_switch_check(){
    
          if(test_mode != test_switch_mode){
            test_mode = test_switch_mode;
            set_timing_variables();
            reset_all_timers_and_values();
          }
        }
        
        void set_timing_variables(){
          if(test_mode){
            work_length = work_test_length;
            limbo_length = limbo_test_length;
            break_length = break_test_length;
            long_break_length = long_break_test_length;
            long_break_every_x_breaks = long_break_test_every_x_breaks;
            
          }else{
            work_length = irl_work_length;
            limbo_length = irl_limbo_length;
            break_length = irl_break_length;
            long_break_length = irl_long_break_length;
            long_break_every_x_breaks = irl_long_break_every_x_breaks;
          }
        }

        void monitor_chair_for_one_second()
        {
          for (int i = 0; i < 10; i++)
          {
            delay(100);
            irSwitchReading = analogRead(irSwitchReaderPin);
            in_chair = irSwitchReading < 500;
            set_chair_indicator_led();
            
            testSwitchReading = analogRead(testSwitchReaderPin);
            test_switch_mode = testSwitchReading < 500;
            test_switch_check();
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
          Serial.print("   IR switch reading: ");
          Serial.print(irSwitchReading);
          Serial.print("   test switch reading: ");
          Serial.print(analogRead(testSwitchReaderPin) > 500);
          Serial.print("   work: ");
          Serial.print(work_time_elapsed);
          Serial.print("   break: ");
          Serial.print(break_time_elapsed);
          Serial.print("   long: ");
          Serial.println(work_time_completed_since_last_long_break);
          Serial.print("   switch analog read: ");
          Serial.println(analogRead(onOffSwitchReaderPin));
          Serial.print("   switch on: ");
          Serial.println(on_off_switch_is_on);
                    
          Serial.println();
          Serial.println("--------------------------------------");
          Serial.println();

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
