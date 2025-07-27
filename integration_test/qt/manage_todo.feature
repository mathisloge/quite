# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT
Feature: Managing todo items

  Scenario: Adding a new todo item to the list
    Given I have entered 'Buy groceries' into the todo input field
    When I click the 'Add' button
    Then the todo list should display 'Buy groceries' as a new item
    Given I have entered 'Buy groceries 2' into the todo input field
    When I click the 'Add' button
    Then the todo list should display 'Buy groceries 2' as a new item
