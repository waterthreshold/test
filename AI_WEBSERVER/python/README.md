Sure! Here's a sample code for a basic web server using Python's built-in `http.server` module:

```python
from http.server import HTTPServer, BaseHTTPRequestHandler

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(b"Hello, World!")

def run(server_class=HTTPServer, handler_class=MyHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Server running on port {port}")
    httpd.serve_forever()

if __name__ == '__main__':
    run()
```

To build and run the web server, follow these steps:

1. Save the code in a file, e.g., `server.py`.
2. Open a terminal or command prompt and navigate to the directory where the file is saved.
3. Run the command `python server.py` to start the server.
4. The server will be running on `http://localhost:8000` by default.
5. Open a web browser and visit `http://localhost:8000` to see the "Hello, World!" message.

You can customize the server's behavior by modifying the `MyHandler` class's methods, such as `do_GET` for handling GET requests.
