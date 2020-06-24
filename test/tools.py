from constants import * # pylint: disable=unused-wildcard-import
from hamcrest import * # pylint: disable=unused-wildcard-import
import psutil    


def is_server_running() -> bool:
    return SERVER_NAME in (p.name() for p in psutil.process_iter())