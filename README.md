# Holberton School Shell (hsh)

This is a simple UNIX command-line interpreter developed as a project for Holberton School.
The program starts a loop to read input lines, parses them and execute commands if any.

## Compilation
Compile the shell using the provided Makefile with this command:
```bash
make all
```
## Usage
Run the shell with the following command:
```bash
./hsh
```

## Features
- Basic command execution
- Built-in commands:
  - `exit`: Exit the shell with optional status.
  - `cd`: Change the current working directory.
  - `env`: Display the current environment variables.
  - `setenv`: Initialize or modify an environment variable.
  - `unsetenv`: Remove an environment variable.

- Redirections:
  - `>`: Right stream redirection for output.
  - `>>`: Double right stream redirection for appending output.
  - `<`: Left stream redirection for input.
  - `<<`: Double left stream redirection (heredoc) for multiline input.

- Pipelines:
  - `|`: Pipe stream redirection to connect the output of one command to the input of another.

- Logical operators:
  - `&&`: Logical AND, execute the right command only if the left command succeeds.
  - `||`: Logical OR, execute the right command only if the left command fails.

- Command separators:
  - `;`: Separates multiple commands on a single line, allowing sequential execution.

- Additional Functionality:
  - Environment variable updates using `setenv` and `unsetenv`.

## Examples

### Basic Command Execution
Run the shell and execute a basic command:
```bash
user1@~$ ./hsh
ls -l
total 16
-rwxrwxr-x 1 user user 16528 Jan 14 00:00 hsh
exit
user1@~$
```
### Built-in Commands
``` bash
user1@~$ ./hsh
cd /
pwd
/
env
SHELL=/bin/bash
LC_ALL=en_US.UTF-8
setenv MY_VARIABLE my_value
env
SHELL=/bin/bash
LC_ALL=en_US.UTF-8
MY_VARIABLE=my_value
unsetenv MY_VARIABLE
env
SHELL=/bin/bash
LC_ALL=en_US.UTF-8
exit
user1@~$
```

### Redirections
```bash
user1@~$ ./hsh
echo "Hello, World!" > output.txt
cat output.txt
"Hello, World!"
echo "Hello, World!" >> output.txt
cat output.txt
"Hello, World!"
"Hello, World!"
rev < output.txt
"!dlroW ,olleH"
"!dlroW ,olleH"
cat << END
This is a heredoc.
Multiple lines of text.
END
This is a heredoc.
Multiple lines of text.
exit
user1@~$
```

### Pipelines
```bash
user1@~$ ./hsh
ls /var | grep log
syslog
exit
user1@~$
```

### Logical Operators
```bash
user1@~$ ./hsh
ls /var && ls /var
backups  cache  devcontainer  lib  local  lock  log  mail  opt  run  spool  tmp
backups  cache  devcontainer  lib  local  lock  log  mail  opt  run  spool  tmp
ls /hbtn && ls /var
ls: cannot access /hbtn: No such file or directory
ls /var || ls /var
backups  cache  devcontainer  lib  local  lock  log  mail  opt  run  spool  tmp
ls /hbtn || ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
exit
user1@~$
```

### Command Separators
```bash
user1@~$ ./hsh
ls /var ; ls /hbtn ; ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
exit
user1@~$
```
