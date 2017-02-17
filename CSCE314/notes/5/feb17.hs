{- URL format:
 - <URI> := <protocol> <hostname>[<port>]<path><filename>
 - <protocol> := "http" | ...
 - <hostname> := <host>(<subdomain>)<topleveldomain>
 -}

data Protocol = Http | Https | Ftp
type Hostname = String
type Subdomain = String
data TopLevelDomain = Com | Edu | Net
type Port = Int
type Path = String
type Filename = String

type URI = (Protocol, Hostname, Subdomain, TopLevelDomain, Port, Path, Filename)

uriParser :: String -> [URI]
uriParser x | take 5 x == "https" = [(Https, "", "", Com, -1, "", "")]
            | take 4 x == "http"  = [(Http, "", "", Com, -1, "", "")]
            | take 3 x == "ftp"   = [(Ftp, "", "", Com, -1, "", "")]
            | otherwise           = []

-- Notes incomplete, see Dr. Shell's notes for a full account of this class
