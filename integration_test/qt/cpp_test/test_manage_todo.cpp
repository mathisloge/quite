// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <fstream>
#include <print>
#include <boost/ut.hpp>
#include <bdd_features.hpp>
#include <quite/test/probe.hpp>
#include <quite/test/probe_manager.hpp>
#include <quite/value/object_query.hpp>
#include <test_application_path.hpp>

#include <quite/client/remote_object.hpp>
#include <quite/meta_any_formatter.hpp>

using namespace boost::ut;
using namespace std::literals::string_view_literals;
using namespace quite::test;

template <class... Ts>
struct overloads : Ts...
{
    using Ts::operator()...;
};

static suite<"integration manage todo"> _ = [] { // NOLINT
    bdd::gherkin::steps steps = [](auto &steps) {
        ProbeManager probe_manager;
        steps.feature("*") = [&] {
            auto probe = probe_manager.launch_probe_application("test_application", kTestApplicationPath);
            probe.wait_for_connected(std::chrono::seconds{5});
            steps.scenario("*") = [&] {};
            steps.when("I have entered '{todoText}' into the todo input field") = [&](std::string todoText) {
                auto input_obj =
                    probe.find_object(quite::make_query().with_property("objectName", std::string{"inputField"}));
                input_obj.property("text").write(std::move(todoText));
            };
            steps.when("I click the 'Add' button") = [&]() {
                auto btn_query = quite::make_query().with_property("objectName", std::string{"addButton"});
                auto btn_obj = probe.find_object(btn_query);
                btn_obj.mouse_action();
            };

            steps.then("the todo list should display '{expectedTodoText}' as a new item") = [&](std::string todoText) {
                auto delegate_query = quite::make_query().with_property("text", todoText).with_type("SwipeDelegate");
                auto delegate_text = probe.try_find_object(delegate_query, std::chrono::seconds{2}).property("text");
                expect(std::holds_alternative<std::string>(delegate_text.value()));
                expect(that % todoText == std::get<std::string>(delegate_text.value()));
            };
        };
    };

    for (auto &&feature : kFeatures)
    {
        std::ifstream feature_file_stream(std::filesystem::path{kFeatureRoot} / feature, std::ios::binary);

        std::string feature_content((std::istreambuf_iterator<char>(feature_file_stream)),
                                    (std::istreambuf_iterator<char>()));

        test(feature) = steps | feature_content;
    }
};
