import os
import multiprocessing
import logging
import json

proc = _in_queue = _out_queue = None

def _send_msg(action, **kwargs):
    msg = {"action": action}
    msg.update(kwargs)
    _in_queue.put(json.dumps(msg))

def start():
    global _in_queue, _out_queue, proc
    _in_queue = multiprocessing.Queue()
    _out_queue = multiprocessing.Queue()
    proc = multiprocessing.Process(target=_some_process, args=(_in_queue, _out_queue))
    proc.start()
    return proc.is_alive() and proc.pid

def stop():
    _send_msg("quit")
    proc.join()
    return proc.exitcode

def sample_command(param1, param2):
    _send_msg("sample_command", param1=param1, param2=param2)

def _some_process(in_q, out_q):
    logger = logging.getLogger()
    logger.addHandler(logging.FileHandler(os.path.join(os.path.dirname(__file__), "app.log")))
    logger.setLevel(logging.INFO)
    logger.info("=====Initialized logger=====")

    while True:
        msg = json.loads(in_q.get())
        logger.info("message %s", msg)
        assert 'action' in msg
        action = msg.pop('action')
        if action == "quit":
            break
        elif action == "sample_command":
            logger.info("Special message test received: param1: %s and 2: %s",
                        msg['param1'], msg['param2'])
        else:
            logger.info("Unknown message type %s", action)
    logger.info("-- terminating --")


if __name__ == '__main__':
    start()
    _send_msg("heelo", a=5)
    _send_msg("quit")
    proc.join()
