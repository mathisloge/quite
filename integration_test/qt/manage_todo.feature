Feature: Managing todo items

  Scenario: Adding a new todo item to the list
    When I have entered 'Buy groceries' into the todo input field
    When I click the 'Add' button
    Then the todo list should display 'Buy groceries' as a new item
    When I have entered 'Buy groceries 2' into the todo input field
    When I click the 'Add' button
    Then the todo list should display 'Buy groceries 2' as a new item
