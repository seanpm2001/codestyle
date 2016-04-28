#include <stdio.h>

void
check_file(int *had_err, const char *fn)
{
	FILE *fp;
	int ln_nbr;
	char ln[4096];
	int msgs = 0;
	int max_msgs = 20;
	
	if ((fp = fopen (fn, "r")) == NULL) {
		perror (fn);
		*had_err = 1;
		return;
	}

	ln_nbr = 1;
	while (fgets (ln, sizeof(ln), fp) != NULL) {
		if (ln[0] == ' ' && ln[1] != '*') {
			if(msgs == max_msgs) {
				fprintf(stderr, "reached max %d messages, not reporting more\n",
					max_msgs);
				goto done;
			}
			fprintf(stderr, "error: %s:%d: invalid indention (SP at column 1):"
				"\n%s\n", fn, ln_nbr, ln);
			*had_err = 1;
			++msgs;
		}
		++ln_nbr;
	}

done:
	fclose (fp);
}


int
main(int argc, char *argv[])
{
	int had_err = 0;
	for(int i = 1 ; i < argc ; ++i) {
		check_file(&had_err, argv[i]);
	}
	return had_err;
}
