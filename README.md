Chinese doorbell mod using esp8266 with mobile and desktop notifications.

This mod uses a chinese doorbell, the reciever it's rebuild from scratch, i've used only the musical IC form the stock one(i didn't found datasheet for the chip, but it was easy to deduce what's his pinout. You can find the pinout and the model in picture named TR1206.jpg).

The reciever it's build from ESP8266 and RF module(XLC-RF-5V, 433Mhz)
The RF transmitter(doorbell button) has been changed only on OC crystal(it had 315Mhz one) and the antena lenght(the pcb was build for both 315Mhz and 433Mhz), the modification consists only in removing the wire at the end of PCB antena. The transmitter uses an EV1527 with K1 and K2 pins pulled up(it can be changed and matched in sketch via data string).

For the notifications, you'll need to install pushbullet and get an api key and also create a device and get the device identification(follow the api guide given by pushbullet website).

For the power supply i've used a mini PSU from aliexpres(https://www.aliexpress.com/item/4001260682974.html)

The slide switch allows:<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1st position - Play next ring.<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2nd position - Mute.<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3th position - Repeat current ring.<br/>
![alt text](https://github.com/kyme32/DoorBell-ESP8266/blob/main/IMG_20210323_164443.jpg?raw=true)
![alt text](https://github.com/kyme32/DoorBell-ESP8266/blob/main/IMG_20210323_163051.jpg?raw=true)