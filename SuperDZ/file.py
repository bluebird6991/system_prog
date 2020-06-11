import os

def get_temp():
	# f = open("/dev/DHT11_Device", "rb")
	# temp = f.readlines()
	# f.close
	# print(temp)
	#f = os.open("/dev/DHT11_Device", os.O_RDONLY)
	#text = os.read(f)
	#print(text)
	#os.close(f)
	# with open("/dev/DHT11_Device", "rb") as f:
	# 	print repr(f.read(10))
	#print("Hello")
	return os.popen("sudo /home/pi/ArturBot/bot3/temp").read()


if __name__ == '__main__':
	print(get_temp())