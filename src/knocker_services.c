/* knocker version 0.8.0
 * Release date: 28 December 2020
 *
 * Project homepage: https://knocker.sourceforge.io
 *
 * Copyright 2001,2020 Gabriele Giorgetti <g.giorgetti@gmail.com>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "knocker_services.h"
#include "knocker_core.h"


int knocker_core_services_db_init;
char *knocker_core_services_db[SERVICES_DB_TOTAL_SERVICES];


/* this following list of services has been automatically
   generated from /etc/services */

int init_knocker_core_services_db (void)
{
#ifdef DEBUG
  int n_of_services = 0;
  int i = 0;
#endif

/* if it has been already initialized we do anything */
  if (knocker_core_services_db_init)
    return 0;

  knocker_core_services_db_init = 0;

#ifdef DEBUG
  fprintf (stderr, "debug: function init_knocker_core_services_db (...) called.\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: allocating memory to store service strings... ");
#endif

  knocker_core_services_db[1] = malloc (6 + 1);
  strcpy (knocker_core_services_db[1], "tcpmux");

  if (knocker_core_services_db[1] == NULL)
    return -1;

  knocker_core_services_db[7] = malloc (4 + 1);
  strcpy (knocker_core_services_db[7], "echo");

  if (knocker_core_services_db[7] == NULL)
    return -1;

  knocker_core_services_db[9] = malloc (7 + 1);
  strcpy (knocker_core_services_db[9], "discard");

  if (knocker_core_services_db[9] == NULL)
    return -1;

  knocker_core_services_db[11] = malloc (6 + 1);
  strcpy (knocker_core_services_db[11], "systat");

  if (knocker_core_services_db[11] == NULL)
    return -1;

  knocker_core_services_db[13] = malloc (7 + 1);
  strcpy (knocker_core_services_db[13], "daytime");

  if (knocker_core_services_db[13] == NULL)
    return -1;

  knocker_core_services_db[15] = malloc (7 + 1);
  strcpy (knocker_core_services_db[15], "netstat");

  if (knocker_core_services_db[15] == NULL)
    return -1;

  knocker_core_services_db[17] = malloc (4 + 1);
  strcpy (knocker_core_services_db[17], "qotd");

  if (knocker_core_services_db[17] == NULL)
    return -1;

  knocker_core_services_db[18] = malloc (3 + 1);
  strcpy (knocker_core_services_db[18], "msp");

  if (knocker_core_services_db[18] == NULL)
    return -1;

  knocker_core_services_db[19] = malloc (7 + 1);
  strcpy (knocker_core_services_db[19], "chargen");

  if (knocker_core_services_db[19] == NULL)
    return -1;

  knocker_core_services_db[20] = malloc (8 + 1);
  strcpy (knocker_core_services_db[20], "ftp-data");

  if (knocker_core_services_db[20] == NULL)
    return -1;

  knocker_core_services_db[21] = malloc (3 + 1);
  strcpy (knocker_core_services_db[21], "ftp");

  if (knocker_core_services_db[21] == NULL)
    return -1;

  knocker_core_services_db[22] = malloc (3 + 1);
  strcpy (knocker_core_services_db[22], "ssh");

  if (knocker_core_services_db[22] == NULL)
    return -1;

  knocker_core_services_db[23] = malloc (6 + 1);
  strcpy (knocker_core_services_db[23], "telnet");

  if (knocker_core_services_db[23] == NULL)
    return -1;

  knocker_core_services_db[25] = malloc (4 + 1);
  strcpy (knocker_core_services_db[25], "smtp");

  if (knocker_core_services_db[25] == NULL)
    return -1;

  knocker_core_services_db[37] = malloc (4 + 1);
  strcpy (knocker_core_services_db[37], "time");

  if (knocker_core_services_db[37] == NULL)
    return -1;

  knocker_core_services_db[39] = malloc (3 + 1);
  strcpy (knocker_core_services_db[39], "rlp");

  if (knocker_core_services_db[39] == NULL)
    return -1;

  knocker_core_services_db[42] = malloc (10 + 1);
  strcpy (knocker_core_services_db[42], "nameserver");

  if (knocker_core_services_db[42] == NULL)
    return -1;

  knocker_core_services_db[43] = malloc (5 + 1);
  strcpy (knocker_core_services_db[43], "whois");

  if (knocker_core_services_db[43] == NULL)
    return -1;

  knocker_core_services_db[50] = malloc (10 + 1);
  strcpy (knocker_core_services_db[50], "re-mail-ck");

  if (knocker_core_services_db[50] == NULL)
    return -1;

  knocker_core_services_db[53] = malloc (6 + 1);
  strcpy (knocker_core_services_db[53], "domain");

  if (knocker_core_services_db[53] == NULL)
    return -1;

  knocker_core_services_db[57] = malloc (3 + 1);
  strcpy (knocker_core_services_db[57], "mtp");

  if (knocker_core_services_db[57] == NULL)
    return -1;

  knocker_core_services_db[67] = malloc (6 + 1);
  strcpy (knocker_core_services_db[67], "bootps");

  if (knocker_core_services_db[67] == NULL)
    return -1;

  knocker_core_services_db[68] = malloc (6 + 1);
  strcpy (knocker_core_services_db[68], "bootpc");

  if (knocker_core_services_db[68] == NULL)
    return -1;

  knocker_core_services_db[69] = malloc (4 + 1);
  strcpy (knocker_core_services_db[69], "tftp");

  if (knocker_core_services_db[69] == NULL)
    return -1;

  knocker_core_services_db[70] = malloc (6 + 1);
  strcpy (knocker_core_services_db[70], "gopher");

  if (knocker_core_services_db[70] == NULL)
    return -1;

  knocker_core_services_db[77] = malloc (3 + 1);
  strcpy (knocker_core_services_db[77], "rje");

  if (knocker_core_services_db[77] == NULL)
    return -1;

  knocker_core_services_db[79] = malloc (6 + 1);
  strcpy (knocker_core_services_db[79], "finger");

  if (knocker_core_services_db[79] == NULL)
    return -1;

  knocker_core_services_db[80] = malloc (3 + 1);
  strcpy (knocker_core_services_db[80], "www");

  if (knocker_core_services_db[80] == NULL)
    return -1;

  knocker_core_services_db[87] = malloc (4 + 1);
  strcpy (knocker_core_services_db[87], "link");

  if (knocker_core_services_db[87] == NULL)
    return -1;

  knocker_core_services_db[88] = malloc (8 + 1);
  strcpy (knocker_core_services_db[88], "kerberos");

  if (knocker_core_services_db[88] == NULL)
    return -1;

  knocker_core_services_db[95] = malloc (6 + 1);
  strcpy (knocker_core_services_db[95], "supdup");

  if (knocker_core_services_db[95] == NULL)
    return -1;

  knocker_core_services_db[98] = malloc (9 + 1);
  strcpy (knocker_core_services_db[98], "linuxconf");

  if (knocker_core_services_db[98] == NULL)
    return -1;

  knocker_core_services_db[101] = malloc (9 + 1);
  strcpy (knocker_core_services_db[101], "hostnames");

  if (knocker_core_services_db[101] == NULL)
    return -1;

  knocker_core_services_db[102] = malloc (8 + 1);
  strcpy (knocker_core_services_db[102], "iso-tsap");

  if (knocker_core_services_db[102] == NULL)
    return -1;

  knocker_core_services_db[105] = malloc (8 + 1);
  strcpy (knocker_core_services_db[105], "csnet-ns");

  if (knocker_core_services_db[105] == NULL)
    return -1;

  knocker_core_services_db[107] = malloc (7 + 1);
  strcpy (knocker_core_services_db[107], "rtelnet");

  if (knocker_core_services_db[107] == NULL)
    return -1;

  knocker_core_services_db[109] = malloc (4 + 1);
  strcpy (knocker_core_services_db[109], "pop2");

  if (knocker_core_services_db[109] == NULL)
    return -1;

  knocker_core_services_db[110] = malloc (4 + 1);
  strcpy (knocker_core_services_db[110], "pop3");

  if (knocker_core_services_db[110] == NULL)
    return -1;

  knocker_core_services_db[111] = malloc (6 + 1);
  strcpy (knocker_core_services_db[111], "sunrpc");

  if (knocker_core_services_db[111] == NULL)
    return -1;

  knocker_core_services_db[113] = malloc (4 + 1);
  strcpy (knocker_core_services_db[113], "auth");

  if (knocker_core_services_db[113] == NULL)
    return -1;

  knocker_core_services_db[115] = malloc (4 + 1);
  strcpy (knocker_core_services_db[115], "sftp");

  if (knocker_core_services_db[115] == NULL)
    return -1;

  knocker_core_services_db[117] = malloc (9 + 1);
  strcpy (knocker_core_services_db[117], "uucp-path");

  if (knocker_core_services_db[117] == NULL)
    return -1;

  knocker_core_services_db[119] = malloc (4 + 1);
  strcpy (knocker_core_services_db[119], "nntp");

  if (knocker_core_services_db[119] == NULL)
    return -1;

  knocker_core_services_db[123] = malloc (3 + 1);
  strcpy (knocker_core_services_db[123], "ntp");

  if (knocker_core_services_db[123] == NULL)
    return -1;

  knocker_core_services_db[129] = malloc (6 + 1);
  strcpy (knocker_core_services_db[129], "pwdgen");

  if (knocker_core_services_db[129] == NULL)
    return -1;

  knocker_core_services_db[137] = malloc (10 + 1);
  strcpy (knocker_core_services_db[137], "netbios-ns");

  if (knocker_core_services_db[137] == NULL)
    return -1;

  knocker_core_services_db[138] = malloc (11 + 1);
  strcpy (knocker_core_services_db[138], "netbios-dgm");

  if (knocker_core_services_db[138] == NULL)
    return -1;

  knocker_core_services_db[139] = malloc (11 + 1);
  strcpy (knocker_core_services_db[139], "netbios-ssn");

  if (knocker_core_services_db[139] == NULL)
    return -1;

  knocker_core_services_db[143] = malloc (5 + 1);
  strcpy (knocker_core_services_db[143], "imap2");

  if (knocker_core_services_db[143] == NULL)
    return -1;

  knocker_core_services_db[161] = malloc (4 + 1);
  strcpy (knocker_core_services_db[161], "snmp");

  if (knocker_core_services_db[161] == NULL)
    return -1;

  knocker_core_services_db[162] = malloc (9 + 1);
  strcpy (knocker_core_services_db[162], "snmp-trap");

  if (knocker_core_services_db[162] == NULL)
    return -1;

  knocker_core_services_db[163] = malloc (8 + 1);
  strcpy (knocker_core_services_db[163], "cmip-man");

  if (knocker_core_services_db[163] == NULL)
    return -1;

  knocker_core_services_db[164] = malloc (10 + 1);
  strcpy (knocker_core_services_db[164], "cmip-agent");

  if (knocker_core_services_db[164] == NULL)
    return -1;

  knocker_core_services_db[174] = malloc (5 + 1);
  strcpy (knocker_core_services_db[174], "mailq");

  if (knocker_core_services_db[174] == NULL)
    return -1;

  knocker_core_services_db[177] = malloc (5 + 1);
  strcpy (knocker_core_services_db[177], "xdmcp");

  if (knocker_core_services_db[177] == NULL)
    return -1;

  knocker_core_services_db[178] = malloc (8 + 1);
  strcpy (knocker_core_services_db[178], "nextstep");

  if (knocker_core_services_db[178] == NULL)
    return -1;

  knocker_core_services_db[179] = malloc (3 + 1);
  strcpy (knocker_core_services_db[179], "bgp");

  if (knocker_core_services_db[179] == NULL)
    return -1;

  knocker_core_services_db[191] = malloc (8 + 1);
  strcpy (knocker_core_services_db[191], "prospero");

  if (knocker_core_services_db[191] == NULL)
    return -1;

  knocker_core_services_db[194] = malloc (3 + 1);
  strcpy (knocker_core_services_db[194], "irc");

  if (knocker_core_services_db[194] == NULL)
    return -1;

  knocker_core_services_db[199] = malloc (4 + 1);
  strcpy (knocker_core_services_db[199], "smux");

  if (knocker_core_services_db[199] == NULL)
    return -1;

  knocker_core_services_db[201] = malloc (7 + 1);
  strcpy (knocker_core_services_db[201], "at-rtmp");

  if (knocker_core_services_db[201] == NULL)
    return -1;

  knocker_core_services_db[202] = malloc (6 + 1);
  strcpy (knocker_core_services_db[202], "at-nbp");

  if (knocker_core_services_db[202] == NULL)
    return -1;

  knocker_core_services_db[204] = malloc (7 + 1);
  strcpy (knocker_core_services_db[204], "at-echo");

  if (knocker_core_services_db[204] == NULL)
    return -1;

  knocker_core_services_db[206] = malloc (6 + 1);
  strcpy (knocker_core_services_db[206], "at-zis");

  if (knocker_core_services_db[206] == NULL)
    return -1;

  knocker_core_services_db[209] = malloc (4 + 1);
  strcpy (knocker_core_services_db[209], "qmtp");

  if (knocker_core_services_db[209] == NULL)
    return -1;

  knocker_core_services_db[210] = malloc (5 + 1);
  strcpy (knocker_core_services_db[210], "z3950");

  if (knocker_core_services_db[210] == NULL)
    return -1;

  knocker_core_services_db[213] = malloc (3 + 1);
  strcpy (knocker_core_services_db[213], "ipx");

  if (knocker_core_services_db[213] == NULL)
    return -1;

  knocker_core_services_db[220] = malloc (5 + 1);
  strcpy (knocker_core_services_db[220], "imap3");

  if (knocker_core_services_db[220] == NULL)
    return -1;

  knocker_core_services_db[369] = malloc (11 + 1);
  strcpy (knocker_core_services_db[369], "rpc2portmap");

  if (knocker_core_services_db[369] == NULL)
    return -1;

  knocker_core_services_db[370] = malloc (9 + 1);
  strcpy (knocker_core_services_db[370], "codaauth2");

  if (knocker_core_services_db[370] == NULL)
    return -1;

  knocker_core_services_db[372] = malloc (9 + 1);
  strcpy (knocker_core_services_db[372], "ulistserv");

  if (knocker_core_services_db[372] == NULL)
    return -1;

  knocker_core_services_db[389] = malloc (4 + 1);
  strcpy (knocker_core_services_db[389], "ldap");

  if (knocker_core_services_db[389] == NULL)
    return -1;

  knocker_core_services_db[443] = malloc (5 + 1);
  strcpy (knocker_core_services_db[443], "https");

  if (knocker_core_services_db[443] == NULL)
    return -1;

  knocker_core_services_db[444] = malloc (4 + 1);
  strcpy (knocker_core_services_db[444], "snpp");

  if (knocker_core_services_db[444] == NULL)
    return -1;

  knocker_core_services_db[487] = malloc (4 + 1);
  strcpy (knocker_core_services_db[487], "saft");

  if (knocker_core_services_db[487] == NULL)
    return -1;

  knocker_core_services_db[610] = malloc (10 + 1);
  strcpy (knocker_core_services_db[610], "npmp-local");

  if (knocker_core_services_db[610] == NULL)
    return -1;

  knocker_core_services_db[611] = malloc (8 + 1);
  strcpy (knocker_core_services_db[611], "npmp-gui");

  if (knocker_core_services_db[611] == NULL)
    return -1;

  knocker_core_services_db[612] = malloc (8 + 1);
  strcpy (knocker_core_services_db[612], "hmmp-ind");

  if (knocker_core_services_db[612] == NULL)
    return -1;

  knocker_core_services_db[631] = malloc (3 + 1);
  strcpy (knocker_core_services_db[631], "ipp");

  if (knocker_core_services_db[631] == NULL)
    return -1;

  knocker_core_services_db[512] = malloc (4 + 1);
  strcpy (knocker_core_services_db[512], "exec");

  if (knocker_core_services_db[512] == NULL)
    return -1;

  knocker_core_services_db[513] = malloc (5 + 1);
  strcpy (knocker_core_services_db[513], "login");

  if (knocker_core_services_db[513] == NULL)
    return -1;

  knocker_core_services_db[514] = malloc (5 + 1);
  strcpy (knocker_core_services_db[514], "shell");

  if (knocker_core_services_db[514] == NULL)
    return -1;

  knocker_core_services_db[515] = malloc (7 + 1);
  strcpy (knocker_core_services_db[515], "printer");

  if (knocker_core_services_db[515] == NULL)
    return -1;

  knocker_core_services_db[517] = malloc (4 + 1);
  strcpy (knocker_core_services_db[517], "talk");

  if (knocker_core_services_db[517] == NULL)
    return -1;

  knocker_core_services_db[518] = malloc (5 + 1);
  strcpy (knocker_core_services_db[518], "ntalk");

  if (knocker_core_services_db[518] == NULL)
    return -1;

  knocker_core_services_db[520] = malloc (5 + 1);
  strcpy (knocker_core_services_db[520], "route");

  if (knocker_core_services_db[520] == NULL)
    return -1;

  knocker_core_services_db[525] = malloc (5 + 1);
  strcpy (knocker_core_services_db[525], "timed");

  if (knocker_core_services_db[525] == NULL)
    return -1;

  knocker_core_services_db[526] = malloc (5 + 1);
  strcpy (knocker_core_services_db[526], "tempo");

  if (knocker_core_services_db[526] == NULL)
    return -1;

  knocker_core_services_db[530] = malloc (7 + 1);
  strcpy (knocker_core_services_db[530], "courier");

  if (knocker_core_services_db[530] == NULL)
    return -1;

  knocker_core_services_db[531] = malloc (10 + 1);
  strcpy (knocker_core_services_db[531], "conference");

  if (knocker_core_services_db[531] == NULL)
    return -1;

  knocker_core_services_db[532] = malloc (7 + 1);
  strcpy (knocker_core_services_db[532], "netnews");

  if (knocker_core_services_db[532] == NULL)
    return -1;

  knocker_core_services_db[533] = malloc (7 + 1);
  strcpy (knocker_core_services_db[533], "netwall");

  if (knocker_core_services_db[533] == NULL)
    return -1;

  knocker_core_services_db[538] = malloc (6 + 1);
  strcpy (knocker_core_services_db[538], "gdomap");

  if (knocker_core_services_db[538] == NULL)
    return -1;

  knocker_core_services_db[540] = malloc (4 + 1);
  strcpy (knocker_core_services_db[540], "uucp");

  if (knocker_core_services_db[540] == NULL)
    return -1;

  knocker_core_services_db[548] = malloc (10 + 1);
  strcpy (knocker_core_services_db[548], "afpovertcp");

  if (knocker_core_services_db[548] == NULL)
    return -1;

  knocker_core_services_db[556] = malloc (8 + 1);
  strcpy (knocker_core_services_db[556], "remotefs");

  if (knocker_core_services_db[556] == NULL)
    return -1;

  knocker_core_services_db[543] = malloc (6 + 1);
  strcpy (knocker_core_services_db[543], "klogin");

  if (knocker_core_services_db[543] == NULL)
    return -1;

  knocker_core_services_db[544] = malloc (6 + 1);
  strcpy (knocker_core_services_db[544], "kshell");

  if (knocker_core_services_db[544] == NULL)
    return -1;

  knocker_core_services_db[563] = malloc (5 + 1);
  strcpy (knocker_core_services_db[563], "nntps");

  if (knocker_core_services_db[563] == NULL)
    return -1;

  knocker_core_services_db[636] = malloc (5 + 1);
  strcpy (knocker_core_services_db[636], "ldaps");

  if (knocker_core_services_db[636] == NULL)
    return -1;

  knocker_core_services_db[655] = malloc (4 + 1);
  strcpy (knocker_core_services_db[655], "tinc");

  if (knocker_core_services_db[655] == NULL)
    return -1;

  knocker_core_services_db[749] = malloc (12 + 1);
  strcpy (knocker_core_services_db[749], "kerberos-adm");

  if (knocker_core_services_db[749] == NULL)
    return -1;

  knocker_core_services_db[765] = malloc (7 + 1);
  strcpy (knocker_core_services_db[765], "webster");

  if (knocker_core_services_db[765] == NULL)
    return -1;

  knocker_core_services_db[873] = malloc (5 + 1);
  strcpy (knocker_core_services_db[873], "rsync");

  if (knocker_core_services_db[873] == NULL)
    return -1;

  knocker_core_services_db[989] = malloc (9 + 1);
  strcpy (knocker_core_services_db[989], "ftps-data");

  if (knocker_core_services_db[989] == NULL)
    return -1;

  knocker_core_services_db[990] = malloc (4 + 1);
  strcpy (knocker_core_services_db[990], "ftps");

  if (knocker_core_services_db[990] == NULL)
    return -1;

  knocker_core_services_db[992] = malloc (7 + 1);
  strcpy (knocker_core_services_db[992], "telnets");

  if (knocker_core_services_db[992] == NULL)
    return -1;

  knocker_core_services_db[993] = malloc (5 + 1);
  strcpy (knocker_core_services_db[993], "imaps");

  if (knocker_core_services_db[993] == NULL)
    return -1;

  knocker_core_services_db[994] = malloc (4 + 1);
  strcpy (knocker_core_services_db[994], "ircs");

  if (knocker_core_services_db[994] == NULL)
    return -1;

  knocker_core_services_db[995] = malloc (5 + 1);
  strcpy (knocker_core_services_db[995], "pop3s");

  if (knocker_core_services_db[995] == NULL)
    return -1;

  knocker_core_services_db[1080] = malloc (5 + 1);
  strcpy (knocker_core_services_db[1080], "socks");

  if (knocker_core_services_db[1080] == NULL)
    return -1;

  knocker_core_services_db[1352] = malloc (9 + 1);
  strcpy (knocker_core_services_db[1352], "lotusnote");

  if (knocker_core_services_db[1352] == NULL)
    return -1;

  knocker_core_services_db[1524] = malloc (10 + 1);
  strcpy (knocker_core_services_db[1524], "ingreslock");

  if (knocker_core_services_db[1524] == NULL)
    return -1;

  knocker_core_services_db[1525] = malloc (11 + 1);
  strcpy (knocker_core_services_db[1525], "prospero-np");

  if (knocker_core_services_db[1525] == NULL)
    return -1;

  knocker_core_services_db[1645] = malloc (11 + 1);
  strcpy (knocker_core_services_db[1645], "datametrics");

  if (knocker_core_services_db[1645] == NULL)
    return -1;

  knocker_core_services_db[1646] = malloc (11 + 1);
  strcpy (knocker_core_services_db[1646], "sa-msg-port");

  if (knocker_core_services_db[1646] == NULL)
    return -1;

  knocker_core_services_db[1812] = malloc (6 + 1);
  strcpy (knocker_core_services_db[1812], "radius");

  if (knocker_core_services_db[1812] == NULL)
    return -1;

  knocker_core_services_db[1813] = malloc (11 + 1);
  strcpy (knocker_core_services_db[1813], "radius-acct");

  if (knocker_core_services_db[1813] == NULL)
    return -1;

  knocker_core_services_db[2101] = malloc (10 + 1);
  strcpy (knocker_core_services_db[2101], "rtcm-sc104");

  if (knocker_core_services_db[2101] == NULL)
    return -1;

  knocker_core_services_db[2401] = malloc (10 + 1);
  strcpy (knocker_core_services_db[2401], "cvspserver");

  if (knocker_core_services_db[2401] == NULL)
    return -1;

  knocker_core_services_db[2430] = malloc (5 + 1);
  strcpy (knocker_core_services_db[2430], "venus");

  if (knocker_core_services_db[2430] == NULL)
    return -1;

  knocker_core_services_db[2431] = malloc (8 + 1);
  strcpy (knocker_core_services_db[2431], "venus-se");

  if (knocker_core_services_db[2431] == NULL)
    return -1;

  knocker_core_services_db[2432] = malloc (7 + 1);
  strcpy (knocker_core_services_db[2432], "codasrv");

  if (knocker_core_services_db[2432] == NULL)
    return -1;

  knocker_core_services_db[2433] = malloc (10 + 1);
  strcpy (knocker_core_services_db[2433], "codasrv-se");

  if (knocker_core_services_db[2433] == NULL)
    return -1;

  knocker_core_services_db[2583] = malloc (3 + 1);
  strcpy (knocker_core_services_db[2583], "mon");

  if (knocker_core_services_db[2583] == NULL)
    return -1;

  knocker_core_services_db[2628] = malloc (4 + 1);
  strcpy (knocker_core_services_db[2628], "dict");

  if (knocker_core_services_db[2628] == NULL)
    return -1;

  knocker_core_services_db[3050] = malloc (6 + 1);
  strcpy (knocker_core_services_db[3050], "gds_db");

  if (knocker_core_services_db[3050] == NULL)
    return -1;

  knocker_core_services_db[3130] = malloc (5 + 1);
  strcpy (knocker_core_services_db[3130], "icpv2");

  if (knocker_core_services_db[3130] == NULL)
    return -1;

  knocker_core_services_db[3306] = malloc (5 + 1);
  strcpy (knocker_core_services_db[3306], "mysql");

  if (knocker_core_services_db[3306] == NULL)
    return -1;

  knocker_core_services_db[5002] = malloc (3 + 1);
  strcpy (knocker_core_services_db[5002], "rfe");

  if (knocker_core_services_db[5002] == NULL)
    return -1;

  knocker_core_services_db[5308] = malloc (8 + 1);
  strcpy (knocker_core_services_db[5308], "cfengine");

  if (knocker_core_services_db[5308] == NULL)
    return -1;

  knocker_core_services_db[6000] = malloc (3 + 1);
  strcpy (knocker_core_services_db[6000], "x11");

  if (knocker_core_services_db[6000] == NULL)
    return -1;

  knocker_core_services_db[6001] = malloc (5 + 1);
  strcpy (knocker_core_services_db[6001], "x11-1");

  if (knocker_core_services_db[6001] == NULL)
    return -1;

  knocker_core_services_db[6002] = malloc (5 + 1);
  strcpy (knocker_core_services_db[6002], "x11-2");

  if (knocker_core_services_db[6002] == NULL)
    return -1;

  knocker_core_services_db[6003] = malloc (5 + 1);
  strcpy (knocker_core_services_db[6003], "x11-3");

  if (knocker_core_services_db[6003] == NULL)
    return -1;

  knocker_core_services_db[6004] = malloc (5 + 1);
  strcpy (knocker_core_services_db[6004], "x11-4");

  if (knocker_core_services_db[6004] == NULL)
    return -1;

  knocker_core_services_db[6005] = malloc (5 + 1);
  strcpy (knocker_core_services_db[6005], "x11-5");

  if (knocker_core_services_db[6005] == NULL)
    return -1;

  knocker_core_services_db[6006] = malloc (5 + 1);
  strcpy (knocker_core_services_db[6006], "x11-6");

  if (knocker_core_services_db[6006] == NULL)
    return -1;

  knocker_core_services_db[6007] = malloc (5 + 1);
  strcpy (knocker_core_services_db[6007], "x11-7");

  if (knocker_core_services_db[6007] == NULL)
    return -1;

  knocker_core_services_db[7000] = malloc (15 + 1);
  strcpy (knocker_core_services_db[7000], "afs3-fileserver");

  if (knocker_core_services_db[7000] == NULL)
    return -1;

  knocker_core_services_db[7001] = malloc (13 + 1);
  strcpy (knocker_core_services_db[7001], "afs3-callback");

  if (knocker_core_services_db[7001] == NULL)
    return -1;

  knocker_core_services_db[7002] = malloc (13 + 1);
  strcpy (knocker_core_services_db[7002], "afs3-prserver");

  if (knocker_core_services_db[7002] == NULL)
    return -1;

  knocker_core_services_db[7003] = malloc (13 + 1);
  strcpy (knocker_core_services_db[7003], "afs3-vlserver");

  if (knocker_core_services_db[7003] == NULL)
    return -1;

  knocker_core_services_db[7004] = malloc (13 + 1);
  strcpy (knocker_core_services_db[7004], "afs3-kaserver");

  if (knocker_core_services_db[7004] == NULL)
    return -1;

  knocker_core_services_db[7005] = malloc (11 + 1);
  strcpy (knocker_core_services_db[7005], "afs3-volser");

  if (knocker_core_services_db[7005] == NULL)
    return -1;

  knocker_core_services_db[7006] = malloc (11 + 1);
  strcpy (knocker_core_services_db[7006], "afs3-errors");

  if (knocker_core_services_db[7006] == NULL)
    return -1;

  knocker_core_services_db[7007] = malloc (8 + 1);
  strcpy (knocker_core_services_db[7007], "afs3-bos");

  if (knocker_core_services_db[7007] == NULL)
    return -1;

  knocker_core_services_db[7008] = malloc (11 + 1);
  strcpy (knocker_core_services_db[7008], "afs3-update");

  if (knocker_core_services_db[7008] == NULL)
    return -1;

  knocker_core_services_db[7009] = malloc (11 + 1);
  strcpy (knocker_core_services_db[7009], "afs3-rmtsys");

  if (knocker_core_services_db[7009] == NULL)
    return -1;

  knocker_core_services_db[7100] = malloc (12 + 1);
  strcpy (knocker_core_services_db[7100], "font-service");

  if (knocker_core_services_db[7100] == NULL)
    return -1;

  knocker_core_services_db[22273] = malloc (4 + 1);
  strcpy (knocker_core_services_db[22273], "wnn6");

  if (knocker_core_services_db[22273] == NULL)
    return -1;

  knocker_core_services_db_init = 1;    /* Initialization complete */

#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif


#ifdef DEBUG
  for (i = 0; i < SERVICES_DB_TOTAL_SERVICES; i++)
    {
      if (knocker_core_services_db[i] != NULL)
        n_of_services++;
    }
  fprintf (stderr, "debug: succesfully stored %d service strings.\n", n_of_services);
#endif

  return 0;
}


void free_knocker_core_services_db (void)
{
  int i;

  /* if it hasn't been initialized yet we don't free anything */
  if (!knocker_core_services_db_init)
    return;

  for (i = 0; i < SERVICES_DB_TOTAL_SERVICES; i++)
    {
	/* FIXME DELIBERATELLY NOT FREEING HERE TO AVOID CRASHDUMPS      
      if (knocker_core_services_db[i] != NULL)
        free (knocker_core_services_db[i]); */
    }

  knocker_core_services_db_init = 0;    /* deinitialized state */
}


char *knocker_core_services_db_get_service (unsigned int port, int protocol)
{
  int slenght;                  /* string lenght */

  if (!knocker_core_services_db_init)
    {
      /* if the services string list is not initialized */
      return NULL;
    }

  if (protocol != PROTO_TCP)
    {

      if (protocol != PROTO_UDP)
        {
          return NULL;
        }
    }

  /* this functions returns the number of copied chars in tmpstr, if it is
     successfull, else -1 */
  if (knocker_core_services_db[port] != NULL)
    slenght = strlen (knocker_core_services_db[port]);
  else
    slenght = -1;

  if (slenght == -1)
    {
      if (knocker_core_last_service == NULL)
        {
          knocker_core_last_service = malloc (strlen ("unknown") + 1);
          strcpy (knocker_core_last_service, "unknown");
        }
      else
        {
          knocker_core_last_service = realloc (knocker_core_last_service, strlen ("unknown") + 1);
          strcpy (knocker_core_last_service, "unknown");
        }
      return NULL;
    }


  if (knocker_core_last_service == NULL)
    {
      knocker_core_last_service = malloc (slenght + 1);
    }
  else
    {
      knocker_core_last_service = realloc (knocker_core_last_service, slenght + 1);

    }

  return (strcpy (knocker_core_last_service, knocker_core_services_db[port]));
}
