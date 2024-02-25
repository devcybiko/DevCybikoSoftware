#!/bin/csh
foreach i ( *.* )
	set size=`ls -l $i | tail -1` 
	echo "update cybikoapps set app_size=$size[5] where filename='Cybiko/CybikoApps/$i';"
end
