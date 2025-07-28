from datetime import timedelta
from time import sleep
from pytest_bdd import scenario, given, when, then, parsers
import pytest
from quite import Probe, ProbeManager,make_query
import test_paths

@pytest.fixture
def application():
   """Test article."""
   return ProbeManager().launch_qt_probe_application(name="todo-app", path_to_application=test_paths.APP_PATH)

@scenario("manage_todo.feature", "Adding a new todo item to the list")
def test_add_todo():
    pass

@when(parsers.parse("I have entered '{todo_text}' into the todo input field"))
def enter_todo_text(application: Probe, todo_text: str):
    input_field = application.find_object(object_query=make_query().with_property("objectName", "inputField"))
    input_field.property("text").write(todo_text)

@when("I click the 'Add' button")
def click_add_button(application: Probe):
    button = application.find_object(object_query=make_query().with_property("objectName", "addButton"))
    button.mouse_action()

@then(parsers.parse("the todo list should display '{expected_todo_text}' as a new item"))
def verify_new_todo_exists(application: Probe, expected_todo_text: str):
    list_item = application.find_object(object_query=make_query().with_property("objectName", "listView"))
    new_item_index = list_item.property("count").value() - 1
    todo_list_item = application.try_find_object(object_query=make_query().with_property("index", new_item_index).with_type("SwipeDelegate"), timeout=timedelta(seconds=1))
    assert todo_list_item.property("text").value() == expected_todo_text
