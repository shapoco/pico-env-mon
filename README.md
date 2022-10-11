# pico-env-mon

秋月電子で買える部品でできる環境モニタです。

----

## 作例

3Dプリンタで作ったケースに収めた例です。

![作例の写真](img/example.jpg)

----

## 使用部品

- [Raspberry Pi Pico](https://akizukidenshi.com/catalog/g/gM-16132/)
- [シャープ モノクロHR-TFTメモリ液晶モジュール (LS027B4DH01)](https://akizukidenshi.com/catalog/g/gP-04944/)
- [フレキコネクタDIP化キット(AE-CNCONV-10P-0.5)](https://akizukidenshi.com/catalog/g/gK-07253/)
- [BME280使用　温湿度・気圧センサモジュールキット (AE-BME280)](https://akizukidenshi.com/catalog/g/gK-09421/)
- [CO2センサーモジュール MH-Z19C](https://akizukidenshi.com/catalog/g/gM-16142/)

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

![接続図](img/circuit.png)

----

## プログラム

### バイナリ

Coming Soon!

### ソースコード

コンパイルするには Raspberry Pi Pico SDK が必要です。インストール方法はググってください。Windows の場合は WSL2上にインストールすることをお勧めします。

1. 本リポジトリを clone して次のコマンドを実行します。

    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

    - Linux の場合は次のコマンドでもビルドできます。

        ```sh
        make -f Makefile.sample.mk
        ```

2. Raspberry Pi Pico の `BOOT SEL`ボタンを押しながら USBケーブルを接続し、書き込みモードにします。
3. `build/pico_env_mon.uf2` を Raspberry Pi Pico に書き込みます。

----

## 注意点

BME280 で取得できる温度の値は湿度と気圧の補正のためのもので、実際の気温より数度程度高くなります。このため、本プロジェクトではデフォルトでは取得した温度から 3.0℃ 減算した値を表示しています。

参考 : [第28回 温湿度・気圧センサ(BME280) 〜仕様概要〜 | ツール・ラボ](https://tool-lab.com/pic-practice-28/)

実際の気温とどの程度乖離するかはセンサの使用条件によります。ケースに入れたり、BME280 を CO2センサに近接させたりすると乖離が大きくなります。

補正値を変更するには、`src/pico_env_mon.cpp` の次の箇所を変更してコンパイルし直してください。

```c++
static const float TEMPERATURE_OFFSET = -3.0f;
```

----
