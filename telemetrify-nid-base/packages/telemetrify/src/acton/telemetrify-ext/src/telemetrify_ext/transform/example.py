# Copyright (C) Deutsche Telekom AG
#
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

import logging

from telemetrify.common.mod import *
from telemetrify.common.utils import *
from telemetrify.main.common import *
from telemetrify.main.resource.shared_resources import *
from telemetrify.main.transform.common import *
from telemetrify.main.transform.ctor import *

YANG_NAME = 'example'

TAG = PTag('tlme', YANG_NAME)

class ExampleTransformCtor(TransformCtor):
    def __init__(self):
        pass

    def create(self, uid: int, config: TNode, shared_resources: SharedResources, on_closed: action() -> None, log_handler: logging.Handler) -> Transform:
        transform_act = ExampleTransform(uid, config, on_closed, log_handler)
        return Transform(uid, transform_act.attach, transform_act.detach, transform_act.close, transform_act.write, transform_act.update_output)

actor ExampleTransform(
        uid: int,
        config: TNode,
        on_closed: action() -> None,
        log_handler: ?logging.Handler):

    var logh = logging.Handler(YANG_NAME + "-transform")
    if log_handler is not None:
        logh.set_handler(log_handler)
    var log = logging.Logger(logh)

    # Workaround compiler ordering issue
    # var transform_base = TransformMixin(uid, output_upstream_msg_trampoline, _on_closed, log)
    var transform_base = TransformMixin(uid, lambda m: None, lambda: None, log)

    log.info("TRANSFORM " + YANG_NAME + " CREATED", {"uid": uid})

    def attach(client_uid: int, msg_cb: action(Message) -> None):
        transform_base.attach(client_uid, msg_cb)

    def detach(client_uid: int):
        transform_base.detach(client_uid)

    def update_output(update: list[(Keypath, ?OutputUpdate)]) -> None:
        transform_base.update_output(update)

    def write(sender_uid: int, node: Node, flow_params: TNode) -> None:

        # TODO: Create output data
        output_node = node

        transform_base.write(sender_uid, output_node, flow_params)

    def close():
        transform_base.close()

    def output_upstream_msg_trampoline(msg: Message) -> None:
        transform_base.on_output_upstream_msg(msg)

    def _on_closed():
        log.debug("TRANSFORM " + YANG_NAME + " CLOSED", {"uid": uid})
        on_closed()

    # Workaround compiler ordering issue
    transform_base.output_mixin.output_upstream_msg_trampoline = output_upstream_msg_trampoline
    transform_base.on_closed = _on_closed
