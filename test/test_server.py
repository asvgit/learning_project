from os import path
from subprocess import Popen
from tools import * # pylint: disable=unused-wildcard-import


def test_ping_server():
    write_read('ping', 'pong')
    assert_that(is_server_running(), 'server is not running')

def test_multiping_server():
    for _ in range(5):
        write_read('ping', 'pong')
    assert_that(is_server_running(), 'server is not running')

@pytest.mark.skip(reason='Unnecessary now')
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

@pytest.mark.skip(reason='Skip benchmarks')
def test_benchmark_echo(benchmark):
    benchmark(write_read, 'no_ping', 'no_ping')
    assert_that(is_server_running(), 'server is not running')

@pytest.mark.skip(reason='Skip benchmarks')
def test_benchmark_echo_matrix_msg(benchmark):
    n = 100
    msg = '\n'.join([''.join([str(i) for _ in range(n)]) for i in range(n)])
    benchmark(write_read, msg)
