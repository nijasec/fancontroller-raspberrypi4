import time
import lgpio

LED = 17
HIGHTEMP = 65
LOWTEMP = 50


def getTemp():
	f=open('/sys/class/thermal/thermal_zone0/temp','r')
	return int(f.read())/1000


# open the gpio chip and set the LED pin as output
h = lgpio.gpiochip_open(0)
lgpio.gpio_claim_output(h, LED)

try:
    while True:
        temp=getTemp()
        if temp>=HIGHTEMP:
        # Turn the GPIO pin on
             lgpio.gpio_write(h, LED, 1)
        elif temp<=LOWTEMP:
        # Turn the GPIO pin off
             lgpio.gpio_write(h, LED, 0)
        time.sleep(10)
except KeyboardInterrupt:
    lgpio.gpio_write(h, LED, 0)
    lgpio.gpiochip_close(h)
