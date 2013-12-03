echo off
set mainpath=%cd:\=/%
set projpath=%2
set projpath=%projpath:\=/%      
echo on
"./cygwin/bin/bash" -c "./upload.sh %1 %projpath% %mainpath%"
