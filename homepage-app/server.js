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

// Import the Express library
const express = require('express');
const path = require('path');

// Create an instance of an Express application
const app = express();
const port = process.env.PORT || 3000;

// Middleware to parse incoming JSON data (like from a form)
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Serve the homepage's index.html for the root URL (/)
app.get('/', (req, res) => {
    // Now directly serve index.html from the current directory (homepage-app/)
    res.sendFile(path.join(__dirname, 'index.html'));
});

// Tell Express to serve other static files (CSS, JS, images) from the current directory.
// This means files like homepage-app/style.css will be served as /style.css
// It must be placed after specific routes like app.get('/') to ensure specific routes are handled first.
app.use(express.static(__dirname)); // <-- Corrected: Now refers directly to homepage-app/

// A simple API endpoint to handle a form submission
app.post('/api/contact', (req, res) => {
    console.log('Form data received:', req.body);
    res.json({ message: 'Thank you for your message!' });
});

// General Fallback Route
// This is a catch-all route. It ensures that if a user requests any path
// that isn't specifically handled by other routes (like '/api/contact' or '/'),
// your homepage's index.html is still served.
// This should be the VERY LAST route defined before app.listen().
app.get('*', (req, res) => {
    // Now directly serve index.html from the current directory (homepage-app/)
    res.sendFile(path.join(__dirname, 'index.html'));
});

// Start the server and have it listen on the specified port
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
