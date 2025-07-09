import json
import os
import sys

def main():
    app_dirs_json = os.environ.get("APP_DIRS_JSON_FROM_FIND_APPS") 
    
    if not app_dirs_json:
        print("::error::APP_DIRS_DIRS_JSON_FROM_FIND_APPS environment variable is missing.", file=sys.stderr)
        sys.exit(1)

    try:
        app_dirs = json.loads(app_dirs_json)
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from env var: {app_dirs_json}", file=sys.stderr)
        sys.exit(1)

    apps_data = [] # List to hold dictionaries for each app

    # Read package.json for each app to get its data
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
                print(f"::warning::Skipping JSON entry for \'{app_folder_name}\' as \'deployedUrl\' is missing or empty in its package.json.", file=sys.stderr)
                continue
            
            # Add app data to the list
            apps_data.append({
                "name": app_folder_name,
                "url": app_url
            })

        except Exception as e:
            print(f"::error::Error processing {package_json_path}: {e}", file=sys.stderr)
            continue

    # Define the output file path within the 'homepage-app/apps' directory
    output_dir = os.path.join("homepage-app", "apps")
    output_file_path = os.path.join(output_dir, "apps.json")

    # Create the directory if it doesn't exist
    os.makedirs(output_dir, exist_ok=True)

    # Write the data to the JSON file
    try:
        with open(output_file_path, "w") as f:
            json.dump(apps_data, f, indent=2) # Use indent=2 for pretty-printing
        print(f"::notice::Successfully generated {output_file_path}")
    except Exception as e:
        print(f"::error::Failed to write {output_file_path}: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
