// Init Routines
void bme_init(int cs);
void ds_init();
char* ds_getData();
char* ds_packageData();

// Data-collection Routines
char* bme_getTemperatureC();
int bme_getHumidity();
int bme_getPressure();
char* bme_packageData();
