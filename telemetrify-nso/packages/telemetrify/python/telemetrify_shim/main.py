import logging
import subprocess
import sys
import os
import multiprocessing
import threading

import ncs

log = logging.getLogger(__name__)


class RestartTelemetrify(ncs.dp.Action):
    def init(self, init_args):
        self.q = init_args[0]

    @ncs.dp.Action.action
    def cb_action(self, uinfo, name, kp, action_input, action_output, t_read):
        self.q.put(name)


class App(ncs.application.Application):
    def setup(self):
        self.log.info('telemetrify_shim SETUP')
        # We use a multiprocessing queue to communicate with the supervisor
        # thread because the supervisor thread may run in a separate process,
        # depending on the NSO configuration and the number of other application
        # components in this package.
        self.q = multiprocessing.Queue()
        self.sup = Supervisor(self, self.log, self.q)
        self.register_action('restart-telemetrify', RestartTelemetrify, init_args=(self.q, ))

        self.sup.start()

        # self.watchdog = Watchdog(self, self.log)
        # self.watchdog.start()

    def teardown(self):
        self.log.info('telemetrify_shim TEARDOWN')
        self.q.put('teardown')
        self.sup.join()


class Supervisor(threading.Thread):
    def __init__(self, app, log, q: multiprocessing.Queue):
        super().__init__()
        self.app = app
        self.log = log
        self.q = q

    def run(self) -> None:
        self.app.add_running_thread(self.name)
        self.telemetrify_start()

        while action := self.q.get():
            match action:
                case 'start':
                    self.telemetrify_start()
                case 'restart':
                    self.telemetrify_stop()
                    self.telemetrify_start()
                case 'stop':
                    self.telemetrify_stop()
                case 'teardown':
                    self.telemetrify_stop()
                    break
        self.app.del_running_thread(self.name)

    def telemetrify_start(self):
        bin_path = os.path.abspath(os.path.dirname(__file__) + "/../../bin/telemetrify.main.main")
        self.log.info("starting: " + bin_path)
        self.proc = subprocess.Popen(bin_path, stdout=sys.stdout, stderr=sys.stderr)

    def telemetrify_stop(self):
        self.log.info("stopping telemetrify")
        self.proc.terminate()

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
