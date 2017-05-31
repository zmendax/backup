#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Run the backup script to generate the sql file */
void run_script(char *file)
{
	FILE *fp, *pp;
	char line[1024], buf[1024];

	if ((fp = fopen(file, "r")) == NULL) {
		perror("open script");
		return;
	}

	printf("\n");
	while (!feof(fp))
	{
		memset(buf, 0, sizeof(buf));
		fgets(line, sizeof(line), fp);
		if (line != NULL && strlen(line) > 0) {
			printf("[SCRIPT]: %s\n", line);
			pp = popen(line, "r");
			//fgets(buf, sizeof(buf), pp);
			//puts(buf);
			pclose(pp);
		}
	}
	fclose(fp);
}

// void run_cmd(char *cmd)
// {
// 	char buf[1024];
// 	FILE *pp = popen(cmd, "r");
// 	fgets(buf, sizeof(buf), pp);
// 	puts(buf);
// 	pclose(pp);
// }