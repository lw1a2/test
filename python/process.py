#! /usr/bin/env python3.3

from multiprocessing import Process
import os

def f(name):
    print(os.getpid(), 'hello', name)

if __name__ == '__main__':
    print(os.getpid())
    p = Process(target=f, args=('bob',))
    p.start()
    p.join()

