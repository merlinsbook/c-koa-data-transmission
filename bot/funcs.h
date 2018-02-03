/**
 * Reading-Transmitter
 * @author [David Tolbert](npm.merlin@gmail.com)
 * @see https://curl.haxx.se/libcurl/c/
 * @todo refactor code and add more functions
 */

#ifndef HEADER_FILE
#define HEADER_FILE

#include <curl/curl.h> 
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>
 
#define URL_AUTH "http://127.0.0.1:3000/test-hook/auth/"                  // Login route
#define URL_TRANSMISSION "http://127.0.0.1:3000/test-hook/transmissions/" // Transmission route
#define BUFFER_SIZE (256 * 1024)                                          // Receive buffer (256kB)
#define API_KEY "Ks9lkns5Lsskaa781satU8jsab8245s33"                       // API Key
#define SEPERATOR "&"                                                     // Parameter separator.

#define API_KEY_PREFIX "apiKey="
#define TOKEN_PREFIX "token="
#define READING_PREFIX "reading="

#define DUMMY_READING "12.75 mV"

#define VERIFY 1
#define TRANSMIT 0

// STRUCTURES

// Result of write callback. 
struct write_result {
  char *data;
  int pos;
};

// Device step specifications.
struct device_specs {
  int step;
  float tol1;
  float tol2;
};


// HELPER FUNCTIONS

/**
 * Allocate the receive buffer
 */
char * allocReceiveBuffer();

/**
 * Fake token generator
 */
char * gen_random(char *s, const int len);


// CLIENT FUNCTIONS

/**
 * Generate client token
 * @parame {const char *} api_key - API Key
 */
char * generateClientToken(const char *api_key);

/**
 * Connect device
 * @parame {const char *} api_key - API Key
 */
char * verifyClient(CURL *curl, const char *api_key);

/**
 * Transmit reading
 * @parame {const char *} reading - reading of measurement device
 */
char * transmitReading(CURL *curl, const char *reading);

/**
 * Set device properties.
 * @parame {const char *} name - Device name
 * @device_name {const char *} version - Device version
 * @device_name {int} mtype - Type of measurement
 */
int setDeviceProperties(const char *name, const char *version, int mtype);


#endif