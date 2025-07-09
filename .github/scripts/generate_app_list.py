import json
import os
import sys

def main():
    app_dirs_json = os.environ.get("APP_DIRS_JSON_FROM_FIND_APPS") 
    
    if not app_dirs_json:
        print("::error::APP_DIRS_JSON_FROM_FIND_APPS environment variable is missing.", file=sys.stderr)
        sys.exit(1)

    try:
        app_dirs = json.loads(app_dirs_json)
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from env var: {app_dirs_json}", file=sys.stderr)
        sys.exit(1)

    # Building content with literal newlines (\n)
    header = "# 🚀 Deployed Applications\n\n"
    intro_text = "This file lists the applications deployed from this repository to Heroku.\n\n"
    app_list_heading = "## App List\n\n"
    
    app_items = [] # Use a list to build individual app entries

    apps_updated_flag = False

    for app_dir in app_dirs:
        app_folder_name = os.path.basename(app_dir)
        package_json_path = os.path.join(app_dir, "package.json")
        
        if not os.path.exists(package_json_path):
            print(f"::warning::package.json not found for {app_folder_name} at {app_dir}. Skipping.", file=sys.stderr)
            continue

        try:
            with open(package_json_path, "r") as f:
                package_json_data = json.load(f)
            
            app_url = package_json_data.get("deployedUrl") 
            
            if not app_url: 
                print(f"::warning::Skipping apps.md entry for \'{app_folder_name}\' as \'deployedUrl\' is missing or empty in its package.json. Please add it.", file=sys.stderr)
                continue
            
            # Add an extra newline at the end of each list item for more spacing
            app_items.append(f"* **{app_folder_name}:** [{app_url}]({app_url})") # No trailing \n here yet
            apps_updated_flag = True

        except Exception as e:
            print(f"::error::Error processing {package_json_path}: {e}", file=sys.stderr)
            continue

    # Join the app items with double newlines for spacing
    app_list_content = "\n\n".join(app_items) + "\n\n" if app_items else "" # Add two newlines after last item

    # Concatenate all parts into the final content
    final_apps_md_content = header + intro_text + app_list_heading + app_list_content

    # --- CRITICAL FIX: Write to GITHUB_OUTPUT using native multi-line variable syntax ---
    # This involves setting a custom delimiter.
    # We'll print a special marker, then the content, then the marker again.
    # This tells GHA that the variable spans multiple lines.
    
    # Generate a unique delimiter
    delimiter = "EOF_APPS_MD" 
    
    # Write to $GITHUB_OUTPUT file using the multi-line format
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        output_file.write(f"apps_md_section_content<<{delimiter}\n")
        output_file.write(final_apps_md_content) # Write content with literal newlines
        output_file.write(f"{delimiter}\n")
        output_file.write(f"apps_md_updated_flag={str(apps_updated_flag).lower()}\n")

if __name__ == "__main__":
    main()
