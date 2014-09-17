#! /usr/bin/env python3

import json
import pprint
import fcntl
import time
import os

while True:
    lock = open('lock', 'w')
    fcntl.lockf(lock, fcntl.LOCK_EX)
    f = open('1.json', 'w')
    data = {'time': time.time()}
    pprint.pprint(data)
    json.dump(data, f, indent = 4)
    f.close()
    fcntl.lockf(lock, fcntl.LOCK_UN)
    lock.close()
    time.sleep(1)

