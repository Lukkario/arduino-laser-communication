import serial
import sys

if( len(sys.argv) < 3 )
{
    print("usage: data-reciver.py path/to/serial-port file")
    sys.exit(1)
}

#cnt = 0 #debug
ser = serial.Serial(sys.argv[1], 115200)

try:
    while True:
        data = ser.readline()
        #cnt += 1 #debug
        data = data[:-2]
        response = data
        with open(sys.argv[2], "ab+") as f:
            datastream = hex(int(response, 2))[2:]
            if len(datastream)%2 != 0:
                datastream = "0" + datastream #fixing leading zero
            print(datastream)
            f.write(bytes.fromhex(datastream))
        f.close()
        #print(cnt) #debug

except KeyboardInterrupt:
    ser.close()
