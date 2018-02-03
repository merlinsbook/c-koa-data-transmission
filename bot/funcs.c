/**
 * Reading-Transmitter
 * @author [David Tolbert](npm.merlin@gmail.com)
 * @see https://curl.haxx.se/libcurl/c/
 * @todo refactor code and add more functions
 */

#include "funcs.h"

const char *privateRoute = "";

// Allocate the receive buffer.
char * allocReceiveBuffer() {

  char *receiveBuffer;

  receiveBuffer = (char *) malloc(BUFFER_SIZE);

  if (! receiveBuffer) {
    return 0;
    //fprintf(stderr, "Error allocating %d bytes.\n", BUFFER_SIZE);
  }
  
  return receiveBuffer;
}

// Fake token generator
char * gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

  return s;
}

  
// CLIENT FUNCTIONS

// Generate client token
char * generateClientToken(const char *api_key) {
  // TODO: do some encryption here.
  char s[31];
  
  char *token = gen_random(s, 30);

  printf("\nCLIENT MSG: api_key: %s\n", api_key);
  printf("CLIENT MSG: token: %s\n", token);
  
  return token;
}

// Connect device
char * verifyClient(CURL *curl, const char *api_key) {
    
  char *token = generateClientToken(api_key);

  char *credentials = (char *) malloc(1 + strlen(API_KEY_PREFIX) + strlen(api_key) + strlen(SEPERATOR) + strlen(TOKEN_PREFIX) + strlen(token) );
  strcpy(credentials, API_KEY_PREFIX);
  strcat(credentials, API_KEY);
  strcat(credentials, SEPERATOR);
  strcat(credentials, TOKEN_PREFIX);
  strcat(credentials, token);

  printf("CLIENT MSG: credentials: %s\n", credentials);

  curl_easy_setopt(curl, CURLOPT_URL, URL_AUTH);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, credentials);
  curl_easy_perform(curl);
}

// Set device properties.
int setDeviceProperties(const char *name, const char *version, int mtype) {
  printf("\nInitializing transmission...\n");
  printf("Target: %s\n", name);
}

// Transmit reading
char * transmitReading(CURL *curl, const char *reading) {

  char *data = (char *) malloc(1 + strlen(READING_PREFIX) + strlen(reading));
  strcpy(data, READING_PREFIX);
  strcat(data, reading);

  printf("CLIENT MSG: reading: %s\n", data);


  curl_easy_setopt(curl, CURLOPT_URL, URL_TRANSMISSION);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
  curl_easy_perform(curl);
}
