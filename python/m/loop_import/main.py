#! /usr/bin/env python3

def f():
    import b.b as b
    b.f2()
    print("main.f()")

if __name__ == '__main__':
    f()