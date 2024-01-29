-- Main.hs
{-# LANGUAGE OverloadedStrings #-}

import Network.Wai
import Network.HTTP.Types (status200)
import Network.Wai.Handler.Warp (run)

main :: IO ()
main = do
    putStrLn "Server running on http://localhost:8080"
    run 8080 app

app :: Application
app _ respond = do
    respond $ responseLBS
        status200
        [("Content-Type", "text/plain")]
        "Hello, World!"

