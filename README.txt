Assignment3 Project
A Concurrent Server is up and run, waiting for any client to connect and send a series of transactions (each request is a Unix/Linux command to be processed by the server).  When a client is connected to the server, the server will create a worker thread to serve the connected client and thus to free the server to wait for any other incoming clients. 

Each worker thread (assigned to serve a client) of the server is in a loop to: (1) receive a transaction (a command) from its client, (2) process each transaction (a command), (3) send the outcome of the transaction back to the client and (4) go back to the loop, until it receives a command "exit" from the client to terminate its loop (serving the current client).

The server and client codes are incrementally built by adding more code from the previous parts.

Part 1.
#1. Design and implement the Server (a3p1Server1.c) and the Client#1 (a3p1Client1.c). The concurrent server is up and listening. The Client#1 connects to the server to do each command from client in a loop. The server (when it starts) takes one argument (its port number) to bind and listen for client's connection. The client (when it starts) takes two arguments (IP address and Port number of the server) to be used to connect.

#2. The Client#1 is up and running a loop to: (1) send a command to the server, (2) wait and receive the result of the command from the server, (3) display the result, (4) go into a sleep for 3 seconds, and then (5) wake up, go back in the loop. For this example, the Client#1 keeps one command ("date") each time.

The Client #1 sends a command string (e.g., "ls") to the server to be processed. Once the Client #1 is connected to the server, the server creates a worker thread (Thread #1). The server receives a command string to be run and sends its result back to the client. The server lets a worker thread receive (read via socket) the command string from the client (e.g., "date"). Then it runs the command and sends the result back to the client. 

#3. The Client #1 then receives the result from the server and displays it to the console. 

In addition, the client outputs (appends) the result to a log file (a3Client1.log). The log file of the client is opened in the beginning of the client program, writing each result from the server, with a proper heading. The log file is closed at the end of the client program, and then the client displays a message (with a time of the day and its process ID or thread ID) to the console.  

#4. Then the Client#1 goes into sleep for 3 seconds. And then the client wakes up and displays a message (with a time of the day and its process ID or thread ID) to the console. Then the client repeats this cycle until it is killed by the user (via CTRL+C or kill command).

#5. In addition, the Server opens its log file (a3p1Server.log) to be shared by all of its threads. Then each server's thread displays a message (with a time of the day with PID and its thread ID) to the console saying that it is going to process a client's request with a proper heading (Process ID or Thread ID with the time of day).
 
 #6. Let both client and server run together for 10 to 30 seconds. Then the client sends "exit" to terminate its request and to terminate itself (or you can kill it manually). The server will be killed manually by you after the client is terminated.

 As the server returns the output to the client each time, the client displays the output (with a heading of the output) to the console. To terminate the client, you should use kill command or CTRL+C to kill each client first and then the server.  



 ** Clean up any process (server or client) with kill command
 After all are done, kill the server (ps to find the pid of the server, and kill command to kill it).
 Use ps and netstat commands to check the server terminated and the port is now freed (available).
 (Or you may set up a timer for some time (e.g., 5 minutes) to be interrupted and terminate itself.)

 ** For this task, you should have two separate login-sessions (e.g., ssh or MobaXterm sessions – login for one session to run one client and the other session to run the server). With this setup, you can show one client working with one server concurrently. 


 WARNING. Please make sure to kill any running process after each run. If you do not clean up these processes (still alive and left behind), then you may lose your login privilege as a result. There have been a few cases reported each semester (as one's user account is locked due to abusive use).  




  
  Part 2.
  Once all tasks in Part1 are working with one server and one client, you will do the same tasks (with a few exceptions) with one server and two clients (Client#1 and Client#2) running concurrently. 

  #1. The Client#1 goes in a loop of sending a few commands and receiving its results. The loop is: 
  	send the command: " date; ls -l junk.txt; touch junk.txt; ls -l junk.txt "
	sleep 3


	#2. The Client#2 goes in a loop of sending a few commands and receiving its results. The loop is: 
		send the command: " date; ls -l junk.txt; rm -f junk.txt; ls -l junk.txt  "
		sleep 2

		 
		 #3. The server will do the same as in Part1 for each client. Each client will be served by a worker-thread of the server (Thread#1 for Client#1 and Thread#2 for Client#2). The clients and the server do the same and output (1) command sent or received and (2) its result being sent or received, output to console and also to a log file (of server and of clients) as in Part1. 


		 #4. Let two clients and one server be run together for 10 to 30 seconds. Then each client sends "exit" to terminate its request and to terminate itself (or you can kill it manually). The server will be killed manually by you after all clients are terminated.


		 As the server returns the output to the client each time, the client displays the output (with a heading of the output and time of day) to the console. To terminate the client, you should use kill command or CTRL+C to kill each client first and then the server.  


		 ** Clean up any process (server or client) with kill command
		 After all done, kill the server (ps to find the pid of the server, and kill command to kill it).
		 Use ps and netstat commands to check the server terminated and the port is now freed (available).
		 (Or you may set up a timer for some time (e.g., 5 minutes) to be interrupted and terminate itself.)

		 ** For this task, you should have three separate login sessions (e.g., ssh or MobaXterm sessions – login to each session to run each client and one session to run the server). With this setup, you can show two clients working with one server concurrently. 


		 WARNING. Please make sure to kill any running process after each run. If you do not clean up these processes (still alive and left behind), then you may lose your login privilege as a result. There have been a few cases reported each semester (as one's user account is locked due to abusive use).  


		  

		  Part 3.
		  Once all tasks in Part2 are working with one server and two clients, you will do the same tasks (with a few exceptions) with one server and two clients (Client#1 and Client#2 and Client#3) running concurrently. 

		  #1. The Client#1 goes in a loop of sending a few commands and receiving its results. The loop is: 
		  	send the command: " date; ls -l junk.txt; touch junk.txt "
			sleep 2


			#2. The Client#2 goes in a loop of sending a few commands and receiving its results. The loop is: 
				send the command: "date; ls -l junk.txt; rm -f junk.txt "
				sleep 3

				#3. The Client#3 goes in a loop of sending a few commands and receiving its results. The loop is: 
					send the command: "date; ls -l junk.txt; uname -a "
					sleep 1


					#4. The server will do the same as in Part2 for each client. Each client will be served by a child-process or a worker-thread of the server. The clients and the server do the same and to output (1) command sent or received and (2) its result being sent or received, output to console and also to a log file (of server and of clients) as in Part2. 


					#5. Let three clients and one server be run together for 10 to 30 seconds. Then each client sends "exit" to terminate its request and to terminate itself (or you can kill it manually). The server will be killed manually by you after all clients are terminated.


As the server returns the output to the client each time, the client displays the output (with a heading of the output and time of day) to the console. To terminate the client, you should use kill command or CTRL+C to kill each client first and then the server.  


** Clean up any process (server or client) with kill-command
					After all done, kill the server (ps to find the pid of the server, and kill command to kill it).
					Use ps and netstat commands to check the server terminated and the port is now freed (available).
(Or you may set up a timer for some time (e.g., 5 minutes) to be interrupted and terminate itself.)

** For this task, you should have four separate login sessions (e.g., ssh or MobaXterm sessions – login to each session to run each client and one session to run the server). With this setup, you can show three clients working with one server concurrently. 

WARNING. Please make sure to kill any running process after each run. If you do not clean up these processes (still alive and adding up), then you may lose your login privilege as a result. There have been a few cases reported each semester (as one's user account is locked due to abusive use).  



					 
Part 4. Makefile
Provide Makefile




Part 5. Version Control
Set up and provide a version control of your codes (using git, github, gitlab, or svn) for local repository with your laptop using gui api. You may use hello.c program for this part.



					  

