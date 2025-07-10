#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT 53557
#define BUFFER_SIZE 1024
#define MAX_CONNECTIONS 10

// Global server socket for cleanup
int server_socket = -1;

// Simple HTTP response template
const char* HTTP_200_HEADER = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
const char* HTTP_404_HEADER = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";

// HTML pages stored as strings for simplicity
const char* HOME_PAGE = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "    <title>C HTTP Server</title>\n"
    "    <style>\n"
    "        * { margin: 0; padding: 0; box-sizing: border-box; }\n"
    "        body { \n"
    "            font-family: 'Courier New', monospace; \n"
    "            background: linear-gradient(135deg, #0a0a0a 0%, #1a1a2e 50%, #16213e 100%);\n"
    "            color: #00ff41;\n"
    "            min-height: 100vh;\n"
    "            padding: 20px;\n"
    "            background-attachment: fixed;\n"
    "        }\n"
    "        .container { max-width: 1000px; margin: 0 auto; }\n"
    "        .header { \n"
    "            background: linear-gradient(45deg, #ff006e, #8338ec, #3a86ff);\n"
    "            padding: 30px;\n"
    "            border-radius: 15px;\n"
    "            text-align: center;\n"
    "            box-shadow: 0 0 30px rgba(255, 0, 110, 0.3);\n"
    "            border: 2px solid #00ff41;\n"
    "            margin-bottom: 30px;\n"
    "        }\n"
    "        .header h1 { \n"
    "            font-size: 3em;\n"
    "            color: #fff;\n"
    "            text-shadow: 0 0 10px #00ff41;\n"
    "            margin-bottom: 10px;\n"
    "        }\n"
    "        .header p { \n"
    "            font-size: 1.2em;\n"
    "            color: #fff;\n"
    "            text-shadow: 0 0 5px #8338ec;\n"
    "        }\n"
    "        .content { \n"
    "            background: rgba(0, 0, 0, 0.8);\n"
    "            padding: 30px;\n"
    "            border-radius: 15px;\n"
    "            border: 2px solid #8338ec;\n"
    "            box-shadow: 0 0 20px rgba(131, 56, 236, 0.2);\n"
    "            margin-bottom: 30px;\n"
    "        }\n"
    "        .content h2 { \n"
    "            color: #ff006e;\n"
    "            font-size: 2.5em;\n"
    "            margin-bottom: 20px;\n"
    "            text-shadow: 0 0 10px #ff006e;\n"
    "        }\n"
    "        .content h3 { \n"
    "            color: #3a86ff;\n"
    "            font-size: 1.8em;\n"
    "            margin: 25px 0 15px 0;\n"
    "            text-shadow: 0 0 8px #3a86ff;\n"
    "        }\n"
    "        .content p { \n"
    "            font-size: 1.1em;\n"
    "            line-height: 1.6;\n"
    "            margin-bottom: 20px;\n"
    "            color: #00ff41;\n"
    "        }\n"
    "        .tech-list { \n"
    "            display: grid;\n"
    "            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));\n"
    "            gap: 15px;\n"
    "            margin: 20px 0;\n"
    "        }\n"
    "        .tech-item { \n"
    "            background: rgba(255, 0, 110, 0.1);\n"
    "            padding: 15px;\n"
    "            border-radius: 10px;\n"
    "            border: 1px solid #ff006e;\n"
    "            text-align: center;\n"
    "        }\n"
    "        .tech-item strong { \n"
    "            color: #ff006e;\n"
    "            display: block;\n"
    "            margin-bottom: 5px;\n"
    "        }\n"
    "        .steps { \n"
    "            background: rgba(58, 134, 255, 0.1);\n"
    "            padding: 20px;\n"
    "            border-radius: 10px;\n"
    "            border: 1px solid #3a86ff;\n"
    "            margin: 20px 0;\n"
    "        }\n"
    "        .step { \n"
    "            padding: 10px;\n"
    "            margin: 10px 0;\n"
    "            background: rgba(0, 0, 0, 0.5);\n"
    "            border-radius: 5px;\n"
    "            border-left: 4px solid #00ff41;\n"
    "        }\n"
    "        .step-number { \n"
    "            color: #8338ec;\n"
    "            font-weight: bold;\n"
    "            display: inline-block;\n"
    "            width: 30px;\n"
    "        }\n"
    "        .code { \n"
    "            background: rgba(0, 0, 0, 0.8);\n"
    "            color: #00ff41;\n"
    "            padding: 5px 10px;\n"
    "            border-radius: 5px;\n"
    "            font-family: 'Courier New', monospace;\n"
    "            border: 1px solid #00ff41;\n"
    "            display: inline-block;\n"
    "            margin: 0 5px;\n"
    "        }\n"
    "        .status-grid { \n"
    "            display: grid;\n"
    "            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));\n"
    "            gap: 20px;\n"
    "            margin: 20px 0;\n"
    "        }\n"
    "        .status-card { \n"
    "            background: rgba(131, 56, 236, 0.1);\n"
    "            padding: 20px;\n"
    "            border-radius: 10px;\n"
    "            border: 2px solid #8338ec;\n"
    "            text-align: center;\n"
    "        }\n"
    "        .status-card h4 { \n"
    "            color: #8338ec;\n"
    "            margin-bottom: 10px;\n"
    "            font-size: 1.2em;\n"
    "        }\n"
    "        .status-value { \n"
    "            color: #00ff41;\n"
    "            font-size: 1.5em;\n"
    "            font-weight: bold;\n"
    "        }\n"
    "        .demo-link { \n"
    "            display: inline-block;\n"
    "            background: linear-gradient(45deg, #ff006e, #8338ec);\n"
    "            color: white;\n"
    "            padding: 15px 30px;\n"
    "            border-radius: 25px;\n"
    "            text-decoration: none;\n"
    "            font-size: 1.2em;\n"
    "            font-weight: bold;\n"
    "            margin: 20px 0;\n"
    "            box-shadow: 0 0 20px rgba(255, 0, 110, 0.5);\n"
    "            transition: all 0.3s ease;\n"
    "        }\n"
            "        .demo-link:hover { \n"
        "            transform: translateY(-2px);\n"
        "            box-shadow: 0 0 30px rgba(255, 0, 110, 0.8);\n"
        "        }\n"
        "        .demo-buttons { \n"
        "            display: flex;\n"
        "            gap: 20px;\n"
        "            justify-content: center;\n"
        "            flex-wrap: wrap;\n"
        "        }\n"
        "        .main-title { \n"
        "            display: flex;\n"
        "            justify-content: space-between;\n"
        "            align-items: center;\n"
        "            margin-bottom: 20px;\n"
        "        }\n"
        "        .branding { \n"
        "            color: #8338ec;\n"
        "            font-size: 1.2em;\n"
        "            font-weight: bold;\n"
        "            text-shadow: 0 0 5px #8338ec;\n"
        "        }\n"
    "    </style>\n"
    "</head>\n"
    "<body>\n"
    "    <div class=\"container\">\n"
    "        <div class=\"content\">\n"
    "            <div class=\"main-title\">\n"
    "                <h2>HTTP WEB SERVER ONLINE</h2>\n"
    "                <span class=\"branding\"></span>\n"
    "            </div>\n"
    "            <p>This is a simple web server written in C using Berkeley sockets for network programming. Experience the power of low-level network programming with a cyberpunk aesthetic.</p>\n"
    "            \n"
    "            <h3>TECHNICAL SPECIFICATIONS</h3>\n"
    "            <div class=\"tech-list\">\n"
    "                <div class=\"tech-item\">\n"
    "                    <strong>Berkeley Sockets</strong>\n"
    "                    Standard Unix socket API\n"
    "                </div>\n"
    "                <div class=\"tech-item\">\n"
    "                    <strong>TCP/IP</strong>\n"
    "                    Reliable connection protocol\n"
    "                </div>\n"
    "                <div class=\"tech-item\">\n"
    "                    <strong>HTTP/1.1</strong>\n"
    "                    Request/response handling\n"
    "                </div>\n"
    "                <div class=\"tech-item\">\n"
    "                    <strong>Signal Handling</strong>\n"
    "                    Graceful shutdown system\n"
    "                </div>\n"
    "            </div>\n"
    "            \n"
    "            <h3>SYSTEM ARCHITECTURE</h3>\n"
    "            <div class=\"steps\">\n"
    "                <div class=\"step\">\n"
    "                    <span class=\"step-number\">1.</span>\n"
    "                    Create socket using <span class=\"code\">socket()</span>\n"
    "                </div>\n"
    "                <div class=\"step\">\n"
    "                    <span class=\"step-number\">2.</span>\n"
    "                    Bind to port 8080 using <span class=\"code\">bind()</span>\n"
    "                </div>\n"
    "                <div class=\"step\">\n"
    "                    <span class=\"step-number\">3.</span>\n"
    "                    Listen for connections using <span class=\"code\">listen()</span>\n"
    "                </div>\n"
    "                <div class=\"step\">\n"
    "                    <span class=\"step-number\">4.</span>\n"
    "                    Accept clients using <span class=\"code\">accept()</span>\n"
    "                </div>\n"
    "                <div class=\"step\">\n"
    "                    <span class=\"step-number\">5.</span>\n"
    "                    Parse HTTP requests and send responses\n"
    "                </div>\n"
    "            </div>\n"
    "            \n"
    "            <h3>SERVER STATUS</h3>\n"
    "            <div class=\"status-grid\">\n"
    "                <div class=\"status-card\">\n"
    "                    <h4>Port</h4>\n"
    "                    <div class=\"status-value\">8080</div>\n"
    "                </div>\n"
    "                <div class=\"status-card\">\n"
    "                    <h4>Protocol</h4>\n"
    "                    <div class=\"status-value\">HTTP/1.1</div>\n"
    "                </div>\n"
    "                <div class=\"status-card\">\n"
    "                    <h4>Socket Type</h4>\n"
    "                    <div class=\"status-value\">TCP</div>\n"
    "                </div>\n"
    "                <div class=\"status-card\">\n"
    "                    <h4>Max Connections</h4>\n"
    "                    <div class=\"status-value\">10</div>\n"
    "                </div>\n"
    "            </div>\n"
    "            \n"
    "            <h3>DEMO ZONE</h3>\n"
    "            <p>Test the server's capabilities:</p>\n"
    "            <div class=\"demo-buttons\">\n"
    "                <a href=\"/code\" class=\"demo-link\">VIEW SOURCE CODE</a>\n"
    "                <a href=\"/nonexistent\" class=\"demo-link\">TRIGGER 404 ERROR</a>\n"
    "            </div>\n"
    "        </div>\n"
    "    </div>\n"
    "</body>\n"
    "</html>";

const char* NOT_FOUND_PAGE = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "    <title>404 Not Found - C HTTP Server</title>\n"
    "    <style>\n"
    "        * { margin: 0; padding: 0; box-sizing: border-box; }\n"
    "        body { \n"
    "            font-family: 'Courier New', monospace; \n"
    "            background: linear-gradient(135deg, #0a0a0a 0%, #1a1a2e 50%, #16213e 100%);\n"
    "            color: #00ff41;\n"
    "            min-height: 100vh;\n"
    "            display: flex;\n"
    "            align-items: center;\n"
    "            justify-content: center;\n"
    "            padding: 20px;\n"
    "            background-attachment: fixed;\n"
    "        }\n"
    "        .container { \n"
    "            text-align: center;\n"
    "            max-width: 600px;\n"
    "        }\n"
    "        .error-header { \n"
    "            background: linear-gradient(45deg, #ff006e, #8338ec);\n"
    "            padding: 40px;\n"
    "            border-radius: 15px;\n"
    "            text-align: center;\n"
    "            box-shadow: 0 0 30px rgba(255, 0, 110, 0.3);\n"
    "            border: 2px solid #ff006e;\n"
    "            margin-bottom: 30px;\n"
    "        }\n"
    "        .error-code { \n"
    "            font-size: 4em;\n"
    "            color: #fff;\n"
    "            text-shadow: 0 0 20px #ff006e;\n"
    "            margin-bottom: 10px;\n"
    "        }\n"
    "        .error-title { \n"
    "            font-size: 2em;\n"
    "            color: #fff;\n"
    "            text-shadow: 0 0 10px #8338ec;\n"
    "        }\n"
    "        .error-content { \n"
    "            background: rgba(0, 0, 0, 0.8);\n"
    "            padding: 30px;\n"
    "            border-radius: 15px;\n"
    "            border: 2px solid #8338ec;\n"
    "            box-shadow: 0 0 20px rgba(131, 56, 236, 0.2);\n"
    "            margin-bottom: 30px;\n"
    "        }\n"
    "        .error-message { \n"
    "            font-size: 1.3em;\n"
    "            color: #00ff41;\n"
    "            margin-bottom: 30px;\n"
    "            line-height: 1.6;\n"
    "        }\n"
    "        .back-link { \n"
    "            display: inline-block;\n"
    "            background: linear-gradient(45deg, #00ff41, #3a86ff);\n"
    "            color: #000;\n"
    "            padding: 15px 30px;\n"
    "            border-radius: 25px;\n"
    "            text-decoration: none;\n"
    "            font-size: 1.2em;\n"
    "            font-weight: bold;\n"
    "            margin: 20px 0;\n"
    "            box-shadow: 0 0 20px rgba(0, 255, 65, 0.5);\n"
    "            transition: all 0.3s ease;\n"
    "        }\n"
            "        .back-link:hover { \n"
        "            transform: translateY(-2px);\n"
        "            box-shadow: 0 0 30px rgba(0, 255, 65, 0.8);\n"
        "        }\n"
    "    </style>\n"
    "</head>\n"
    "<body>\n"
    "    <div class=\"container\">\n"
    "        <div class=\"error-header\">\n"
    "            <div class=\"error-code\">404</div>\n"
    "            <div class=\"error-title\">ACCESS DENIED</div>\n"
    "        </div>\n"
    "        \n"
            "        <div class=\"error-content\">\n"
        "            <div class=\"error-message\">\n"
        "                RESOURCE NOT FOUND<br>\n"
        "                The requested endpoint does not exist on this server.\n"
        "            </div>\n"
        "            <a href=\"/\" class=\"back-link\">RETURN TO BASE</a>\n"
        "        </div>\n"
    "    </div>\n"
    "</body>\n"
    "</html>";

const char* CODE_PAGE = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "    <title>Source Code - HTTP Server</title>\n"
    "    <style>\n"
    "        * { margin: 0; padding: 0; box-sizing: border-box; }\n"
    "        body { \n"
    "            font-family: 'Courier New', monospace; \n"
    "            background: linear-gradient(135deg, #0a0a0a 0%, #1a1a2e 50%, #16213e 100%);\n"
    "            color: #00ff41;\n"
    "            min-height: 100vh;\n"
    "            padding: 20px;\n"
    "            background-attachment: fixed;\n"
    "        }\n"
    "        .container { max-width: 1000px; margin: 0 auto; }\n"
    "        .content { \n"
    "            background: rgba(0, 0, 0, 0.8);\n"
    "            padding: 30px;\n"
    "            border-radius: 15px;\n"
    "            border: 2px solid #8338ec;\n"
    "            box-shadow: 0 0 20px rgba(131, 56, 236, 0.2);\n"
    "            margin-bottom: 30px;\n"
    "        }\n"
    "        .main-title { \n"
    "            display: flex;\n"
    "            justify-content: space-between;\n"
    "            align-items: center;\n"
    "            margin-bottom: 20px;\n"
    "        }\n"
    "        .main-title h2 { \n"
    "            color: #ff006e;\n"
    "            font-size: 2.5em;\n"
    "            margin-bottom: 20px;\n"
    "            text-shadow: 0 0 10px #ff006e;\n"
    "        }\n"
    "        .branding { \n"
    "            color: #8338ec;\n"
    "            font-size: 1.2em;\n"
    "            font-weight: bold;\n"
    "            text-shadow: 0 0 5px #8338ec;\n"
    "        }\n"
    "        .content h3 { \n"
    "            color: #3a86ff;\n"
    "            font-size: 1.8em;\n"
    "            margin: 25px 0 15px 0;\n"
    "            text-shadow: 0 0 8px #3a86ff;\n"
    "        }\n"
    "        .content p { \n"
    "            font-size: 1.1em;\n"
    "            line-height: 1.6;\n"
    "            margin-bottom: 20px;\n"
    "            color: #00ff41;\n"
    "        }\n"
    "        .code-block { \n"
    "            background: rgba(0, 0, 0, 0.9);\n"
    "            border: 2px solid #00ff41;\n"
    "            border-radius: 10px;\n"
    "            padding: 20px;\n"
    "            margin: 20px 0;\n"
    "            font-size: 14px;\n"
    "            line-height: 1.4;\n"
    "            color: #00ff41;\n"
    "            white-space: pre-wrap;\n"
    "        }\n"
    "        .demo-buttons { \n"
    "            display: flex;\n"
    "            gap: 20px;\n"
    "            justify-content: center;\n"
    "            flex-wrap: wrap;\n"
    "        }\n"
    "        .demo-link { \n"
    "            display: inline-block;\n"
    "            background: linear-gradient(45deg, #ff006e, #8338ec);\n"
    "            color: white;\n"
    "            padding: 15px 30px;\n"
    "            border-radius: 25px;\n"
    "            text-decoration: none;\n"
    "            font-size: 1.2em;\n"
    "            font-weight: bold;\n"
    "            margin: 20px 0;\n"
    "            box-shadow: 0 0 20px rgba(255, 0, 110, 0.5);\n"
    "            transition: all 0.3s ease;\n"
    "        }\n"
    "        .demo-link:hover { \n"
    "            transform: translateY(-2px);\n"
    "            box-shadow: 0 0 30px rgba(255, 0, 110, 0.8);\n"
    "        }\n"
    "    </style>\n"
    "</head>\n"
    "<body>\n"
    "    <div class=\"container\">\n"
    "        <div class=\"content\">\n"
    "            <div class=\"main-title\">\n"
    "                <h2>SOURCE CODE VIEWER</h2>\n"
    "                <span class=\"branding\"></span>\n"
    "            </div>\n"
    "            <p>Berkeley sockets implementation showing the core networking functions from server.c</p>\n"
    "            \n"
    "            <h3>CORE NETWORKING FUNCTIONS</h3>\n"
    "            <div class=\"code-block\">\n"
    "// Signal handler for graceful shutdown\n"
    "void handle_signal(int signal) {\n"
    "    printf(\"\\nReceived signal %d, shutting down server...\\n\", signal);\n"
    "    if (server_socket != -1) {\n"
    "        close(server_socket);\n"
    "    }\n"
    "    printf(\"Server stopped successfully!\\n\");\n"
    "    exit(0);\n"
    "}\n"
    "\n"
    "// Parse the HTTP request to extract the path\n"
    "void parse_request(const char* request, char* path) {\n"
    "    char method[10];\n"
    "    char protocol[10];\n"
    "    sscanf(request, \"%s %s %s\", method, path, protocol);\n"
    "    printf(\"Request: %s %s\\n\", method, path);\n"
    "}\n"
    "\n"
    "// Handle a single client connection\n"
    "void handle_client(int client_socket) {\n"
    "    char buffer[BUFFER_SIZE];\n"
    "    char path[256];\n"
    "    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);\n"
    "    if (bytes_received > 0) {\n"
    "        buffer[bytes_received] = '\\0';\n"
    "        parse_request(buffer, path);\n"
    "        send_response(client_socket, path);\n"
    "    }\n"
    "    close(client_socket);\n"
    "    printf(\"Client disconnected\\n\");\n"
    "}\n"
    "\n"
    "// Main server loop with Berkeley sockets\n"
    "int main() {\n"
    "    // Step 1: Create a socket\n"
    "    server_socket = socket(AF_INET, SOCK_STREAM, 0);\n"
    "    if (server_socket == -1) {\n"
    "        perror(\"Failed to create socket\");\n"
    "        exit(1);\n"
    "    }\n"
    "\n"
    "    // Step 2: Set up server address structure\n"
    "    struct sockaddr_in server_addr;\n"
    "    server_addr.sin_family = AF_INET;\n"
    "    server_addr.sin_addr.s_addr = INADDR_ANY;\n"
    "    server_addr.sin_port = htons(PORT);\n"
    "\n"
    "    // Step 3: Bind socket to address and port\n"
    "    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {\n"
    "        perror(\"Failed to bind socket\");\n"
    "        exit(1);\n"
    "    }\n"
    "\n"
    "    // Step 4: Start listening for connections\n"
    "    if (listen(server_socket, MAX_CONNECTIONS) < 0) {\n"
    "        perror(\"Failed to listen on socket\");\n"
    "        exit(1);\n"
    "    }\n"
    "\n"
    "    // Step 5: Accept connections in a loop\n"
    "    while (1) {\n"
    "        struct sockaddr_in client_addr;\n"
    "        socklen_t client_len = sizeof(client_addr);\n"
    "        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);\n"
    "        if (client_socket < 0) {\n"
    "            perror(\"Failed to accept connection\");\n"
    "            continue;\n"
    "        }\n"
    "        handle_client(client_socket);\n"
    "    }\n"
    "    close(server_socket);\n"
    "    return 0;\n"
    "}\n"
    "            </div>\n"
    "            \n"
    "            <h3>DEMO ZONE</h3>\n"
    "            <p>Navigate back to the main server:</p>\n"
    "            <div class=\"demo-buttons\">\n"
    "                <a href=\"/\" class=\"demo-link\">RETURN TO BASE</a>\n"
    "            </div>\n"
    "        </div>\n"
    "    </div>\n"
    "</body>\n"
    "</html>";

// Signal handler for graceful shutdown
void handle_signal(int signal) {
    printf("\nReceived signal %d, shutting down server...\n", signal);
    if (server_socket != -1) {
        close(server_socket);
    }
    printf("Server stopped successfully!\n");
    exit(0);
}

// Parse the HTTP request to extract the path
void parse_request(const char* request, char* path) {
    // Look for "GET /path HTTP/1.1" pattern
    char method[10];
    char protocol[10];
    
    // Parse the first line: METHOD PATH PROTOCOL
    sscanf(request, "%s %s %s", method, path, protocol);
    
    printf("Request: %s %s\n", method, path);
}

// Send HTTP response based on the requested path
void send_response(int client_socket, const char* path) {
    char response[16384];  // Buffer for complete response (increased for code page)
    
    // Route the request to appropriate page
    if (strcmp(path, "/") == 0) {
        // Home page
        sprintf(response, "%s%s", HTTP_200_HEADER, HOME_PAGE);
    } else if (strcmp(path, "/code") == 0) {
        // Code viewer page
        sprintf(response, "%s%s", HTTP_200_HEADER, CODE_PAGE);
    } else {
        // 404 Not Found
        sprintf(response, "%s%s", HTTP_404_HEADER, NOT_FOUND_PAGE);
    }
    
    // Send the complete response
    send(client_socket, response, strlen(response), 0);
    printf("Sent response for %s\n", path);
}

// Handle a single client connection
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    char path[256];
    
    // Read the HTTP request
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';  // Null-terminate the string
        
        // Parse and handle the request
        parse_request(buffer, path);
        send_response(client_socket, path);
    }
    
    // Close the client connection
    close(client_socket);
    printf("Client disconnected\n\n");
}

int main() {
    // Print startup banner
    printf("Starting Simple HTTP Server...\n");
    printf("Created with C and Berkeley Sockets\n");
    printf("Using Berkeley Sockets and TCP/IP\n\n");
    
    // Set up signal handler for graceful shutdown
    signal(SIGINT, handle_signal);   // Ctrl+C
    signal(SIGTERM, handle_signal);  // Termination signal
    
    // Step 1: Create a socket
    // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = default protocol
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Failed to create socket");
        exit(1);
    }
    printf("Socket created successfully\n");
    
    // Set socket option to reuse address (helps with restart)
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Failed to set socket options");
        exit(1);
    }
    
    // Step 2: Set up server address structure
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Accept connections from any IP
    server_addr.sin_port = htons(PORT);         // Convert port to network byte order
    
    // Step 3: Bind socket to address and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to bind socket");
        close(server_socket);
        exit(1);
    }
    printf("Socket bound to port %d\n", PORT);
    
    // Step 4: Start listening for connections
    if (listen(server_socket, MAX_CONNECTIONS) < 0) {
        perror("Failed to listen on socket");
        close(server_socket);
        exit(1);
    }
    printf("Server listening on http://localhost:%d\n", PORT);
    printf("Waiting for connections... (Press Ctrl+C to stop)\n\n");
    
    // Step 5: Accept connections in a loop
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        // Accept incoming connection
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Failed to accept connection");
            continue;
        }
        
        // Convert client IP to string for logging
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("New connection from %s:%d\n", client_ip, ntohs(client_addr.sin_port));
        
        // Handle the client request
        handle_client(client_socket);
    }
    
    // Cleanup (this won't be reached due to infinite loop, but good practice)
    close(server_socket);
    return 0;
} 