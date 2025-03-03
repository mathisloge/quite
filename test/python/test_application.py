from __future__ import annotations

import datetime

import pytest
from test_paths import APP_PATH

from quite import ApplicationManager, ObjectQueryBuilder


@pytest.fixture
def app_manager():
    return ApplicationManager()


@pytest.fixture
def hello_btn_query():
    query = ObjectQueryBuilder().add_property("objectName", "helloBtn")
    return query.query()


@pytest.fixture
def text_field_query():
    query = ObjectQueryBuilder().add_property("objectName", "textArea")
    return query.query()


def test_launch_application(app_manager: ApplicationManager):
    app = app_manager.create_host_application(path_to_application=APP_PATH)
    assert app
    app.wait_for_connected()

    app.exit()

    with pytest.raises(RuntimeError):
        app.wait_for_connected(timeout=datetime.timedelta(seconds=2))


def test_find_object(app_manager: ApplicationManager, hello_btn_query):
    app = app_manager.create_host_application(path_to_application=APP_PATH)
    invalid_object_query = ObjectQueryBuilder().add_property(
        "objectName", "not-existing"
    )
    with pytest.raises(RuntimeError):
        app.find_object(invalid_object_query.query())

    btn = app.find_object(hello_btn_query)
    assert btn

    text_query = ObjectQueryBuilder().add_property("text", "...")
    text = app.find_object(text_query.query())
    assert text


def test_property(app_manager: ApplicationManager, hello_btn_query, text_field_query):
    app = app_manager.create_host_application(path_to_application=APP_PATH)

    btn = app.find_object(hello_btn_query)
    text = app.find_object(text_field_query)

    text_prop = text.property("text")
    assert text_prop.value() == "..."

    assert isinstance(text_prop.value(), str)
    assert isinstance(text.property("width").value(), float)
    assert isinstance(text.property("visible").value(), bool)

    btn.mouse_action()
    assert text_prop.fetch() == "Hello"

    with pytest.raises(RuntimeError):
        text.property("non-existing-property")


def test_method_invoke(
    app_manager: ApplicationManager, hello_btn_query, text_field_query
):
    app = app_manager.create_host_application(path_to_application=APP_PATH)

    btn = app.find_object(hello_btn_query)
    text = app.find_object(text_field_query)

    btn.invoke(method="click()")
    assert text.property("text").fetch() == "Hello"


def test_take_snapshot(app_manager: ApplicationManager, hello_btn_query):
    app = app_manager.create_host_application(path_to_application=APP_PATH)
    btn = app.find_object(hello_btn_query)
    btn.take_snapshot()
