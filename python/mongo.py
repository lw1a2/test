#! /usr/bin/env python3

import pymongo

conn = pymongo.Connection('localhost', 27017)
db = conn.fts_db
collections = db.collection_names()
if 'HttpRpsTP' in collections:
    print('exist')
else:
    print('no exist')

