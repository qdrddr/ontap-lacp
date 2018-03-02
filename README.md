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
See output example https://github.com/qdrddr/ontap-lacp/blob/master/Output_Example.txt
