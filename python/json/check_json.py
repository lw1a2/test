#!/usr/bin/env python3

import json
import sys
import pprint
import os
import re

def usage():
    usage = 'Usage: {} dir'.format(sys.argv[0])
    print(usage)

def get_json_files():
    json_files = []
    files = os.listdir(sys.argv[1])
    for json_file in files:
        m = re.search('.json$', json_file)
        if m:
            json_files.append(sys.argv[1] + '/' + json_file)
    json_files.sort()
    return json_files

def check():
    if len(sys.argv) != 2:
        usage()
        sys.exit()

    json_files = get_json_files()
    for json_file in json_files:
        print('checking ' + json_file)
        json_data = open(json_file)
        data = json.load(json_data)
        # pprint.pprint(data)
        json_data.close()
        print('done')

if __name__ == "__main__":
    check()
