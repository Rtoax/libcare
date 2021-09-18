#include "cclp_log.h"

int main()
{
    const char *in_file1 = "../foo.s";
    const char *in_file2 = "../bar.s";
    const char *out_file = "./foobar.s";

    FILE *in_file1_fp = fopen(in_file1, "rt");
    FILE *in_file2_fp = fopen(in_file2, "rt");
	FILE *out_file_fp = fopen(out_file, "wt");


    
    fclose(in_file1_fp);
    fclose(in_file2_fp);
    fclose(out_file_fp);
}
