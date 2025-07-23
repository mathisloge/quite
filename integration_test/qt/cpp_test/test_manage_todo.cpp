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
                steps.given("I have entered '{todoText}' into the todo input field") = [&](std::string todoText) {
                    auto input_obj =
                        probe.find_object(quite::make_query().with_property("objectName", std::string{"inputField"}));
                    input_obj.property("text").write(std::move(todoText));

                    steps.when("I click the 'Add' button") = [&]() {
                        auto btn_query = quite::make_query().with_property("objectName", std::string{"addButton"});
                        auto btn_obj = probe.find_object(btn_query);
                        btn_obj.mouse_action();
                        steps.then("the todo list should display '{expectdTodoText}' as a new item") =
                            [&](std::string todoText) {
                                auto list_query =
                                    quite::make_query().with_property("objectName", std::string{"listView"});
                                auto list_obj = probe.find_object(list_query);

                                auto delegate_query = quite::make_query().with_property("text", todoText);
                                // delegate_query->container = list_query;
                                auto delegate_index =
                                    probe.try_find_object(delegate_query, std::chrono::seconds{2}).property("index");
                                expect(std::holds_alternative<std::uint64_t>(delegate_index.value()));
                                expect(that % 0 == std::get<std::uint64_t>(delegate_index.value()));
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
    Given I have entered 'Buy groceries' into the todo input field
    When I click the 'Add' button
    Then the todo list should display 'Buy groceries' as a new item

    )";
};
