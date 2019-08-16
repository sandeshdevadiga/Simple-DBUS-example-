g++ sender.cpp -I/usr/include/dbus-1.0            -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include            -I/usr/include/glib-2.0            -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/            -ldbus-1            -ldbus-glib-1  -o sender


 g++ server.cpp -I/usr/include/dbus-1.0            -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include            -I/usr/include/glib-2.0            -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/            -ldbus-1            -ldbus-glib-1 -o server


Session bus config path
 /etc/dbus-1/session.d/in.softprayog.add_client.conf
/etc/dbus-1/session.d/in.softprayog.add_server.conf

Find server and client conf for reference in  busconfig directory



