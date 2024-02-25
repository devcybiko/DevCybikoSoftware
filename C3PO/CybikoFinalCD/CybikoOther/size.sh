#!/bin/csh
foreach i ( *.exe )
	set size=`ls -l $i | tail -1` 
	echo "insert into cybikoapps set app_size=$size[5], app_author='Cybiko Inc.', filename='Cybiko/CybikoOther/$i', app_name='`basename $i .exe`', app_release='2001-01-01', app_windows=1, app_xtreme=1, app_classic=1;"
end
