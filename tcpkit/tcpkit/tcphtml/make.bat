@2pic root.ico ..\tcpkit.bmp

copy html.inf root.inf
copy html.spl root.spl
vcc -V13 tcphtml.c ..\tcplib.o root.inf root.ico root.spl  -o tcphtml.app

