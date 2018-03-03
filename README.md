# httpserver

This project is a solution to the final test at "Multithreaded  programming" course @ stepik.org (https://stepik.org/course/149).
The task is to build a simple http-server which:
*  supports HTTP 1.0
*  processes GET requests
*  supports multithreading
*  builds with cmake
*  runs in background (daemon)

Usage: ./final [-h] [-p] [-d]
*  -h - host address
*  -p - port
*  -d - root path

Example: ./final -h 127.0.0.1 -p 12345 -d /website_path