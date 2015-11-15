# What is fugu? #

Fugu is a C ++ template for web applications

The system consists of the following modules:
  * [nginx](http://nginx.org) - back-end web server. It has gives static content from the clients. Nginx also forwards  dynamic requests to the another aplications likes that engine(fugiservice)
  * fuguservice is the heart of the project. It handles requests from users, provides access to the database, etc.
  * 
  * mongo db - database.
  * javascript - client logic.
  * [redis](http://redis.io). He has not yet developed after porting on Ubuntu/

# What we use? #

Server side:
  * C([redis4nginx module](https://github.com/donhuanmatus/redis4nginx)), C++(fugu service), or FastCGI back-end, [Node.js](http://nodejs.org)
  * [boost(asio, threads, etc)](http://boost.org)
  * [http parser](https://github.com/ry/http-parser)
  * [mongo db](http://www.mongodb.org)

Client side:
  * HTML, javacript, css
  * [jquery](http://jquery.com)
  * [jquery ui](http://jqueryui.com)
  * [box2djs](http://box2d-js.sourceforge.net)