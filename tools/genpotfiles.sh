#! /bin/sh
# Copyright 2000  Alexandre Duret-Lutz <duret_g@epita.fr>
#
# This file is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

pf=po/POTFILES.in

rm -f $pf
echo '# This file was generated by tools/genpotfiles.sh' > $pf
echo "# on `date`" >> $pf
egrep -l '_\(|N_\(' {lib,src{,/media{,/*}}}/*.{c,h,gperf} >> $pf 2> /dev/null
true