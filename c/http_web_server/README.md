# 🌐 HTTP Web Server with Berkeley Sockets

Today I rebuilt and earlier attempt at a HTTP web server from scratch using C and Berkeley sockets! Hopefully it now better represents better quality low-level network programming.

## What you'll see

When you run this server, you'll get a fully functional web server with:
- **Cyberpunk-themed web interface** with neon colors and gradients
- **Multiple interactive pages** - main server info, source code viewer, and 404 error demo
- **Real HTTP request/response handling** - your browser actually talks to the C program!
- **Berkeley sockets implementation** - the same networking foundation used by real web servers

The coolest part is watching the terminal output as your browser makes requests - you can see the actual HTTP parsing happening in real-time!

## How to run this

```bash
cd c/http_web_server

# Build the server
make

# Start the server (runs on port 53557)
./server

# Visit in your browser
http://127.0.0.1:53557
```

The server will show you live connection logs in the terminal while serving the web interface!

## How it works

This implements the complete Berkeley sockets workflow that real web servers use:

1. **Create Socket** - `socket(AF_INET, SOCK_STREAM, 0)` creates the network endpoint
2. **Bind to Port** - `bind()` attaches the socket to port 53557
3. **Listen for Connections** - `listen()` starts accepting incoming requests
4. **Accept Clients** - `accept()` handles each browser connection
5. **Parse HTTP Requests** - Extract the URL path from browser requests
6. **Send HTML Responses** - Return the cyberpunk-styled web pages
7. **Clean Up** - Close connections and handle graceful shutdown

The server handles multiple routes: `/` (main page), `/code` (source viewer), and any other path triggers a 404 error page.

## Try changing this

- **Port number** (line 10): Change `#define PORT 53557` to any port you want
- **Buffer size** (line 11): Adjust `BUFFER_SIZE` for larger/smaller requests
- **Cyberpunk colors** (lines 30-60): Modify the neon color scheme in the CSS
- **Add new routes** (lines 578-597): Add more pages by extending the `send_response()` function
- **Server title** (line 196): Change "HTTP WEB SERVER ONLINE" to your own branding
- **Code content** (lines 369-553): Update the source code viewer with different functions

## What I learned

Building this web server was a huge leap in my C programming journey! I learned:

- **Berkeley Sockets API** - The foundation of all internet communication, from basic `socket()` calls to handling multiple connections
- **HTTP Protocol** - How browsers actually communicate with servers, parsing request headers and sending proper responses
- **Network Programming** - Understanding TCP/IP, port binding, and client-server architecture
- **Memory Management** - Handling dynamic buffer allocation for HTTP requests and responses
- **Signal Handling** - Graceful server shutdown with `SIGINT` and proper resource cleanup
- **Web Development** - Creating HTML/CSS interfaces that work with C backend systems

One of the most exciting moments is when you first see the browser successfully connect to the C program - it feels like building the internet from scratch! This is exactly how real web servers work under the hood.

## Technical Details

**Architecture:**
- Single-threaded server handling one connection at a time
- Dynamic HTML content generation with embedded CSS styling
- Proper HTTP response headers and status codes
- Signal handling for clean shutdown with Ctrl+C

**Key Functions:**
- `main()` - Sets up the socket, binds to port, and runs the connection loop
- `handle_client()` - Processes individual browser connections
- `parse_request()` - Extracts URL paths from HTTP requests
- `send_response()` - Routes requests to appropriate HTML pages
- `handle_signal()` - Graceful shutdown when interrupted

**Network Concepts:**
- TCP/IP socket programming with `AF_INET` and `SOCK_STREAM`
- Network byte order conversion with `htons()`
- HTTP request parsing and response generation
- Connection lifecycle management

---

*This project represents my transition from basic C programming to building real networked applications - the foundation for understanding how the internet actually works!* 