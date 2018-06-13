import socket
import os
import time
import gpiozero

programSocket = "/tmp/programManager.socket"
button = gpiozero.Button(27)

while True:
	if(os.path.exists(programSocket)):
		break
	else:
		print("Esperando pelo Program Manager...")
		time.sleep(1)

while True:
	try:
		sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
	except socket.error:
		print("Criando socket...")
		continue
	break



while True:

	button.wait_for_press()
	try:
		sock.connect(programSocket)
		sock.send("0C".encode('utf-8'))
	except socket.error:
		print("Socket error")
	finally:
		sock.close()
		time.sleep(3)
	







