/*
 *    This file is part of mPrinter CUPS Driver.
 *
 *    mPrinter CUPS driver is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    mPrinter CUPS Driver is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with mPrinter CUPS Driver.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *	  (c)2013 Stepan Badger Knakal 
 *	
 *	  http://jezevcinora.cz/mprinter_forum
 */

#include <stdio.h>

#include <cups/raster.h>


FILE *debug_file; 

int main (int argc, char **argv)
{
    int i;
    char c;

    int page = 0;
    int y;
    char *buffer;
    int rv;

    cups_raster_t *ras;
    cups_page_header2_t header;


    debug_file = fopen("/tmp/cups_mprinter.log","a+"); /*open log file for appending */
    if(debug_file==NULL)
        exit(-1);

//    fprintf(debug_file,"---start---\n");
    fflush(debug_file);
//    printf("---start---\n");
    /* open raster stream */
    ras = cupsRasterOpen(0, CUPS_RASTER_READ);
    rv=cupsRasterReadHeader2(ras, &header);
    fprintf(debug_file,"rv=%x\n",rv);
    fflush(debug_file);
    /* take page by page */
    while (rv)
    {
        int bytes_per_line=73;
        /* setup this page */
        page ++;
        fprintf(stderr, "PAGE: %d %d\n", page, header.NumCopies);
        fprintf(debug_file, "PAGE: %d copies %d\n", page, header.NumCopies);
        fflush(debug_file);
        fprintf(debug_file, " BytesPerLine %d\n", header.cupsBytesPerLine);
        fprintf(debug_file, " BitsPerColor %d\n", header.cupsBitsPerColor);
        fprintf(debug_file, " BitsPerPixel %d\n", header.cupsBitsPerPixel);
        fprintf(debug_file, " BytesPerLine %d\n", header.cupsBytesPerLine);
        fprintf(debug_file, " Width %d Height %d\n", header.cupsWidth, header.cupsHeight);
        fprintf(debug_file, " resolution %dx%d\n", header.HWResolution[0],header.HWResolution[1]);
        fflush(debug_file);

        /* allocate memory for 1 line */
        buffer = malloc(header.cupsBytesPerLine);

        printf("%c%c",0);
        /* read raster data */
        for (y = 0; y < header.cupsHeight; y ++)
        {
            if (cupsRasterReadPixels(ras, buffer, header.cupsBytesPerLine) == 0)
                break;


            /* write raster data to printer on stdout */
            fflush(debug_file);
        printf("%c%c",0,0);
            for( i = 0; i < bytes_per_line ; i++) {
                /*FIXME solve if the last byte is not used fully */
                if(i<header.cupsBytesPerLine){
                    printf("%c",buffer[i]);
                    fprintf(debug_file, "%02x ", (unsigned char)buffer[i]);
                }
                else{
                    printf("%c",0);
                    fprintf(debug_file, "%02x ", 0);
                }
            }
                    fprintf(debug_file, "\n", 0);
//            for( i = 0; i < header.cupsBytesPerLine ; i++) {
//                fprintf(debug_file, "%02x ", (unsigned char)buffer[i]);
//            }
//            fprintf(debug_file,"\n");

        //    for( i = 0; i < header.cupsBytesPerLine ; i++)
        //    {
        //        char c;
        //        c=buffer[i];
        //        fprintf(debug_file,"%c",(c>=' ' && c<='~')?c:'.');
       //     }

            fflush(debug_file);
        }

        /* finish this page */
        /* try to read next page */
        rv=cupsRasterReadHeader2(ras, &header);
        fprintf(debug_file,"rv=%x\n",rv);
        fflush(debug_file);
    }





    cupsRasterClose(ras);
    fprintf(debug_file,"---done---\n");
    fflush(debug_file);
    fclose(debug_file);
    return 0;
}


