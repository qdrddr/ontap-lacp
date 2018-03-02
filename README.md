# ontap-lacp
SuperFastHash load balancing algorithm used in ONTAP 8 & 9, writen for article in this blog

http://blog.sentrium.io/ethernet-port-aggregation-and-load-balancing-with-ontap

To compile the algorithm copy and paste algorithm.cpp file in tested online compiler 

http://www.tutorialspoint.com/compile_cpp11_online.php or https://www.onlinegdb.com/online_c++_compiler

You can modify next variables:

    st_ports = 4; // number of ethernet ports to a storage node
    srv_ports = 4; // number of ethernet ports to a server
    subnet = 53; // IP 3rd octet XXX.XXX.53.XXX
    src_start = 21; // Server's start IP 4th octet XXX.XXX.53.21
    src_end = 22; // Server's end IP 4th octet XXX.XXX.53.22
    dst_start = 30; // Start from storage node potential IP: XXX.XXX.53.30
    dst_end = 250; // End storage node potential IP: XXX.XXX.53.250


In application's otput:
SuperFastHash used for NTAP OUT column - function balance_ip_netapp(); https://kb.netapp.com/app/answers/answer_view/a_id/1032252

Ordinary XOR used for NTAP IN & Server IN&OUT columns - function balance_ip_lacp_xor();    
    
Though I did my best to make the algorithm to work precisely as in your storage system, switch and server, I do not give any guarantees, so you can use it AS IS, and you are welcome to contribute to this open-source code.  

To find the best IPv4 for your storage nodes in your environment just find the biggest number in column "SUM Totl Used". So if you need 4x IP addresses, in this example you'll be interested in XXX.XXX.53.32, XXX.XXX.53.43, XXX.XXX.53.49 & XXX.XXX.53.58.
Example of application output:

       ¦NTAP       %  ¦NTAP       %  ¦Srv        %  ¦ SUM¦
       ¦OUT      |Path¦IN       |Path¦IN&O     |Path¦Totl¦
Stor IP¦  21|  22|Used¦  21|  22|Used¦  21|  22|Used¦Used¦
 53.30 ¦   1|   0|  75|   3|   0|  75|   3|   0| 100|  83|
 53.31 ¦   1|   1|  37|   2|   1|  62|   2|   1| 100|  66|
 53.32 ¦   0|   3| 100|   1|   2| 100|   1|   2| 100| 100|
 53.33 ¦   2|   3|  75|   0|   3|  75|   0|   3| 100|  83|
 53.34 ¦   0|   1|  75|   3|   0|  75|   3|   0| 100|  83|
 53.35 ¦   0|   2|  75|   2|   1|  75|   2|   1| 100|  83|
 53.36 ¦   1|   2|  75|   1|   2|  75|   1|   2| 100|  83|
 53.37 ¦   3|   2|  75|   0|   3|  75|   0|   3| 100|  83|
 53.38 ¦   0|   2|  75|   3|   0|  75|   3|   0| 100|  83|
 53.39 ¦   0|   1|  75|   2|   1|  75|   2|   1| 100|  83|
 53.40 ¦   1|   0|  75|   1|   2|  75|   1|   2| 100|  83|
 53.41 ¦   1|   0|  75|   0|   3|  75|   0|   3| 100|  83|
 53.42 ¦   1|   0|  75|   3|   0|  75|   3|   0| 100|  83|
 53.43 ¦   0|   3| 100|   2|   1| 100|   2|   1| 100| 100|
 53.44 ¦   0|   2|  75|   1|   2|  75|   1|   2| 100|  83|
 53.45 ¦   0|   1|  75|   0|   3|  75|   0|   3| 100|  83|
 53.46 ¦   3|   3|  37|   3|   0|  62|   3|   0| 100|  66|
 53.47 ¦   2|   0|  75|   2|   1|  75|   2|   1| 100|  83|
 53.48 ¦   1|   0|  75|   1|   2|  75|   1|   2| 100|  83|
 53.49 ¦   1|   2| 100|   0|   3| 100|   0|   3| 100| 100|
 53.50 ¦   3|   2|  75|   3|   0|  75|   3|   0| 100|  83|
 53.51 ¦   2|   0|  75|   2|   1|  75|   2|   1| 100|  83|
 53.52 ¦   2|   3|  75|   1|   2|  75|   1|   2| 100|  83|
 53.53 ¦   2|   2|  50|   0|   3|  75|   0|   3| 100|  75|
 53.54 ¦   0|   3|  75|   3|   0|  75|   3|   0| 100|  83|
 53.55 ¦   2|   1|  75|   2|   1|  75|   2|   1| 100|  83|
 53.56 ¦   0|   2|  75|   1|   2|  75|   1|   2| 100|  83|
 53.57 ¦   1|   1|  50|   0|   3|  75|   0|   3| 100|  75|
 53.58 ¦   2|   1| 100|   3|   0| 100|   3|   0| 100| 100|
 53.59 ¦   3|   3|  50|   2|   1|  75|   2|   1| 100|  75|
 53.60 ¦   2|   3|  75|   1|   2|  75|   1|   2| 100|  83|
