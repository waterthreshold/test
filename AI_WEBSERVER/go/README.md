Sure! Here's a sample code for a basic web server using Go language:

```go
package main

import (
	"fmt"
	"net/http"
)

func main() {
	http.HandleFunc("/", helloHandler)
	fmt.Println("Server is running on http://localhost:8080")
	http.ListenAndServe(":8080", nil)
}

func helloHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello, World!")
}
```

To build and run the web server, follow these steps:

1. Save the code in a file with a `.go` extension (e.g., `main.go`).
2. Open a terminal or command prompt and navigate to the directory where the file is saved.
3. Run the following command to build the executable file:
   ```
   go build
   ```
4. After the build is successful, run the following command to start the server:
   ```
   ./your-executable-name
   ```
   Replace `your-executable-name` with the name of the executable file generated in the previous step.
5. Open a web browser and visit `http://localhost:8080`. You should see the message "Hello, World!" displayed on the page.

That's it! You now have a basic web server running using Go language.
