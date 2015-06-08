#ifndef NCWEBSERVER_HTTP_H
#define NCWEBSERVER_HTTP_H

#include <sys/types.h>

#define NCWEBSERVER_HTTP_UNKNOWN                   0x0001
#define NCWEBSERVER_HTTP_GET                       0x0002
#define NCWEBSERVER_HTTP_HEAD                      0x0004
#define NCWEBSERVER_HTTP_POST                      0x0008
#define NCWEBSERVER_HTTP_PUT                       0x0010
#define NCWEBSERVER_HTTP_DELETE                    0x0020

#define NCWEBSERVER_HTTP_CONTINUE                  100
#define NCWEBSERVER_HTTP_SWITCHING_PROTOCOLS       101
#define NCWEBSERVER_HTTP_PROCESSING                102

#define NCWEBSERVER_HTTP_OK                        200
#define NCWEBSERVER_HTTP_CREATED                   201
#define NCWEBSERVER_HTTP_ACCEPTED                  202
#define NCWEBSERVER_HTTP_NO_CONTENT                204
#define NCWEBSERVER_HTTP_PARTIAL_CONTENT           206

#define NCWEBSERVER_HTTP_SPECIAL_RESPONSE          300
#define NCWEBSERVER_HTTP_MOVED_PERMANENTLY         301
#define NCWEBSERVER_HTTP_MOVED_TEMPORARILY         302
#define NCWEBSERVER_HTTP_SEE_OTHER                 303
#define NCWEBSERVER_HTTP_NOT_MODIFIED              304
#define NCWEBSERVER_HTTP_TEMPORARY_REDIRECT        307

#define NCWEBSERVER_HTTP_BAD_REQUEST               400
#define NCWEBSERVER_HTTP_UNAUTHORIZED              401
#define NCWEBSERVER_HTTP_FORBIDDEN                 403
#define NCWEBSERVER_HTTP_NOT_FOUND                 404
#define NCWEBSERVER_HTTP_NOT_ALLOWED               405
#define NCWEBSERVER_HTTP_REQUEST_TIME_OUT          408
#define NCWEBSERVER_HTTP_CONFLICT                  409
#define NCWEBSERVER_HTTP_LENGTH_REQUIRED           411
#define NCWEBSERVER_HTTP_PRECONDITION_FAILED       412
#define NCWEBSERVER_HTTP_REQUEST_ENTITY_TOO_LARGE  413
#define NCWEBSERVER_HTTP_REQUEST_URI_TOO_LARGE     414
#define NCWEBSERVER_HTTP_UNSUPPORTED_MEDIA_TYPE    415
#define NCWEBSERVER_HTTP_RANGE_NOT_SATISFIABLE     416

/**
 * The basic header of a HTTP request.
 *
 * The header features a verb, such as GET,
 * a resource, such as /index.html, and a protocol,
 * such as HTTP/1.1.
 */
struct ncwebserver_http_request_header_t {
    unsigned short int verb;
    char resource[2084];
    char protocol[32];
};

/**
 * A HTTP request has a header and content. The content
 * pointer points into the buffer.
 */
struct ncwebserver_http_request_t {
    struct ncwebserver_http_request_header_t header;
    char *content;
};

/**
 * The basic header of a HTTP response.
 *
 * The header features a status code, such as 200 OK,
 * and a content length.
 */
struct ncwebserver_http_response_header_t {
    unsigned int status_code;
    unsigned long long int content_length;
};

/**
 * A HTTP response has a header and content. The content
 * points into some buffer, such as a read file.
 */
struct ncwebserver_http_response_t {
    struct ncwebserver_http_response_header_t header;
    char *content;
};

/**
 * Builds a HTTP header string from the response.
 *
 * @param buf    The buffer to write the response header.
 * @param buflen The maximum length of the buffer.
 * @param hdr    The header object to serialize.
 */
void
ncwebserver_http_build_response_header(char *buf,
                                       size_t buflen,
                                       struct ncwebserver_http_response_header_t *hdr);

/**
 * Parses the HTTP request.
 *
 * @param buf     The buffer containing the HTTP request string.
 * @param buflen  The length of the buffer.
 * @param req     The request object.
 */
void
ncwebserver_http_parse_request(char *buf,
                                size_t buflen,
                                struct ncwebserver_http_request_t *req);


#endif