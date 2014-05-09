#! /usr/bin/env python3

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

# x = 0
# while x < 10:
#     print(x)
#     x += 1



#import sys
#sys.path.append("m")
#import m.spam
#spam.f()


#print(dir())


# from m.m.m1 import f
# f()
# print(dir(m))


# from m import m1
# m1.f()

# from m.m1 import f
# f()


# s = 'test\n'
# print(s)
# print(str(s))
# print(repr(s))


# print("this is a {}, that is a {}".format('cat', 'dog'))
# print("{:f}".format(1))

# print("%d" % 123)


# f = open('f.txt', 'r+')
# #print(f.read())
# # print(repr(f.readline()))
# # print(repr(f.readline()))
# # print(repr(f.readline()))
# # print(repr(f.readline()))
# # print(repr(f.readline()))
# # print(repr(f.readline()))
# for l in f:
#     print(l, end='')

# import json
# s = json.dumps([1, '2', "kkk"])
# print(s)
# f = open("1.json", 'w')
# json.dump([1, '2', "kkk"], f)


# import os
# s = os.getcwd()
# print(s)

# import shutil
# s = shutil.disk_usage('.')
# print(s)

# import glob
# s = glob.glob("*.txt")
# print(s)
# s = glob.glob("m/*.py")
# print(s)


# import sys
# print(sys.argv)
# print(sys.argv[0])

# from datetime import date
# print(date.today())

# import zlib
# s = b'abc abc abc abc abc abc abc abc abc abc'
# print(len(s), s)
# s = zlib.compress(s)
# print(len(s), s)
# s = zlib.decompress(s)
# print(len(s), s)


# from string import Template
# s = Template('$a $b $c')
# s = s.substitute(a = '1', b = '2', c = '3')
# print(s)

# s = Template('$a $b $c')
# s = s.safe_substitute(a = '1', b = '2')
# print(s)

#print(dir(__main__))

# import logging
# logging.warning('Warning:config file %s not found', 'server.conf')

#assert(1)

#print(' aa bb '.strip())

# import os
# os.system('ls')

# import getopt
# import sys
# optlist, args = getopt.getopt(sys.argv[1:], 'abc:d:')
# print(optlist)
# print(args)

# import os
# who = os.system('whoami')
# print(who)

# import os
# who = os.popen('whoami').read().strip()
# print(who)

# import sys
# import os
# def fts_single_process(pro):
#     pid = os.getpid()
#     who = os.popen('whoami').read().strip()

#     cmd = 'ps -ef | grep ' + pro + '| grep -v grep | grep -v sudo | grep -v -P ' + who + '"\\s+' + str(pid) + '"'
#     out = os.popen(cmd).read().strip()
   
#     if len(out):
#         print("\nAnother $pro is running, please wait it finish, ps output\n{}\n\n".format(out))
#         sys.exit(1)

# fts_single_process('bash')

# import m.m.m1
# m.m.m1.f()

# import datetime
# print(datetime.datetime.today())

# import re
# m = re.match(r'processor\s+:\s+(\d+)', 'processor : 7')
# if (m):
#     print(m.group(1))

# d = {}
# def f():
#     global d
#     if 1 in d:
#         d[1][1] = 1
#     else:
#         d[1] = {1: 1}
#     d[1][2] = 2

# f()
# print(d)
# print(d[1][1])
# print(d[1][2])

# import re
# out = '''1: lo: <LOOPBACK,UP,LOWER_UP> mtu 16436 qdisc noqueue state UNKNOWN 
#     link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
# 2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP qlen 1000
#     link/ether e0:3f:49:49:a7:be brd ff:ff:ff:ff:ff:ff'''
# #print(out)
# l = out.split(' brd ')
# for s in l:
#     m = re.search(r'(\d+): (eth\d+): \<', s)
#     if m:
#         id = m.groups()
#         print(*id)

#     m = re.search(r'link/ether (\S+)', s)
#     if m:
#         mac, = m.groups()
#         print(mac)

# s = 'abc ddd'
# m = re.search(r'ddd', s)
# if m:
#     print('match')

# s = 'abc ddd'
# m = re.match(r'ddd', s)
# if m:
#     print('match')



# import os
# out = os.popen('lsa 2>&1').read().strip()
# print(out)

# import subprocess
# out = subprocess.Popen("ls", stdout=subprocess.PIPE).stdout.read()
# print(out)

# import subprocess
# cmd = 'ethtool -i ' + 'eth0' + ' | grep driver 2>&1'
# out = subprocess.check_output(cmd, shell = True).strip()
# print(str(out, encoding = "utf8"))

#import subprocess
#subprocess.call('ls')

# import sys
# import subprocess
# ret = 0
# try:
#     ret = subprocess.call('a')
# except FileNotFoundError:
#     print(sys.exc_info()[0])
#     print(ret)

# import subprocess
# ret = subprocess.call('a', shell = True)
# print(ret)


# import subprocess
# cmd = 'ls -l'
# subprocess.call(cmd, shell = True)


# import subprocess
# subprocess.call(['ls', '-l'])


# import subprocess
# ret = subprocess.call(['rm', '12345'])
# print(ret)


# import subprocess
# try:
#     subprocess.check_call(['rm', '12345'])
# except subprocess.CalledProcessError as e:
#     print(e.returncode)


# import subprocess
# try:
#     out = subprocess.check_output('ls')
#     print(out)
# except subprocess.CalledProcessError as e:
#     print(e.returncode)


# import subprocess
# try:
#     cmd = 'rm 12345'
#     subprocess.check_output(cmd, shell = True, stderr = subprocess.STDOUT)
# except subprocess.CalledProcessError as e:
#     print(e.output)


# import subprocess
# server_ns = 'fts'
# cmd = "ip netns delete " + server_ns
# try:
#     subprocess.check_output(cmd, stderr = subprocess.STDOUT, shell = True)
# except subprocess.CalledProcessError as e:
#     print(e.output)

# import os
# import subprocess
# import sys
# pid = os.getpid()
# who = subprocess.check_output('whoami').strip()
# who = str(who, encoding = 'utf8')
# cmd = 'ps -ef | grep ' + 'bash' + '| grep -v grep | grep -v sudo | grep -v -P ' + who + '"\\s+' + str(pid) + '"'
# try:
#     out = subprocess.check_output(cmd, shell = True).strip()
#     out = str(out, encoding = 'utf8')
#     if out != '':
#         print("\nAnother $pro is running, please wait it finish, ps output\n{}\n\n".format(out))
#         sys.exit(1)
# except subprocess.CalledProcessError as e:
#     pass



# import subprocess
# server_ns = 'fts'
# cmd = "ip netns|grep " + server_ns
# try:
#     subprocess.check_output(cmd, shell = True)
# except subprocess.CalledProcessError:
#     print('INFO', "netns {} doesn't exist, so return".format(server_ns))


def _dict(d):
    pass

d = {}
d[3] = 4
_dict(d[1][5])
d[1][5] = 6
print(d)





