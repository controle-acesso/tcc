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

	if button.is_pressed:
		try:
			sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
			sock.connect(programSocket)		
			sock.send("0C".encode('utf-8'))
		except socket.error:
			print("Socket error")
			continue
		except KeyboardInterrupt:
			break
		finally:
			sock.close()	
		print('Menssagem enviada')
		time.sleep(3)
		
print("Programa encerrado.")

	







