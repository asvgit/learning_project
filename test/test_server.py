from os import path
from subprocess import Popen
from tools import * # pylint: disable=unused-wildcard-import
from threading import Thread


def test_ping_server():
    write_read('ping', 'pong')
    assert_that(is_server_running(), 'server is not running')

def test_multiping_server():
    for _ in range(5):
        write_read('ping', 'pong')
    assert_that(is_server_running(), 'server is not running')

# @pytest.mark.skip(reason='Unnecessary now')
def test_restart_server():
    write_read('shutdown_now', 'ok')
    assert_that(not is_server_running(), 'server is still running')
    Popen(path.join(BIN_PATH, SERVER_NAME))
    assert_that(is_server_running(), 'server is not running')

def test_echo():
    write_read('no_ping', 'no_ping')
    assert_that(is_server_running(), 'server is not running')

def test_echo_multiline():
    msg = '\n'.join(['no_ping', 'no_ping'])
    write_read(msg, msg)
    assert_that(is_server_running(), 'server is not running')

def test_echo_matrix_msg():
    n = 100
    msg = '\n'.join([''.join([str(i) for _ in range(n)]) for i in range(n)])
    resp = write_read(msg)
    msgs = msg.split('\n')
    resps = resp.split('\n')
    assert_that(len(resps), equal_to(len(msgs)))
    for i in range(n):
        assert_that(resps[i], equal_to(msgs[i]))
    assert_that(is_server_running(), 'server is not running')

class PropagatingThread(Thread):
    def run(self):
        self.exc = None
        try:
            self.ret = self._target(*self._args, **self._kwargs)
        except BaseException as e:
            self.exc = e

    def join(self):
        super(PropagatingThread, self).join()
        if self.exc:
            raise self.exc
        return self.ret

def test_thread():
    def f():
        write_read('ping', 'pong')
        # print(args)
        # print(kwargs)
        # raise Exception('I suck')

    for _ in range(1000):
        n = 8
        workers = [PropagatingThread(target=f) for _ in range(n)]
        for w in workers:
            w.start()
        for w in workers:
            w.join()