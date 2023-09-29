/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:37:51 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/12 14:27:08 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

char    *get_icmp_code(uint8_t code, t_icmp_code_list *code_list, int size)
{
    uint8_t i = 0;
    while (i < size)
    {
        if (i == code)
            return(code_list[i].diag);
        i++;
    }
    return("Unknow error");
}

void    analyse_packet(void *packet)
{
    t_icmp_code_list icmp_code_unreach[] = {
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
    t_icmp_code_list icmp_code_redirect[] = {
    {ICMP_REDIR_NET, "Redirect Network"},
    {ICMP_REDIR_HOST, "Redirect Host"},
    {ICMP_REDIR_NETTOS, "Redirect Type of Service and Network"},
    {ICMP_REDIR_HOSTTOS, "Redirect Type of Service and Host"},
    };
    t_icmp_code_list icmp_code_time_exceed[] = {
    {ICMP_EXC_TTL, "Time to live exceeded"},
    {ICMP_EXC_FRAGTIME, "Frag reassembly time exceeded"},
    };
    t_icmp_diag icmp_diag[] = {
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
    struct iphdr *ip_header = packet;
    struct icmphdr *icmp_header = packet + sizeof(struct iphdr);
    uint8_t i = 0;
    char *error = NULL;
    if (icmp_header->type == ICMP_ECHO)
        return;
    if (icmp_header->un.echo.id != g_data.pid)
        return;
    if (icmp_header->type != ICMP_ECHOREPLY)
    {
        if (icmp_header->type == ICMP_DEST_UNREACH)
            error = get_icmp_code(icmp_header->code, icmp_code_unreach, 11);
        else if (icmp_header->type == ICMP_REDIRECT)
            error = get_icmp_code(icmp_header->code, icmp_code_redirect, 4);
        else if (icmp_header->type == ICMP_TIME_EXCEEDED)
            error = get_icmp_code(icmp_header->code, icmp_code_time_exceed, 2);
        else
        {
            for (; i < 12 && icmp_diag[i].type != icmp_header->type; i++);
            error = icmp_diag[i].description;
        }
        g_data.nb_errors++;
    }
    else
    {
        g_data.packet_received++;
    }
    refresh_ping_info(error, icmp_header->un.echo.sequence, ip_header->ttl);
}