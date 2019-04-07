// Init Routines
void bme_init(int cs);
void ds_init();

// Data-collection Routines
int bme_getTemperatureC();
int bme_getHumidity();
int bme_getPressure();
