# Real filename:    ScarlettWiFiFirmware.py
# Version code:     2
# Version name:     1.1
# Created on:       Apr 4, 2024
# Author:           Piotr Grala


# Imports
import socket
import network
import utime
from machine import UART, Pin


# Configuration parameters
''' General '''
debug_mode = False

''' Times '''
waste_time = 1500
reset_time = 100

''' Pins '''
pin_number_stm32_reset = 2
pin_number_led = 'LED'
pin_number_uart_tx = 0
pin_number_uart_rx = 1

''' Peripherals '''
uart_number = 0
uart_baudrate = 115200
uart_bits = 8
uart_parity = None
uart_stop = 2

''' Access point '''
ssid = 'S(car)lett A1'
password = '00000000'
ip_address = '192.168.4.1'
subnet_mask = '255.255.255.0'
gateway = '192.168.4.1'
dns_server = '8.8.8.8'
max_clients = 5

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

    ''' Access point activation wait '''
    while access_point.active() == False:
        pass

    ''' Socket configuration '''
    socket_rx = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    socket_rx.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    socket_rx.bind((filter, port))
    socket_rx.listen(max_clients)


def reset(pin_handle_device_reset, pin_handle_led):
    ''' Target device reset '''
    pin_handle_device_reset.off()
    pin_handle_led.on()
    utime.sleep_ms(reset_time)
    pin_handle_device_reset.on()
    pin_handle_led.off()


# Main function
if __name__ == '__main__':
    ''' UART initialization '''
    device_handle_uart = UART(uart_number, baudrate=uart_baudrate,
                              tx=Pin(pin_number_uart_tx), rx=Pin(pin_number_uart_rx))
    device_handle_uart.init(bits=uart_bits, parity=uart_parity, stop=uart_stop)

    ''' Pin initialization '''
    pin_handle_stm32_reset = Pin(
        pin_number_stm32_reset, mode=Pin.OUT, pull=Pin.PULL_UP)
    pin_handle_led = machine.Pin(
        pin_number_led, machine.Pin.OUT)

    ''' Startup wait '''
    utime.sleep_ms(waste_time)

    ''' Main microcontroller reset '''
    reset(pin_handle_stm32_reset, pin_handle_led)

    ''' Access point initialization '''
    access_point_initialize()

    ''' Received signal transmission '''
    if debug_mode:
        while True:
            conn, addr = socket_rx.accept()
            request = conn.recv(length)

            print('Connection from %s' % str(addr))
            print('Content: %s' % str(request))

            device_handle_uart.write(request)
            conn.close()
    else:
        while True:
            conn, addr = socket_rx.accept()
            request = conn.recv(length)
            device_handle_uart.write(request)
            conn.close()
