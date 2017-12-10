#!/bin/bash
PORT=8080
BUILDDIR=build
if [ "$1" = "client" ];then
	$BUILDDIR/client.bin localhost $PORT
elif [ "$1" = "server" ];then
	$BUILDDIR/server.bin $PORT
elif [ "$1" = "rsagen" ];then
	$BUILDDIR/rsagen.bin "rsakey"
else
	echo "Usage: run.sh <client/server/rsagen>"
fi