Sure! Here's a sample code for a simple web server using the Rust programming language:

```rust
use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};

fn handle_client(mut stream: TcpStream) {
    let mut buffer = [0; 1024];
    stream.read(&mut buffer).unwrap();

    let response = "HTTP/1.1 200 OK\r\n\r\nHello, World!";
    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();
}

fn main() {
    let listener = TcpListener::bind("127.0.0.1:8080").unwrap();
    println!("Server listening on port 8080...");

    for stream in listener.incoming() {
        let stream = stream.unwrap();
        handle_client(stream);
    }
}
```

To build and run the web server, you'll need to have Rust installed on your machine. Once you have Rust installed, follow these steps:

1. Create a new directory for your project and navigate to it in your terminal.
2. Create a new file called `main.rs` and copy the sample code into it.
3. In the terminal, run the command `cargo build` to build the project.
4. Once the build is successful, run the command `cargo run` to start the web server.
5. The server will start listening on port 8080. You can access it by opening your web browser and navigating to `http://localhost:8080`.

That's it! You now have a basic web server up and running using Rust. Feel free to modify the code to suit your needs and explore more advanced features of the Rust programming language.

another build way
```
rustc main.rs
./main
```
