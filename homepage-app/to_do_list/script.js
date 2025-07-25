/*
 * Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward) (https://github.com/apm-essence-groove/apm-essence-groove-ci-cd)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

document.addEventListener('DOMContentLoaded', () => {
    const todoInput = document.getElementById('todo-input');
    const addButton = document.getElementById('add-button');
    const todoList = document.getElementById('todo-list');

    // --- Helper Functions for Local Storage ---

    // Save tasks to localStorage
    function saveTasks() {
        const tasks = [];
        todoList.querySelectorAll('li').forEach(listItem => {
            tasks.push({
                text: listItem.querySelector('span').textContent,
                completed: listItem.classList.contains('completed')
            });
        });
        localStorage.setItem('todos', JSON.stringify(tasks));
    }

    // Load tasks from localStorage
    function loadTasks() {
        const tasks = JSON.parse(localStorage.getItem('todos') || '[]');
        tasks.forEach(task => {
            createTodoElement(task.text, task.completed);
        });
    }

    // --- Function to create a new To-Do List Item Element ---
    function createTodoElement(taskText, isCompleted = false) {
        const listItem = document.createElement('li');
        listItem.setAttribute('tabindex', '0'); // Make list item focusable for keyboard users

        if (isCompleted) {
            listItem.classList.add('completed');
        }

        listItem.innerHTML = `
            <span>${taskText}</span>
            <button aria-label="Delete task ${taskText}">Delete</button>
        `;

        todoList.appendChild(listItem);
    }

    // --- Event Handlers ---

    function addTodoItem() {
        const taskText = todoInput.value.trim();

        if (taskText === '') {
            alert('Please enter a task!');
            todoInput.focus();
            return;
        }

        createTodoElement(taskText); // Create the element
        saveTasks(); // Save after adding
        todoInput.value = ''; // Clear the input field
        todoInput.focus(); // Return focus to input for quick entry
    }

    // Event Delegation for clicking on list items or delete buttons
    todoList.addEventListener('click', (event) => {
        const target = event.target;

        // Check if the clicked element is a delete button
        if (target.tagName === 'BUTTON' && target.textContent === 'Delete') {
            target.closest('li').remove(); // Remove the parent <li> element
            saveTasks(); // Save after deleting
        }
        // Check if the clicked element is the span (task text) or the li itself (to toggle completion)
        else if (target.tagName === 'SPAN' || target.tagName === 'LI') {
            // If span is clicked, toggle class on its parent li
            const listItem = target.tagName === 'SPAN' ? target.parentElement : target;
            listItem.classList.toggle('completed');
            saveTasks(); // Save after toggling completion
        }
    });

    // Add task when Add button is clicked
    addButton.addEventListener('click', addTodoItem);

    // Add task when Enter key is pressed in the input field
    todoInput.addEventListener('keypress', (event) => {
        if (event.key === 'Enter') {
            addTodoItem();
            event.preventDefault();
        }
    });

    // --- Initial Load ---
    loadTasks(); // Load tasks when the page first loads
});
