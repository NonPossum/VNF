#!/usr/bin/python3
from struct import *
import sys
import os



def decrypt(argv):
	with open(str(argv),"rb") as f:
		Header = f.read()[1:4]
		if unpack("bbb",Header) == (0x56,0x4E,0x46):
			pass
		else:
			raise Exception("Not a vnf file.")
			
	with open(str(argv),"rb") as file,open(str(argv),"rb") as key:
		size = os.path.getsize(argv)
		data = file.read()[10:size-11]
		key  = key.read()[size-11:]
		tab = []

		for i,d in enumerate(data): 
			tab.append(chr(abs(12 - d) ^ key[i % len(key)]))

		return "".join(tab)

def parse(data):
	split_string = (data.split(chr(0x1D)))[1:]
	name   = []
	status = []
	text   = [ ]
	tempstr = ""
	tempstr2 = ""
	i = 0
	while i < len(split_string):
		status.append(split_string[i][0])
		d = split_string[i][1:]
		
		b = 0
		while b < len(d):
			if d[b] != "[":
				tempstr += d[b]
			else:
				name.append(tempstr)
				tempstr = ""
				break
			b += 1 
		
		c = b + 1
		while c < len(d):
			if d[c] != "]":
				tempstr2 += d[c]
			else:
				text.append(tempstr2)
				tempstr2 = ""
				break
			
			c += 1
		
		i += 1
	return status , name, text


		


def main(argv):		
		data  = decrypt(argv)
		Pdata = parse(data)
		print(Pdata)


if __name__ == '__main__':
	if len(sys.argv) == 1:
		print("usage: python VNF.py <FileName>")
		exit(1)
		
	main(sys.argv[1])