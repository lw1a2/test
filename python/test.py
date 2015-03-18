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
# for x in range(2, 4):
#     print(x)
# else:
#     print("done")


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


# d = {}
# if len(d):
#     print('a')

# s = 'a'
# if s:
#     print(s)
# s = ''
# if s:
#     print(s)



# import ipaddress
# network = ipaddress.ip_network('10.1.1.1/16', strict = False)
# network = str(network)
# print(network[:network.index('/')])



# from collections import defaultdict
# d = defaultdict(defaultdict)
# d['a']['b'] = 1       #ok
# d['a']['d']['e'] = 1  #error
# print(d)



# def f():
#     print('fff')

# d = {}
# d['f'] = f
# func = d['f']
# func()


# d = {}

# def f():
#     d['a'] = 1

# f()
# print(d)

# s = 'abc[dd]'
# s = s.replace('[','')
# s = s.replace(']','')
# print(s)

# import re
# s = 'abc[dd]'
# s = re.sub('\[|\]', '', s)
# print(s)


# print("{:.3f}".format(1.1116))


# d = {}
# d['port4'] = 1
# d['port3'] = 1

# print(sorted(d.keys()))

# import subprocess

# try:
#     cmd = []
#     cmd.append('sleep')
#     cmd.append('50')
#     subprocess.Popen(cmd)
# except subprocess.CalledProcessError as e:
#     print(str(e.output.strip(), encoding = 'utf8'))



# import datetime
# print(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"))


# import os
# files = os.listdir('.') 
# print(files)


# def f():
#     return 1, 3

# ret, message = f()
# print(ret, message)

# def f():
#     import subprocess

#     try:
#         print("f")
#         cmd = []
#         cmd.append('sleep')
#         cmd.append('50')
#         subprocess.Popen(cmd)
#     except subprocess.CalledProcessError as e:
#         print(str(e.output.strip(), encoding = 'utf8'))


# import ipaddress
# ip1 = ipaddress.ip_address("10.1.1.0")
# ip2 = ipaddress.ip_address("10.1.1.255")
# for x in range(int(ip1), int(ip2) + 1):
#     print(ipaddress.ip_address(x))

# import re
# logf = "/run/ftslog/HttpRps/HttpRpsNAT/ToolsLog/curl_loader/10.12.1.2/cl.log"
# m = re.search(r'curl_loader\/(.*)\/cl.log', logf)
# if m:
#     print(m.groups())


# ports = ['port3', 'port4']
# msg = ", ".join(ports)
# msg += " is down."
# print(msg)

# import re
# out = '''9: port3: <BROADCAST,MULTICAST> mtu 1500 qdisc pfifo_fast state DOWN mode DEFAULT group default qlen 1000
# 10: port4: <BROADCAST,MULTICAST> mtu 1500 qdisc pfifo_fast state DOWN mode DEFAULT group default qlen 1000'''
# ports = re.findall(r'\d+:\s+(port\d+):', out)
# print(ports)

# l = ["a", "c", "b"]
# l.sort()
# print(l)

# import os
# from pathlib import Path
# path = '/a'
# if Path(path).exists():
#     dirs = os.listdir(path)
#     print(dirs)

# import re
# import pprint
# log = '''fap(38005:cw->RUN:sta->READY): ps:512 pn:10 txp:35380 rxp:0 txpf:0 txb:18397600 rxb:0 txbf:0
# fap(38008:cw->1:sta->READY): ps:512 pn:10 txp:0 rxp:35440 txpf:0 txb:0 rxb:18357920 txbf:0
# fap(38003:cw->1:sta->aa): ps:512 pn:10 txp:35380 rxp:0 txpf:0 txb:18397600 rxb:0 txbf:0
# fap(38007:cw->33:sta->aa): ps:512 pn:10 txp:35440 rxp:0 txpf:0 txb:18428800 rxb:0 txbf:0
# fap(38001:cw->33:sta->READY): ps:512 pn:10 txp:35400 rxp:0 txpf:0 txb:18408000 rxb:0 txbf:0
# fap(38006:cw->RUN:sta->READY): ps:512 pn:10 txp:0 rxp:35380 txpf:0 txb:0 rxb:18326840 txbf:0
# fap(38002:cw->RUN:sta->READY): ps:512 pn:10 txp:0 rxp:35400 txpf:0 txb:0 rxb:18337200 txbf:0
# fap(38004:cw->RUN:sta->READY): ps:512 pn:10 txp:0 rxp:35380 txpf:0 txb:0 rxb:18326840 txbf:0
# TOTAL:thrput_out:56.18 Mbps thrput_in:55.96 Mbps tx_pkts:14160 rx_pkts:14160 tx_pkt_fail:0 tx_byte_fail:0
# '''
# m = re.search(r'TOTAL:thrput_out:(.*) Mbps thrput_in:(.*) Mbps tx_pkts:(.*) rx_pkts:(.*) tx_pkt_fail:(.*) tx_byte_fail:(.*)$', log)
# if m:
#     thrput_out, thrput_in, tx_pkts, rx_pkts, tx_pkt_fail, tx_byte_fail = m.groups()
#     print(thrput_out, thrput_in, tx_pkts, rx_pkts, tx_pkt_fail, tx_byte_fail)
#     print(m.group(0))

# v = re.findall(r'cw->(\w+):sta->(\w+)', log)
# # print(v)
# status = {}
# status['AP_STATUS'] = {}
# status['STA_STATUS'] = {}
# for i in range(len(v)):
#     if v[i][0] in status['AP_STATUS']:
#         status['AP_STATUS'][v[i][0]] += 1
#     else:
#         status['AP_STATUS'][v[i][0]] = 1
#     if v[i][1] in status['STA_STATUS']:
#         status['STA_STATUS'][v[i][1]] += 1
#     else:
#         status['STA_STATUS'][v[i][1]] = 1

# s = 'AP_STATUS: '
# for ap_status in status['AP_STATUS']:
#     s += ap_status + ': ' + str(status['AP_STATUS'][ap_status]) + ', '
# s = s[0: len(s) - 2]
# s += '; '
# s += 'STA_STATUS: '
# for sta_status in status['STA_STATUS']:
#     s += sta_status + ': ' + str(status['STA_STATUS'][sta_status]) + ', '
# s = s[0: len(s) - 2]
# print(s)
# pprint.pprint(status)

# import re
# m = re.search(r'Cps|Rps', 'HttppsTP')
# if m:
#     print('Found')

# import re
# out = 'total cps:     61821'
# cps_rps = 0
# m = re.search(r'total\s+\w+:\s+(\d+)', out)
# if m:
#     cps_rps, = m.groups()
#     print(m.group(0))

# print(len("\r\n"))

# import datetime
# str_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
# print(str_time)
# int_time = datetime.datetime.strptime(str_time, "%Y-%m-%d %H:%M:%S")
# print(int_time)

# print(datetime.datetime.now() - int_time < datetime.timedelta(seconds = 5))

# import re
# out = '''khttpc status: running
# total cps:     137911
# total success: 55170
# total failure: 0

# khttpc/1:9 port1 530 0 cps 1325
# khttpc/1:8 port1 602 0 cps 1505
# khttpc/1:7 port1 586 0 cps 1465
# khttpc/1:6 port1 555 0 cps 1387
# khttpc/1:5 port1 586 0 cps 1465
# khttpc/1:4 port1 594 0 cps 1485
# khttpc/1:3 port1 481 0 cps 1202
# khttpc/1:2 port1 580 0 cps 1450
# khttpc/1:1 port1 609 0 cps 1522
# khttpc/1:0 port1 475 0 cps 1187
# khttpc/3:9 port1 1783 0 cps 4457
# khttpc/3:8 port1 1776 0 cps 4440
# khttpc/3:7 port1 1784 0 cps 4460
# khttpc/3:6 port1 1783 0 cps 4457
# khttpc/3:5 port1 1793 0 cps 4482
# khttpc/3:4 port1 1794 0 cps 4485
# khttpc/3:3 port1 1780 0 cps 4450
# khttpc/3:2 port1 1766 0 cps 4415
# khttpc/3:1 port1 1793 0 cps 4482
# khttpc/3:0 port1 1788 0 cps 4470
# khttpc/1:9 port1 527 0 cps 1317
# khttpc/1:8 port1 609 0 cps 1522
# khttpc/1:7 port1 567 0 cps 1417
# khttpc/1:6 port1 582 0 cps 1455
# khttpc/1:5 port1 542 0 cps 1355
# khttpc/1:4 port1 530 0 cps 1325
# khttpc/1:3 port1 531 0 cps 1327
# khttpc/1:2 port1 570 0 cps 1425
# khttpc/1:1 port1 560 0 cps 1400
# khttpc/1:0 port1 522 0 cps 1305
# khttpc/3:9 port2 419 0 cps 1047
# khttpc/3:8 port2 420 0 cps 1050
# khttpc/3:7 port2 422 0 cps 1055
# khttpc/3:6 port2 427 0 cps 1067
# khttpc/3:5 port2 423 0 cps 1057
# khttpc/3:4 port2 422 0 cps 1055
# khttpc/3:3 port2 427 0 cps 1067
# khttpc/3:2 port2 425 0 cps 1062
# khttpc/3:1 port2 423 0 cps 1057
# khttpc/3:0 port2 425 0 cps 1062
# khttpc/1:9 port2 440 0 cps 1100
# khttpc/1:8 port2 553 0 cps 1382
# khttpc/1:7 port2 444 0 cps 1110
# khttpc/1:6 port2 379 0 cps 947
# khttpc/1:5 port2 473 0 cps 1182
# khttpc/1:4 port2 463 0 cps 1157
# khttpc/1:3 port2 415 0 cps 1037
# khttpc/1:2 port2 444 0 cps 1110
# khttpc/1:1 port2 441 0 cps 1102
# khttpc/1:0 port2 540 0 cps 1350
# khttpc/3:9 port2 1736 0 cps 4340
# khttpc/3:8 port2 1738 0 cps 4345
# khttpc/3:7 port2 1751 0 cps 4377
# khttpc/3:6 port2 1730 0 cps 4325
# khttpc/3:5 port2 1739 0 cps 4347
# khttpc/3:4 port2 1730 0 cps 4325
# khttpc/3:3 port2 1748 0 cps 4370
# khttpc/3:2 port2 1728 0 cps 4320
# khttpc/3:1 port2 1743 0 cps 4357
# khttpc/3:0 port2 1724 0 cps 4310'''

# lines = re.findall(r'khttpc/\d+:\d+\s+(.*)\s+(\d+)\s+(\d+)\s+.*', out)
# d = {}
# for i in range(len(lines)):
#     port = lines[i][0]
#     success = int(lines[i][1])
#     failure = int(lines[i][2])
#     if port in d:
#         d[port]['success'] += success
#         d[port]['failure'] += failure
#     else:
#         d[port] = {'success': success, 'failure': failure}

# print(d)

# def total(initial = 5, *numbers, **keywords):
#     count = initial
#     for number in numbers:
#         count += number
#     for key in keywords:
#         count += keywords[key]
#     return count

# print(total(10, 1, 2, 3, vegetables = 50, fruits = 100))

# l = [1, 2, 3]
# print(l)
# del l[0: 2]
# print(l)
# del l[0: 2]
# print(l)

# print(total(10, 1, 2, 3, vegetables = 50, fruits = 100))


# import pickle

# l = ['a', 'b', 'c']
# f = open('1.pickle', 'wb')
# pickle.dump(l, f)
# f.close()
# del l

# f = open('1.pickle', 'rb')
# l = pickle.load(f)

# a = list(range(1))
# print(a)
# print(a[::10])

# import re
# driver = 'bonding'
# m = re.search(r'ixgbe|bonding', driver)
# if m:
#     print(driver)

# import math
# a = ['0', '1', '2', '3', '4', '5']
# b = 0
# for i in a:
#     b += int(math.pow(2, int(i)))
# print(hex(b))

# import copy
# d = {1: [1, 2, 3]}
# dd = copy.deepcopy(d)
# d[1].pop()
# print(d)
# print(dd)

# import math
# core_mask = 0
# cpu_count = 20
# core_list = ['10', '11', '12', '13', '14', '15', '16', '17', '18', '19']
# if cpu_count > 4:
#     # use 1 cores for system
#     core_list.pop(0)
# for core in core_list:
#     core_mask += int(math.pow(2, int(core)))
# print(hex(core_mask))


# import re
# out = '916318     40841    828909   5% /'
# d = {}
# m = re.search(r'(\d+)\s+(\d+)\s+\d+\s+\d+%', out)
# if m:
#     print(m.groups(0))
#     d["Total"] = round(float(m.group(1)) / 1000, 2)
#     d["Used"] = round(float(m.group(2)) / 1000, 2)
# print(d)

# out = '/dev/sda2               108794      2107    101138   2% /var/log'
# d = {}
# m = re.search(r'(\d+)\s+(\d+)\s+\d+\s+\d+%', out)
# if m:
#     print(m.groups(0))
#     d["Total"] = round(float(m.group(1)) / 1000, 2)
#     d["Used"] = round(float(m.group(2)) / 1000, 2)
# print(d)

# l = [1, 2, 3]
# l2 = l[:]
# print(l2)
# l3 = l[0:1]
# print(l3)
# l4 = l[:-1]
# print(l4)

# del l[0]
# print(l)

# import os
# import time

# if __name__ == "__main__":  
#     ret = os.fork()
#     if ret == 0:
#         # child
#         time.sleep(5)
#         print('done')

# d = range(0, 1)
# print(list(d))
# d = range(1, 2)
# print(list(d))

import datetime
import time
monitor_start_time = datetime.datetime.now()
time.sleep(2)
print(datetime.datetime.now() - monitor_start_time < datetime.timedelta(seconds = 1))
