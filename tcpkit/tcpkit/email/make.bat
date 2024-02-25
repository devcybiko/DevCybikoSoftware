@2pic root.ico ..\tcpkit.bmp

copy email.inf root.inf
copy email.spl root.spl
vcc -V16 email.c loginform.c pop3.c jed.o ..\tcplib.o root.inf root.ico root.spl  -o email.app

@del root.inf
@del root.spl
