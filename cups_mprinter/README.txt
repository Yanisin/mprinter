Simple cups driver for mPrinter
===============================

you will most likely need some devel headers/libraries of cups.
On Debian-like distro it libcups2-dev libcupsimage2-dev libcupsfilters-dev

Quick "howto"
-------------
1)
compile with the given Makefile:
$ make

2)
install the CUPS filter for mprinter
$make install
Eventually modify the makefile if your CUPS filter folder is different.

3)
add printer in CUPS
-in web browser open "localhost:631" or where your cups installation "listens"
-choose adminstration->add printer
-select AppSocket/HP JetDirect, click next
-type socket://<IP address of you mPrinter>:9100, click "continue"
-in next screen fill name and such of your choice
-click on "Choose file" and choose the mprinter.ppd build in step 1)
-then click "add printer"

4)
if all went well you can try to print a test page. ;)
