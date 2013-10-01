#
#    This file is part of mPrinter CUPS Driver.
#
#    mPrinter CUPS driver is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    mPrinter CUPS Driver is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with mPrinter CUPS Driver.  If not, see <http://www.gnu.org/licenses/>.
#
#
#	  (c)2013 Stepan Badger Knakal 
#	
#	  http://jezevcinora.cz/mprinter_forum
#


all: mprinter.ppd rastertomprinter


mprinter.ppd: mprinter.drv
	ppdc -d . mprinter.drv

rastertomprinter.o: rastertomprinter.c
	gcc -c -o rastertomprinter.o `cups-config --cflags` -lcups rastertomprinter.c `cups-config --image --libs`

rastertomprinter: rastertomprinter.o
	gcc  -o rastertomprinter rastertomprinter.o `cups-config --image --libs`

install: rastertomprinter
	sudo cp rastertomprinter /usr/lib/cups/filter

clean:
	rm -f mprinter.ppd
	rm -f rastertomprinter.o
	rm -f rastertomprinter
