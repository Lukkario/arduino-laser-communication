import serial
import sys

if( len(sys.argv) < 3 )
{
    print("usage: data-transmitter.py path/to/serial-port file")
    sys.exit(1)
}

ser = serial.Serial(sys.argv[1], 115200)

try:
    while True:
        data = []
        start = input("Press enter to start transmission")
        with open(sys.argv[2], "rb") as f:
            bits = f.read(8)
            while bits:
                data.append(bits)
                bits = f.read(8)
        f.close()
        for i in range(0, len(data)):
            print(data[i])
            data[i] = bin(int.from_bytes(data[i], 'big'))[2:]
            print(len(data[i]))

        print(len(data))
        for i in range(0, len(data)):
            ser.write(data[i].encode())
            ser.readline()
except KeyboardInterrupt:
    ser.close()
