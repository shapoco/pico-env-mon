# pico-env-mon

秋月電子で買える部品でできる環境モニタです。

温度、湿度、気圧、CO2濃度を 5秒間隔で取得し、24時間のトレンドグラフとともに表示します。

反射型のディスプレイなので寝室等でも眩しくありません。

----

## 作例

3Dプリンタで作ったケースに収めた例です。

![作例の写真](img/example.jpg)

![基板の写真](img/board.jpg)

----

## 使用部品

- [Raspberry Pi Pico](https://akizukidenshi.com/catalog/g/gM-16132/)
- [シャープ モノクロHR-TFTメモリ液晶モジュール (LS027B4DH01)](https://akizukidenshi.com/catalog/g/gP-04944/)
    - :warning: フレキケーブルは乱暴に扱うと壊れやすいので注意してください。
- [フレキコネクタDIP化キット(AE-CNCONV-10P-0.5)](https://akizukidenshi.com/catalog/g/gK-07253/)
- [BME280使用　温湿度・気圧センサモジュールキット (AE-BME280)](https://akizukidenshi.com/catalog/g/gK-09421/)
- [CO2センサーモジュール MH-Z19C](https://akizukidenshi.com/catalog/g/gM-16142/)
    - :warning: ピンヘッダが付いていますが 2.54mmピッチのユニバーサル基板には適合しません。1.27mmピッチのユニバーサル基板を使用するか、ピンヘッダを使用せずに配線してください。
- [タクトスイッチ (黒色)](https://akizukidenshi.com/catalog/g/gP-03647/)
    - CO2センサのキャリブレーションに使用します。
- [分割ロングピンソケット 1x42(42P)](https://akizukidenshi.com/catalog/g/gC-05779/)
- その他
    - ユニバーサル基板
    - 配線類
    - microUSBケーブル (書き込み/電源供給)

----

## 接続

|Pico|LS027B4DH01|BME280|MH-Z19C|
|:--|:--|:--|:--|
|`VBUS`|`VDD`, `VDDA`, `EXTMODE`||`Vin`|
|`3V3`||`VDD`||
|`GND`|`VSS`, `VSSA`|`GND`|`GND`|
|`GPIO0` (uart0 TX)|||`RX`|
|`GPIO1` (uart1 RX)|||`TX`|
|`GPIO16` (spi0 RX)||`SDO`|
|`GPIO17` (spi0 CSn)||`CSB`|
|`GPIO18` (spi0 SCLK)|`SCLK`|`SCK`|
|`GPIO19` (spi0 TX)|`SI`|`SDI`|
|`GPIO20`|`SCS`||
|`GPIO21`|`EXTCOMIN`||
|`GPIO22`|`DISP`||

![接続図](img/connection.png)

----

## プログラム

### バイナリ

1. [Releases](https://github.com/shapoco/pico-env-mon/releases) から `pico_env_mon_x.x.zip` をダウンロードし、展開します。
2. Raspberry Pi Pico の `BOOT SEL`ボタンを押しながら USBケーブルを接続し、書き込みモードにします (USBストレージとして認識されます)。
3. `pico_env_mon.uf2` を Raspberry Pi Pico に書き込みます。

### ソースコードからのビルド

ビルドするには Raspberry Pi Pico SDK が必要です。インストール方法はググってください。Windows の場合は WSL2上にインストールすることをお勧めします。

1. 本リポジトリを clone し、リポジトリのディレクトリ内でビルドを実行します。

    ```sh
    git clone https://github.com/shapoco/pico-env-mon.git
    cd pico-env-mon
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Raspberry Pi Pico の `BOOT SEL`ボタンを押しながら USBケーブルを接続し、書き込みモードにします (USBストレージとして認識されます)。
4. `pico-env-mon/build/pico_env_mon.uf2` を Raspberry Pi Pico に書き込みます。

----

## 調整

### BME280 の温度

BME280 で取得できる温度の値は湿度と気圧の補正のためのもので、実際の気温より若干高くなります。

> The integrated temperature sensor has been optimized for lowest noise and highest resolution. Its output is used for temperature compensation of the pressure and humidity sensors and can also be used for estimation of the ambient temperature. 

> Temperature measured by the internal temperature sensor. This temperature value depends on the PCB temperature, sensor element self-heating and ambient temperature and is typically above ambient temperature.

実際の気温とどの程度乖離するかはセンサの使用条件によります。ケースに入れたり、BME280 を CO2センサに近接させたりすると乖離が大きくなります。本プロジェクトではこれらを考慮し、デフォルトでは取得した温度から 1.5℃ 減算した値を表示します。

補正値を変更するには、`src/pico_env_mon.cpp` の次の箇所を変更してビルドし直してください。

```c++
static const float TEMPERATURE_OFFSET = -1.5f;
```

### MH-Z19C のキャリブレーション

MH-Z19C は初期状態では正しい値を示さないケースがあるようです。

屋外に放置して値が 400ppm 付近まで下がらない場合や、人がいる室内なのに 400ppm 付近に張り付いてしまう場合はキャリブレーションを実施してください。

参考 : [Home Assistant: ESP32+MH-Z19CでCO2モニター構築(2) [キャリブレーション編] - Sympapaのスマートホーム日記](https://sympapa.hatenablog.com/entry/2022/06/05/091621)

1. 本機を屋外や誰もいない風通しの良い場所に 20分間放置します。
2. 吐息がかからないように息を止めて、Zero Point Calibrationスイッチを 7秒間押下します。

なお、本プロジェクトではオートキャリブレーションは無効化されています。

### 時間軸のスケール変更

デフォルトでは 24時間分のグラフが表示されます。

スケールを変更するには、`src/pico_env_mon.cpp` の次の箇所を変更してビルドし直してください。

```c++
static const int GRAPH_TIME_RANGE_H = 24;
```

----
