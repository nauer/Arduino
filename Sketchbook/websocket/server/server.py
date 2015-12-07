#!/usr/bin/python3
#
# Websockets
# http://opensourceforu.efytimes.com/2012/04/getting-started-with-html5-websockets/
#

import tornado.web
import tornado.websocket
import tornado.ioloop
import serial


class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("../html/front.html")

class WebSocketHandler(tornado.websocket.WebSocketHandler):
    def open(self, *args):
        self.stream.set_nodelay(True)
        
        while 1:  # Wait forever for anything
          tdata = ser.readline()
          print(tdata)
          self.write_message(tdata)



#    def on_message(self, message):
#        self.write_message(u"Server echoed: " + message)

application = tornado.web.Application([
    (r"/", MainHandler),
    (r"/websocket", WebSocketHandler),
])


if __name__ == "__main__":
    # Create serial connection to Arduino
    ser = serial.Serial('/dev/ttyACM0', 19200)

    # check which port was really used
    print("Connected to: {}".format(ser.name))

    # Start reading on Arduino - send 1
    ser.write(bytearray("1",'ascii'))

    application.listen(5005)
    tornado.ioloop.IOLoop.instance().start()

    # Stop Arduino
    ser.write(bytearray("0",'ascii'))
    ser.close()
