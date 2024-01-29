Sure! Here's a sample code for a simple web server using Haskell:

```haskell
import Network.Wai
import Network.HTTP.Types (status200)
import Network.Wai.Handler.Warp (run)

app :: Application
app _ respond = respond $ responseLBS status200 [("Content-Type", "text/plain")] "Hello, World!"

main :: IO ()
main = do
  putStrLn "Starting server on port 8080..."
  run 8080 app
```

To build and run the web server, you'll need to follow these steps:

1. Install the Haskell compiler (GHC) and the Cabal build tool if you haven't already.
2. Create a new directory for your project and navigate to it in your terminal.
3. Create a new file called `server.hs` and paste the sample code into it.
4. Open your terminal and navigate to the project directory.
5. Run the following command to build the project: `cabal build`
6. Once the build is successful, run the following command to start the server: `cabal run`
7. You should see the message "Starting server on port 8080..." indicating that the server is running.
8. Open your web browser and visit `http://localhost:8080` to see the "Hello, World!" message.

That's it! You now have a basic web server up and running using Haskell. Feel free to modify the `app` function to handle different routes and responses according to your needs.


another build way
```
ghc -o Main Main.hs
```
