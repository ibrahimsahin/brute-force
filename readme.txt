It  is  normally  impossible  to  find  out  someone’s  password  without  using  Brute-Force
techniques. Even with a machine with quad CPU, a simple brute-force attack on a single password
takes weeks. In this experiment, you will write a distributed password cracking tool. You are asked
to write a server program which will distrubute plain password possibilities which is divided in to
reasonable sections (for an example 1000 passwords for client) to its connected clients in order to
find  out  concurrently  a  valid  password  in  an  acceptable  amount  of  time.  A  client  should  try  all
possibilities in the range assigned by the server for the encrypted password. If a client finds out
the password,  other  clients will  stop  processing. If client can not  “crack” the password  in given
range, it will demand a new section for cracking.
Hence the password possiblities are big enough, you are asked to check only 4, 5 and 6
digit passwords. You are also asked to compare for 4 digit passwords the necessary amounts of
time with a single, 2 and 3 clients system. 