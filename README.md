# Client-Server-For-Prefux-Calculations
A Client Server architectue which permits associative prefix calculations.


-- Hello,
-- I am   presenting   a   client-server   architecture to you.   To  use  it 
   and  perform  calculations,  please    follow    the    following   steps:

-----------------------------PRELIMINARY STEP-------------------------------

(To be done only once)

-- Go    to   the   configuration file and modify WORKER_PATH and SERVER_PATH
   by    respectively    writing    the   paths   of   server_d   and  worker.

-------------------------------USAGE----------------------------------------

1- Launch the server first with the   following    command: ./server_launcher
2- In another terminal (or the same one): ./client x x x x x y, where the x's 
   are the values to be taken into account for the prefix calculation, and  y 
   is                 the                 desired                    operator.

-- The supported operations are:
- Addition -----> operator '+'
- Multiplication -----> operator 'x'
- Maximum -----> operator 'm'
- Minimum -----> operator 'l'
- PGCD -----> operator 'p'

------------------------------ADDING OPERATIONS-----------------------------

-- To add operations, go to the operators.c file, write the    definition of a 
   function representing the operation, and add it to makeCalcul() by choosing
   the character representing the operation,         as well as to opExists().

------------------------------SERVER CLOSURE--------------------------------

-- The server shuts down automatically when the machine is turned off, or you 
   can       use       the       following      command     "pkill server_d".
