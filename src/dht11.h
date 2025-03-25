#ifndef SRC_DHT11_H_
#define SRC_DHT11_H_

void initDHT11(void);
void readDHT11(void);

struct DHT11Data
{
    float temperature;
    float humidity;
};
extern struct DHT11Data data;

#endif /* SRC_DHT11_H_ */