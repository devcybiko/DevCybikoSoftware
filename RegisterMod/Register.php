<?php
/*****************************************************************************/
/* Register.php                                                              */
/*****************************************************************************/
/* YaBB: Yet another Bulletin Board                                          */
/* Open-Source Project started by Zef Hemel (zef@zefnet.com)                 */
/* Software Version: YaBB SE                                                 */
/* ========================================================================= */
/* Software Distributed by:    http://www.yabb.info                          */
/* Support, News, Updates at:  http://www.yabb.info/community                */
/*                             http://yabb.xnull.com/community               */
/* ========================================================================= */
/* Copyright (c) 2001-2002 Lewis Media - All Rights Reserved                 */
/* Software by: The YaBB Development Team                                    */
/*****************************************************************************/
/* This program is free software; you can redistribute it and/or modify it   */
/* under the terms of the GNU General Public License as published by the     */
/* Free Software Foundation; either version 2 of the License, or (at your    */
/* option) any later version.                                                */
/*                                                                           */
/* This program is distributed in the hope that it will be useful, but       */
/* WITHOUT ANY WARRANTY; without even the implied warranty of                */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General */
/* Public License for more details.                                          */
/*                                                                           */
/* The GNU GPL can be found in gpl.txt in this directory                     */
/*****************************************************************************/

$registerplver="YaBB SE 1.4.1";

function Register (){
	global $yytitle,$txt,$color,$cgi,$action,$allow_hide_email,$modSettings,$RegAgree,$emailpassword,$vardir,$db_prefix;
	global $imagesdir, $boarddir;
	$yytitle = "$txt[97]";
	template_header();
	print <<<EOT
<form action="$cgi;action=register2" method="POST" name="creator" onSubmit="alert('There will be a 30-second delay');">
<table border="0" width="100%" cellspacing="1" bgcolor="$color[bordercolor]" class="bordercolor" cellpadding="2">
  <tr>
    <td class="titlebg" bgcolor="$color[titlebg]"><font size=2 class="text1" color="$color[titletext]"><b>$txt[97]</b> $txt[517]</font></td>
  </tr><tr>
    <td class="windowbg" bgcolor="$color[windowbg]" width="100%">
    <table cellpadding="3" cellspacing="0" border=0 width="100%">
      <tr>
        <td width="40%"><font size=2>* <b>$txt[98]:</b></font>
        <BR><font size="1">$txt[520]</font></td>
        <td><input type=text name=user size=20 maxlength=18></td>
      </tr><tr>
        <td width="40%"><font size=2>* <b>$txt[69]:</b></font>
        <BR><font size="1">$txt[679]</font></td>
EOT;
if ($allow_hide_email == 1) {
print <<<EOT
        <td><font size=2><input type=text name=email size=30> <input type="checkbox" name="hideemail"> $txt[721]</font></td>
EOT;
}
else {
print <<<EOT
        <td><input type=text name=email size=30>
        <BR><font size="1">$txt[679]</font></td>
EOT;
}
print "      </tr>\n";
	if( $emailpassword == "") {
		print <<<EOT
      <tr>
        <td width="40%"><font size=2>* <b>$txt[81]:</b></font></td>
        <td><font size=2><input type=password name=passwrd1 size=30></font></td>
      </tr><tr>
        <td width="40%"><font size=2>* <b>$txt[82]:</b></font></td>
        <td><font size=2><input type=password name=passwrd2 size=30></font></td>
      </tr>
EOT;
}
mt_srand(time());
$digit1 = mt_rand(0,9);
$digit2 = mt_rand(0,9);
$digit3 = mt_rand(0,9);
$digit4 = mt_rand(0,9);
$outfile = fopen("$boarddir/a.txt", "w") or die("fopen failed");
fwrite($outfile, "$digit1$digit2$digit3$digit4") or die("fwrite failed");
fclose($outfile) or die("fclose failed");
$imagedir = $boarddir."/YaBBImages";
copy("$imagedir/digits/$digit1.jpg", "$imagedir/1.jpg");
copy("$imagedir/digits/$digit2.jpg", "$imagedir/2.jpg");
copy("$imagedir/digits/$digit3.jpg", "$imagedir/3.jpg");
copy("$imagedir/digits/$digit4.jpg", "$imagedir/4.jpg");
print "<tr><td><font size=2>* <b>Enter this Number:</b></font><img src=$imagesdir/1.jpg><img src=$imagesdir/2.jpg><img src=$imagesdir/3.jpg><img src=$imagesdir/4.jpg></td><td><input type=text name=secretcode></td></tr>";
print <<<EOT
    </table>
    </td>
  </tr>
</table>
EOT;
if ($RegAgree) {
	$request = mysql_query("SELECT value FROM {$db_prefix}settings WHERE variable='agreement'");
	$temp = mysql_fetch_row($request);
	$fullagree = nl2br($temp[0]);
	print <<<EOT
<table border=0 cellspacing=1 cellpadding="5" bgcolor="$color[bordercolor]" class="bordercolor" width="100%" align="center">
  <tr>
    <td bgcolor="$color[windowbg2]" class="windowbg2">
    <font size=2><BR>$fullagree<BR><BR></font>
    </td>
  </tr><tr>
    <td bgcolor="$color[windowbg]" align="center" class="windowbg"><font size=2>
    <B>$txt[585]</B> <input type=radio name="regagree" value="yes">
    &nbsp;&nbsp;&nbsp; <B>$txt[586]</B> <input type=radio name="regagree" value="no" checked>
    </font></td>
  </tr>
</table>
EOT;
}
	print <<<EOT
<BR><center><input type=submit value="$txt[97]"></center>
</form>
EOT;
	footer();
	obExit();
}

function Register2 () {
	global $HTTP_GET_VARS,$HTTP_POST_VARS,$mbname,$emailwelcome,$Cookie_Length,$emailpassword,$color,$cgi;
	global $hideemail,$yySetLocation,$scripturl,$yyTitle,$txt,$user,$regagree,$db_prefix,$webmaster_email;
	global $allow_hide_email,$modSettings,$REMOTE_ADDR, $boarddir, $secretcode;

	sleep(20);
	$lines = file("$boarddir/a.txt");
	$secretcode = $HTTP_POST_VARS['secretcode'];
	if ($secretcode != $lines[0]) {
		die("Go back and try again");
	}

	$hideemail = ($allow_hide_email && $hideemail=='on')?'1':'0';

	if($regagree == "no") {
        header("Location: $scripturl");
        exit();
  	}
	$member = array();
    foreach($HTTP_GET_VARS as $key => $value)
		$member[$key] = str_replace("\n","",str_replace("\r","",trim($value)));
	foreach($HTTP_POST_VARS as $key=>$value)
		$member[$key] = str_replace("\n","",str_replace("\r","",trim($value)));

#	$member[username] = str_replace(list(" ","\t"),"_",$member[username]);
	if (strlen($member['user']) > 25) { $member['user'] = substr($member['user'],0,25); }
	if($member['user'] == '') {fatal_error("$member[user] $txt[37]"); }
	if(!preg_match("/^[\s0-9A-Za-z#,-\.:=?@^_äöéèöüçåãâáàßêìíîïðñòóôõøùúûýÿ]+$/",$user)) {fatal_error("$txt[240]"); }
	if($member['user'] == '_' || $member['user'] == '|') {fatal_error("$member[user] $txt[99]"); }
	if(strstr($member['user'],"Guest")) { fatal_error("$txt[244] $member[user]");}
	//if(!preg_match("/A[0-9A-Za-z#%+,-\.@^_]+\Z/",$member['user'])) {fatal_error("$txt[240]");}
	if($member['email'] == ""){ fatal_error("$member[user] $txt[76]"); }
	$request = mysql_query("SELECT ID_MEMBER FROM {$db_prefix}members WHERE memberName='$member[user]'");
	if(mysql_num_rows($request) > 0) { fatal_error("($member[user]) $txt[100]"); }

	if( $emailpassword )
	{
		// randomly generate a new password
		mt_srand(time());
		$password = crypt(mt_rand(-100000,100000));
	
		// remove all non alpha-numeric characters
		$password = preg_replace("/\W/","",$password);

		// limit it to 10 characters max
		$member['passwrd1']= substr($password,0,10);
	}
	else
	{
		if($member['passwrd1'] !=  $member['passwrd2']) { fatal_error("($member[username]) $txt[213]");}
		if($member['passwrd1'] == '') {fatal_error("($member[username]) $txt[91]");}
	}

	$request = mysql_query ("SELECT value FROM {$db_prefix}banned WHERE (type='email' && value='$member[email]')");
	if (mysql_num_rows($request) > 0)
		fatal_error("$txt[678]$txt[430]!");

	/* Check if the email address  or the username is in use */
	$request = mysql_query("SELECT realName FROM {$db_prefix}members WHERE emailAddress='$member[email]'");
	if (mysql_num_rows($request) > 0)
		fatal_error("$txt[730] ($member[email]) $txt[731]");
	$request = mysql_query("SELECT realName FROM {$db_prefix}members WHERE (memberName='$member[user]' || realName='$member[user]')");
	if (mysql_num_rows($request) > 0)
		fatal_error("($member[user]) $txt[473]");
	htmlentities($member['email']);

	$request = mysql_query("SELECT setting,value FROM {$db_prefix}reserved_names WHERE 1");
	if (mysql_num_rows($request) > 0 )
	{
		$reserve = array();
		while ($row = mysql_fetch_array($request))
			if ($row['setting'] == 'word')
				$reserve[] = trim($row['value']);
			else
				${$row['setting']} = trim($row['value']);

		$namecheck = ($matchcase == '1') ? $member['user'] : strtolower($member['user']);

		foreach ($reserve as $reserved) {
			$reservecheck = ($matchcase=='1') ? $reserved : strtolower ($reserved);
			if ($matchuser=='1') {
				if ($matchword=='1') {
					if ($namecheck == $reservecheck) { fatal_error("$txt[244] $reserved"); }
				}
				else {
					if (strstr($namecheck,$reservecheck)) { fatal_error("$txt[244] $reserved"); }
				}
			}
		}
	}

	$request = mysql_query("SELECT ID_MEMBER FROM {$db_prefix}members WHERE memberName='$member[user]'");
	if (mysql_num_rows($request) > 0)
		fatal_error("$txt[100]");

	$requesttime = time();

	$queryPasswdPart = crypt($member['passwrd1'],substr($member['passwrd1'],0,2));
    $memIP=$REMOTE_ADDR;
	$request = mysql_query("INSERT INTO {$db_prefix}members (memberName,realName,passwd,emailAddress,posts,personalText,avatar,dateRegistered,hideEmail,memberIP) VALUES ('$member[user]','$member[user]','$queryPasswdPart','$member[email]',0,'$txt[209]','blank.gif',$requesttime,'$hideemail','$memIP')");

    if ($modSettings['trackStats']==1){
      $date = getdate(time());
      $statsquery = mysql_query("UPDATE {$db_prefix}log_activity SET registers = registers + 1 WHERE month = $date[mon] AND day = $date[mday] AND year = $date[year]");
      if(mysql_affected_rows() == 0)
        $statsquery = mysql_query("INSERT INTO {$db_prefix}log_activity (month, day, year, registers) VALUES ($date[mon], $date[mday], $date[year], 1)");
    }

	$yytitle="$txt[245]";
	template_header();


	if( $emailpassword ) {
		sendmail($member['email'], "$txt[700] $mbname", "$txt[248] $member[user]!\n\n$txt[719] $member[user]\n\n $txt[492] $member[passwrd1]\n\n$txt[701]\n",$webmaster_email);

		print <<<EOT
<BR>
<table border=0 width=100% cellspacing=1 bgcolor="$color[bordercolor]" class="bordercolor" align="center">
  <tr>
    <td class="titlebg" bgcolor="$color[titlebg]"><font size=2 class="text1" color="$color[titletext]"><b>$txt[97]</b></font></td>
  </tr><tr>
    <td class="windowbg" bgcolor="$color[windowbg]" align="left" cellpadding=3><font size=2>$txt[703]</font></td>
  </tr><tr>
    <td class="windowbg" bgcolor="$color[windowbg]" valign=top><form action="$cgi;action=login2" method="POST">
    <table border=0 cellpadding="0" cellspacing="0">
      <tr>
        <td><font size=2><b>$txt[35]:</b></font></td>
        <td><font size=2><input type=text name="user" size=15 value="$member[user]"></font></td>
        <td><font size=2><b>$txt[36]:</b></font></td>
        <td><font size=2><input type=password name="passwrd" size=10></font> &nbsp;</td>
        <td><font size=2><b>$txt[497]:</b></font></td>
        <td><font size=2><input type=text name="cookielength" size=4 value="$Cookie_Length">
        <td><font size=2><b>$txt[508]:</B></font></td>
        <td><font size=2><input type=checkbox name="cookieneverexp"></font></td> &nbsp;</font></td>
        <td align=center colspan=2><input type=submit value="$txt[34]"></td>
      </tr>
    </table>
		</form>
    </td>
  </tr>
</table>
EOT;
	}
	else {
	if( $emailwelcome ) {
		$euser=urlencode($member['user']);
		sendmail($member['email'],"$txt[700] $mbname", "$txt[248] $member[user]!\n\n$txt[719] $member[user], $txt[492] $member[passwrd1]\n\n$txt[701]\n$scripturl?action=profile;user=$euser\n\n$txt[130]",$webmaster_email);
	}
		print <<<EOT
<BR><BR><BR>
<center>$txt[431]</center>
<BR><BR>
<table border=0 width=300 cellspacing=1 bgcolor="$color[bordercolor]" class="bordercolor" align="center">
  <tr>
    <td class="titlebg" bgcolor="$color[titlebg]"><font size=2 class="text1" color="$color[titletext]"><b>$txt[97]</b></font></td>
  </tr><tr>
    <td class="windowbg" bgcolor="$color[windowbg]" align="center"><font size=2><form action="$cgi;action=login2" method="POST">
    <input type=hidden name="user" value="$member[user]">
    <input type=hidden name="passwrd" value="$member[passwrd1]">
    <input type=hidden name="cookielength" value="$Cookie_Length">
    <input type=submit value="$txt[34]"></td>
    </form></font>
    </td>
  </tr>
</table>
EOT;
	}
	footer();
	obExit();
}

?>
