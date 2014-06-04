#! /usr/bin/env python3

import json
import pprint

import pymongo

# def insert_data(db, data):
#     db.a.insert(data['a'])

# json_data = open('a.json')
# data = json.load(json_data)
# # pprint.pprint(data)
# json_data.close()

# conn = pymongo.Connection('localhost', 27017)
# db = conn.test
# count = db.a.find({'name': 'jack'}).count()
# if count:
#     print('data has exist')
# else:
#     print('data doesn\'t exist, start to insert data')
#     insert_data(db, data);
#     print('insert data ok')


conn = pymongo.Connection('localhost', 27017)
db = conn.test
names = db.a.find().sort([('name', pymongo.DESCENDING)]).limit(1)
for name in names:
    print(str(name['_id']))

name2 = {}
name2['TestID'] = str(name['_id'])
db.b.insert(name2)
bs = db.b.find()
for b in bs:
    print(b)