# MiniSumoRC
 
1. Para sincronizar o controle com o ESP32, baixe o programa: https://sixaxispairtool.en.lo4d.com/windows
2. Plugue o controle e abra o SixAxis.
3. Rode o código MACAdressEsp32 e descubra o MAC do ESP em questão.

Alguns valores mapeados: <br>
Esp32 Shazam: 94:B9:7E:D0:7D:40<br>
Esp32 Valquiria: 8C:AA:B5:8C:B5:F8<br>
Esp32 Tsunami: 40:F5:20:80:BF:4C<br>
Esp32 Podolski: 34:86:5D:3A:34:38<br>

4. Substitua esses valores no SixAxis para sincronizar o controle
5. No código substitua o *Ps3.begin("O MAC ADRESS DO ESP32 AQUI");* no código em questão