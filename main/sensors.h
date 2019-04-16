// Init Routines
void bme_init();
void mpu_init();
void uv_init();

// Data-collection Routines
char* bme_getTemperatureC();
int bme_getHumidity();
char* bme_getPressure();
char* bme_packageData();

int uv_getData();
char* uv_packageData();
