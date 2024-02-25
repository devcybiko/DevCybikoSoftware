@2pic root.ico tcpkit.bmp
@vcc -V13 tcplib.c -o tcplib.o

@rem copy client.inf root.inf
@rem vcc -V13 tcpclient.c tcplib.o root.inf root.ico root.spl  -o tcpclient.app
                            
@rem copy html.inf root.inf
@rem vcc -V13 tcphtml.c tcplib.o root.inf root.ico root.spl  -o tcphtml.app

@rem copy test.inf root.inf
@rem vcc test.c root.inf root.ico root.spl  -o test.app

