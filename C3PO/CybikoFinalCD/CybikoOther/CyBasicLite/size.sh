#!/bin/csh
foreach i ( *.bs.txt )
	set size=`ls -l $i | tail -1` 
	echo "insert into cybikoapps set app_size=$size[5], app_author='Cybiko Inc.', filename='Cybiko/CybikoOther/CyBasicLite/$i', app_name='`basename $i .bs.txt`', app_release='2001-01-01', app_basic=1;"
end
