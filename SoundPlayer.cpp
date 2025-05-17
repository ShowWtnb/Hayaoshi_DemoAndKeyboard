#include "Arduino.h"
#include "SoundPlayer.h"
// #include "my_sound.h"
#include "pitches.h"

// 同期だがブロックされるわけではないのでタイミングによっては割り込まれる可能性がある
void playSound(SoundType soundType)
{
    switch (soundType)
    {
    case SOUND_BUZZER:
        // ボタン音
        tone(SOUND_OUT_PIN, 640);
        delay(120);
        tone(SOUND_OUT_PIN, 522);
        delay(220);
        noTone(SOUND_OUT_PIN);
        break;
    case SOUND_CORRECT:
        // 正解
        tone(SOUND_OUT_PIN, 640);
        delay(120);
        tone(SOUND_OUT_PIN, 522);
        delay(120);
        tone(SOUND_OUT_PIN, 640);
        delay(120);
        tone(SOUND_OUT_PIN, 522);
        delay(120);
        tone(SOUND_OUT_PIN, 640);
        delay(120);
        tone(SOUND_OUT_PIN, 522);
        delay(220);
        noTone(SOUND_OUT_PIN);
        break;
    case SOUND_WRONG:
        // 不正解
        tone(SOUND_OUT_PIN, 100);
        delay(120);
        noTone(SOUND_OUT_PIN);
        delay(100);
        tone(SOUND_OUT_PIN, 100);
        delay(500);
        noTone(SOUND_OUT_PIN);
        break;
    case SOUND_WRONG_CONTINUE:
        // 不正解音を流し続ける
        tone(SOUND_OUT_PIN, 100);
        delay(120);
        noTone(SOUND_OUT_PIN);
        delay(100);
        tone(SOUND_OUT_PIN, 100);
        break;
    case SOUND_STOP:
        // 音の再生を止める
        noTone(SOUND_OUT_PIN);
        break;
    default:
        break;
    }
}

void playGsus4()
{
    tone(SOUND_OUT_PIN, NOTE_G3);
    delay(100);
    tone(SOUND_OUT_PIN, NOTE_C4);
    delay(50);
    tone(SOUND_OUT_PIN, NOTE_D4);
    delay(50);
    tone(SOUND_OUT_PIN, NOTE_G4);
    delay(100);
    tone(SOUND_OUT_PIN, 0);
    delay(100);
    tone(SOUND_OUT_PIN, NOTE_C5);
    delay(100);
    tone(SOUND_OUT_PIN, NOTE_G5);
    delay(100);
    noTone(SOUND_OUT_PIN);
}
void playFaug7()
{
    tone(SOUND_OUT_PIN, NOTE_F3);
    delay(300);
    tone(SOUND_OUT_PIN, NOTE_DS3);
    delay(100);
    tone(SOUND_OUT_PIN, NOTE_A3);
    delay(100);
    tone(SOUND_OUT_PIN, NOTE_CS3);
    delay(100);
    tone(SOUND_OUT_PIN, 0);
    delay(100);
    tone(SOUND_OUT_PIN, NOTE_DS4);
    delay(100);
    tone(SOUND_OUT_PIN, NOTE_F3);
    delay(300);
    noTone(SOUND_OUT_PIN);
}
void playGoodMelody()
{
    playGsus4();
}
void playSadMelody()
{
    playFaug7();
}