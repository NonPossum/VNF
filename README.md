# VNF

File format for visual novel.
And 2 example parsers. [Python](https://github.com/Ryuel/VNF/blob/main/VNF/python/VNF.py)  [C#](https://github.com/Ryuel/VNF/blob/main/VNF/c%23/Program.cs)

## File Structure:
1. **Magic**: 10 bytes with string VNF.
2. **Data**: Accept only ```^0name[text]``` format where ^ mean start of new sentence 0-9 num  mean number of image to display emotions of character name and text contain what a name suggest.
3. **Key**: 11 bytes of key to crypt and encrypt file. 
![img](https://github.com/Ryuel/VNF/blob/main/img/img.png)
