#!/bin/csh
echo "use gregsmith;"
set s=`ls *.app`
foreach i ( $s )
	echo "update cybikoapps set app_readme=lower('http://www.cybiko.com/download/game/`basename $i .app`.asp') WHERE app_name='`basename $i .app`';"
end
