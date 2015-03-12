#!/usr/bin/env python2

import nanomsg2

print(dir(nanomsg2))
sock = nanomsg2.Socket(nanomsg2.AF_SP, nanomsg2.NN_PULL)
print sock
print dir(sock)
