//##############################################################################
//    filename:        gpsNMEA.c
//##############################################################################
//    library for GPS Sensors using  NMEA sentences
//##############################################################################
//
//      Author:            	V.SchK
//      Company:        	HS-Ulm
//
//      Revision:           1.0
//      Date:               Feb. 2014
//     	Assembled using:
//
//   	todo	- add comments ;-)
//             	-
//
//##############################################################################

#include "gpsNMEA.h"

GPS_DATA_t gps;

void extract_gpsData(char *gpsBuffer, unsigned char sizeGpsBuffer)
{
    unsigned char iGpsDetail, i;

//------------------------------------------------------------------------$GPRMC
    if(gpsBuffer[4] == 'M') for (i = 0; i <= sizeGpsBuffer; i++) {
        while (gpsBuffer[++i] != ',') {;}   //$GPRMC
        iGpsDetail = 0;
        while (gpsBuffer[++i] != ',') {
            if (iGpsDetail < sizeof (gps.UTC)) {
                gps.UTC[iGpsDetail++] = gpsBuffer[i];
            }
        }
        iGpsDetail = 0;
        while (gpsBuffer[++i] != ',') {
            if (iGpsDetail < sizeof (gps.Status)) {
                gps.Status[iGpsDetail++] = gpsBuffer[i];
            }
        }
        iGpsDetail = 0;
        while (gpsBuffer[++i] != ',') {
            if (iGpsDetail < sizeof (gps.Latitude)) {
                gps.Latitude[iGpsDetail++] = gpsBuffer[i];
            }
        }
        iGpsDetail = 0;
        while (gpsBuffer[++i] != ',') {
            if (iGpsDetail < sizeof (gps.NS)) {
                gps.NS[iGpsDetail++] = gpsBuffer[i];
            }
        }
        iGpsDetail = 0;
        while (gpsBuffer[++i] != ',') {
            if (iGpsDetail < sizeof (gps.Longitude)) {
                gps.Longitude[iGpsDetail++] = gpsBuffer[i];
            }
        }
        iGpsDetail = 0;
        while (gpsBuffer[++i] != ',') {
            if (iGpsDetail < sizeof (gps.EW)) {
                gps.EW[iGpsDetail++] = gpsBuffer[i];
            }
        }
        iGpsDetail = 0;
        while (gpsBuffer[++i] != ',') {
            if (iGpsDetail < sizeof (gps.Date)) {
                gps.Date[iGpsDetail++] = gpsBuffer[i];
            }
        }
//        while (gpsBuffer[++i] != ',') {;}   // gps.MagVariation
//        while (gpsBuffer[++i] != ',') {;}   // gps.MagOrientation
        break;
    }//for(i= 0;i<= iGpsBuffer;i++){
//------------------------------------------------------------------------$GPGGA
    else if(gpsBuffer[4] == 'G') for (i = 0; i <= sizeGpsBuffer; i++) {
        while (gpsBuffer[++i] != ',') {;}   // $GPGGA
        while (gpsBuffer[++i] != ',') {;}   // gps.UTC
        while (gpsBuffer[++i] != ',') {;}   // gps.Latitude
        while (gpsBuffer[++i] != ',') {;}   // gps.NS
        while (gpsBuffer[++i] != ',') {;}   // gps.Longitude
        while (gpsBuffer[++i] != ',') {;}   // gps.EW
        iGpsDetail = 0;
        while (gpsBuffer[++i] != ',') {
            if (iGpsDetail < sizeof (gps.FixQuality)) {
                gps.FixQuality[iGpsDetail++] = gpsBuffer[i];
            }
        }
        iGpsDetail = 0;
        while (gpsBuffer[++i] != ',') {
            if (iGpsDetail < sizeof (gps.NrSatellites)) {
                gps.NrSatellites[iGpsDetail++] = gpsBuffer[i];
            }
        }
//        while (gpsBuffer[++i] != ',') {;}   // gps.HorDilution
//        while (gpsBuffer[++i] != ',') {;}   // gps.Altitude
//        while (gpsBuffer[++i] != ',') {;}   // M
//        while (gpsBuffer[++i] != ',') {;}   // gps.HeightGeoid
        //...
        break;
    }
//------------------------------------------------------------------------$GPGSA
    else if(gpsBuffer[4] == 'S') for (i = 0; i <= sizeGpsBuffer; i++) {
        break;
    }
//------------------------------------------------------------------------$GPGLL
    else if(gpsBuffer[4] == 'L') for (i = 0; i <= sizeGpsBuffer; i++) {
        break;
    }
//------------------------------------------------------------------------$GPVTG
    else if(gpsBuffer[4] == 'T') for (i = 0; i <= sizeGpsBuffer; i++) {
        break;
    }
//------------------------------------------------------------------------$GP???
    else if(gpsBuffer[0] == '$') for (i = 0; i <= sizeGpsBuffer; i++) {
        break;
    }
}
