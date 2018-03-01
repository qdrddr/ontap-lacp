#include <stdio.h>
//#include <math.h> // for sqrt
#include <string>
#include <cstdlib>

int debug = 0;
 
void f_shiftL(int *r, int step, int i, int offset) {
    r[step] = r[i] << offset;
    if (debug > 0) {
        printf("\nStep %i Left Shift %i %i\n", step, i, offset);
        printf("\t%i << %i\n", r[i], offset);
        printf("\t%i\n", r[step]);
    }
}
 
void f_shiftR(int *r, int step, int i, int offset) {
    r[step] = r[i] >> offset;
    if (debug > 0) {
        printf("\nStep %i Right Shift %i %i\n", step, i, offset);
        printf("\t%i\n", r[i]);
        printf("\t%i\n", r[step]);
    }
}
 
void f_xor(int *r, int step, int i, int j) {
    r[step] = r[i] ^ r[j];
    if (debug > 0) {
        printf("\nStep %i XOR %i %i\n", step, i, j);
        printf("\t%i\n", r[i]);
        printf("\t%i\n", r[j]);
        printf("\t%i\n", r[step]);
    }
}
 
void f_sum(int *r, int step, int i, int j) {
    r[step] = r[i] + r[j];
    if (debug > 0) {
        printf("\nStep %i ADD %i %i\n", step, i, j);
        printf("\t%i\n", r[i]);
        printf("\t%i\n", r[j]);
        printf("\t%i\n", r[step]);
    }
}

// Function balance_ip_netapp() is a realization of NetApp's SuperFastHash algorithm
// https://kb.netapp.com/app/answers/answer_view/a_id/1032252
int balance_ip_netapp (int net, int src, int dst, int link_cnt) {
    int res[30];
    res[0] = net*256 + src;
    res[1] = net*256 + dst;
    //printf ("a = %i.%i (%i)\n", net, src, res[0]);
    //printf ("b = %i.%i (%i)\n", net, dst, res[1]);
    f_shiftL(res, 2, 1,11);
    f_xor   (res, 3, 0, 2);
    f_shiftL(res, 4, 0,16);
    f_xor   (res, 5, 3, 4);
    f_shiftR(res, 6, 5,11);
    f_sum   (res, 7, 5, 6);
    f_shiftL(res,15, 7, 3);
    f_xor   (res,16, 7,15);
    f_shiftR(res,17,16, 5);
    f_sum   (res,18,16,17);
    f_shiftL(res,19,18, 4);
    f_xor   (res,20,18,19);
    f_shiftR(res,21,20,17);
    f_sum   (res,22,20,21);
    f_shiftL(res,23,22,25);
    f_xor   (res,24,22,23);
    f_shiftR(res,25,24, 6);
    f_sum   (res,26,24,25);
    res[27] = res[26] % link_cnt;
    if (res[27] < 0) {
        res[27] = res[27] + link_cnt;
    }
//    printf ("%i.%i -> %i, %i\n", net, src, dst, res[27]);
 
    return res[27];
}
int  balance_ip_lacp_xor(int net, int src, int dst, int link_cnt) {
    int res[30];
    res[0] = net*256 + src;
    res[1] = net*256 + dst;
    f_xor   (res, 26, 0, 1);
    res[27] = res[26] % link_cnt;
 //   if (res[27] < 0) {
 //       res[27] = res[27] + link_cnt;
 //   }
    
 //   printf ("%i.%i -> %i, %i\n", net, src, dst, res[27]);
    return res[27]; 
}
int f_prnt(int x){
    if (x > 99 ) { printf ("%i",x);  return 0; }
    if (x <= 9 && x >= 0)  { printf ("  %i",x); return 0; }
    if (x <= 99 && x >= 10) { printf (" %i",x);  return 0; }
    
    if (x >= -9 && x < 0 )  { printf (" %i",x); return 0; }
    if (x >= -99 && x < 10)  { printf ("%i",x); return 0; }
    printf ("%i",x);    
    return 0;
}

int f_prnt_rev(int x){
    if (x > 99 ) { printf ("%i",x);  return 0; }
    if (x <= 9 && x >= 0)  { printf ("%i  ",x); return 0; }
    if (x <= 99 && x >= 10) { printf ("%i ",x);  return 0; }
    
    if (x >= -9 && x < 0 )  { printf ("%i ",x); return 0; }
    if (x >= -99 && x < 10)  { printf ("%i",x); return 0; }
    printf ("%i",x);    
    return 0;
}

void f_prnt_l_char (int src_start, int src_end){
    int src;
    for (src=src_start; src<=src_end; src++) {
        printf ("     ");
    }
}
void f_prnt_l_int (int src_start, int src_end){
    int src;
    for (src=src_start; src<=src_end; src++) {
        if (src==src_start) {printf ("¦ ");}
        else {printf ("| ");}
        f_prnt(src);
    }
}
void head_lines (int src_start, int src_end)
{
    int src;
    //       | NTAP              | NTAP              | Server            | SUM|
    printf ("\n");
    printf ("       ¦NTAP");
    f_prnt_l_char (src_start, src_end-1);
    printf ("  %%  ");
    printf ("¦NTAP");
    f_prnt_l_char (src_start, src_end-1);
    printf ("  %%  ");
    printf ("¦Srv ");           
    f_prnt_l_char (src_start, src_end-1);
    printf ("  %%  ");
    printf ("¦ SUM¦\n");
    
    //       | OUT               | IN                | IN & OUT          |    |
    printf ("       ¦OUT ");
    f_prnt_l_char (src_start, src_end-1);
    printf ("|Path");
    printf ("¦IN  ");
    f_prnt_l_char (src_start, src_end-1);
    printf ("|Path");
    printf ("¦IN&O");           
    f_prnt_l_char (src_start, src_end-1);
    printf ("|Path");
    printf ("¦Totl¦\n");
    //   IP  | 21 | 22 | .. | PU | 21 | 22 | .. | PU | 21 | 22 | .. | PU | XX |
    printf ("Stor IP"); // | 21 | 22 | .. | PU | 21 | 22 | .. | PU | 21 | 22 | .. | PU | XX |\n");
    f_prnt_l_int (src_start, src_end);
    printf ("|Used");
    f_prnt_l_int (src_start, src_end);
    printf ("|Used");
    f_prnt_l_int (src_start, src_end);
    printf ("|Used");
    printf ("¦Used¦\n"); 
}

int count_path (int a[][4], int src_c, int ports, int dedup )
{
    int i, j, count = 0 ;
    float ip_dedup = (float) src_c / (float) dedup;

/*
    printf ("\n---");
    for(i=0;i<src_c;++i){
       //a[i][1] = a[i][0];
        printf ("\n %i",a[i][0]);
    }
    printf ("\n===");
    for(i=0;i<dedup;++i){
       //a[i][1] = a[i][0];
        printf ("\n %i",a[i][1]);
    }
    printf ("\n+++");
*/

    for (j = 0; j < dedup; j++) {
        a[j][2] = 0;
        for (i = 0; i < src_c; i++){
            if (a[i][0] == a[j][1]) a[j][2]++;
        }
    }
    
/*    for(i=0;i<dedup;++i){
        printf ("\n a[%i],%i=%i",i,a[i][1],a[i][2]);
    }
*/
//  printf("\nsrc_c=%i; dedup=%i",src_c, dedup);
//    printf("\nip_dedup=%f", ip_dedup);
    for (i = 0; i < dedup; i++){
        if ( a[i][2] > ip_dedup ) a[i][3]= (100*ip_dedup) / a[i][2];
        else a[i][3]= (100*a[i][2]) / ip_dedup;
 //       printf ("\n a[%i],%i|%i=%i",i,a[i][1],a[i][2],a[i][3]);
    }
    for (i = 0; i < dedup; i++){
        count += a[i][3];
    }
//    printf ("\n count=%i",count/100);
    return count/100;
}

int removeDuplicates(int a[][4], int src_c, int ports)
{
    int n = src_c;
    int i,j,k;
    
    for(i=0;i<src_c;++i){
       a[i][1] = a[i][0];
        //printf ("\n el%i=%i",i,a[i][1]);
    }
    
    for(i=0;i<n;++i)
        for(j=i+1;j<n;)
        {
            if(a[i][1]==a[j][1])
            {
                for(k=j;k<n-1;++k)
                    a[k][1]=a[k+1][1];
                    
                --n;
            }
            else
                ++j;
        }
    
    if (debug > 0) {
        printf("\n");
        for(i=0;i<n;++i)
            printf("%i ",a[i][1]);
        printf("\nn=%i",n);
    }
    //count_path(a, src_c, ports, n);
    return count_path(a, src_c, ports, n);
    
}



int main() {
    int src, src1, dst, st_ports, srv_ports, subnet, src_start, src_end, src_c, dst_start, dst_end, dst_c;

//////////////////////////////////////////////////////////////////////////////
 
    st_ports = 4; // number of ethernet ports to a storage node
    srv_ports = 4; // number of ethernet ports to a server
    subnet = 53; // IP 3rd octet XXX.XXX.53.XXX
    src_start = 21; // Server's start IP 4th octet XXX.XXX.53.21
    src_end = 22; // Server's end IP 4th octet XXX.XXX.53.22
    dst_start = 30; // Start from storage node potential IP: XXX.XXX.53.30
    dst_end = 250; // End storage node potential IP: XXX.XXX.53.250
 
 //////////////////////////////////////////////////////////////////////////////
    src_c = src_end - src_start +1;
    dst_c = dst_end - dst_start +1;
    int in_out_collumns = 1+3*(src_c+1)+1;
    int in_out_rows = dst_c;
    int aggr_table [in_out_rows][in_out_collumns];
    int src_arr[src_c+1];
    //print header
    head_lines (src_start, src_end);

//    printf ("in_out_collumns = %i\n", in_out_collumns);
//    printf ("in_out_rows = %i\n", in_out_rows);
//    printf ("IP Octet3.IP Octet4 Source -> IP Octet4 Destination, storage ports \n");
    //Начинаем перебор destination для четверного октета IP адреса (в примере с 21 до 23)
    for (src=src_start; src<=src_end; src++) {
 //       printf ("\n====src IP %i====\n", src);
    //Начинаем перебор source для четверного октета IP адреса (в примере с 30 до 250)
        for (dst=dst_start; dst<=dst_end; dst++) {
            aggr_table [dst-dst_start][1-src_start+src] = balance_ip_netapp(subnet, dst, src, st_ports );
            aggr_table [dst-dst_start][1-src_start+src+1*(src_c+1)] = balance_ip_lacp_xor(subnet, src, dst, st_ports );
            aggr_table [dst-dst_start][1-src_start+src+2*(src_c+1)] = balance_ip_lacp_xor(subnet, dst, src, srv_ports );
        }
    }
        int x[src_c][4];
        int y[src_c][4];
        int z[src_c][4];
        int w[src_c*2][4];
        for (dst=dst_start; dst<=dst_end; dst++) {
            for (src=src_start; src<=src_end; src++) {
                x[src-src_start][0] = aggr_table [dst-dst_start][1-src_start+src];
                y[src-src_start][0] = aggr_table [dst-dst_start][1-src_start+src+1*(src_c+1)];
                z[src-src_start][0] = aggr_table [dst-dst_start][1-src_start+src+2*(src_c+1)];
                
                w[src-src_start][0] = aggr_table [dst-dst_start][1-src_start+src];
                w[src_c+src-src_start][0] = aggr_table [dst-dst_start][1-src_start+src+1*(src_c+1)];
            }
            if ( 1 ) // src_c >  st_ports 
            {
                aggr_table [dst-dst_start][1*(src_c+1)] = (removeDuplicates(x, src_c, st_ports)*50)/src_c+(removeDuplicates(w, 2*src_c,st_ports)*25)/src_c;
//                printf ("\nw=%i",removeDuplicates(w, 2*src_c));
                aggr_table [dst-dst_start][2*(src_c+1)] = (removeDuplicates(y, src_c,st_ports)*50)/src_c+(removeDuplicates(w, 2*src_c,st_ports)*25)/src_c;
            } else {
                aggr_table [dst-dst_start][1*(src_c+1)] = removeDuplicates(x, src_c,st_ports);
                aggr_table [dst-dst_start][2*(src_c+1)] = removeDuplicates(y, src_c,st_ports);                
            }
            if ( 1 ) // src_c >  srv_ports 
            {
                aggr_table [dst-dst_start][3*(src_c+1)] = (removeDuplicates(z, src_c,srv_ports)*100)/src_c;
            } else {
                aggr_table [dst-dst_start][3*(src_c+1)] = removeDuplicates(z, src_c,srv_ports);
            }
        }


    for (dst=dst_start; dst<=dst_end; dst++) {
        aggr_table [dst-dst_start][in_out_collumns-1] = (aggr_table [dst-dst_start][1*(src_c+1)] + aggr_table [dst-dst_start][2*(src_c+1)] + aggr_table [dst-dst_start][3*(src_c+1)])/3;
        f_prnt(subnet);
        printf(".");
        f_prnt_rev(dst);
        printf("¦");
        for (src=1; src<=in_out_collumns-1; src++) {
            printf(" ");
            f_prnt(aggr_table[dst-dst_start][src]);
            printf("|");
        }

        printf("\n");
            

    }
    printf("\n");  
}
