/* This is not the real Pilot.h or PalmOS.h!

   The genuine files are part of a Palm OS SDK, which is not part of prc-tools.
   But it is a common error to install SDKs incorrectly, or not to install any
   at all, or to use the old-style Pilot.h with a new-style SDK or vice versa,
   and the following is not always a very useful diagnostic:

	Pilot.h: No such file or directory

   This placeholder file lets us provide a better explanation.  */

#error No genuine Pilot.h found
#warning use PalmOS.h instead if you are using the 3.5 SDK or later; \
you may need to run palmdev-prep or use a suitable -palmosX option -- \
see "http://prc-tools.sourceforge.net/cgi-bin/info/palmdev-prep" for details
