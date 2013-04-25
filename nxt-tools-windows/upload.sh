#!/bin/bash
export PATH=$PWD/cygwin/bin:$PATH
cd example0
make clean
make all
echo Executing NeXTTool to upload example0_OSEK.rxe...
 ../nexttool/NeXTTool.exe /COM=usb -download=example0_OSEK.rxe
 ../nexttool/NeXTTool.exe /COM=usb -listfiles=example0_OSEK.rxe
echo "NeXTTool is terminated"
echo "Done"