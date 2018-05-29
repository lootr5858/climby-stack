import serial
import time

motor = serial.Serial("/dev/ttyACM1", 9600, timeout=.1)
#motor = serial.Serial("/dev/ttyACM0", 9600, timeout=.1)
servo = serial.Serial("/dev/ttyACM0", 9600, timeout=.1)
time.sleep(1)

print("all stop")
motor.write(("<" + str(0) + ">").encode())
servo.write(("<" + str(0) + ">").encode())
time.sleep(0.5)
input("Press Enter to continue...")

print("forward (backwards kiv)")
motor.write(("<" + str(10) + ">").encode())
time.sleep(2)

print("left")
servo.write(("<" + str(45) + ">").encode())
time.sleep(2)
motor.write(("<" + str(10) + ">").encode())
time.sleep(5)
print("right")
servo.write(("<" + str(135) + ">").encode())
time.sleep(2)
motor.write(("<" + str(10) + ">").encode())
time.sleep(5)

print("all stop")
motor.write(("<" + str(0) + ">").encode())
servo.write(("<" + str(0) + ">").encode())

