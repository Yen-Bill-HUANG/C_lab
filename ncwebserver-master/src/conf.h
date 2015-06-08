#ifndef NCWEBSERVER_CONF_H
#define NCWEBSERVER_CONF_H

#include <arpa/inet.h>

/**
 * The configuration variables of a nc web server. 
 * 
 * The bind address, which binds to all interfaces
 * by default, can be set to bind the server to a specific
 * interface, such as eth0 or lo0.
 *
 * The bind port, which binds to a random, unused port
 * by default, can be set to bind the server to a specific
 * port number. You will need to run the server with
 * administrative priviliedges to bind to a restricted port.
 *
 * The webroot defines the path to root for the HTTP server.
 */
struct ncwebserver_conf_t {
    struct in_addr addr;
    unsigned short int port;
    char webroot[1024];
};

#endif