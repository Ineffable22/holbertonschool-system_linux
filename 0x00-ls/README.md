# 0x00-ls (list directory contents)

## Description
This is the ls command as in Linux. List information about the files (the current directory by default). Sort entries alphabetically.
### SYNOPSIS
- `ls [OPTION]... [FILE]...`

### Learning Objectives
At the end of this project, you are expected to be able to [explain to anyone](https://fs.blog/feynman-learning-technique/), without the help of Google.

### Requirements:
- Allowed editors: `vi`, `vim`, `emacs`.
All your files will be compiled on Ubuntu 14.04 LTS using `gcc 4.8.4`, using the flags `-Wall -Werror -Wextra -pedantic`.
- All your files should end with a new line.
- A `README.md` file, at the root of the folder of the project.
- Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl).
- No more than 5 functions per file.
- All your header files should be include guarded
- Valgrind should show 0 memory leak and 0 error
- Unless specified otherwise, your program must have the exact same output as ls as well as the exact same error output - except for alignment.

### Allowed Functions and System Calls
- `opendir` (man 3 opendir)
- `readdir` (man 3 readdir)
- `closedir` (man 3 closedir)
- `exit` (man 3 exit)
- `free` (man 3 free)
- `lstat` (man 2 lstat)
- `malloc` (man 3 malloc)
- `perror` (man 3 perror)
- `write` (man 2 write)
- `printf` (man 3 printf)
- `sprintf` (man 3 sprintf)
- `fprintf` (man 3 fprintf)
- `readlink` (man 2 readlink)
- `ctime` (man 3 ctime)
- `getpwuid` (man 3 getpwuid)
- `getgrgid` (man 3 getgrgid)
- `errno` (man 3 errno)

## More Info
### Compilation
Your program will be compiled this way:
```C
gcc -Wall -Werror -Wextra -pedantic *.c -o hls
```
### Testing
Your program should give the same result as the real ls:
```C
$ ls test
abc  BCD  file  file2  file3  folder1  folder2  folder3
$ ./hls test
abc  BCD  file  file2  file3  folder1  folder2  folder3
$ ls -1
abc
BCD
file
file2
file3
folder1
folder2
folder3
hls
$ ./hls -1
abc
BCD
file
file2
file3
folder1
folder2
folder3
hls
$
```
## Files
### main.h
Stores the prototypes of all files.

### 0 - Let's start with something simple!
Create a program that lists the content of the current directory.
- Usage : `hls`
```C
Ineffable@~$ ls
abc  file  File2  file3  folder1  Folder2  folder3  hls
Ineffable@~$ ./hls
abc  file  File2  file3  folder1  Folder2  folder3  hls
Ineffable@~$
```

### 1. Maybe some parameters?
Your program should now take one or more file or directory names as parameters.

Usage : `hls [FILE]...`

Errors must be printed the same way than `ls` does:

- In `stderr`
- Starting by `<program>:` (`<program>` being `argv[0]`)
- `No such file or directory`, `Permission denied`, etc…
- Don’t forget the exit value

```C
Ineffable@~$ ls test
abc  file  File2  file3  folder1  Folder2  folder3
Ineffable@~$ ./hls test
abc  file  File2  file3  folder1  Folder2  folder3
Ineffable@~$ ./hls test/folder1/ test
test:
abc  file  File2  file3  folder1  Folder2  folder3

test/folder1/:
folder1-1  folder1-2  folder1-3
/simple_ls$ ./hls test/random
./hls: cannot access test/random: No such file or directory
Ineffable@~$
```

### 2. What about options?
Implement the `-1` option.

Usage : `hls [-1] [FILE]...`

For the rest of the project, an option will be identified by a command-line argument starting with the character `-` (like `ls`).
```
Ineffable@~$ ls test -1
abc
file
File2
file3
folder1
Folder2
folder3
Ineffable@~$ ./hls test -1
abc
file
File2
file3
folder1
Folder2
folder3
Ineffable@~$
```C
Note: Pay attention to “edge cases”: you should be able to handle multiple options, in any order.

### 3. Hidden files
Implement the -a option.

Usage : `hls [-a1] [FILE]...`

```C
Ineffable@~$ ls -a test
.  ..  abc  file  File2  file3  folder1  Folder2  folder3  .hidden1  .hidden2  ..hidden3
Ineffable@~$ ./hls -a test
.  ..  abc  file  File2  file3  folder1  Folder2  folder3  .hidden1  .hidden2  ..hidden3
Ineffable@~$ ./hls -a test/folder1
.  ..  folder1-1  folder1-2  folder1-3
Ineffable@~$ 
```

### 4. Almost all
Implement the -A option.

Usage : hls [-A] [FILE]...
```C
Ineffable@~$ ls -A test
abc  file  File2  file3  folder1  Folder2  folder3  .hidden1  .hidden2  ..hidden3
Ineffable@~$ ./hls -A test
abc  file  File2  file3  folder1  Folder2  folder3  .hidden1  .hidden2  ..hidden3
Ineffable@~$ ./hls -A test/folder1
folder1-1  folder1-2  folder1-3
Ineffable@~$
```

### 5. More details
Implement the `-l` option.

Usage : `hls [-l] [FILE]...`
```C
Ineffable@~$ ls -l test
total 12
-rw-rw-r-- 1 Ineffable Ineffable    0 May  8 00:19 abc
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
Ineffable@~$ ./hls -l test
-rw-rw-r-- 1 Ineffable Ineffable    0 May  8 00:19 abc
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
Ineffable@~$
```
You might notice the `total 12` in the first line of `ls -l`. You can ignore this value for this exercise.

Note: Pay attention to “edge cases”: Usernames and group names are not always defined.

### 6. Mixing options
All options together.

Usage : `hls [-1aAl] [FILE]...`
```C
Ineffable@~$ ./hls -lA test
-rw-rw-r-- 1 Ineffable Ineffable    0 May  8 00:19 abc
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 30 16:30 .hidden1
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 30 16:30 .hidden2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 30 17:08 ..hidden3
Ineffable@~$ ./hls -lA -a test
drwxrwxr-x 5 Ineffable Ineffable 4096 May  8 01:12 .
drwxrwxr-x 4 Ineffable Ineffable 4096 May 15 11:51 ..
-rw-rw-r-- 1 Ineffable Ineffable    0 May  8 00:19 abc
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 30 16:30 .hidden1
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 30 16:30 .hidden2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 30 17:08 ..hidden3
Ineffable@~$ ./hls -1A test
abc
file
File2
file3
folder1
Folder2
folder3
.hidden1
.hidden2
..hidden3
Ineffable@~$
```

### 7. Esrever
Implement the `-r` option.

Usage : `hls [-1aAlr] [FILE]...`

```C
Ineffable@~$ ./hls test
abc file File2 file3 folder1 Folder2 folder3
Ineffable@~$ ./hls test -r
folder3  Folder2  folder1  file3  File2  file  abc
Ineffable@~$ ./hls test/folder1/ test/folder3/ -r
test/folder3/:
symlink  folder3-1  file2  file1

test/folder1/:
folder1-3  folder1-2  folder1-1
Ineffable@~$ 
```

### 8. More sorting?
Implement the `-S` option.

Usage : `hls [-1aAlrS] [FILE]...`
```C
Ineffable@~$ ./hls -l test
-rw-rw-r-- 1 Ineffable Ineffable    0 May 16 12:36 abc
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
Ineffable@~$ ./hls -lS test
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
-rw-rw-r-- 1 Ineffable Ineffable    0 May 16 12:36 abc
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
Ineffable@~$ ./hls -lSr test
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 May 16 12:36 abc
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
Ineffable@~$
```

### 9. I know you like sorting things.
Implement the -t option.

Usage : `hls [-1aAlrSt] [FILE]...`
```C
Ineffable@~$ ./hls -l test
-rw-rw-r-- 1 Ineffable Ineffable    0 May 16 12:36 abc
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
Ineffable@~$ ./hls -lt test
-rw-rw-r-- 1 Ineffable Ineffable    0 May 16 12:36 abc
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
Ineffable@~$ ./hls -ltr test
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3
-rw-rw-r-- 1 Ineffable Ineffable    0 May 16 12:36 abc
Ineffable@~$
```

### 10. The Juggernaut
Implement the `-R` option.

Usage : `hls [-1aAlrStR] [FILE]...`
```C
Ineffable@~$ ./hls -R test
test:
abc  ABC  file  File2  file3  folder1  Folder2  folder3

test/folder1:
folder1-1  folder1-2  folder1-3

test/folder1/folder1-1:
file1  file2  file3

test/folder1/folder1-2:
file1

test/folder1/folder1-3:
file1  file2

test/Folder2:
file1  file2

test/folder3:
file1  file2  folder3-1  symlink

test/folder3/folder3-1:
file1  folder3-1-1

test/folder3/folder3-1/folder3-1-1:
file1  file2
Ineffable@~$ ./hls -Rl test
test:
-rw-rw-r-- 1 Ineffable Ineffable    0 May 16 12:36 abc
-rw-rw-r-- 1 Ineffable Ineffable    0 May  8 00:19 ABC
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 File2
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 18 14:04 file3
drwxrwxr-x 5 Ineffable Ineffable 4096 Apr 30 15:22 folder1
drwxrwxr-x 2 Ineffable Ineffable 4096 May  7 15:36 Folder2
drwxrwxr-x 3 Ineffable Ineffable 4096 May  7 15:37 folder3

test/folder1:
drwxrwxr-x 2 Ineffable Ineffable 4096 Apr 30 14:59 folder1-1
drwxrwxr-x 2 Ineffable Ineffable 4096 Apr 30 14:59 folder1-2
drwxrwxr-x 2 Ineffable Ineffable 4096 Apr 30 14:59 folder1-3

test/folder1/folder1-1:
-rw-rw-r-- 1 Ineffable Ineffable 0 Apr 30 14:59 file1
-rw-rw-r-- 1 Ineffable Ineffable 0 Apr 30 14:59 file2
-rw-rw-r-- 1 Ineffable Ineffable 0 Apr 30 14:59 file3

test/folder1/folder1-2:
-rw-rw-r-- 1 Ineffable Ineffable 0 Apr 30 14:59 file1

test/folder1/folder1-3:
-rw-rw-r-- 1 Ineffable Ineffable 0 Apr 30 14:59 file1
-rw-rw-r-- 1 Ineffable Ineffable 0 Apr 30 14:59 file2

test/Folder2:
-rw-rw-r-- 1 Ineffable Ineffable 0 Apr 30 14:59 file1
-rw-rw-r-- 1 Ineffable Ineffable 0 May  7 15:36 file2

test/folder3:
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 30 15:03 file1
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 30 15:03 file2
drwxrwxr-x 3 Ineffable Ineffable 4096 Apr 30 15:22 folder3-1
lrwxrwxrwx 1 Ineffable Ineffable    5 May  8 00:01 symlink -> file2

test/folder3/folder3-1:
-rw-rw-r-- 1 Ineffable Ineffable    0 Apr 30 15:03 file1
drwxrwxr-x 2 Ineffable Ineffable 4096 Apr 30 15:03 folder3-1-1

test/folder3/folder3-1/folder3-1-1:
-rw-rw-r-- 1 Ineffable Ineffable 0 Apr 30 15:03 file1
-rw-rw-r-- 1 Ineffable Ineffable 0 Apr 30 15:03 file2
Ineffable@~$ 
```

## Author:

<div align="center">
<a href="https://www.linkedin.com/in/miguel-enrique-grillo-orellana/">
<img src="https://img.shields.io/badge/Miguel-Linkedind-blue"></a>

<a href="https://medium.com/@Miguel_Grillo"><img src="https://miro.medium.com/max/1200/0*jTIO9a1_5T3mv-pR.png" alt="Link Medium" width="100px" height= "50px"></a>
</div>
