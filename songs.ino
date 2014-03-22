

void play_victory(int buzzer)
{
   int victory_notes[] = { 
    NOTE_C6, NOTE_C6, NOTE_C6,
    NOTE_C6,
    NOTE_GS5,
    NOTE_AS5,
    NOTE_C6, REST, NOTE_AS5,
    NOTE_C6
   };

  double victory_beats[] = {0.333,0.333,0.333,1,1,1,0.333,0.333,0.333,2};
  double victory_tempo = 370;

  playSong(buzzer, victory_notes, victory_beats, victory_tempo);
}

    void playSong(int buzzer, int notes[], double beats[], int tempo){
      int i;
      double duration;

      for (i = 0; i < 10; i++) // step through the song arrays
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