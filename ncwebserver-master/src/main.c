#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "conf.h"
#include "macro.h"
#include "ncwebserver.h"
#include "usage.h"

const char ncwebserver_usage_string[] = 
    "[-h] [-d web-root] [-b bind-address] [-p port]";

static void
parse_argv(int argc, char **argv, struct ncwebserver_conf_t *conf)
{
    int c;

    while ((c = getopt(argc, argv, "b:hp:d:")) != -1) {
        switch (c) {
            case 'b':
                // Check the user has specified valid IP address.
                if (inet_pton(AF_INET, optarg, &conf->addr) == 0) {
                    fprintf(stderr, "-b: please check the bind address '%s'\n", optarg);
                    exit(1);
                }
                break;
            case 'd':
                strncpy(conf->webroot, optarg, sizeof(conf->webroot));
                break;
            case 'h':
                usage(ncwebserver_usage_string);
                break;
            case 'p':
                // Check the destination port number is a valid port number
                // such that it is in the range of [0, 65535]
                if (in_range(atoi(optarg), 0, 65535) == 0) {
                    fprintf(stderr, "error: the port number '%d' must be in the range [0, 65535].\n", atoi(optarg));
                    exit(1);
                }
                conf->port = atoi(optarg);
                break;
        }
    }
}

int
main(int argc, char **argv)
{
    struct ncwebserver_t server;
    struct ncwebserver_conf_t conf;

    memset(&conf, 0, sizeof(conf));
    parse_argv(argc, argv, &conf);

    ncwebserver_init(&server, &conf);
    ncwebserver_start(&server);

    return 0;
}