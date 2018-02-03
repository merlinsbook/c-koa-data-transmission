/**
 * Reading-Transmitter
 * @author [David Tolbert](npm.merlin@gmail.com)
 * @see https://curl.haxx.se/libcurl/c/
 * @todo refactor code
 */

#include "funcs.h"
#include <unistd.h>
unsigned int sleep(unsigned int seconds);

// ######################################
// SERVER RESPONSE 
size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream) {

// Get the received buffer
struct write_result *result = (struct write_result *)stream;

// Check buffer size
if(result->pos + size * nmemb >= BUFFER_SIZE - 1) {
  fprintf(stderr, "curl error: too small buffer\n");
  return 0;
}

// Copy buffer
memcpy(result->data + result->pos, ptr, size * nmemb);

// Advance the position
result->pos += size * nmemb;

return size * nmemb;
} 


// ######################################
// TRANSMITTER
int connect(CURL *curl, int verify) {

  // Allocate receive buffer.
  char *response = allocReceiveBuffer();

  struct write_result write_result = {
    .data = response,
    .pos = 0
  };

  // Set curl options
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_result);

  // Set some device properties
  setDeviceProperties("Titan-234", "1.3.5", 0);

  // Verify device
  if(verify) {
    verifyClient(curl, API_KEY); 
  } else {
    transmitReading(curl, DUMMY_READING);
  }
 
  // null terminate the string
  response[write_result.pos] = '\0';

  // Return status
  if(sizeof(response) > 0 && !(strstr(response, "Internal Server Error") != NULL)) {
    printf("\nSERVER MSG: %s\n\n", response);
    return 1;
  } else {
    printf("\nSERVER ERROR: %s\n\n", response);
    return 0;
  }
}

/**
 * MAIN
 */
int main(int argc, char **argv) {

  // Initialize curl handle.
  CURL *curl = curl_easy_init(); 

  int transmit = connect(curl, VERIFY);

  int timer = 40;  // Timer causes transmission to end after 4s. 

  // Transmit data.
  while(transmit) {
    sleep(1);
    connect(curl, TRANSMIT);
    timer--;
    if(timer == 0) break; // for testing. remove for continuous reading.
  }
  
  // Free memory
  //free(response);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  
}
