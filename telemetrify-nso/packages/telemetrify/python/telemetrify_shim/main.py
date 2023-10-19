import logging
import subprocess
import sys
import os
import selectors
import threading

import ncs

log = logging.getLogger(__name__)

# ---------------------------------------------
# COMPONENT THREAD THAT WILL BE STARTED BY NCS.
# ---------------------------------------------
class App(ncs.application.Application):
    def setup(self):
        self.log.info('telemetrify_shim SETUP')
        bin_path = os.path.abspath(os.path.dirname(__file__) + "/../../bin/telemetrify.main.main")
        self.log.info("starting: " + bin_path)
        self.proc = subprocess.Popen(bin_path, stdout=sys.stdout, stderr=sys.stderr)
        # self.watchdog = Watchdog(self, self.log)
        # self.watchdog.start()

    def teardown(self):
        self.proc.terminate()
        # self.watchdog.stop()
        self.log.info('telemetrify_shim TEARDOWN')

# class Watchdog(threading.Thread):
#     def __init__(self, app, log):
#         super().__init__(name=(str(self.__class__.__module__) + "." + str(self.__class__.__name__)))
#         self.app = app
#         self.log = log
#         self.pipe = os.pipe()

#     def run(self):
#         self.log.info(self.name + " STARTED")

#         self.app.add_running_thread(self.name)

#         try:
#             selector = selectors.DefaultSelector()
#             # selector.register(self.proc.stdout, selectors.EVENT_READ)
#             # selector.register(self.proc.stderr, selectors.EVENT_READ)
#             selector.register(self.pipe[0], selectors.EVENT_READ)

#             running = True
#             while running:
#                 for key, mask in selector.select():
#                     fd = key.fd
#                     # if fd == self.proc.stdout and mask & selectors.EVENT_READ != 0:
#                     #     ...
#                     # elif fd == self.proc.stdout and mask & selectors.EVENT_READ != 0:
#                     #     ...
#                     if fd == self.pipe[0] and mask & selectors.EVENT_READ != 0:
#                         running = False
#         finally:
#             # selector.unregister(self.proc.stdout)
#             # selector.unregister(self.proc.stderr)
#             os.close(self.pipe[0])
#             os.close(self.pipe[1])
#             self.app.del_running_thread(self.name)

#         self.log.info(self.name + " STOPPED")

#     def stop(self):
#         os.write(self.pipe[1], b'q')
