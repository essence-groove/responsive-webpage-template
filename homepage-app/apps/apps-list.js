document.addEventListener('DOMContentLoaded', () => {
    const appsJsonPath = 'apps.json'; // apps.json is in the same directory

    // Function to safely fetch and parse JSON
    async function fetchAppsData() {
        try {
            const response = await fetch(appsJsonPath);

            // Check if the response was successful (e.g., status 200-299)
            if (!response.ok) {
                // Log the network error internally but produce no output to the user
                console.error(`Error fetching ${appsJsonPath}: ${response.status} ${response.statusText}`);
                return null; // Return null on network or HTTP error
            }

            const data = await response.json(); // Parse the JSON data

            // Basic validation: ensure data is an array
            if (!Array.isArray(data)) {
                console.error(`Error: ${appsJsonPath} does not contain a valid JSON array.`, data);
                return null; // Return null if data is not an array
            }

            return data; // Return the parsed array
        } catch (error) {
            // Catch any other errors (e.g., network issues, malformed JSON)
            console.error(`An unexpected error occurred while processing ${appsJsonPath}:`, error);
            return null; // Return null on any exception
        }
    }

    // Function to generate and append the app list
    async function displayAppLinks() {
        const apps = await fetchAppsData(); // Attempt to fetch data

        if (apps && apps.length > 0) { // Only proceed if data is valid and not empty
            const articleElement = document.createElement('article');
            articleElement.id = 'app-links-container'; // Optional: add an ID for styling/selection

            apps.forEach(app => {
                // Basic validation for each app object
                if (app && typeof app === 'object' && app.name && app.url) {
                    const paragraph = document.createElement('p');
                    const link = document.createElement('a');
                    link.href = app.url;
                    link.textContent = app.name;
                    link.target = '_blank'; // Open link in a new tab
                    link.rel = 'noopener noreferrer'; // Security best practice for target='_blank'

                    paragraph.appendChild(link);
                    articleElement.appendChild(paragraph);
                } else {
                    console.warn('Skipping malformed app entry:', app);
                }
            });

            // Append the article element to the body or a specific container
            // For a robust solution, you might want a specific element on your HTML page
            // to append to, e.g., document.getElementById('main-content').appendChild(articleElement);
            document.body.appendChild(articleElement);
        }
        // If apps is null or empty, no output is done, fulfilling the requirement.
    }

    displayAppLinks(); // Call the function to display links when the DOM is loaded
});
