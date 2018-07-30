all: a3p1s a3p2s a3p3s a3p1c a3p2c1 a3p2c2 a3p3c1 a3p3c2 a3p3c3

a3p1s: a3p1server.c
	gcc a3p1server.c -lpthread -o a3p1s
a3p1c: a3p1client.c
	gcc a3p1client.c -o a3p1c
a3p2s: a3p2server.c
	gcc a3p2server.c -lpthread -o a3p2s
a3p2c1: a3p2client1.c
	gcc a3p2client1.c -o a3p2c1
a3p2c2: a3p2client2.c
	gcc a3p2client2.c -o a3p2c2
a3p3s: a3p3server.c
	gcc a3p3server.c -lpthread -o a3p3s
a3p3c1: a3p3client1.c
	gcc a3p3client1.c -o a3p3c1
a3p3c2: a3p3client2.c
	gcc a3p3client2.c -o a3p3c2
a3p3c3: a3p3client3.c
	gcc a3p3client3.c -o a3p3c3
