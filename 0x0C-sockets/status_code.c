#include "socket.h"

/**
 * get_1xx_3xx - Get the response according to status_code
 * @status_code: Status code to evaluate
 *
 * Return: String representation of the response
 */
char *get_1xx_3xx(const int status_code)
{
	switch (status_code)
	{
	case 100: return ("Continue");
	case 101: return ("Switching Protocols");
	case 102: return ("Processing");
	case 103: return ("Early Hints");
	case 200: return ("OK");
	case 201: return ("Created");
	case 202: return ("Accepted");
	case 203: return ("Non-Authoritative Information");
	case 204: return ("No Content");
	case 205: return ("Reset Content");
	case 206: return ("Partial Content");
	case 207: return ("Multi-Status");
	case 208: return ("Already Reported");
	case 226: return ("IM Used");
	case 300: return ("Multiple Choices");
	case 301: return ("Moved Permanently");
	case 302: return ("Found");
	case 303: return ("See Other");
	case 304: return ("Not Modified");
	case 305: return ("Use Proxy");
	case 306: return ("Switch Proxy"); /* no longer used */
	case 307: return ("Temporary Redirect");
	case 308: return ("Permanent Redirect");
	default: return ("Unknown Status Code");
	};
}

/**
 * get_4xx - Get the response according to status_code
 * @status_code: Status code to evaluate
 *
 * Return: String representation of the response
 */
char *get_4xx(const int status_code)
{
	switch (status_code)
	{
	case 400: return ("Bad Request");
	case 401: return ("Unauthorized");
	case 402: return ("Payment Required");
	case 403: return ("Forbidden");
	case 404: return ("Not Found");
	case 405: return ("Method Not Allowed");
	case 406: return ("Not Acceptable");
	case 407: return ("Proxy Authentication Required");
	case 408: return ("Request Timeout");
	case 409: return ("Conflict");
	case 410: return ("Gone");
	case 411: return ("Length Required");
	case 412: return ("Precondition Failed");
	case 413: return ("Payload Too Large");
	case 414: return ("URI Too Long");
	case 415: return ("Unsupported Media Type");
	case 416: return ("Range Not Satisfiable");
	case 417: return ("Expectation Failed");
	case 418: return ("I'm a teapot"); /* RFC 2324 Easter Egg */
	case 421: return ("Misdirected Request");
	case 422: return ("Unprocessable Entity");
	case 423: return ("Locked");
	case 424: return ("Failed Dependency");
	case 425: return ("Too Early");
	case 426: return ("Upgrade Required");
	case 428: return ("Precondition Required");
	case 429: return ("Too Many Requests");
	case 431: return ("Request Header Fields Too Large");
	case 451: return ("Unavailable For Legal Reasons");
	default: return ("Unknown Status Code");
	};
}

/**
 * get_5xx - Get the response according to status_code
 * @status_code: Status code to evaluate
 *
 * Return: String representation of the response
 */
char *get_5xx(const int status_code)
{
	switch (status_code)
	{
	case 500: return ("Internal Server Error");
	case 501: return ("Not Implemented");
	case 502: return ("Bad Gateway");
	case 503: return ("Service Unavailable");
	case 504: return ("Gateway Timeout");
	case 505: return ("HTTP Version Not Supported");
	case 506: return ("Variant Also Negotiates");
	case 507: return ("Insufficient Storage");
	case 508: return ("Loop Detected");
	case 510: return ("Not Extended");
	case 511: return ("Network Authentication Required");
	default: return ("Unknown Status Code");
	};
}

/**
 * get_response - Identifies the status code range
 * @status_code: Status code to evaluate
 *
 * Return: String representation of the response
 */
char *get_response(const int status_code)
{
	if (status_code < 400)
		return (get_1xx_3xx(status_code));
	else if (status_code < 500)
		return (get_4xx(status_code));
	return (get_5xx(status_code));
}

/**
 * http_response - Validates the response and send it to the client
 * @status_code: Status code to evaluate
 *
 * Return: EXIT_SUCCESS if successful otherwise EXIT_FAILURE
 */
int http_response(const int status_code)
{
	char *http = "HTTP/1.1";
	char *cl = "Content-Length: ";
	char *ct = "Content-Type: application/json";
	int len = strlen(http) + 3 + strlen(cl) + strlen(ct) + 1;
	char *response = NULL;
	char *buf;

	response = get_response(status_code);
	buf = malloc(sizeof(char) * (strlen(response) + strlen(ram_json[id - 1])));
	if (status_code == 201)
	{
		sprintf(buf, "%s %d %s" CRLF "Content-Length: %lu"
		CRLF "Content-Type: application/json" CRLF CRLF "%s",
		http, status_code, response, strlen(buf), ram_json[id - 1]);
	}
	else
		sprintf(buf, "%s %d %s" CRLF CRLF, http, status_code, response);
	send(client_fd, buf, strlen(buf), 0);
	if (client_fd != -1 && close(client_fd) == -1)
	{
		fprintf(stderr, "close client error\n");
		return (EXIT_FAILURE);
	}
	client_fd = -1;
	free(buf);
	return (EXIT_SUCCESS);
}
