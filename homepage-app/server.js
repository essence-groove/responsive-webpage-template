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
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Tell Express to serve other static files (CSS, JS, images) from the 'public' directory.
// This should come after specific routes (like the '/' route above) so that
// specific routes are handled first.
app.use(express.static(path.join(__dirname, 'public')));

// A simple API endpoint to handle a form submission
app.post('/api/contact', (req, res) => {
    console.log('Form data received:', req.body);
    // In a real application, you would save this to a database
    res.json({ message: 'Thank you for your message!' });
});

// General Fallback Route
// This is a catch-all route. It ensures that if a user requests any path
// that isn't specifically handled by other routes (like '/api/contact' or '/'),
// your homepage's index.html is still served. This is crucial for single-page applications
// or to avoid "Cannot GET /path" errors for unhandled routes.
// This should be the VERY LAST route defined before app.listen().
app.get('*', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Start the server and have it listen on the specified port
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
