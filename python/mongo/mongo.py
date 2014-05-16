#! /usr/bin/env python3

import json
import pprint

import pymongo

def insert_data(db, data):
    db.a.insert(data['a'])

json_data = open('a.json')
data = json.load(json_data)
# pprint.pprint(data)
json_data.close()

conn = pymongo.Connection('localhost', 27017)
db = conn.test
count = db.a.find({'name': 'jack'}).count()
if count:
    print('data has exist')
else:
    print('data doesn\'t exist, start to insert data')
    insert_data(db, data);
    print('insert data ok')

