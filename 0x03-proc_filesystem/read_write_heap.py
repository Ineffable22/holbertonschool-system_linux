#!/usr/bin/python3
""" Replaces the string being printed in a process """
from sys import argv
import os


def print_error():
    """Prints a Error"""
    print("""Usage:
    \tsudo python3 read_write_heap.py PID String_to_find String_to_replace""")
    exit(1)


def search_replace():
    if len(argv) < 4:
        print_error()
    try:
        pid = intargv[1]
        old_string = argv[2]
        new_string = argv[3]
        if pid == "":
            print("PID not found")
            print_error()
        if old_string == "":
            print("Insert string to find")
            print_error()
        if new_string == "":
            print("Insert string to replace")
            print_error()
    except IndexError as Error:
        print("Error: {}". format(Error))
        print_error()

    filename = "/proc/{}".format(pid)
    maps = filename + "/maps"
    mem = filename + "/mem"
    cmd_line = filename + "/cmdline"

    heap = ""
    try:
        with open(maps, "r") as fd:
            data = fd.read()
            data = data.split()
            for i in range(len(data)):
                if "[heap]" == data[i]:
                    heap = data[i]
                    inode = data[i - 1]
                    offset = data[i - 3]
                    permision = data[i - 4]
                    address = data[i - 5].split("-")
                    start = int(address[0], 16)
                    end = int(address[1], 16)
                    break
    except FileNotFoundError:
        print("PID not found")
        exit(1)
    except IOError as Error:
        print("Error: {}". format(Error))
        print_error()

    if heap == "":
        print("Heap not found")
        exit(1)

    with open(cmd_line, "r") as fd:
        cmd = fd.read()

    # Replaces rest of the Old String with spaces.
    # new_string = new_string + (len(old_string) - len(new_string)) * " "
    try:
        with open(mem, "rb+") as fd:
            fd.seek(start)
            mem_field = fd.read(end - start)
            try:
                i = mem_field.find(old_string.encode('ASCII'))
                if (i == -1):
                    print("'{}' string to find not found".format(old_string))
                    exit(1)
            except ValueError:
                print("Not matching string")
                exit(1)
            fd.seek(start + i)
            fd.write(new_string.encode('ASCII'))
    except PermissionError as Error:
        print("Error: {}". format(Error))
        print_error()

    heredoc = """[*] Command detected: {0}
    [*] maps: {1}
    [*] mem: {2}
    [*] Found {3}:
    \tpathname = {3}
    \taddresses = {4}-{5}
    \tpermisions = {6}
    \toffset = {7}
    \tinode = {8}
    [*] Addr start [{4}] | end [{5}]
    [*] Found '{9}' at {10}
    [*] Writting '{11}' at {12}
    """.format(cmd, maps, mem, heap, start, end,
               permision, offset, inode, old_string,
               i, new_string, start + i)
    print(heredoc)


if __name__ == '__main__':
    search_replace()
