from socket import socket, AF_INET, SOCK_STREAM
from tools import * # pylint: disable=unused-wildcard-import


def test_ping_server():
    assert_that(is_server_running(), 'server is not running')
    with socket(AF_INET, SOCK_STREAM) as sock:
        sock.connect((SERVER_HOST, SERVER_PORT))
        sock.sendall(b'ping!')
        resp = sock.recv(5)
        assert_that(resp, equal_to(b'pong!'), 'wrong answer')
    assert_that(not is_server_running(), 'server is still running')
