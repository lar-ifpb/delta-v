
all: main.c
	gcc main.c -lev3dev-c -o bin
sync:
	sftp -oBatchMode=no -b upload.sftp "robot@10.42.0.3:delta-v/"
clean:
	rm -rf *.o
	rm bin

