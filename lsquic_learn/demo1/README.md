# Usage

## All options
```bash
sh$ ./tut -h
Usage: tut [-c cert -k key] [options] IP port

   -c cert.file    Certificate.
   -k key.file     Key file.
   -f log.file     Log message to this log file.  If not specified, the
                     are printed to stderr.
   -L level        Set library-wide log level.  Defaults to 'warn'.
   -l module=level Set log level of specific module.  Several of these
                     can be specified via multiple -l flags or by combining
                     these with comma, e.g. -l event=debug,conn=info.
   -v              Verbose: log program messages as well.
   -b VERSION      Use callbacks version VERSION.
   -p VERSION      Use packets_out version VERSION.
   -w VERSION      Use server write callback version VERSION.
   -o opt=val      Set lsquic engine setting to some value, overriding the
                     defaults.  For example,
                           -o version=ff00001c -o cc_algo=2
   -G DIR          Log TLS secrets to a file in directory DIR.
   -h              Print this help screen and exit.
```

## Running the server
Both client and server logic are contained in the `tut` program.  It knows it is meant to run in the server
mode when `-c` and `-k` options are specified:

```bash
sh$ ./tut -c mycert-cert.pem -k mycert-key.pem ::0 12345 -p 1 -L debug -f server.log
```

The server can select one of two versions of "on stream write" callbacks.  Use `-w` command-line option for that.

## Running the client
```bash
sh$ ./tut ::1 12345 -L debug -f client.log
Hello!
!olleH
^D
sh$
```

The server can select one of three versions of "on stream read" callbacks.  Use `-b` command-line option for that.

Both client and server can use the `-p` option to select one of two "send packets out" callbacks.

# HTTP/3 Client
As a bonus, a simple [HTTP/3](https://en.wikipedia.org/wiki/HTTP/3) client is provided.  Example:

```bash
sh$ ./h3cli -M HEAD www.litespeedtech.com 443 /
HTTP/1.1 200 OK
x-powered-by: PHP/7.3.5
x-logged-in: False
x-content-powered-by: K2 v2.7.1 (by JoomlaWorks)
content-type: text/html; charset=utf-8
expires: Wed, 17 Aug 2005 00:00:00 GMT
last-modified: Wed, 12 Aug 2020 18:54:05 GMT
cache-control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0
pragma: no-cache
etag: "23485-1597258445;gz"
vary: Accept-Encoding
x-frame-options: SAMEORIGIN
x-lsadc-cache: hit
date: Thu, 13 Aug 2020 02:48:06 GMT
server: LiteSpeed
```
