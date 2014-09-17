#! /usr/bin/env python3

import json
import pprint
import fcntl
import time

while True:
    lock = open('lock')
    fcntl.lockf(lock, fcntl.LOCK_SH)
    f = open('1.json')
    data = json.load(f)
    pprint.pprint(data)
    # time.sleep(1)
    fcntl.lockf(lock, fcntl.LOCK_UN)
    f.close()
    lock.close()

