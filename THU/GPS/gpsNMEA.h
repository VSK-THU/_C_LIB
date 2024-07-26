//*******************************************************************
//
//  File:   gpsNMEA.h
//  Author: VSK
//
//  Created on 25. Feb 2014
//
//*******************************************************************
// https://www.gpsinformation.org/dale/nmea.htm

#ifndef GPS_NMEA_H
#define GPS_NMEA_H

#define START_OF_GPSSTR     '$'
#define END_OF_GPSSTR       0x0A     // LF
#define MAX_BUFFER_LENGTH   100

typedef struct{
    char UTC[6];
    char Status[1];         // RMC only
    char Latitude[10];
    char NS[1];
    char Longitude[11];
    char EW[1];
    char Speed[5];          // RMC only
    char TrackAngle[5];     // RMC only
    char Date[6];           // RMC only
    char MagVariation[4];   // RMC only
    char MagOrientation[1]; // RMC only
    char FixQuality[1];     // GGA only
    char NrSatellites[2];   // GGA only
    char HorDilution[3];    // GGA only
    char Altitude[5];       // GGA only
    char HeightGeoid[4];    // GGA only
}GPS_DATA_t;

extern GPS_DATA_t gps;      // in gpsNMEA.c
extern void extract_gpsData(char *gpsBuffer, unsigned char sizeGpsBuffer);

#endif	/* GPS_NMEA_H */

/*
--------------------------------------------------------------------------------
The most important NMEA sentences include the GGA which provides
the current Fix data, the RMC which provides the minimum gps sentences
information, and the GSA which provides the Satellite status data.
--------------------------------------------------------------------------------

GGA - essential fix data which provide 3D location and accuracy data.

	$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
Albert-Einstein-Allee T305 ->
$GPGGA,122533,4825.1123,N,00956.2946,E,1,07,02.8,00619.6,M,040.9,M,,*47<\r><\n>

Where:
     GGA          Global Positioning System Fix Data
     123519       Fix taken at 12:35:19 UTC
     4807.038,N   Latitude 48 deg 07.038' N
     01131.000,E  Longitude 11 deg 31.000' E
     1            Fix quality: 0 = invalid
					1 = GPS fix (SPS)
					2 = DGPS fix
					3 = PPS fix
					4 = Real Time Kinematic
					5 = Float RTK
					6 = estimated (dead reckoning) (2.3 feature)
					7 = Manual input mode
					8 = Simulation mode
     08           Number of satellites being tracked
     0.9          Horizontal dilution of position
     545.4,M      Altitude, Meters, above mean sea level
     46.9,M       Height of geoid (mean sea level) above WGS84 ellipsoid
     (empty field) time in seconds since last DGPS update
     (empty field) DGPS station ID number
     *47          the checksum data, always begins with *

If the height of geoid is missing then the altitude should be suspect.
Some non-standard implementations report altitude with respect to the ellipsoid
rather than geoid altitude.
Some units do not report negative altitudes at all.
This is the only sentence that reports altitude.
--------------------------------------------------------------------------------

RMC - NMEA has its own version of essential gps pvt (position, velocity, time)
data. It is called RMC, The Recommended Minimum, which will look similar to:

	$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A
Albert-Einstein-Allee T305 ->
$GPRMC,122532,A,4825.1123,N,00956.2946,E,000.0,000.0,240214,,,A*7D<\r><\n>

Where:
     RMC          Recommended Minimum sentence C
     123519       Fix taken at 12:35:19 UTC
     A            Status A=active or V=Void.
     4807.038,N   Latitude 48 deg 07.038' N
     01131.000,E  Longitude 11 deg 31.000' E
     022.4        Speed over the ground in knots
     084.4        Track angle in degrees True
     230394       Date - 23rd of March 1994
     003.1,W      Magnetic Variation
     *6A          The checksum data, always begins with *
*/
