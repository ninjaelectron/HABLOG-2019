
void gps_init();
boolean gps_readWrapper();

char* gps_getLatLong();
char* gps_getTime();
char* gps_getFlightParameters();
char* gps_getMiscData();
int gps_getSeconds();

boolean gps_getFix();
