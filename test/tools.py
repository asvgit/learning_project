from constants import * # pylint: disable=unused-wildcard-import
from hamcrest import * # pylint: disable=unused-wildcard-import
import psutil    
import pytest    
from socket import socket, AF_INET, SOCK_STREAM


def is_server_running() -> bool:
    return SERVER_NAME in (p.name() for p in psutil.process_iter())

def read(sock: socket) -> str:
    size = 0
    resp = ''
    sub_res = []
    while (size == 0):
        resp += sock.recv(1024).decode('utf-8')
        if ('\n' in resp):
            size = int(resp.split('\n')[0])
            if (resp[-1] == '\n'):
                resp = '\n'.join([i for i in resp.split('\n')[1:] if i]) + '\n'
            else:
                resp = '\n'.join([i for i in resp.split('\n')[1:] if i])
    while (len(sub_res) < size):
        chunk = sock.recv(1024).decode('utf-8')
        print(f'\n\ngot chunk {chunk}\n\n')
        resp += chunk
        print(f'\n\nnew resp \n{resp}\n\n')
        # resp += sock.recv(1024).decode('utf-8')
        if (resp[-1] == '\n'):
            for i in resp.split('\n'):
                sub_res.append(i)
            resp = ''
        else:
            for i in resp.split('\n')[:-1]:
                sub_res.append(i)
            resp = resp.split('\n')[-1]
    return '\n'.join([i for i in sub_res if i])

def write(sock: socket, msg: str):
    data = str(len(msg.split('\n'))) + '\n' + msg + '\n'
    sock.sendall(bytes(data, encoding='utf-8'))

def write_read(msg: str, expect_answ: str = '') -> str:
    assert_that(is_server_running(), 'server is not running')
    with socket(AF_INET, SOCK_STREAM) as sock:
        sock.connect((SERVER_HOST, SERVER_PORT))
        write(sock, msg)
        resp = read(sock)
        if (expect_answ):
            assert_that(resp, equal_to(expect_answ), 'wrong answer')
        return resp
