# esp8266-twitter
sending tweets with esp8266 and IFTT

-setting up IFTT:

 for the code to work you need to create a acount at https://ifttt.com/. after that set up a webhooks integrtion with
 twitter to send a tweet when the essage you set on the code is fired.
 
 -board leds explanation:
when the board turns on it blinks the led 3 times.

after that the board tries to connect to wifi, if it succeeds the led turns on , otherwise it stays off.

the board then reatins the same led state while waiting for the push of the buton.

after the button is pushed the led turns off and sends the get request, after that it goes back to trying to connect to wifi.
