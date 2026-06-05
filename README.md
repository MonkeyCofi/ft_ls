# ft_ls
A project that involves recreating the ls function with a limited amount of flags

Flags:
- -a: display all entries, not ignoring entries starting with . (hidden files/folders)
- -l: long listing format. Lists the total 
- -r: list in reverse order while sorting
- -R: recursively list subdirectories within the directory
- -t: sort by time, sorting by newest first

Returns: 
- 0 if everything is ok
- 1 if there are minor problems (eg: cannot access a subdirectory)
- 2 if there is a serious issue (eg: cannot access directory listed as command line argument)

Functions allowed:
- write
- opendir
- readdir
- closedir
- stat: used to display file status
- lstat
- getpwuid
- getgrgid
- listxattr: 
- getxattr
- time
- ctime
- readlink
- malloc
- free
- perror
- strerror
- exit

## Resources
- ["How does 'ls' work?"](https://medium.com/better-programming/how-does-ls-work-14fdc2b85308) by Sanil Khurana