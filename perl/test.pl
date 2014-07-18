#!/usr/bin/perl -w

#open LOG, ">>logfile";
#print LOG "this is a message.\n";

#open LOG, "logfile";
#while (<LOG>) {
#   print;
#}

##array
#my @aaa=(1,2,"a");
#
#foreach (0..$#aaa) {
#   print ("$aaa[$_]\n");
#}
#
#print "\n";
#
##hash
#my %bbb = ("0" => 1, "dd" => 2, "2" => "a");
#
#foreach (keys %bbb) {
#   print "$_ => $bbb{$_}\n";
#}
#
#while (($key, $value) = each %bbb) {
#   print "$key => $value\n";
#}

#for (@INC) {
#   print ("$_\n");
#}

#$_ = "yabba dabba doo";
#if (/abba/) {
#    print "It matched!\n";
#}

#my $md5_out = `md5sum test.pl`;
#my ($md5) = $md5_out =~ /^(\w+)\s/;
#print "$md5_out";
#print "$md5\n";
#
#
#$_ = "ahttp://www.fortinet.com";
#if (m%^http://%) {
#    print "It matched!\n";
#}


#my $file = "2012-12-12_15-38-21=DEV_2_B=1=9ac5013fcad9a4c8251d03c4977dedd9.tgz";
#my ($filename_md5) = $file =~ /=([0-9a-f]+).tgz$/;
#print "$filename_md5\n";


#my $a1 = "baaabbb";
#my ($a2, $a3) = $a1 =~ /([a]+)([b]+)/;
#print "$a2\n";
#print "$a3\n";

#$_ = "Hello there, neighbor!";
#my ($first, $second, $third) = /(\S+) (\S+), (\S+)/;
#print "$second is my $third\n";

#my $match = "Nand flash has 0X1000 blocks, bad block(s): 0X0004";
#my ($badblocks) = $match =~ /Nand flash has .* blocks, bad block.*: 0X(.*)/;
#print "$badblocks\n";
#$badblocks = hex $badblocks;
#print "$badblocks\n";


#my $prompt = '/Blocks verification passed!|Failed block of verification:/i';
##$_ = "Blocks verification passed!";
#$_ = "Failed block of verification";
#if (/Blocks verification passed!|Failed block of verification:/i) {
#    print "It matched!\n";
#}




#my $prematch = "bad block 0x0725, pos 0x01c94000, ret=1
#bad block 0x0a97, pos 0x02a5c000, ret=1
#bad block 0x0b53, pos 0x02d4c000, ret=1
#bad block 0x0b69, pos 0x02da4000, ret=1
#bad block 0x0e64, pos 0x03990000, ret=1
#bad block 0x0ef7, pos 0x03bdc000, ret=1
#bad block 0x0f63, pos 0x03d8c000, ret=1";
#my @marr = $prematch =~ /(bad block \w+, pos \w+, ret=1)/img;
#
#print scalar(@marr)."\n";




##my $date = "02/07/2013";
#my $date = "2013-02-07";
#my ($month,$day,$year) = $date=~ /(\d+)\/(\d+)\/(\d+)/;
#if (!$month || !$day || !$year) {
#    ($year,$month,$day) = $date=~ /(\d{4})\-(\d{2})\-(\d{2})/;
#}
#print "$month,$day,$year\n";
#
#


#my $date_now = "02/07/2013";
#my ($month, $day, $year) = $date_now =~ /(\d+)\/(\d+)\/(\d+)/;
#$date_now = $year."-".$month."-".$day;
#print "$date_now\n";






#my $out = "diagnose npu np4 stat\n
#The following NP4 IDs are available:\n
#\n
#0\n
#1\n
#";
#
#my @IDs;
#my @out = split(/\n/, $out);
#foreach my $line (@out)
#{
#    if ($line =~ /^(\d)/) {
#        push (@IDs, $1);
#    }
#}
#
#foreach (@IDs) {
#    print "$_\n";
#}








#my $out = "
#diagnose npu np2 performance 0
#NP2 Performance
#
#ISCP2 Performance:
#Nr_int	  : 0x00002eb6	 INTwoInd  : 0x00000000	 RXwoDone  : 0x00000000
#PKTwoEnd : 0x00000000	 PKTCSErr  : 0x00000000
#PKTidErr : 0x00000000
#CSUMOFF  : 0x00000000	 BADCSUM   : 0x00000000	 MSGINT	   : 0x00000000
#IPSEC	  : 0x00000000	 IPSVLAN   : 0x00000000	 SESMISS   : 0x00000000
#TOTUP	  : 0x00000000	 TCPPLTOT  : 0x00000000	 TCPPLBADCT: 0x00000000
#TCPPLBADL: 0x00000000	 TCPPLSESI : 0x00000000	 TCPPLSESR : 0x00000000
#TCPPLBD  : 0x00000000	 TXInt	   : 0x5be/0x487/0x5c6/0x47a RxI : 0x1c2b
#BDEmpty  : 0x0/0x0/0x0/0x0 Congest: 0x0/0x0/0x0/0x0
#TMM_Busy : 0x0
#Poll List: 0 0 0 0
#MSG Performance:
#TOTMSG	 : 0x00000000	BADMSG	  : 0x00000000	 TOUTMSG  : 0x00000000 MSGLostEvent : 0x00000000
#QUERY	 : 0x00000000	TAE	  : 0x00000000
#SAEXP-SN : 0x00000000	SAEXP-TRF : 0x00000000	 OUTUPD	  : 0x00000000 INUPD	 : 0x00000000
#NULLTK: 0x00000000
#NAT Performance: BYPASS (Enable) BLOCK (Disable)
#
#IRQ    : 00000524 QFTL   : 00000000 DELF  : 00000000 FFTL  : 00000000
#OVTH   : 00000524 QRYF   : 00000000 INSF  : 00000000 INVC  : 00000000
#ALLO   : 00000c3b FREE   : 00000c3b ALLOF : 00000000 BPENTR: 00000000 BKENTR: 00000000
#PBPENTR: 00000000 PBKENTR: 00000000 NOOP  : 00000000 THROT : 00000000(0x002625a0)
#SWITOT : 0000061a SWDTOT : 0000061a ITDB  : 00000000 OTDB  : 00000000
#SPISES : 00000000 FLUSH  : 00000000
#";
#
#my @out = split(/\n/, $out);
#
#my $out_session_insert = 'SWITOT\s*:\s*(\w+)\s+';
#my        $out_session_del = 'SWDTOT\s*:\s*(\w+)\s+';
#my ($session_insert, $session_del);
#foreach my $line (@out)
#{
#    #print "$line\n";
#    if ($line =~ /$out_session_insert/) {
#        $session_insert = $1;
#        print "session_insert: $session_insert\n";
#    }
#    if ($line =~ /$out_session_del/) {
#        $session_del = $1;
#        print "session_del: $session_del\n";
#    }
#}
#
#print hex '10';












#
#my $npu_ses_del_ratio = 'NA';
#my $check_np_msg = "Check Np: SWITOT: 0, SWDTOT: 12496, npu_ses_del_ratio: $npu_ses_del_ratio";
#if (my ($ses_ins_name, $ses_ins, $ses_del_name, $ses_del, $npu_ses_del_ratio)
#    = $check_np_msg =~ /Check Np: (\w+): (\w+), (\w+): (\w+), npu_ses_del_ratio: (\w+)/) {
#    print "----------------------------------\n";
#}





#my $ratio = 0.02;
#my $a = $ratio*100;
#print "$ratio"*"100"."%\n";
#my $b = 100;
#$b += 100;
#print "$b\n";
#




#my $str = 'a';
#if ($str && $str eq 'a') {
#    print "a\n";
#}





#my @aaa = (1,2);
#if (!@aaa) {
#    print "1\n";
#}








#my $NpuCheck = 'enable';
#if ($NpuCheck =~ /Enable/i)
#{
#    print "----------\n";
#}

















#my $txt = "y
#
#
#System is shutting down...
#
#System is shutting down...
#
#
#The system is going down NOW !!
#
#System is shutting down...
#
#FG3K2C3Z12800034 (global) #
#The system is halted.";

#my $txt = "y
#
#
#System is shutting down...
#
#System is shutting down...
#
#
#The system is going down NOW !!
#
#System is shutting down...
#
#FG3K2C3Z12800034 (global) #
#The system is halted.";
#
#if ($txt =~ /y\s*(System is shutting down\.+\s*|The system is going down NOW \!+\s*)+\s*\w{16}\s(\(global\)\s)*#\s*The system is halted/mi)
#{
#    print "----------\n";
#}
#





#my $s = 'TX: 713Mbps, RX: 0Mbps';
#my ($TX, $RX) = $s =~ /TX: (\d+)Mbps, RX: (\d+)Mbps/;
#print "$s\n";
#print "TX: $TX\n";
#print "RX: $RX\n";



#my $logcnt = "====== Round 1 ======
## netperf -t TCP_STREAM -H 10.16.1.2 -D 5 -l 10 -f m -P 1 -- -s 256K -S 256K -m 1460 -P 20051,20051 >> /var/log/bit_pro/2013-8-27_12-53-43=DEV_3_A/TrafficLog_1st_1/Session1_1/netperf_tcp_1.log 2>&1 &
#MIGRATED TCP STREAM TEST from 0.0.0.0 (0.0.0.0) port 20051 AF_INET to 10.16.1.2 () port 20051 AF_INET : histogram : interval : demo
#Interim result:  128.46 10^6bits/s over 5.064 seconds ending at 1377579676.901
#Interim result:  118.14 10^6bits/s over 0.088 seconds ending at 1377579676.989
#recv_response: partial response received: 0 bytes
#====== Round 2 ======
## netperf -t TCP_STREAM -H 10.16.1.2 -D 5 -l 10 -f m -P 1 -- -s 256K -S 256K -m 1460 -P 20052,20052 >> /var/log/bit_pro/2013-8-27_12-53-43=DEV_3_A/TrafficLog_1st_1/Session1_1/netperf_tcp_1.log 2>&1 &
#MIGRATED TCP STREAM TEST from 0.0.0.0 (0.0.0.0) port 20052 AF_INET to 10.16.1.2 () port 20052 AF_INET : histogram : interval : demo
#Interim result:  125.10 10^6bits/s over 5.006 seconds ending at 1377579683.182
#Interim result:  120.97 10^6bits/s over 4.994 seconds ending at 1377579688.176
#Recv   Send    Send
#Socket Socket  Message  Elapsed
#Size   Size    Size     Time     Throughput
#bytes  bytes   bytes    secs.    10^6bits/sec
#
#524288 524288   1460    10.26     119.96";
#
#my @log_arr = split(/====== Round \d+ ======/, $logcnt);
#my $last_log = $log_arr[@log_arr - 1];
#print "last_log: $last_log\n";
#
#my @thpt_arr    = $last_log =~ /Interim result:\s+(.*)\s+over/mgi;
# my $tool_thpt   = $thpt_arr[ @thpt_arr -  1 ];
#
#
# print "\n\ntool_thpt: $tool_thpt\n";

#my $a = "abc";
#my $ref = \$a;
#print "$ref\n";
#my $deref = $$ref;
#print "$deref\n";
#
#my @b = qw(aa bb cc);
#$ref = \@b;
#print "$ref\n";
#$deref = @$ref;
#print "$deref\n";


#sub ff {
#    my ($dev, %k) = @_;
#    print "$k{String}\n";
#    print "$k{K}\n";
#    print "$dev\n";
#}
#
#my %hash = (String=>1, K=>2);
#&ff(1, %hash);


#my $fail = 0;
#
## check interfaces status
#if (!$fail) {
#    my $out = `ethtool eth1 |grep -i speed`;
#    print "eth1: $out";
#    my ($eth1_speed) = $out =~ /([\d.]+)/;
#    if (!defined($eth1_speed)) {
#        $fail = 1;
#    }
#    if (!$fail) {
#        $out = `ethtool eth2 |grep -i speed`;
#        print "eth2: $out";
#        my ($eth2_speed) = $out =~ /([\d.]+)/;
#        if (!defined($eth2_speed)) {
#            $fail = 1;
#        }
#    }
#    print "fail: $fail\n";
#}


#my $s = "a b  c d";
#$s =~ s/\s{1,}/_/g;
##$s =~ s/ /_/g;
#print "$s\n";

#my $os_str = "v5.0_build0252";
#my ($os_ver) = $os_str =~ /.*(v\d+\.\d+).*/;
#print "$os_ver\n";

#my $err_msg = 'aaa ';
#$err_msg .= "exit now!";
#print "$err_msg\n";

#my $msg = 'Device S*           7.5 GB      ref: n/a         USB DISK Pro (USB)';
#if ($msg =~ /Device\s*S\*\s*\d\.\d\s*GB\s*ref:\s*n\/a\s*USB\s*DISK\s*Pro\s*\(USB\)/) {
#    print "a\n"
#}

# my $outmsg = '524288 524288 524288    14.00       0.00';
# my ($np_pkg, $np_time, $tool_thpt) = $outmsg 
#             =~ /^\d+\s+\d+\s+([\d.]+)\s+([\d.]+)\s+([\d.]+)\s*$/m;
# print "tool_thpt: $tool_thpt\n";
# if ($tool_thpt eq '0.00') {
#     print "1\n";
# }

# my $cmdout = "== [ port36 ]
# name: port36    link-status: down   status: up
# == [ port37 ]
# name: port37    link-status: down   status: up
# == [ port38 ]
# name: port38    link-status: down   status: up
# == [ port39 ]
# name: port39    link-status: down   status: up
# == [ port40 ]
# name: port40    link-status: down   status: up
# == [ port41 ]
# name: port41    link-status: down   status: up
# == [ port42 ]
# name: port42    link-status: down   status: up
# == [ port43 ]
# name: port43    link-status: down   status: up
# == [ port44 ]
# name: port44    link-status: down   status: up
# == [ port45 ]
# name: port45    link-status: up (10Gbps full-duplex)   status: up
# == [ port46 ]
# name: port46    link-status: down   status: up
# == [ port47 ]
# name: port47    link-status: up (10Gbps full-duplex)   status: up
# == [ port48 ]
# name: port48    link-status: down   status: up
# == [ port49 ]
# name: port49    link-status: down   status: up
# == [ port50 ]
# name: port50    link-status: down   status: up
# == [ port51 ]
# name: port51    link-status: down   status: up
# == [ port52 ]
# name: port52    link-status: down   status: up
# == [ internal ]
# name: internal    link-status: up (1Gbps full-duplex)";

# if ($cmdout =~ /name:\s+port46\s+link-status:\s+up.*/i) {
#     print("kkkk");
# }


# my $cmdout = 'config switch interface
# edit "port1"
# set allowed-vlans 50
# next
# edit "port2"
# next
# edit "port3"
# set allowed-vlans 51
# next
# edit "port4"
# set native-vlan 2
# next
# edit "internal"
# set native-vlan 4095
# set stp-state disabled
# next
# edit "bit_trunk"
# next
# end';

# my @linearr = split("next\n", $cmdout);
# foreach my $section (@linearr) {
#     # print("$section\n\n")
#     my ($port) = $section =~ /edit\s+\"(\w+)\"/;
#     my ($vid) = $section =~ /set\s+allowed-vlans\s+(\d+)/;
#     if ($vid) {
#         print("$port: $vid\n");
#     }
# }

# my $vlan = '50';
# if (index($vlan, ',') == -1) {
#     print($vlan);
# }

# $vlan = '50,51';
# if (index($vlan, ',') == -1) {
#     print($vlan);
# }

my $i = 1;
my $a;
my $b;
($a, $b) = $i =~ /(\d+)-*(\w*)/;
if (defined($b)) {
    print("$a-$b\n");
} else {
    print("$a\n");
}