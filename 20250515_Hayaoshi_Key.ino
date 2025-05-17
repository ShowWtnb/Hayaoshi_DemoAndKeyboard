#include <Arduino.h>
#include <Keyboard.h>
#include "SoundPlayer.h"
// #define LED_PIN A6
// #define BUTTON_PIN A7
// #define VOL_PIN A8
#define LED_PIN A2
#define BUTTON_PIN A1
#define VOL_PIN A3
#define Ket_Select_Pin BUTTON_PIN
#define KEY_SPACE 0x20
char key_press = KEY_KP_ENTER;
bool reset = true;
bool isPCMode = true;

void setup() {
  // pinの初期化
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(Ket_Select_Pin, INPUT_PULLUP);

  // スイッチが押された時に送るキーを選択する
  // デフォルトはEnter、ボタンを押しながら起動するとSpace
  if (digitalRead(Ket_Select_Pin) == LOW) {
    key_press = KEY_SPACE;
  } else {
    key_press = KEY_KP_ENTER;
  }

  // 接続されているのがPCか電源かを判定する
  // VOL_PIN（電源電圧）を測定する
  int value = analogRead(VOL_PIN);
  double volt = value * 5.0 / 1023.0;

  // 測定された電圧が3.0V以上だったら単独モード
  // 測定された電圧が3.0V以下だったらPCモード
  if (volt >= 3.0) {
    isPCMode = false;
    // 点滅と音でモードを通知する
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
    playGoodMelody();
  } else {
    // 点滅と音でモードを通知する
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(50);
    }
    playSadMelody();
  }
  Keyboard.releaseAll();
}

void loop() {
  if (isPCMode) {
    mainPC();
  } else {
    mainIndependent();
  }
}

void mainPC() {
  if ((digitalRead(BUTTON_PIN) == LOW)) {
    digitalWrite(LED_PIN, HIGH);
    if (reset) {
      reset = false;
      Keyboard.write(key_press);
      Keyboard.release(key_press);
    }
    delay(50);
  } else {
    digitalWrite(LED_PIN, LOW);
    reset = true;
  }
}

bool st = false;
uint64_t cnt = 0;
#define CNT_MAX 3000
#define BLINK_INTERVAL 250
void mainIndependent() {
  if (st) {
    // ボタンが押された
    bool isBlink = true;
    while (true) {
      // 反転して
      isBlink = !isBlink;
      // LEDを操作する
      if (isBlink) {
        // LEDをオン
        digitalWrite(LED_PIN, HIGH);
      } else {
        // LEDをオン
        digitalWrite(LED_PIN, LOW);
      }
      // インターバル分だけ休んで
      delay(BLINK_INTERVAL);
      // カウンターをインクリメント
      cnt++;
      // 規定時間経過していたら
      if (cnt * BLINK_INTERVAL > CNT_MAX) {
        // 点滅終了
        break;
      }
    }

    // ボタン検知モードに戻る
    st = false;
  } else {
    // ボタンが押されたかを検知する
    if ((digitalRead(BUTTON_PIN) == LOW)) {
      // 押されていたら
      // 次のモードを点滅モードに設定
      st = true;
      // カウンターのリセット
      cnt = 0;
      // LEDをオンにして
      digitalWrite(LED_PIN, HIGH);
      // 音再生
      playSound();
      // 一応ちょっと休む（チャタリング防止）
      delay(10);
    }
  }
}

void playSound() {
  // 音再生
  playSound(SOUND_BUZZER);
}
