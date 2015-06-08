#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "conf.h"
#include "http.h"
#include "ncwebserver.h"
#include "usage.h"

void
ncwebserver_do(struct ncwebserver_t *server, int clientfd)
{
    int fd, ret;
    char buf[8192], filename[256];
    struct stat statbuf;
    struct ncwebserver_http_request_t req;
    struct ncwebserver_http_response_header_t hdr;
    
    recv(clientfd, buf, sizeof(buf), 0);

    ncwebserver_http_parse_request(buf, sizeof(buf), &req);

    memset(filename, '\0', sizeof(filename));
    strncat(filename, server->webroot, sizeof(filename) - 1);
    strncat(filename, req.header.resource, sizeof(filename) - strlen(filename) - 1);

    if (filename[strlen(filename) - 1] == '/') {
        strncat(filename, INDEX_FILE, sizeof(filename) - strlen(filename) - 1);
    }

    if ((fd = open(filename, O_RDONLY)) == -1) {
        hdr.status_code = NCWEBSERVER_HTTP_NOT_FOUND;
        hdr.content_length = 0;
    } else {
        fstat(fd, &statbuf);
        hdr.status_code = NCWEBSERVER_HTTP_OK;
        hdr.content_length = statbuf.st_size;
    }

    ncwebserver_http_build_response_header(buf, sizeof(buf), &hdr);
    
    // // Write the HTTP headers to the socket.
    write(clientfd, buf, strlen(buf));

    // Write the content to the socket.
    if (fd != -1) {
        while ((ret = read(fd, buf, sizeof(buf))) > 0) {
            write(clientfd, buf, strlen(buf));
        }
    }
}

void
ncwebserver_init(struct ncwebserver_t *server,
                  struct ncwebserver_conf_t *conf)
{
    socklen_t len = sizeof(server->addr);

    if ((server->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server->addr, 0, sizeof(server->addr));
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(conf->port);
    server->addr.sin_addr = conf->addr;

    if (bind(server->sockfd, (struct sockaddr *) &server->addr, sizeof(server->addr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(server->sockfd, MAX_PENDING_CONNECTIONS) == -1) {
        perror("listen");
        exit(1);
    }

    // Gets the current address and port number to which we are bound.
    if (getsockname(server->sockfd, (struct sockaddr *) &server->addr, &len)) {
        perror("getsockname");
        exit(1);
    }

    strncpy(server->webroot, conf->webroot, sizeof(server->webroot));

    if (strlen(server->webroot) == 0) {
        if ((getcwd(server->webroot, sizeof(server->webroot))) == NULL) {
            perror("cwd");
        }
        strncat(server->webroot, "/", sizeof(server->webroot) - strlen(server->webroot) - 1);
        strncat(server->webroot, DEFAULT_WEBROOT, sizeof(server->webroot) - strlen(server->webroot) - 1);
    }

    ncwebserver_pprint_conn(server);
}

void
ncwebserver_start(struct ncwebserver_t *server)
{
    int clientfd;
    socklen_t addrlen;
    struct sockaddr_in clientaddr;

    while(1) {
        addrlen = sizeof(clientaddr);
        clientfd = accept(server->sockfd, (struct sockaddr *) &clientaddr, &addrlen);
        ncwebserver_do(server, clientfd);
        close(clientfd);
    }
}

void
ncwebserver_pprint_conn(const struct ncwebserver_t *server)
{
    char addrstr[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, (struct in_addr *) &server->addr.sin_addr, addrstr, sizeof(addrstr));
    printf("Listening on %s:%d.\n", addrstr, ntohs(server->addr.sin_port));
}