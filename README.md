README
===============
会議時間と会議に要した人件費を計測します。

## ソースコードの動作環境
* Win7 32bit
* Qt 5.5.1
* Qt Creator 3.5.1

## 仕様
* exeフォルダを丸ごとコピーして，exeを起動するだけで使えるお手軽タイマー。
* 単価・会議の人数・会議時間・赤字額は整数範囲で自由に設定できます。
* スタートで計測開始，ストップで一時停止。リセットはexe再度立ち上げが必要
* 会議時間をオーバーするとビープ音が鳴り，文字が赤字になる
* 常に前面表示。パワポのスライドショーモードでも前面表示するハズ。
* 保存ボタンで，txtにメモや会議時間等のデータを保存する。