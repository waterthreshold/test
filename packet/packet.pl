#!/usr/bin/perl -w 
use strict;
use warnings;
=pod
print "$-\n";
print "$$\n";
print "$^F\n";
print "$^S\n";
print "$>\n";
print "$~\n";
print "$^X\n";
=cut 

#my $version='1.1.0.16_2.1.25'
#validate_version ($version);

my @version_array =();
sub calculate_checksum {
	my $c0 = 0;
	my $c1 = 0;
	my $checksum =0;
	my @s = unpack('C*', $_[0]);
	foreach  my $byte (@s){
		$c0 += $byte & 0xFF;
		$c1 += $c0;
	}
	my $b = ($c0 & 65535 ) + (( $c0 >> 16) & 65535 );
	$c0 = (($b>>16) + $b) & 65535;
	
	$b = ($c1 & 65535) + (($c1 >> 16)  & 65535);
	$c1 = ($b >> 16) + $b & 65535;

	$checksum = ( ( $c1 << 16 ) | $c0);
	return int ($checksum);
}
sub validate_version {
	my $version = $_[0];
	my ($main_ver , $sub_ver) = split(/_/ , $version);	
	# main_version item must be 4 
	my @main_ver_arr = split (/\./, $main_ver);

	my $count =  @main_ver_arr;
	if( $count != 4 ){
		print STDERR "Main Version must have  4 item seperate by .\n";
		return 0;
	}
	# sub_version item must be 3 
	my @sub_ver_arr = split (/\./, $sub_ver);
	
	$count =  @sub_ver_arr;
	my $tmp='';
	if( $count != 3 ){
		print STDERR "Sub Version must have  3 item seperate by .\n";
		return 0;
	}
	foreach  $tmp (@main_ver_arr){
			#print "$tmp\n";
		if ( int ($tmp) > 255 ){
			return 0;
		}
		push @version_array, $tmp;
	}
	foreach  $tmp (@sub_ver_arr){
			#		print "$tmp\n";
		if( int ($tmp) > 255){
			return 0;
		}
		push @version_array, $tmp;
	}
	

	return 1;
	
}
sub create_header {
	my $board_id =$_[0];
	my $image_buf = $_[1];
	my @buf;
	my $length = 40 + length ($board_id);
	my $magic= '*#$^';
	# 1 magic
	my @tmp = unpack ("C*", $magic);
	for my $i (@tmp){
		push @buf, $i;
	}
	# 2  length
	for  my $i (0..3){
		push @buf, ($length >> (8 * (3 - $i))) & 0xFF;
	}
	#2.1 sku 
	push @buf ,1; 
	# 3 version
	push @buf, @version_array;
	# 4, kernel checksum as image checksum	
	my $kernel_cksum = calculate_checksum( $image_buf);	
	for my $i (0..3){
		push @buf, ($kernel_cksum >> (8 * ( 3- $i))) & 0xFF;
	}
	#5, rootfs checksum  always 0
	my $rootfs_cksum = 0 ; 
	for my $i (0..3){
		push @buf, ($rootfs_cksum >> (8 * (3-$i))) & 0xFF;
	}	
	
	# 6 , kernel length
	my $kernel_len = length ($image_buf);
	for my $i (0..3){
		push @buf, ($kernel_len >> (8 * (3-$i))) & 0xFF;
	}	

	#7, rootfs length always 0
	my $rootfs_len = 0 ; 
	for my $i (0..3){
		push @buf, ($rootfs_len >> (8 * (3-$i))) & 0xFF;
	}	
	#8 image checksum as kernel checksum
	my $img_cksum =$kernel_cksum;
	for my  $i (0..3){
		push @buf, ($img_cksum >> (8 * ( 3- $i))) & 0xFF;
	}
	my @tmp_buf= @buf;
	for my $i (0..3){
		push @buf, ($rootfs_len >> (8 * (3-$i))) & 0xFF;
	}	
	#10 board id 
	@tmp = unpack ('C*',$board_id);
	for my $i (@tmp){
		push @buf, $i;
	}

	#9 header checkusm fullfill 0 first 
	my $header_cksum = calculate_checksum (pack('C*', @buf));
	for my $i (0..3){
		push @tmp_buf, ($header_cksum >> (8 * (3-$i))) & 0xFF;
	}	
	for my  $i (@tmp){
		push @tmp_buf, $i;
	}
	
	return pack ("C*",@tmp_buf);	
}

sub main {
	my $version =$_[0];
	my $model = $_[1];
	my $filename = $_[2];
	my $new_file_name = $filename . ".chk";
		print "Model = $model\n";
	print "version = $version\n";
	print "File_name = $filename Create file=$new_file_name\n";
	if ( !  -e  $filename ) {
		die "Path not exist !!" 
	}	
	if (validate_version ($version) == 0) {
		die "First Parameter Version is Wrong!!";
	}
	#	my $board_id = get_board_id ($model);
	my $board_id = $model;
	print "$board_id\n";	
	my $file_buf;
	my $header_buf;
	open my $fp , '<:raw', $filename;
	read ($fp,$file_buf, -s $filename);
	close $fp;
	$header_buf = create_header ($board_id,$file_buf); 
	open $fp , '>:raw', $new_file_name;
	print $fp $header_buf;
	print $fp $file_buf;
	close $fp;

	print "done\n";
	return 0;
}
sub get_board_id {
	return 'U12H478T20_NETGEAR';
}

=pod
~~~~
 Main Programe
~~~`
=cut 
if (@ARGV != 3 ) {
	die "Usage: $0 <Version> <model> <original firmware >\n";
}
main ($ARGV[0],$ARGV[1],$ARGV[2]); 
