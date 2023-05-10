
import web             #web.py framework
import gateway_front   #python adapter to c++

#url pattern for web.py to call get_latest.GET beneath
urls = (
    '/.*', 'get_latest',
)

class get_latest:
    def GET(self):
        args = web.input()
        print(args)
        #some browsers don't like plain text, so I use html
        web.header( 'Content-type', 'text/xml' )
        g = gateway_front.Gate() # get gateway to c++
        s = g.get_latest(args.fid)            # get latest' content
        return str(s)            # return it as a HTTP response

#sets web.py's func as WSGI entry point
application = web.application(urls, globals()).wsgifunc()

# to test from console
def main():

    g = gateway_front.Gate()
    s = g.getDefaultQuote()
    print(s)

if __name__ == '__main__':
    # main()
    application.run()
