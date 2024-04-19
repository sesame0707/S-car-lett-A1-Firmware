# Real filename:    ScarlettWiFiFirmware.py
# Version code:     1
# Version name:     1.0
# Created on:       Apr 4, 2024
# Author:           Piotr Grala


# Imports
import socket
import network
from machine import UART, Pin


# Config parameters
''' General '''
debug_mode = False
ssid = 'S(car)lett A1'
password = '00000000'
max_clients = 5

''' Access point '''
ip_address = '192.168.4.1'
subnet_mask = '255.255.255.0'
gateway = '192.168.4.1'
dns_server = '8.8.8.8'

''' Socket '''
socket_rx = None
length = 1024
filter = '0.0.0.0'
port = 80


# Common functions
def access_point_initialize():
    global socket_rx

    ''' Access point configuration '''
    access_point = network.WLAN(network.AP_IF)
    access_point.config(essid=ssid, password=password)
    access_point.active(True)
    access_point.ifconfig((ip_address, subnet_mask, gateway, dns_server))

    ''' Access point activation waiting '''
    while access_point.active() == False:
        pass

    ''' Socket configuration '''
    socket_rx = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    socket_rx.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    socket_rx.bind((filter, port))
    socket_rx.listen(max_clients)


# Main function
if __name__ == '__main__':
    ''' UART1 (GP4, GP5) initialization '''
    uart = UART(1, baudrate=115200, tx=Pin(4), rx=Pin(5))
    uart.init(bits=8, parity=None, stop=2)

    ''' Access point initialization '''
    access_point_initialize()

    ''' Received signal transmission '''
    if debug_mode:
        while True:
            conn, addr = socket_rx.accept()
            request = conn.recv(length)

            print('Connection from %s' % str(addr))
            print('Content: %s' % str(request))

            uart.write(request)
            conn.close()
    else:
        while True:
            conn, addr = socket_rx.accept()
            request = conn.recv(length)
            uart.write(request)
            conn.close()
