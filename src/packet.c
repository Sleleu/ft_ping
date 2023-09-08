/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:25:43 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/08 21:35:28 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

struct icmp_code_list
{
    int     code;
    char    *diag;
};

struct  icmp_code_list icmp_code_unreach[] = {
    {ICMP_NET_UNREACH, "Destination Net Unreachable"},
    {ICMP_HOST_UNREACH, "Destination Host Unreachable"},
    {ICMP_PROT_UNREACH, "Destination Protocol Unreachable"},
    {ICMP_PORT_UNREACH, "Destination Port Unreachable"},
    {ICMP_FRAG_NEEDED, "Fragmentation needed and DF set"},
    {ICMP_SR_FAILED, "Source Route Failed"},
    {ICMP_NET_UNKNOWN, "Network Unknown"},
    {ICMP_HOST_UNKNOWN, "Host Unknown"},
    {ICMP_HOST_ISOLATED, "Host Isolated"},
    {ICMP_NET_UNR_TOS, "Destination Network Unreachable At This TOS"},
    {ICMP_HOST_UNR_TOS, "Destination Host Unreachable At This TOS"},
};

struct  icmp_code_list icmp_code_redirect[] = {
    {ICMP_REDIR_NET, "Redirect Network"},
    {ICMP_REDIR_HOST, "Redirect Host"},
    {ICMP_REDIR_NETTOS, "Redirect Type of Service and Network"},
    {ICMP_REDIR_HOSTTOS, "Redirect Type of Service and Host"},
};

struct icmp_code_list icmp_code_time_exceed[] = {
    {ICMP_EXC_TTL, "Time to live exceeded"},
    {ICMP_EXC_FRAGTIME, "Frag reassembly time exceeded"},
};

struct icmp_diag
{
    int     type;
    char  *description;
};

struct icmp_diag icmp_diag[] = {
    {ICMP_DEST_UNREACH, "Dest Unreachable"},
    {ICMP_SOURCE_QUENCH, "Source Quench"},
    {ICMP_REDIRECT, "Redirect"},
    {ICMP_ECHO, "Echo Request"},
    {ICMP_ROUTERADVERT, "Router Advertisement"},
    {ICMP_TIME_EXCEEDED, "Time exceeded"},
    {ICMP_TIMESTAMP, "Timestamp",},
    {ICMP_TIMESTAMPREPLY, "Timestamp Reply"},
    {ICMP_INFO_REQUEST, "Information Request"},
    {ICMP_INFO_REPLY, "Information Reply"},
    {ICMP_ADDRESS, "Address Mask Request"},
    {ICMP_ADDRESSREPLY, "Address Mask Reply"},
};

unsigned short  checksum(void *address, int len)
{
    unsigned short *buff = address;
    unsigned int sum = 0;
    unsigned short result;

    while (len > 1)
    {
        sum += *buff++;
        len -= 2;
    }
    if (len)
        sum += *(unsigned char *)buff;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return (result);
}

void create_packet(void)
{    
    t_packet packet;

    ft_bzero(&packet, sizeof(packet));

    // ip_header initialisation
    packet.ip_header.version = 4;
    packet.ip_header.ihl = 5;
    packet.ip_header.tot_len = htons(sizeof(packet));
    packet.ip_header.protocol = IPPROTO_ICMP; 
    packet.ip_header.ttl = TTL;
    packet.ip_header.daddr = g_data.sockaddr->sin_addr.s_addr;
    
    // icmp_header initialisation
    packet.icmp_header.type = ICMP_ECHO;
    packet.icmp_header.code = 0;
    packet.icmp_header.un.echo.id = g_data.pid;
    packet.icmp_header.un.echo.sequence = g_data.sequence++;
    packet.icmp_header.checksum = 0;    
    packet.icmp_header.checksum = checksum(&(packet.icmp_header), sizeof(packet.icmp_header) + sizeof(packet.data));

    //get time
    get_timeday(&g_data.send_time);

    // send packet
    ssize_t bytes_sent = sendto(g_data.sockfd, &packet, PING_PACKET_SIZE, 0, (struct sockaddr *)g_data.sockaddr, sizeof(*g_data.sockaddr));
    if (bytes_sent == -1) {
        fprintf(stderr, "ft_ping: sendto error\n");
        exit(EXIT_FAILURE);
    }
    alarm(1);
}


char    *get_icmp_code(uint8_t code, struct icmp_code_list *code_list, int size)
{
    int i = 0;
    while (i++ < size)
    {
        if (i == code)
            return(code_list[i].diag);
    }
    return("Unknow error");
}

void    analyse_packet(void *packet)
{
    struct icmphdr *icmp_header = packet + sizeof(struct iphdr);
    uint8_t i = 0;
    char *error = NULL;

    if (icmp_header->type == ICMP_ECHO)
        return ;
    if (icmp_header->type != ICMP_ECHOREPLY)
    {
        if (icmp_diag[i].type == ICMP_DEST_UNREACH)
            error = get_icmp_code(icmp_header->code, icmp_code_unreach, 11);
        else if (icmp_diag[i].type == ICMP_REDIRECT)
            error = get_icmp_code(icmp_header->code, icmp_code_redirect, 4);
        else if (icmp_diag[i].type == ICMP_TIME_EXCEEDED)
            error = get_icmp_code(icmp_header->code, icmp_code_time_exceed, 2);
        else
        {
            for (; i < 12 && icmp_diag[i].type != icmp_header->type; i++);
            error = icmp_diag[i].description;
        }
    }
    else
    {
        g_data.packet_received++;
        refresh_ping_info();
    }
    printf("error %s\n", error);
}

void receive_packet(void)
{
    char buffer[PING_PACKET_SIZE];
    struct iovec iov;
    struct msghdr msg;

    iov.iov_base = buffer; // ptr vers debut du segment mémoire
    iov.iov_len = PING_PACKET_SIZE;

    msg.msg_name = g_data.sockaddr;
    msg.msg_namelen = sizeof(*g_data.sockaddr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    msg.msg_flags = 0;

    ssize_t bytes_received = recvmsg(g_data.sockfd, &msg, 0);
    if (bytes_received == -1)
    {
        fprintf(stderr,"ft_ping: recvmsg error\n");
        exit(EXIT_FAILURE);
    }
    //printf("Receive_packet(): bytes received = %ld\n", bytes_received);  
    get_timeday(&g_data.rec_time);
    analyse_packet(iov.iov_base);
    //printf("receive time: %ld\n", g_data.rec_time.tv_sec);
}
