# webbclient
sends a GET request for root
You can change the location in sprintf(sendbuf, "GET / HTTP/1.1\r\n\r\n");
with etc sprintf(sendbuf, "GET /dirname/file.html HTTP/1.1\r\n\r\n");
or something along those lines.
