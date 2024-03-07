import Jetson.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
gpio_pin=18
GPIO.setup(gpio_pin,GPIO.IN)

try:
    while True:
        value = GPIO.input(gpio_pin)

        print("Received value:",value)
        time.sleep(0.1)
except KeyboardInterrupt:
    GPIO.cleanup()