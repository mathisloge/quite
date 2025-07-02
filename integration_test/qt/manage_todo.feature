Feature: Managing todo items
  As a user I want to manage my todo list.
  So that I can stay organized by adding, editing, and deleting tasks.

  Scenario: Adding a new todo item to the list
    Given I have entered "Buy groceries" into the todo input field
    When I click the "Add" button
    Then the todo list should display "Buy groceries" as a new item

  Scenario: Editing an existing todo item
    Given the todo list contains an item "Buy groceries"
    When I swipe to the "Edit" button of "Buy groceries"
    And I change the text to "Buy groceries and milk"
    When I click the "Add" button
    Then the todo list should display "Buy groceries and milk" instead of "Buy groceries"

  Scenario: Deleting a todo item
    Given the todo list contains an item "Buy groceries"
    When I click the "Delete" button next to "Buy groceries"
    Then "Buy groceries" should no longer appear in the todo list
