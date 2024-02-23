import network
import time
import socket

from machine import Pin,UART


# def web_page():
#   html = """<html><head><meta name="viewport" content="width=device-width, initial-scale=1"></head>
#             <body><h1>Hello World</h1></body></html>
#          """
#   return html

# if you do not see the network you may have to power cycle
# unplug your pico w for 10 seconds and plug it in again
def ap_mode(ssid, password):
    """
        Description: This is a function to activate AP mode
        
        Parameters:
        
        ssid[str]: The name of your internet connection
        password[str]: Password for your internet connection
        
        Returns: Nada
    """
    # Just making our internet connection
    ap = network.WLAN(network.AP_IF)
    ap.config(essid=ssid, password=password)
    ap.active(True)
    # The first '192.168.4.1' is the static IP address assigned to the AP.
    # The subnet mask is set to '255.255.255.0', defining the local network's size.
    # The gateway IP address is '192.168.8.8', representing the device connecting the local network to the internet.
    # The DNS server is set to '8.8.8.8', using Google's public DNS server.
    # Some IP addresses may not work statically, check IP address conflict or firewall settings.
    ap.ifconfig(('192.168.4.1', '255.255.255.0', '192.168.4.1', '8.8.8.8'))
    
    while ap.active() == False:
        pass
    print('AP Mode Is Active, You can Now Connect')
    print('IP Address To Connect to: ' + ap.ifconfig()[0])
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   #creating socket object
    s.bind(('0.0.0.0', 80))
    s.listen(5)

    while True:
      conn, addr = s.accept()
      # print('Got a connection from %s' % str(addr))
      request = conn.recv(1024)
      # print('Content = %s' % str(request))
      
      uart.write(request)
      
      # response = web_page()
      # conn.send(response)
      conn.close()

uart = UART(1, baudrate=115200, tx=Pin(4), rx=Pin(5))   #UART1, GP4 & GP5 pins
uart.init(bits=8, parity=None, stop=2)

ap_mode('S(car)lett A1',
        '00000000')