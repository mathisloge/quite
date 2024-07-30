from __future__ import annotations

import time

import pytest

import quite


def test_launch_application():
    app = quite.Application("/home/mlogemann/dev/quite/build/test/simple_tester/tester")
    time.sleep(1)
    # btn = app.find_object("helloBtn")
    # btn.reset()

    app.exit()

    time.sleep(1)
    return
    with pytest.raises(RuntimeError):
        app.find_object("adsdadssad")
