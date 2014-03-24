// http://www.rpgamer.com/games/ff/ff7/ff7mid.html

double play_victory(int buzzer)
{
   int notes[] = { 
    NOTE_C6, NOTE_C6, NOTE_C6,
    NOTE_C6,
    NOTE_GS5,
    NOTE_AS5,
    NOTE_C6, REST, NOTE_AS5,
    NOTE_C6
   };

  double beats[] = {0.333,0.333,0.333,1,1,1,0.333,0.333,0.333,2};
  double tempo = 370;
  int note_count = 10;
  
  return playSong(buzzer, notes, beats, tempo, note_count);
}

double play_limbo_level_one(int buzzer)
{
  int note_count = 2;
  int notes[] = { NOTE_AS1, NOTE_CS2 };
  double beats[] = {0.25,0.25};
  double tempo = 370;
  
  return playSong(buzzer, notes, beats, tempo, note_count);
}
double play_limbo_level_two(int buzzer)
{
  int note_count = 2;
  int notes[] = { NOTE_AS2, NOTE_CS3 };
  double beats[] = {0.25,0.25};
  double tempo = 370;
  
  return playSong(buzzer, notes, beats, tempo, note_count);
}
double play_limbo_level_three(int buzzer)
{
  int note_count = 2;
  int notes[] = { NOTE_AS3, NOTE_CS4 };
  double beats[] = {0.25,0.25};
  double tempo = 370;
  
  return playSong(buzzer, notes, beats, tempo, note_count);
}

double play_monster_battle(int buzzer)
{
   int notes[] = { 
    NOTE_F5, NOTE_F5, 
    NOTE_F5, NOTE_F5,
    NOTE_F5, NOTE_F5, 
    NOTE_F5, NOTE_F5//,
    // NOTE_F5, NOTE_F5, 
    // NOTE_C5, NOTE_DS5,
    // NOTE_FS5, NOTE_F5, 
    // NOTE_DS5, NOTE_FS5,
    // NOTE_F5, NOTE_F5, 
    // NOTE_F5, NOTE_F5,
    // NOTE_F5, NOTE_F5, 
    // NOTE_F5, NOTE_F5,
    // NOTE_F5, NOTE_F5, 
    // NOTE_DS5,
    // NOTE_DS5, 
    // NOTE_DS5,
    // NOTE_F5
   };

  double beats[] = {
    0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5//,
    // 0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
    // 0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
    // 0.5,0.5,1,1,1,
    // 4
  };
  double tempo = 250;
  int note_count = 8;//30;

  return playSong(buzzer, notes, beats, tempo, note_count);
}

double play_boss_battle(int buzzer)
{
   int notes[] = { 
    NOTE_A2, NOTE_A2, NOTE_A2, NOTE_C3,
    NOTE_A2, NOTE_A2, NOTE_A2, NOTE_D3,
    NOTE_A2, NOTE_A2, NOTE_A2, NOTE_DS3,
    NOTE_D3, NOTE_C3, NOTE_D3, NOTE_C3,
    NOTE_B2, NOTE_C3, NOTE_B2,

    NOTE_A2, NOTE_A2, NOTE_A2, NOTE_C3,
    NOTE_A2, NOTE_A2, NOTE_A2, NOTE_D3,
    NOTE_A2, NOTE_A2, NOTE_A2, NOTE_DS3,
    NOTE_D3, NOTE_C3, NOTE_D3, NOTE_C3,
    NOTE_B2, NOTE_C3, NOTE_B2,

    NOTE_C3, NOTE_C3, NOTE_C3, NOTE_DS3,
    NOTE_C3, NOTE_C3, NOTE_C3, NOTE_F3,
    NOTE_C3, NOTE_C3, NOTE_C3, NOTE_FS3,
    NOTE_F3, NOTE_DS3, NOTE_F3, NOTE_DS3, 
    NOTE_D3, NOTE_DS3, NOTE_D3,

    NOTE_C3, NOTE_C3, NOTE_C3, NOTE_DS3,
    NOTE_C3, NOTE_C3, NOTE_C3, NOTE_F3,
    NOTE_C3, NOTE_C3, NOTE_C3, NOTE_FS3,
    NOTE_F3, NOTE_DS3, NOTE_F3, NOTE_DS3, 
    NOTE_D3, NOTE_DS3, NOTE_D3//,

    // NOTE_C5
    // , NOTE_D5, NOTE_D5, NOTE_D5,
    // NOTE_C5, NOTE_D5, NOTE_D5, NOTE_D5
    // NOTE_DS5, NOTE_F5, NOTE_F5, NOTE_F5,
    // NOTE_DS5, NOTE_F5, NOTE_F5, NOTE_F5,
    // NOTE_A5
   };

  double beats[] = {
    0.33,0.33,0.33,1,
    0.33,0.33,0.33,1,
    0.33,0.33,0.33,0.33,
    0.33,0.33,0.33,0.33,
    0.33,1,0.33,
    0.33,0.33,0.33,1,
    0.33,0.33,0.33,1,
    0.33,0.33,0.33,0.33,
    0.33,0.33,0.33,0.33,
    0.33,1,0.33,

    0.33,0.33,0.33,1,
    0.33,0.33,0.33,1,
    0.33,0.33,0.33,0.33,
    0.33,0.33,0.33,0.33,
    0.33,1,0.33,
    0.33,0.33,0.33,1,
    0.33,0.33,0.33,1,
    0.33,0.33,0.33,0.33,
    0.33,0.33,0.33,0.33,
    0.33,1,0.33,

    //8
    // ,1,1,1,
    // 5,1,1,1
    // 4,1,1,1,
    // 4,1,1,1,
    // 4
  };
  double tempo = 250;
  int note_count = 76;

  return playSong(buzzer, notes, beats, tempo, note_count);
}


double play_monster_battle_ascension(int buzzer)
{
   int notes[] = { 
    NOTE_C3, NOTE_AS2, NOTE_C3,
    NOTE_DS3//, NOTE_F3, NOTE_G3, 
    // NOTE_GS3, NOTE_G3, NOTE_GS3, 
    // NOTE_AS3, NOTE_C3, NOTE_DS3, 
    // NOTE_F3, NOTE_G3, NOTE_GS3, 
    // NOTE_AS3, NOTE_C4, NOTE_C4,
    // NOTE_F4
   };

  double beats[] = {
    1.5,1.5,1.5,
    1.5//,1,1,
    // 1.5,1.5,1.5,
    // 1.5,1,1,
    // 1.5,1.5,1.5,
    // 1.5,1,1,2
  };
  double tempo = 300;
  int note_count = 4;
  
  return playSong(buzzer, notes, beats, tempo, note_count);
}

    double playSong(int buzzer, int notes[], double beats[], int tempo, int note_count){
      int i;
      double duration, total_duration = 0;

      for (i = 0; i < note_count; i++) // step through the song arrays
      {
        duration = beats[i] * tempo;  // length of note/rest in ms
        total_duration = total_duration + duration;

        if (notes[i] == REST)          // is this a rest? 
        {
          delay(duration);            // then pause for a moment
        }
        else                          // otherwise, play the note
        {
          tone(buzzer, notes[i], duration);
          delay(duration);            // wait for tone to finish
        }
        delay(tempo/10);              // brief pause between notes
      }

      return total_duration;
    }