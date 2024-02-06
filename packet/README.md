
chk header firmware packet prgrogram


## Format

---
+----------------+----------------+----+----------------------------+
|  MAGIC (4)     | Header len(4)  |SKU | Version (7)                |
+----------------+----------------+----+----------------------------+
| kernel cksum(4)|rootfs cksum(4) |kernel len                       |       
+----------------+----------------+---------------------------------+
| image cksum    | header cksum   | Board ID  (200)                 | 
+----------------+----------------+---------------------------------+
|  Board ID... (Cont)                                               | 
+-------------------------------------------------------------------+

Magic: Constant value, 4byte , "*#$^"



checksum algorihm
c0 = c1 = 0

c0 += $byte & 0xFF
c1 += c0

b = (c0 & 65535) + ((c0 >> 16)  & 65535)
c0 = ((b >> 16) + b ) & 65535
b = (c1 & 65535 ) + ((c1 >> 16) & 65535)
c1 = ((b >> 16 ) +b) & 65535 
cksum =  ((c1 << 16) | c0)

---

Info: print the firmware infromation by chk header 
cut: truncate the chk header 
create: add chk header in (default)

--usage 
packet.xx <firmware name>  <version x.x.x.x_x.x.x> <boardid>


P.S. packet.sh need to fxcn_cksum program supported, because using the script way byte by byte was very slow


