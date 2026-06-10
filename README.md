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

# Implementation stuff

### Initialization
Start by parsing the command line arguments to see if any optinos are given<br>

If a '-' character is found, check the next character to see if it is a valid option. If a valid option is found, add it to some place keeping track of the options

### The Command
By default, the command sorts the directories by alphabetical order. However, this behaviour can be altered by the following flags: -r, -t

The -r flag reverses the order of the sort. It also affects the -t flag

The -t flag sorts by the latest time modified. The -r flag would sort it by the earliest time modified

### -R option
Recursively list every directory possible. This would recursively call opendir() for each directory up until the file is not a directory, in which case opendir would set errno as 20.<br>

### -a option
List all files prefixed with '.' (usually hidden files). By default, they will be sorted in alphabetical order

### Functions used
The details about every linux file is stored in an object called an inode (index node).

The very basis of ls starts with the opendir() function. It opens the directory given as a parameter and returns a DIR pointer. This DIR struct represents the directory opened as a parameter to opendir().

Each file in the directory can then be opened with readdir() which returns a dirent address. The struct's glibc implementation is defined as follows:
``` C
struct dirent
{
    ino_t          d_ino;       /* Inode number */
    off_t          d_off;       /* Not an offset; see below */
    unsigned short d_reclen;    /* Length of this record */
    unsigned char  d_type;      /* Type of file; not supported
                                    by all filesystem types */
    char           d_name[256]; /* Null-terminated filename */
};
```
This would be the laziest way to implement ls for the current directory is as follows:
``` C
int main()
{
    DIR *directory;
    struct dirent *entry = NULL;

    directory = opendir("./");  // open the current directory
    if (directory == NULL)      // an error in opendir() call
    {
        perror("opendir");
        return 1;
    }
    entry = readdir(directory)
    while (entry)
    {
        printf("%s\n", entry->d_name);  // print the entry name
        entry = readdir(directory);
    }
}
```

Obviously there should be a lot more to do, but this does print every file in the current directory (including the hidden ones)

Try creating a quene that will store every dirent entry that is returned by readdir()<br>
The entries in this queue can be sorted by either:
- alphabetical order
- time modified

The queue's order will be head-first or rear-first depending on whether the -r flag is set

### Priority
As previously mentioned, there are 5 flags to check for: -l, -a, -r, -R, and -t<br>
There is an order as to how these flags should be processed. The -t flag takes the highest priority, as that switches from sorting alphabetically to sorting by time<br>
After that, the -r flag should be considered, which will reverse the order of the sorting. The rest of the flags don't really have a priority as they just change<br>
the behaviour of the listing rather than the actual order of listing.


### ls display format with -l flag
Here is a sample file listed with the -l flag
-rw-r--r-- 1 pipolint 2023_abu-dhabi 1763 Jun 10 14:07 ft_atoi.c

Here is a sample folder listed with the -l flag
drwxr-xr-x 2 pipolint 2023_abu-dhabi   81 Jun 10 17:57 get_next_line

the first column displays the permissions for the group, the second column displays the username of the owner of the file, 