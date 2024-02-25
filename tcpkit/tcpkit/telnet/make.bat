@2pic root.ico ..\tcpkit.bmp

copy telnet.inf root.inf
copy telnet.spl root.spl
vcc -V16 telnet.c ..\tcplib.o root.inf root.ico root.spl  -o telnet.app

@del root.inf
@del root.spl
@del root.ico
