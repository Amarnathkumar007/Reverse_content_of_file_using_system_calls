## README for Code 1

### Overview

This program performs basically two types of reverser on given file based on given input.
1. if <file_path> and 0 is given as input then it will reverse all content of text file.
2. if <file_path> and 1 along with <start_index> and <end_index> given then it will reverse all content except character in the range of start_index to end_index.

note: Internally this program handles mostly all kinds of error in parameter or file exist or not permission of file etc.

### Flow
so here is the flow of  Program:
1. **checks validity of input**
   - like number of parameters. correctness of path.
   
2. **Existance of given file**
   - Whether given address belongs to file or directory or given file is regular file or not.
   
3. **Creatation of Directory**
   - Directory is named as Assignment1 with 0744 permission.
   
4. **Creation of File**
   - File will be named as 0/1_<given_file_name>.txt with 0744 permission on which reverse output written.

### How to use

1. Compile the program as: 
```bash
g++ 2024202024_A1_Q1.cpp
```
2. Run the file with the shown command: 
```bash
./a.out <file_name> 0
```
or 
```bash
./a.out <file_name> 1 <start_parameter> <end_parameter>
```


## README for Code 2
   
### Overview
   - This program basically checks Content of file1 is reverse of content of file2, along with size of file, and all kinds of permsions like
   - permission of user, group, others on file1.
   - permission of user, group, others on file2.
   - permission of user, group, others on Directory.
   
note: Reversal of content is checked by using chunk that keeps of taking input from file one and file 2 and then reverse file 1 content and checks both are same or not till all the characters are not matched.
   
### Flow
so here is the flow of  Program:
1. **checks validity of input**
   - like number of parameters. correctness of both the file path and directory.
   
2. **Existance of given file**
   - Whether given address belongs to files or directory or given file is regular file or not.
   
3. **Reversed Content**
   - Checks the content of <file1> is reverse of content of <file2>.
   
4. **Checking permission**
   - Checks and prints all kind of permission like r,w,x for owner, group, others for both files and given directory

### How to Use

1. Compile the program as: 

```bash
g++ 2024202024_A1_Q2.cpp
```

2. Run the file with the shown command: 

```bash
./a.out <file1> <file2> <directory>
```
