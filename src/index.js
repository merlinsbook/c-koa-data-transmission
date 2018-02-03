/**
 * Playground - Data transmission between client c-program
 * and a koa server.
 * @author [David Tolbert](npm.merlin@gmail.com)
 * @see http://koajs.com/
 * @see http://graphql.org/learn/
 */

// Node Modules
import http from 'http';

// Server Application
import { app } from './server';

// Define the port.
const port = 3000;

// Create a server instance.
const server = http.createServer(app.callback())

// Start listening.
server.listen(port);

// Hot reload.
if (module.hot) {
  module.hot.accept('./server', () => {
    server.removeAllListeners('request', server);
    server.on('request', app.callback());
  });
}

// Log some info.
console.log(`Server running on: http://localhost:${port}`);
