![](https://github.com/ksh93/ksh/workflows/CI/badge.svg)

# Extras branch
This is a downstream branch of ksh93u+m I maintain that adds
a few extra features. I intend to eventually submit most of these features upstream,
although some of these additions are more debugging oriented and likely will not go upstream.
To list all non-merge commits specific to the extras branch, run the following command in a terminal:
```sh
git log --no-merges extras ^master
```

The extra features the extras branch adds are as follows:

1. Support for `${$var}` from ksh93v- has been added, where `$var` points to the name of a variable.
   For example, `$var` can be set to point to `$foo`:  
```sh
$ var=foo
$ foo='Intended result'
$ echo ${$var}
Intended result
```
2. Extra keybinds have been added to the emacs and vi editing modes. These additions have been submitted upstream in [ksh93#410](https://github.com/ksh93/ksh/pull/410), but aren't merged yet.
  * The following keybinds are added to both editing modes:
    * Support for Haiku's arrow key sequences (`^[OA`, `^[OB`, etc.)
    * Support for Home key sequences `^[[1~` and `^[[7~`
    * Support for End key sequences `^[[4~` and `^[[8~`
    * Ctrl-Left Arrow:	Go back one word
    * Alt-Left Arrow:	Go back one word
    * Ctrl-Right Arrow:	Go forward one word
    * Alt-Right Arrow:	Go forward one word
    * Ctrl-G:		End reverse search
    * Ctrl-Delete:	Delete next word
  * An insert keybind has also been added which functions differently in each mode:
    * Insert (emacs):	Escape next character
    * Insert (vi):	Switch to insert mode
3. The prompt printed for emacs reverse search mode is now `? ` instead of `^R` (this will probably be refactored into a `$PS5` variable).
4. Microsecond precision has been added to the `time` keyword and `times` builtin.
5. The `%C` time format has been backported from ksh2020. `%C` is the total number of CPU seconds (i.e., the sum of `%U` and `%S`).
6. `read -a` (as an alias for `read -A`) has been backported from ksh93v- for bash compatibility.
7. Added the following long options to the libcmd builtins (to match the equivalent GNU coreutils long options):
  * `basename --multiple` as an alias for `basename -a`.
  * `cat --show-tabs` as an alias for `cat -T`.
  * `chgrp --no-dereference` as an alias for `chgrp -h`.
  * `chown --no-dereference` as an alias for `chown -h`.
  * `cp --no-dereference` as an alias for `cp -P`.
  * `cp --symbolic` as an alias for `cp -s`.
  * `join --ignore-case` as an alias for `join -i`.
  * `ln --symbolic` as an alias for `ln -s`.
  * `mv --symbolic` as an alias for `mv -s`. (GNU coreutils doesn't support `mv --symbolic`. It was added because `cp`, `ln` and `mv` share `optget` code.)
  * `rm --dir` as an alias for `rm -d`.
8. The `shcomp` command now supports a `-d/--deparse` option. This flag causes `shcomp` to run the shell deparser on the given script, then output the result.
9. A `banner` command has been added alongside `pty`. This is the AST `banner` command with features added to it from the NetBSD `banner`.
10. All of the `/opt/ast/bin` builtins (excluding `vmstate` when compiling with standard malloc) can now be enabled by compiling with `-DSHOPT_ALL_AST_BUILTINS=1`.

# KornShell 93u+m

See the main repo at https://github.com/ksh93/ksh.
The sources in this repository were forked from the
GitHub [AST repository](https://github.com/att/ast)
which is no longer under active development.

For user-visible fixes, see [NEWS](https://github.com/ksh93/ksh/blame/master/NEWS)
and click on commit messages for full details.
For all fixes, see [the commit log](https://github.com/ksh93/ksh/commits/).
To see what's left to fix, see [the issue tracker](https://github.com/ksh93/ksh/issues).

## Policy

1. Fixing bugs is main focus of the 1.x series.
   Major feature development is for future versions (2.x and up).
2. No major rewrites. No refactoring code that is not fully understood.
3. No changes in documented behaviour, except if required for compliance with the
   [POSIX shell language standard](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html)
   which David Korn [intended](http://www.kornshell.com/info/) for ksh to follow.
4. No 100% bug compatibility. Broken and undocumented behaviour gets fixed.
5. No bureaucracy, no formalities. Just fix it, or report it: create issues,
   send pull requests. Every interested party is invited to contribute.
6. To help increase everyone's understanding of this code base, fixes and
   significant changes should be fully documented in commit messages.
7. Code style varies somewhat in this historic code base.
   Your changes should match the style of the code surrounding them.
   Indent with tabs, assuming an 8-space tab width.
   Opening braces are on a line of their own, at the same indentation level
   as their corresponding closing brace.
   Comments always use `/*`...`*/`.
8. Good judgment may override this policy.

## Why?

Between 2017 and 2020 there was an ultimately unsuccessful
[attempt](https://github.com/att/ast/tree/2020.0.1)
to breathe new life into the KornShell by extensively refactoring the last
unstable AST beta version (93v-).
While that ksh2020 branch is now abandoned and still has many critical bugs,
it also had a lot of bugs fixed. More importantly, the AST issue tracker
now contains a lot of documentation on how to fix those bugs, which made
it possible to backport many of them to the last stable release instead.
This ksh 93u+m reboot now incorporates many of these bugfixes,
plus patches from
[OpenSUSE](https://github.com/ksh93/ksh/wiki/Patch-Upstream-Report:-OpenSUSE),
[Red Hat](https://github.com/ksh93/ksh/wiki/Patch-Upstream-Report:-Red-Hat),
and
[Solaris](https://github.com/ksh93/ksh/wiki/Patch-Upstream-Report:-Solaris),
as well as many new fixes from the community
([1](https://github.com/ksh93/ksh/pulls?q=is%3Apr+is%3Amerged),
[2](https://github.com/ksh93/ksh/issues?q=is%3Aissue+is%3Aclosed+label%3Abug)).
Though there are many
[bugs left to fix](https://github.com/ksh93/ksh/issues),
we are confident at this point that 93u+m is already the least buggy branch
of ksh93 ever released.

## Build

To build ksh with a custom configuration of features, edit
[`src/cmd/ksh93/SHOPT.sh`](https://github.com/ksh93/ksh/blob/master/src/cmd/ksh93/SHOPT.sh).

Then `cd` to the top directory and run:
```sh
bin/package make
```

The compiled binaries are stored in the `arch` directory, in a subdirectory
that corresponds to your architecture. The command `bin/package host type`
outputs the name of this subdirectory.

If you have trouble or want to tune the binaries, you may pass additional
compiler and linker flags. It is usually best to export these as environment
variables *before* running `bin/package` as they could change the name of
the build subdirectory of the `arch` directory, so exporting them is a
convenient way to keep them consistent between build and test commands.
**Note that this system uses `CCFLAGS` instead of the usual `CFLAGS`.**
An example that makes Solaris Studio cc produce a 64-bit binary:
```sh
export CCFLAGS="-m64 -O" LDFLAGS="-m64"
bin/package make
```
Alternatively you can append these to the command, and they will only be
used for that command. You can also specify an alternative shell in which
to run the build scripts this way. For example:
```sh
bin/package make SHELL=/bin/bash CCFLAGS="-O2 -I/opt/local/include" LDFLAGS="-L/opt/local/lib"
```

For more information run
```sh
bin/package help
```
Many other commands in this repo self-document via the `--help`, `--man` and
`--html` options; those that do have no separate manual page.

### Test

After compiling, you can run the regression tests.
Start by reading the information printed by:
```sh
bin/shtests --man
```

### Install

Automated installation is not supported yet.
To install manually:
```sh
cp arch/$(bin/package host type)/bin/ksh /usr/local/bin/
cp src/cmd/ksh93/sh.1 /usr/local/share/man/man1/ksh.1
```
(adapting the destination directories as required).

## What is ksh93?

The following is the official AT&T description from 1993 that came with the
ast-open distribution. The text is original, but hyperlinks were added here.

----

KSH-93 is the most recent version of the KornShell Language described in
"The KornShell Command and Programming Language," by Morris Bolsky and David
Korn of AT&T Bell Laboratories, ISBN 0-13-182700-6. The KornShell is a shell
programming language, which is upward compatible with "sh" (the Bourne
Shell), and is intended to conform to the IEEE P1003.2/ISO 9945.2
[Shell and Utilities standard](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html).
KSH-93 provides an enhanced programming environment in addition to the major
command-entry features of the BSD shell "csh". With KSH-93, medium-sized
programming tasks can be performed at shell-level without a significant loss
in performance. In addition, "sh" scripts can be run on KSH-93 without
modification.

The code should conform to the
[IEEE POSIX 1003.1 standard](http://www.opengroup.org/austin/papers/posix_faq.html)
and to the proposed ANSI C standard so that it should be portable to all
such systems. Like the previous version, KSH-88, it is designed to accept
eight bit character sets transparently, thereby making it internationally
compatible. It can support multi-byte characters sets with some
characteristics of the character set given at run time.

KSH-93 provides the following features, many of which were also inherent in
KSH-88:

* Enhanced Command Re-entry Capability: The KSH-93 history function records
  commands entered at any shell level and stores them, up to a
  user-specified limit, even after you log off. This allows you to re-enter
  long commands with a few keystrokes - even those commands you entered
  yesterday. The history file allows for eight bit characters in commands
  and supports essentially unlimited size histories.
* In-line Editing: In "sh", the only way to fix mistyped commands is to
  backspace or retype the line. KSH-93 allows you to edit a command line
  using a choice of EMACS-TC or "vi" functions. You can use the in-line
  editors to complete filenames as you type them. You may also use this
  editing feature when entering command lines from your history file. A user
  can capture keystrokes and rebind keys to customize the editing interface.
* Extended I/O Capabilities: KSH-93 provides several I/O capabilities not
  available in "sh", including the ability to:
  * specify a file descriptor for input and output
  * start up and run co-processes
  * produce a prompt at the terminal before a read
  * easily format and interpret responses to a menu
  * echo lines exactly as output without escape processing
  * format output using printf formats.
  * read and echo lines ending in "\\". 
* Improved performance: KSH-93 executes many scripts faster than the System
  V Bourne shell. A major reason for this is that many of the standard
  utilities are built-in. To reduce the time to initiate a command, KSH-93
  allows commands to be added as built-ins at run time on systems that
  support dynamic loading such as System V Release 4.
* Arithmetic: KSH-93 allows you to do integer arithmetic in any base from
  two to sixty-four. You can also do double precision floating point
  arithmetic. Almost the complete set of C language operators are available
  with the same syntax and precedence. Arithmetic expressions can be used to
  as an argument expansion or as a separate command. In addition, there is an
  arithmetic for command that works like the for statement in C.
* Arrays: KSH-93 supports both indexed and associative arrays. The subscript
  for an indexed array is an arithmetic expression, whereas, the subscript
  for an associative array is a string.
* Shell Functions and Aliases: Two mechanisms - functions and aliases - can
  be used to assign a user-selected identifier to an existing command or
  shell script. Functions allow local variables and provide scoping for
  exception handling. Functions can be searched for and loaded on first
  reference the way scripts are.
* Substring Capabilities: KSH-93 allows you to create a substring of any
  given string either by specifying the starting offset and length, or by
  stripping off leading or trailing substrings during parameter
  substitution. You can also specify attributes, such as upper and lower
  case, field width, and justification to shell variables.
* More pattern matching capabilities: KSH-93 allows you to specify extended
  regular expressions for file and string matches.
* KSH-93 uses a hierarchical name space for variables. Compound variables can
  be defined and variables can be passed by reference. In addition, each
  variable can have one or more disciplines associated with it to intercept
  assignments and references.
* Improved debugging: KSH-93 can generate line numbers on execution traces.
  Also, I/O redirections are now traced. There is a DEBUG trap that gets
  evaluated before each command so that errors can be localized.
* Job Control: On systems that support job control, including System V
  Release 4, KSH-93 provides a job-control mechanism almost identical to
  that of the BSD "csh", version 4.1. This feature allows you to stop and
  restart programs, and to move programs between the foreground and the
  background.
* Added security: KSH-93 can execute scripts which do not have read
  permission and scripts which have the setuid and/or setgid set when
  invoked by name, rather than as an argument to the shell. It is possible
  to log or control the execution of setuid and/or setgid scripts. The
  noclobber option prevents you from accidentally erasing a file by
  redirecting to an existing file.
* KSH-93 can be extended by adding built-in commands at run time. In
  addition, KSH-93 can be used as a library that can be embedded into an
  application to allow scripting.

Documentation for KSH-93 consists of an "Introduction to KSH-93",
"Compatibility with the Bourne Shell" and a manual page and a README file.
In addition, the "New KornShell Command and Programming Language" book is
available from Prentice Hall.
