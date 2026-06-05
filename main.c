#include <stdio.h>
#include <dirent.h>

int main(void)
{
	DIR *dirp;

	dirp = opendir("./");
	if (dirp == NULL) {
		perror("opendir");
		return 1;
	}
	struct dirent *entry;
	while ((entry = readdir(dirp)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}
}