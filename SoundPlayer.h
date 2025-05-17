#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#define SOUND_OUT_PIN A10
typedef enum sound_type
{
  SOUND_BUZZER = 0,
  SOUND_CORRECT,
  SOUND_WRONG,
  SOUND_WRONG_CONTINUE,
  SOUND_STOP,

  SOUND_NONE = -1
} SoundType;

void playSound(SoundType soundType);
void playGoodMelody();
void playSadMelody();

#endif // SOUND_PLAYER_H
