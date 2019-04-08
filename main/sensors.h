// Init Routines
void bme_init(int cs);
void ds_init();
void uv_init();

// Data-collection Routines
char* bme_getTemperatureC();
int bme_getHumidity();
int bme_getPressure();
char* bme_packageData();

char* ds_getData();
char* ds_packageData();

int uv_getData();
char* uv_packageData();
