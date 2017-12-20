build:
	g++ server.cc -o server -I /usr/local/include /usr/local/lib/librpc.a -lpthread
	g++ client.cc -o client -I /usr/local/include /usr/local/lib/librpc.a -lpthread
