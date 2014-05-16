#! /usr/bin/env python3

import json
from pprint import pprint

# s = json.dumps([1, '2', "kkk"])
# print(s)
# f = open("1.json", 'w')
# json.dump([1, '2', "kkk"], f)



json_data = open('a.json')
data = json.load(json_data)
pprint(data)
json_data.close()

