PATH=$PWD/cygwin/bin:$PATH
cd $2
make clean    
make all
echo Executing NeXTTool to upload $1_OSEK.rxe...
 $3/nexttool/NeXTTool.exe  /COM=usb -download=$1_OSEK.rxe
 $3/nexttool/NeXTTool.exe  /COM=usb -listfiles=$1_OSEK.rxe
echo "NeXTTool is terminated"
echo "Done"
