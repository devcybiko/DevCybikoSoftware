@2pic root.ico tcpkit.bmp
@vcc -V13 tcplib.c -o tcplib.o

@rem copy client.inf root.inf
@rem vcc -V13 tcpclient.c tcplib.o root.inf root.ico root.spl  -o tcpclient.app
                            
copy html.inf root.inf
copy html.spl root.spl
vcc -V13 tcphtml.c tcplib.o root.inf root.ico root.spl  -o tcphtml.app

@rem copy test.inf root.inf
@rem vcc test.c root.inf root.ico root.spl  -o test.app

copy telnet.inf root.inf
copy telnet.spl root.spl
vcc -V16 telnet.c tcplib.o root.inf root.ico root.spl  -o telnet.app

