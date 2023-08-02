import serial
from time import sleep

ser = serial.Serial(
    port="COM20",
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0,
)

print("connected to: " + ser.portstr)
count = 1

try:
    with open("data.csv", "w") as f:
        buffer = ""
        while True:
            cc = str(ser.readline())
            # print(cc)
            message = cc[2:][:-1]
            if len(message) > 1:
                # message = message.replace("\\r\\n", "\r\n")
                if "&" in message:
                    print(buffer + message)
                    f.write(f"{buffer + message}\r\n")
                    buffer = ""
                else:
                    buffer += message
            sleep(0.03)
except:
    ser.close()
