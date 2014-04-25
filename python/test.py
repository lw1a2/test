#! /usr/bin/env python3.3

# if (1 > 0):
#     print("Hello World")

# l = ['1', '22', '3333']
# for w in l[:]:
#     if (len(w) > 3):
#         l.insert(0, w)

# print(l)

# for x in range(1,10):
#     print(x)


# print(range(10))

# print('===========================')
# for x in range(2, 10):
#     print(x)
#     #if x == 5:
#         #break
# else:
#     print("else:")


# print('===========================')
# for num in range(2, 10):
#     if num % 2 == 0:
#         print("Found an even number", num)
#         continue
#     print("Found a number", num)

# f = 0
# def foo():  #foo function
#     global f
#     f = 1
#     print('===========================')
    

# foo()

# def bar():  #foo function
#     print('===========================')
#     b = 333
#     print(f)

# bar()


# print('===========================')
# def incr(n):
#     n += 1

# n = 2
# incr(2)
# print(n)


# print('===========================')
# def insert(l):
#     l.append(2)

# l = [1]
# insert(l)
# print(l)

# print('===========================')
# print(insert(l))

# def ask_ok(a, b = 2, c = 3):
#     print('===========================')
#     print('ask_ok:', a, b, c)

# ask_ok(1)
# ask_ok(1, 1)
# ask_ok(1, 1, 1)


# print('===========================')
# l = [1, 2, 3]
# if 1 in l:
#     print('In')
# else:
#     print('Not In')
# if 4 in l:
#     print('In')
# else:
#     print('Not In')


# def cheeseshop(a, *b, **c):
#     print('===========================')
#     print('a:', a)
#     print(end = '')
#     print('*b(', len(b), '): ', b)
#     print(end = '\n')
#     print('**c:', c)

# cheeseshop(1, 'bb', 'bbb', c = 'c', cc = 'cc')

# def my_function():
#     """Do nothing, but document it.
    
#     No, really, it doesn’t do anything.
#      really really
#     """
#     pass

# print('===========================')
# print(my_function.__doc__)


# # l = [1, 2, 3]
# # l.remove(4)

# from collections import deque
# print('===========================')
# queue = deque(["Eric", "John", "Michael"])
# print(queue)
# queue.append("Terry") # Terry arrives
# print(queue)
# queue.append("Graham") # Graham arrives
# print(queue)
# queue.popleft()
# print(queue)
# queue.popleft()
# print(queue)


# print('===========================')
# l = [(x, y) for x in [1, 2, 3] for y in [3, 4, 5] if x != y]
# print(l)


# print('===========================')
# l = [1, 2, 3, 4, 5, 6]
# del l[1]
# print(l)
# del l[2:4]
# print(l)
# del l[:]
# print(l)
# del l
# #print(l) #error


# print('===========================')
# t = ()
# print(t)
# print(len(t))
# t = (1,)
# print(t)
# print(len(t))

# t = 1, 2, 3
# x, y, z = t
# print('===========================')
# print(x, y, z)


# fruits = {'apple', 'orange', 'banana', 'peach', 'watermelon', 'banana'}
# print(fruits)
# fruits2 = set({'apple', 'orange', 'banana', 'peach', 'watermelon', 'banana'})
# print(fruits2)
# print('apple' in fruits2)
# print('cherry' in fruits2)


# l1 = [1, 2, 3]
# l2 = [3, 4, 5]
# print(l1 | l2)  # list not support

# set1 = {1, 2, 3}
# set2 = {3, 4, 5}
# print(set1 | set2)

# d = {1: 'one', 2: 'two', 3: 'three'}
# print(d)
# d[2] = 2
# print(d)
# del d[2]
# print(d)
# print(1 in d)
# print(1 not in d)

# d = dict(one = 1, two = 2, three = 3)
# print(d)
# for k, v in d.items():
#     print(k)

# for i, v in enumerate([111, 222, 333]):
#     print(i, v)


# fruits = ['apple', 'orange', 'banana', 'peach', 'watermelon']
# print(sorted(fruits))
# print(fruits)
# fruits.sort()
# print(fruits)

x = 0
while x < 10:
    print(x)
    x += 1