const int sensorPin = 0;
const int in_chair_indicator_pin = 3;
const int pomodoro_length = 7;
const int break_length = 4;
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

enum modes_t {WORK_MODE, BREAK_MODE};

modes_t mode = WORK_MODE;
int lightLevel, high = 0, low = 1023, intervals_since_last_full_second = 0;
double work_time_elapsed = 0, break_time_elapsed = 0, interval_in_ms = 100.0;
boolean in_chair;

void setup()
{
  pinMode(in_chair_indicator_pin, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  change_mode_if_mode_time_has_expired();
  
  lightLevel = analogRead(sensorPin);
  in_chair = lightLevel < 670;
  
  set_chair_indicator_led();
  
  set_time_indicator_led();
  
  tick();
}



void change_mode_if_mode_time_has_expired()
{
  if(mode == WORK_MODE && work_time_elapsed >= pomodoro_length)
  {
    reset_timers();
    mode = BREAK_MODE;
  }
  
  if(mode == BREAK_MODE && break_time_elapsed >= break_length)
  {
    reset_timers();
    mode = WORK_MODE;
  }
}

void reset_timers()
{
  work_time_elapsed = 0;
  break_time_elapsed = 0;
}

void set_time_indicator_led()
{
  int pomodoro_completion, break_completion, greenIntensity, blueIntensity, redIntensity;
  
  if(mode == WORK_MODE)
  {
    blueIntensity = 0;
    pomodoro_completion = map(work_time_elapsed, 0, pomodoro_length, 0, 255);
    pomodoro_completion = constrain(pomodoro_completion, 0, 255);
  
    redIntensity = pomodoro_completion;
    greenIntensity = 255 - pomodoro_completion;
  }
  else
  {
    greenIntensity = 0;
    break_completion = map(break_time_elapsed, 0, break_length, 0, 255);
    break_completion = constrain(break_completion, 0, 255);
  
    blueIntensity = break_completion;
    redIntensity = 255 - break_completion;
  }

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
  intervals_since_last_full_second = intervals_since_last_full_second + 1;
  
  if(in_chair)
  {
    work_time_elapsed = work_time_elapsed + interval_in_ms/1000.0;
  }
  else
  {
    break_time_elapsed = break_time_elapsed + interval_in_ms/1000.0;
  }
    
  if(intervals_since_last_full_second == 1000.0/interval_in_ms)
  {
    intervals_since_last_full_second = 0;
    
    Serial.print("light level: ");
    Serial.print(lightLevel);
    Serial.print("       work time: ");
    Serial.print(work_time_elapsed);
    Serial.print("       break time: ");
    Serial.println(break_time_elapsed);
  }
}
