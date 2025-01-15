from __future__ import annotations

import pytest
from test_paths import APP_PATH

import quite


def test_launch_application():
    app = quite.Application(APP_PATH)
    assert app


def test_find_object():
    app = quite.Application(APP_PATH)
    with pytest.raises(RuntimeError):
        app.find_object("not-exiting-object")

    btn = app.find_object("helloBtn")
    assert btn
