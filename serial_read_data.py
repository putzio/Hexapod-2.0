import serial

ser = serial.Serial(
    port="COM7",
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
        while True:
            cc = str(ser.readline())
            message = cc[2:][:-5]
            if len(message) > 0:
                print(message)
                f.write(f"{message}\r\n")
except:
    ser.close()
