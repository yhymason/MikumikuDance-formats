import json
import codecs

with open('motion_out.txt', 'rb') as file:
    string = file.read().decode('shift-jis')