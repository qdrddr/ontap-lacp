# ontap-lacp
ONTAP load balancing algorithm writen for article in this blog
http://blog.sentrium.io/ethernet-port-aggregation-and-load-balancing-with-ontap


To compile the algorithm run it in tested online compiler 
http://www.tutorialspoint.com/compile_cpp11_online.php

You can modify next variables:

    st_ports = 4; // number of ethernet ports to a storage node
    srv_ports = 4; // number of ethernet ports to a server
    subnet = 53; // IP 3rd octet XXX.XXX.53.XXX
    src_start = 21; // Server's start IP 4th octet XXX.XXX.53.21
    src_end = 22; // Server's end IP 4th octet XXX.XXX.53.22
    dst_start = 30; // Start from storage node potential IP: XXX.XXX.53.30
    dst_end = 250; // End storage node potential IP: XXX.XXX.53.250
    
