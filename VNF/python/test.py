import VNF

data = VNF.decrypt("FL.vnf")
parsedData = VNF.parse(data)

print(parsedData[0][0]) # Count of character emotions
print(parsedData[1][0]) # Name of character 
print(parsedData[2][0]) # Text of character 
