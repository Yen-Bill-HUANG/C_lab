#include <stdio.h>
#include <string.h>
#include "http.h"

void
ncwebserver_http_build_response_header(char *buf,
                                       size_t buflen,
                                       struct ncwebserver_http_response_header_t *hdr)
{
    char tmp[1024];

    memset(buf, 0, buflen);
    strncat(buf, "HTTP/1.1 ", buflen - strlen(buf) - 1);

    snprintf(tmp, sizeof(tmp), "%u %s", hdr->status_code, "");
    strncat(buf, tmp, buflen - strlen(buf) - 1);
    strncat(buf, "\n", buflen - strlen(buf) - 1);

    snprintf(tmp, sizeof(tmp), "Content-length: %llu", hdr->content_length);
    strncat(buf, tmp, buflen - strlen(buf) - 1);
    strncat(buf, "\n", buflen - strlen(buf) - 1);

    snprintf(tmp, sizeof(tmp), "Content-type: %s", "text/html");
    strncat(buf, "\n", buflen - strlen(buf) - 1);
}

void
ncwebserver_http_parse_request(char *buf,
                                size_t buflen,
                                struct ncwebserver_http_request_t *req)
{
    char *token;

    // Get the HTTP verb from the HTTP request.
    token = strtok(buf, " ");

    if (strcmp(token, "GET") == 0) {
        req->header.verb = NCWEBSERVER_HTTP_GET;
    } else if (strcmp(token, "HEAD") == 0) {
        req->header.verb = NCWEBSERVER_HTTP_HEAD;
    } else if (strcmp(token, "POST") == 0) {
        req->header.verb = NCWEBSERVER_HTTP_POST;
    } else if (strcmp(token, "PUT") == 0) {
        req->header.verb = NCWEBSERVER_HTTP_PUT;
    } else if (strcmp(token, "DELETE") == 0) {
        req->header.verb = NCWEBSERVER_HTTP_DELETE;
    } else {
        req->header.verb = NCWEBSERVER_HTTP_UNKNOWN;
    }

    // Get the resource from the HTTP request.
    token = strtok(NULL, " ");
    strncpy(req->header.resource, token, sizeof(req->header.resource));

    token = strtok(NULL, " ");
    strncpy(req->header.protocol, token, sizeof(req->header.protocol));
}