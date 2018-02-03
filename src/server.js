/**
 * Data transmission server
 * @author [David Tolbert](npm.merlin@gmail.com)
 * @see http://koajs.com/
 * @see http://graphql.org/learn/
 */

 // Node Modules
import Koa from 'koa';
import KoaRouter from 'koa-router';
import koaBody from 'koa-bodyparser';
import compress from 'koa-compress';
import helmet from 'koa-helmet';
import cors from '@koa/cors';
import bodyParser from 'body-parser';

const SERVER_ID = 842516;

// Declarations
export const app = new Koa();
const router = new KoaRouter();

/**
 * Receiver
 * @param {*} ctx 
 * @param {*} next 
 */
function verifier(ctx, next) {

  if(!ctx.request.body.apiKey) {
    ctx.body = 500;
    ctx.throw(500, 'No API KEY found.');
  }

  if(!ctx.request.body.token) {
    ctx.body = 500;
    ctx.throw(500, 'No TOKEN found.');
  }

  // TODO: test
  //const privateRoute = Math.random().toString(36).substring(7);
  //router.post(`/cdf-hook/transmissions/${privateRoute}`, receiver);

  console.log('API KEY AND TOKEN ARE VALID');
  ctx.body = 'DEVICE IS AUTHORIZED\n';

  next();
}

/**
 * Receiver
 * @param {*} ctx 
 * @param {*} next 
 */
function receiver(ctx, next) {

  console.log(ctx.request.body.reading);
  ctx.body= `Message was transmitted to server with ID:${SERVER_ID}`;

  next();
}

// Middlewares
app.use(compress())
  .use(cors({
    origin: '*'
  }))
  .use(helmet())
  .use(koaBody())
  .use(router.routes())
  .use(router.allowedMethods());

// Routes
router.post('/test-hook/auth', verifier);
router.post('/test-hook/transmissions', receiver);
