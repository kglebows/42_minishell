# 42_minishell

Resources :

https://www.codequoi.com/en/creating-and-killing-child-processes-in-c/

https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/

3https://www.codequoi.com/en/pipe-an-inter-process-communication-method/

https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/



https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/

https://www.codequoi.com/en/errno-and-error-management-in-c/

https://github.com/zstenger93/minishell/blob/master/mindmap.png

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

Allowed functions :
readline, -> https://tiswww.case.edu/php/chet/readline/readline.html
rl_clear_history, 
rl_on_new_line,
rl_replace_line, 
rl_redisplay, 
add_history,
printf, 
malloc, 
free, 
write, 
access, 
open, 
read,
close, 
fork, 
wait, 
waitpid, 
wait3, 
wait4, 
signal,
sigaction, 
sigemptyset, 
sigaddset, 
kill, 
exit,
getcwd, 
chdir, 
stat, 
lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs

# General idea

```yaml
string -> data structure -> action

lexer : string -> [tokens] 
parser : [tokens] -> data

expander : data -> expanded_data
executor : expanded_data -> action
```

# What is the data?

1. command table
2. abstract syntax tree

# Deciding the data structure

linked list or array of commands

## command data structure

1. arguments e.g. "ls", "-l" // execve
2. redirections

```c
enum e_redirection_type
{
  REDIRECTION_IN,
  REDIRECTION_IN_HEREDOC
  REDIRECTION_OUT,
  REDIRECTION_OUT_APPEND
};

struct Redirection
{
  enum e_redirection_type type;
  char                    *data;
};
```

```yaml
data: [command]
command: {arguments, [redirection]}
arguments: char**
redirection: { type, char *}
type: enum
```

## tips

### string slice

```c
struct s_string_slice
{
  char *string;
  int  length;
};
```

### OOP

struct s_lexer
{
};

void  init_lexer(struct s_lexer* lexer);
void  free_lexer(struct s_lexer* lexer);



struct s_lexer lexer;

init_lexer(&lexer, ...);

action(&lexer, ...);

free_lexer(&lexer);


# Execution

## Redirection Concepts

redirections (dup2, dup)

file descriptor -> file description

command writes to fd: stdout -> terminal
what u want: fd: stdout -> file

## 4 types of redirections:

- '< file' reads from a file
- '<< HELLO' reads from a temporal file created on the fly. The user will be prompted to write the file until the user writes 'HELLO'
- '> file' writes to a file with trunc
- '>> file' writes to a file in append mode


## Executor details

stdout -> terminal
fd_file -> file

after dup2:

stdout -> file
fd_file -> file


execve(...)

int fd_file = open(hi.txt); # fd_file -> file
dup2(stdout, fd_file);
close(fd_file);
execve(...)
