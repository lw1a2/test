#! /usr/bin/env python3.3

class MyClass:
    i = 12345

    # def __init__(self):
    #     self.i = 0

    def f(self):
        print("f")

print(MyClass.i)
x = MyClass()
print(x.i)

MyClass.i = 88888
print(MyClass.i, x.i)

x.i = 99999
MyClass.i = 88888
print(MyClass.i, x.i)

x.f()
