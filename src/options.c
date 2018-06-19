#include <getopt.h>

#define PACKAGE "joystext"
#define VERSION "0.0.2"

void show_usage(void) {
   fprintf(stdout,
           "Usage : " PACKAGE " [OPTIONS]\n"
           "  -h, --help                                     Display this help and exit.\n"
           "  -r, --read-from-lower-level-config             Take a lower level config file as input.\n"
           "  -p, --print-parsed-lower-level-config-cover    Do not listen for the joystick, instesad output the lower level config.\n"
           "  Example:\n"
           "  " PACKAGE " ~/.my-config-file\n"
           "\n"
           "Enjoy.\n"
           "\n"
           "This program is free software see the file MIT-LICENSE for licensing info.\n"
           "Copyright Marco Antonio F. Nogueira 2018\n"
           );
   exit(0);
}

void show_version(void) {
   printf(PACKAGE " version " VERSION "\n");
   exit(0);
}

void parse_options(int argc, char *argv[]){
  int c;
  while(1){
    static char stropts[] = "hrpv";
    static struct option long_options[] =
      {
        {"read-from-lower-level-config", no_argument, 0, 'r'},
        {"print-parsed-lower-level-config",  no_argument, 0, 'p'},
        {"help",    no_argument, 0, 'h'},
        {"version",    no_argument, 0, 'v'},
        {0, 0, 0, 0}
      };
    int option_index = 0;

    c = getopt_long (argc, argv, stropts,
                     long_options, &option_index);
    switch (c) {
    case 'r':
      read_lower_level_config_file = 1;
      break;
    case 'p':
      print_parsed_lower_level_config = 1;
      break;
    case 'h':
      show_usage();
    case 'v':
      show_version();
    }

    if (c == -1)
      break;
  }
}


