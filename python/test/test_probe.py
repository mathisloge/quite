# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

from __future__ import annotations

import datetime

import pytest
from test_paths import APP_PATH

from quite import ProbeManager, expect, make_query


@pytest.fixture
def probe_manager():
    return ProbeManager()


@pytest.fixture
def hello_btn_query():
    return make_query().with_property("objectName", "helloBtn")


@pytest.fixture
def text_field_query():
    return make_query().with_property("objectName", "textArea")


def test_launch_application(probe_manager: ProbeManager):
    app = probe_manager.launch_qt_probe_application(
        name="tester", path_to_application=APP_PATH
    )
    assert app
    app.wait_for_connected(timeout=datetime.timedelta(seconds=30))

    app.exit()

    with pytest.raises(RuntimeError):
        app.wait_for_connected(timeout=datetime.timedelta(seconds=2))


def test_find_object(probe_manager: ProbeManager, hello_btn_query):
    app = probe_manager.launch_qt_probe_application(
        name="tester", path_to_application=APP_PATH
    )
    invalid_object_query = make_query().with_property("objectName", "not-existing")
    with pytest.raises(RuntimeError):
        app.find_object(invalid_object_query)

    btn = app.find_object(hello_btn_query)
    assert btn

    text_query = make_query().with_property("text", "...")
    text = app.find_object(text_query)
    assert text


def test_property(probe_manager: ProbeManager, hello_btn_query, text_field_query):
    app = probe_manager.launch_qt_probe_application(
        name="tester", path_to_application=APP_PATH
    )

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


def test_method_invoke(probe_manager: ProbeManager, hello_btn_query, text_field_query):
    app = probe_manager.launch_qt_probe_application(
        name="tester", path_to_application=APP_PATH
    )

    btn = app.find_object(hello_btn_query)
    text = app.find_object(text_field_query)

    btn.invoke(method="clicked()")
    assert text.property("text").fetch() == "Hello"


def test_take_snapshot(probe_manager: ProbeManager, hello_btn_query):
    app = probe_manager.launch_qt_probe_application(
        name="tester", path_to_application=APP_PATH
    )
    btn = app.find_object(hello_btn_query)
    btn.take_snapshot()


def test_expect_screenshot(probe_manager: ProbeManager, hello_btn_query):
    app = probe_manager.launch_qt_probe_application(
        name="tester", path_to_application=APP_PATH
    )
    btn = app.find_object(hello_btn_query)
    expect(object=btn).screenshot(name="test1")
