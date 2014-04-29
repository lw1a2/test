#! /usr/bin/env python3.3

i = 0

def f1():
    #nonlocal i
    i = 1
    def f2():
        # nonlocal i
        # print("nonlocal:", i)
        def f3():
            #i = 1
            print(i)
            global j
            j = 5
            print(j)
        f3()
    f2()
    print(i)


f1()
print("global:", i)