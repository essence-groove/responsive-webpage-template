// Import the Express library
const express = require('express');
const path = require('path');

// Create an instance of an Express application
const app = express();
const port = 3000;

// Tell Express to serve the static files (HTML, CSS, JS) from the 'public' directory
app.use(express.static(path.join(__dirname, 'public')));

// Middleware to parse incoming JSON data (like from a form)
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// A simple API endpoint to handle a form submission
app.post('/api/contact', (req, res) => {
    console.log('Form data received:', req.body);
    // In a real application, you would save this to a database
    res.json({ message: 'Thank you for your message!' });
});

// Start the server and have it listen on the specified port
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
