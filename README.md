# hca2wav

## 概要

[@Nyagamon](https://github.com/Nyagamon)さんの[HCADecoder](https://github.com/Nyagamon/HCADecoder)をベースにしたhcaデコーダです。<br>
macOS High SierraとCentOS7上での動作を確認しています。<br>
コンパイルには **C++11** 対応のコンパイラが必要です。(gcc7が必要？)

## ダウンロード

[Releases](https://github.com/Cryptomelone/hca2wav/releases)の[Latest release](https://github.com/Cryptomelone/hca2wav/releases/latest)からどうぞ。

## コンパイル

```
git clone git@github.com:Cryptomelone/hca2wav.git
cd hca2wav
make compile
```
バイナリは `bin` フォルダ以下 `hca2wav` として生成されます。

## 使い方

```
hca2wav target_file.hca
```

- `-o [output]` 出力ファイル名を指定します。
- `-v [volume]` 音量を指定します。
- `-a [ciphKey1]` HCAキー1を指定します。
- `-b [ciphKey2]` HCAキー2を指定します。
- `-m [mode]` モードを指定します。
- `-l [loop]` ループを指定します。
- `-i` ファイル情報を出力します。
- `-c` 復号化を行います。

## 更新履歴

### HCAデコーダ

|published_at|publisher|version|
|---|---|---|
|2012/12/21 06:57:11.75|[>>799 (mwGK00US)](https://www.logsoku.com/r/2ch.net/gameurawaza/1283865855/799)|v1.00|
|2012/12/26 12:03:20.72|[>>807 (j7dJqDaj)](https://www.logsoku.com/r/2ch.net/gameurawaza/1283865855/807)|v1.01|
|2013/09/24 13:56:10.11|[>>972 (BssXY9a+)](https://www.logsoku.com/r/2ch.net/gameurawaza/1283865855/972)|v1.02|
|2014/04/09 13:11:52.67|[>>66 (VH3iUoHf)](https://www.logsoku.com/r/2ch.net/gameurawaza/1381596257/972)|v1.03|
|2014/04/20 21:55:36.04|[>>89 (AulPpKfN)](https://www.logsoku.com/r/2ch.net/gameurawaza/1381596257/89)|v1.10|
|2014/04/26 10:39:28.94|[>>101 (H4hCNS7+)](https://www.logsoku.com/r/2ch.net/gameurawaza/1381596257/101)|v1.11|
|2014/04/29 19:39:18.80|[>>105 (WtTgNFuQ)](https://www.logsoku.com/r/2ch.net/gameurawaza/1381596257/105)|v1.12|
|2015/02/04 07:47:22.48|[>>205 (+YGssg4f)](https://www.logsoku.com/r/2ch.net/gameurawaza/1381596257/205)|v1.13|
|2017/03/20 16:54:44.47|[>>132 (yeLWLsW/)](https://www.logsoku.com/r/2ch.sc/gameurawaza/1485136997/132)|v1.17|
|2017/03/21 04:22:35.43|[>>148 (f70CrkXN)](https://www.logsoku.com/r/2ch.sc/gameurawaza/1485136997/148)|v1.20|
|2017/07/14 18:58:16.15|[>>705 (3HxdrtVO)](https://www.logsoku.com/r/2ch.sc/gameurawaza/1485136997/705)|v1.21|

### hca2wav
|published_at|version|based version|
|---|---|---|
|2018/01/14 02:00|v1.0.0|v1.21|

以下オリジナルReadme.txt(md化)

---

## HCAファイルのデコード方法

  HCAファイルをhca.exeにドラッグ＆ドロップすると、同じファイル名のWAVEファイルができます。
  複数ファイルのデコードにも対応してます。
  デコードオプションはデフォルト値のままです。

  デコードオプションを指定したいときは
  オプション指定デコード.batにドラッグ＆ドロップしてください。
  こちらも複数ファイルのデコードに対応してます。


## HCAファイルの復号化方法

  HCAファイルを復号化.batにドラッグ＆ドロップすると、HCAファイル自体が復号化されます。
  上書きされるので注意してください。
  複数ファイルの復号化にも対応してます。


## 仕様

  デフォルトのデコードオプションは
    音量 = 1(倍)
    ビットモード = 16(ビット)
    ループ回数 = 0(回)
    復号鍵 = CC55463930DBE1AB ※PSO2で使われている鍵
  です。

  HCAファイルにループ情報が入っていた場合、WAVEファイルにsmplチャンクを追加してます。
  ただし、デコードオプションのループ回数が1回以上のときは、smplチャンクを追加せず、直接波形データとして出力します。
  このとき出力される波形データは以下のようになります。
  ※HCAファイルにループ情報が入っていない場合、ループ開始位置とループ終了位置をそれぞれ先頭位置と末尾位置として扱います。
  [先頭位置～ループ終了位置]＋[ループ開始位置～ループ終了位置]×(ループ回数－１)＋[ループ開始位置～末尾位置]

  HCAファイルにコメント情報が入っていた場合、WAVEファイルにnoteチャンクを追加してます。


## 注意事項

  一応バージョンチェックを外してますが
  今後、v2.1以降のHCAが出てきたとき、デコードに失敗する可能性があります。

  HCAヘッダの破損チェックも無効にしています。
  これはヘッダを改変しやすくするためです。
  もし本当に破損していてもエラーになりません。

  暗号テーブルで使用する鍵はゲーム別に異なります。※開発会社によっては同じ鍵を使うことをがあります。
  暗号テーブルの種類が0x38のとき、鍵が異なるとうまくデコードされません。

  復号鍵を指定してデコードするときは
  オプション指定デコード.batをテキストエディタで開いて、デフォルト値設定の復号鍵を変更しておくと楽です。

  CBRのみ対応。VBRはデコードに失敗します。※VBRは存在しない可能性あり。

  コマンドプロンプトの仕様で、&を含むファイルパス(ファイル名やフォルダ名)は
  オプション指定デコード.batや、復号化.batなどのバッチファイルにドラッグ＆ドロップすると
  ファイルが開けず、エラーが出ます。


## 免責事項

  このアプリケーションを利用した事によるいかなる損害も作者は一切の責任を負いません。
  自己の責任の上で使用して下さい。


## その他

  HCAv2.0からヘッダのVBRチェックをやってない痕跡があるので
  最初からCBRのみしか存在しないのかもしれない。

  ATHテーブルもType0しか存在しなかった痕跡あり。

  普通にデコードすると16ビットPCMになるので音質が劣化するよ！
  オプション指定デコードで、ビットモードをfloatにすると劣化しないよ！
  でもHCA自体が非可逆圧縮なので元々劣化してるよ！
  どっちだよ！
