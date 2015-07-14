import serial, time, threading,sys
import queue
import numpy as np
from matplotlib import pyplot as plt
import csv
import warnings
import matplotlib.cbook
from drawnow import *
warnings.filterwarnings("ignore",category=matplotlib.cbook.mplDeprecation)


ser = serial.Serial(
        port='COM4',
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS
)
q=queue.Queue()
cpuLoad=[]

cnt=0

def serialWriteCpu(cmd: str):
    l=0
    while ser.inWaiting()>0:
        ser.flushInput()
        ser.flushOutput()
    while l < len(cmd):
        ser.write(cmd[l].encode())
        time.sleep(0.01)
        ser.flushInput()
        l=l+1
    ser.write('\r'.encode())  

    
def serialReadCpu():
    time.sleep(0.02)
    out=""
    while ser.inWaiting() > 0:
        out += ser.read().decode("utf-8")
    return out

def serialWriteCmd(cmd: str):
    l=0
    ser.flushOutput()
    while l < len(cmd):
        ser.write(cmd[l].encode())
        time.sleep(0.01)
        ser.flushInput()
        l=l+1
    ser.write('\r'.encode())


def serialReadCmd():
    time.sleep(0.07)
    out=""
    while ser.inWaiting() > 0:
        out += ser.read().decode("utf-8")
    return out

lock=threading.Lock()
data=[]

def read_from_serial():
    lock.acquire()
    try:
        global cnt
        out=""
        serialWriteCpu("cpu")
        out=serialReadCpu()
        q.put(out)
        cnt=cnt+1
        if cnt>20:
            cpuLoad.pop(0)
        threading.Timer(1, read_from_serial).start()
    finally:       
        lock.release()

def read_cmd():
    while True:
        cmd=input()
        if len(cmd) > 0:
            lock.acquire()
            try:
                serialWriteCmd(cmd)
                out=serialReadCmd()
                print (out)
            finally:
                lock.release()
    
def makefig():
    plt.ylim(0,100)
    plt.plot(cpuLoad,'ro-',label="CPU load")
    plt.legend(loc="upper left")
    plt.ylabel("Load in percentage")
    plt.grid()
    plt.draw()
    plt.pause(.001)
  
def plotGraph():
    while True:
        out=q.get()
        data = [float(val) for val in out.split()]
        if data:
            count=0
            while count<len(data):
                cpuLoad.append(data[count])
                count=count+1
        drawnow(makefig)
    
if __name__ == "__main__":
    read_cmd_thread=threading.Thread(target = read_cmd)
    plotGraph_thread=threading.Thread(target = plotGraph)
    read_from_serial_thread = threading.Thread(target = read_from_serial)
    read_from_serial_thread.start()
    read_cmd_thread.start()
    plotGraph_thread.start()
        

  


