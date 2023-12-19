all: app

app: *.cc
	g++ *.cc -g -Wall -o app
