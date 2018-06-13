import socket
import os
import sys
import time
import gpiozero

lockSocket = "/tmp/lock.socket"
led = gpiozero.LED(17)

try:
    os.unlink(lockSocket)
except OSError:
	if os.path.exists(lockSocket):
		print ("Could not unlink file!")
		sys.exit()

while True:
	try:
		sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
	except socket.error:
		print("Creating socket...")
		continue
	break

while True:
	try:
		sock.bind(lockSocket)
	except socket.error:
		print("Binding socket...")
		continue
	break

try:
	sock.listen(100)
except socket.error:
	print("Could not listen.")
	sys.exit()

while True:

	try:
		client_sock, client_addr = sock.accept()
		cmd = client_sock.recv(2).decode('utf-8')		
		if int(cmd, 16):
			cmd = int(cmd, 16)
			print (hex(cmd))
		else:
			raise ValueError
	except KeyboardInterrupt:
		break
	except socket.error:
		print("Some socket error occur.")
	except ValueError:
			print("NaN")
			continue
	finally:
		client_sock.close()

	if( cmd == 0x01):
		print("Porta aberta")
		led.on()
		time.sleep(3)
		led.off()
		print("Porta fechada")
	else:
		print("Unknown command")



sock.close()
os.unlink(lockSocket)






