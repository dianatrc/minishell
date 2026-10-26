# Minishell

A custom UNIX command interpreter written in **C** inspired by **tcsh**. This project is structured in two major developmental phases: a core standalone shell (minishell 1) and an advanced version featuring inter-process communication and file descriptors manipulation (minishell2).

# Key Features and Evolution
**Phase 1: Core Shell and Environment (Minishell 1)**
- **Custom Interactive Prompt:** displays a dynamic prompt, similar to tcsh, by showing the username (with capitalized first letter) and the current working directory with shortcut for home (User:~/path>).
- **PATH Resolution:** automatically searches and executes binaries located within system directories defined in the 'PATH' environment variable or via absolute/relative paths.
- **Environment Management:** copies and safely restores the initial environment so that modifications do not affect the original 'env' variable.
- **Core Built-in Commands:**
    - cd: navigates directories with support for absolute/relative paths, '~' (home directory) and '-' (previous directory).
    - env: displays the current environment variables list.
    - setenv: dynamically adds or updates environment variables with strict alphanumeric name validation.
    - unsetenv: removes one or multiple environment variables.
    - exit: safely terminates the shell session and releases all allocated memory.
- **Exit Status Tracking (echo $?):** accurately propagates the return code of the last executed command or child termination signals.

**Phase 2: Advanced Operators and Redirection (Minishell 2)**
- **Command Chaining (;):** executes multiple sequential commands separated by semicolons on a single input line.
- **Pipes (|):** connects the standard output of one process to the standard input of another using system pipes.
- **File Redirections:**
    - Output Redirections (> and >>): redirects standard output to a file in overwrite or append mode.
    - Input Redirection (<): reads process input directly from a specified file.
- **Syntax and Error Validation:** comprehensive error checks detecting invalid pipe placements, ambiguous redirections and syntax anomalies matching standard tcsh behavior.

# Error Handling and Robustness
- **Process Signals:** intercepts SIGINT (Ctrl+C) without crashing the shell prompt.
- **Error Reporting:** writes all runtime error messages directly to stderr and complies with standard exit code (exits with code 84 on critical failures or 0 on success).

# Project Structure
- include/
    - functions.h       # Main header file with prototypes and system includes
- bonus/
    - bonus.c           # Custom interactive prompt formatting.
- src/
    - main.c            # Main loop and line processing
    - parsing.c         # Command parsing and builtin routing
    - exec.c            # Execution logic, PATH resolution, fork/execve and signal tracking
    - pipe.c            # Pipeline creation and multi-command execution
    - redirections.c    # File descriptor redirection logic
    - builtins.c        # Builtin implementations (env, setenv, unsetenv, exit)
    - cd.c              # Directory navigation
    - env_utils.c       # Helper functions for environment allocation and updates
    - my_lib.c          # Custom string utility functions (part 1)
    - my_lib2.c         # Custom string utility functions (part 2)
- Makefile              # Compilation rules for building (all), cleaning (clean, fclean) and rebuilding (re) the project.
- README.md

# Compilation and Usage
**BUILD**
To compile the 'mysh' binary using the provided Makefile, run: make.
To clean intermediate or target files:
- make clean    # Removes object files.
- make fclean   # Removes object files and binaries.
- make re       # Clean rebuild.

**USAGE**
Run the shell interactively: ./mysh or execute commands via standard input piping: echo "ls" | ./mysh