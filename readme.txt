ls_example is a program that implements partial functionality of shell command 'ls'.

Use command "cmake . -Bbuild", than "cd build" and than "make" to build and compile program.

To use ls_example as a regular command add path where the program is located to $PATH, 
or copy ls_example Unix executable to $PATH, for example "sudo cp ls_example /usr/local/bin",
or create symlink for not having duplicates.

directory path can also be passed to ls_example manually after the keys
for example "ls_example -l -a /some_dir/another_dir"

use -l key to get full info about file
use -a key to display hidden dirs 

