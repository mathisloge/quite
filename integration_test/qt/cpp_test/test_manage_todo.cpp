#include <boost/ut.hpp>
#include <quite/test/probe.hpp>
#include <quite/test/probe_manager.hpp>
#include <quite/value/object_query.hpp>
#include <test_application_path.hpp>

using namespace boost::ut;
using namespace std::literals::string_view_literals;
using namespace quite::test;

static suite<"integration manage todo"> _ = [] { // NOLINT
    bdd::gherkin::steps steps = [](auto &steps) {
        ProbeManager probe_manager;
        steps.feature("*") = [&] {
            auto probe = probe_manager.launch_probe_application("test_application", kTestApplicationPath);
            probe.wait_for_connected(std::chrono::seconds{5});
            steps.scenario("*") = [&] {
                steps.given("I have entered \"{todoText}\" into the todo input field") = [&](std::string todoText) {
                    steps.when("I click the \"Add\" button") = [&]() {
                        auto btn_query = std::make_shared<quite::ObjectQuery>();
                        btn_query->properties.emplace("objectName", "addButton");
                        auto btn_obj = probe.find_object(btn_query);
                        steps.then("the todo list should display \"{expectdTodoText}\" as a new item") =
                            [&](std::string todoText) {

                            };
                    };
                };
            };
        };
    };

    "manage todo"_test = steps |
                         R"(
      Feature: Managing todo items

  Scenario: Adding a new todo item to the list
    Given I have entered "Buy groceries" into the todo input field
    When I click the "Add" button
    Then the todo list should display "Buy groceries" as a new item

    )";
};
