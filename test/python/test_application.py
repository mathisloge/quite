from __future__ import annotations

import pytest
from test_paths import APP_PATH

import quite


def test_launch_application():
    app = quite.Application(APP_PATH)
    assert app


def test_find_object():
    app = quite.Application(APP_PATH)
    invalid_object_query = quite.ObjectQueryBuilder().add_property(
        "objectName", "not-existing"
    )
    with pytest.raises(RuntimeError):
        app.find_object(invalid_object_query.query())

    button_query = quite.ObjectQueryBuilder().add_property("objectName", "helloBtn")
    btn = app.find_object(button_query.query())
    assert btn

    text_query = quite.ObjectQueryBuilder().add_property("text", "...")
    text = app.find_object(text_query.query())
    assert text
