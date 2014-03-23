

void play_victory(int buzzer)
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

  playSong(buzzer, notes, beats, tempo, 10);
}

void play_monster_battle(int buzzer)
{
   int notes[] = { 
    NOTE_F5, NOTE_F5, 
    NOTE_F5, NOTE_F5,
    NOTE_F5, NOTE_F5, 
    NOTE_F5, NOTE_F5,
    NOTE_F5, NOTE_F5, 
    NOTE_C5, NOTE_DS5,
    NOTE_FS5, NOTE_F5, 
    NOTE_DS5, NOTE_FS5,
    NOTE_F5, NOTE_F5, 
    NOTE_F5, NOTE_F5,
    NOTE_F5, NOTE_F5, 
    NOTE_F5, NOTE_F5,
    NOTE_F5, NOTE_F5, 
    NOTE_DS5,
    NOTE_DS5, 
    NOTE_DS5,
    NOTE_F5
   };

  double beats[] = {
    0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
    0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
    0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
    0.5,0.5,1,1,1,
    4
  };
  double tempo = 250;

  playSong(buzzer, notes, beats, tempo, 30);
}


void play_boss_battle(int buzzer)
{
   int notes[] = { 
    NOTE_C4, NOTE_AS3, NOTE_C4,
    NOTE_DS4, NOTE_F4, NOTE_G4, 
    NOTE_GS4, NOTE_G4, NOTE_GS4, 
    NOTE_AS4, NOTE_C5, NOTE_DS5, 
    NOTE_F5, NOTE_G5, NOTE_GS5, 
    NOTE_AS5, NOTE_C6, NOTE_C6,
    NOTE_F6
   };

  double beats[] = {
    1.5,1.5,1.5,
    1.5,1,1,
    1.5,1.5,1.5,
    1.5,1,1,
    1.5,1.5,1.5,
    1.5,1,1,2
  };
  double tempo = 320;

  playSong(buzzer, notes, beats, tempo, 19);
}

    void playSong(int buzzer, int notes[], double beats[], int tempo, int note_count){
      int i;
      double duration;

      for (i = 0; i < note_count; i++) // step through the song arrays
      {
        duration = beats[i] * tempo;  // length of note/rest in ms
        
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
    }