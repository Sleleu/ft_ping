/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:25:43 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/08 17:05:23 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

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
    //printf("send time: %ld\n", g_data.send_time.tv_sec); 

    // send packet
    ssize_t bytes_sent = sendto(g_data.sockfd, &packet, PING_PACKET_SIZE, 0, (struct sockaddr *)g_data.sockaddr, sizeof(*g_data.sockaddr));
    if (bytes_sent == -1) {
        fprintf(stderr, "ft_ping: sendto error\n");
        exit(EXIT_FAILURE);
    }
    alarm(1);
    //printf("create_packet(): bytes sent = %ld\n", bytes_sent);
}

void    analyse_packet(void *packet)
{
    struct icmphdr *icmp_header = packet + sizeof(struct iphdr);

    if (icmp_header->type == ICMP_ECHO)
        return ;
    if (icmp_header->type != ICMP_ECHOREPLY)
    {
        if (icmp_header->type == ICMP_DEST_UNREACH)
        printf("Destination Host Unreachable\n");
    }
    else
        g_data.packet_received++;
    refresh_ping_info();
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
