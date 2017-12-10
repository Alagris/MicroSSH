.PHONY: client server
CLIENT_ARGS=TARGET=client
SERVER_ARGS=TARGET=server
RSAGEN_ARGS=TARGET=rsagen
client:
	make $(CLIENT_ARGS) -f build.mk
	
server:
	make $(SERVER_ARGS) -f build.mk

rsagen:
	make $(RSAGEN_ARGS) -f build.mk
	
clean:
	rm -rf build/*	