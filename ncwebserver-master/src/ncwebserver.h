#ifndef NCWEBSERVER_SERVER_H
#define NCWEBSERVER_SERVER_H

#include "conf.h"

// The default web root if no web root is present
// in the configuration variables.
//
// For example, if a sysadmin boots the webserver 
// with no arguments, the server takes the webroot
// as the DEFAULT_WEBROOT in the current working dir.
#define DEFAULT_WEBROOT "www"

// The default index file.
//
// For example, if a client requests 'GET /', the 
// server rewrites the resource '/' to 'index.html'
// and prepends the webroot.
#define INDEX_FILE "index.html"

// The maximum number of pending connections before
// incoming connections are refused with ECONNREFUSED.
#define MAX_PENDING_CONNECTIONS 100

/**
 * An instance of a nc web server.
 * 
 * The sockfd is the socket file descriptor for
 * the server's listening connection. The file
 * descriptor is required for the accept(), close()
 * and other syscalls.
 *
 * The sockaddr is the bound address and port number of
 * the server.
 *
 * The webroot defines the path to root for the HTTP server.
 */
struct ncwebserver_t {
    int sockfd;
    struct sockaddr_in addr;
    char webroot[1024];
};

/**
 * Handle the request and respond to an accepted client.
 *
 * @param server   The simpleserver that received the connection.
 * @param clientfd The file descriptor of the client connection.
 */
void
ncwebserver_do(struct ncwebserver_t *server,
                int clientfd);

/**
 * Initializes the server.
 *
 * @param server The simpleserver to initialize.
 * @param conf   The configuration to initialize with.
 */
void
ncwebserver_init(struct ncwebserver_t *server,
                  struct ncwebserver_conf_t *conf);

/**
 * Starts the simpleserver.
 *
 * @param server The simpleserver to start.
 */
void
ncwebserver_start(struct ncwebserver_t *server);

/**
 * Prints the address and port listening on.
 *
 * @param addr The address of the socket.
 */
void
ncwebserver_pprint_conn(const struct ncwebserver_t *server);

#endif