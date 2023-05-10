import sys
# .so object, written in C++ with Boost.Python
import gateway_back


class Gate:
    _instance = None

    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            cls._instance = super(Gate, cls).__new__(cls, *args, **kwargs)
        return cls._instance

    def get_latest(self, feed_id):
        """take get_latest from c++ backend"""
        return gateway_back.get_latest(feed_id)


def main():
    """to test from console"""
    g = Gate()
    s = g.get_latest("test")
    print(s)

if __name__ == '__main__':
    main()